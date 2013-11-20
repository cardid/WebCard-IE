/**********************************************************\

  Auto-generated WebCardAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "DOM/Window.h"
#include "global/config.h"

#include "WebCardAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn WebCardPtr WebCardAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
WebCardPtr WebCardAPI::getPlugin()
{
    WebCardPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property Readers
FB::JSObjectPtr WebCardAPI::get_readers()
{
	return m_readers;
}

// Read-only property version
std::string WebCardAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void WebCardAPI::listen(const FB::variant& readers)
{

}

void WebCardAPI::InitializeReaders()
{
	LONG    lRet = 0;
	LPTSTR  pReader;
	DWORD   cch = 0;

	m_readers = m_host->getDOMWindow()->createArray();

	m_rgReaderStates = NULL;
	m_pmszReaders = NULL;
	m_cReaders = 0;
	lRet = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &m_hContext);
#ifdef SCARD_AUTOALLOCATE
	cch = SCARD_AUTOALLOCATE;
	lRet = SCardListReaders(m_hContext, NULL, (LPTSTR)&m_pmszReaders, &cch);
#else
	lRet = SCardListReaders(m_hContext, NULL, NULL, &cch);
	m_pmszReaders = (LPTSTR)calloc(cch, sizeof(char));
	lRet = SCardListReaders(m_hContext, NULL, m_pmszReaders, &cch);
#endif
	switch (lRet)
	{
	case SCARD_E_NO_READERS_AVAILABLE:
		break;

	case SCARD_S_SUCCESS:
		pReader = m_pmszReaders;
		while ('\0' != *pReader)
		{
#ifdef _WINDOWS
			m_rgReaderStates = (LPSCARD_READERSTATE)realloc((LPVOID)m_rgReaderStates, (m_cReaders + 1) * sizeof(SCARD_READERSTATE));
#else
			m_rgReaderStates = (LPSCARD_READERSTATE_A)realloc((LPVOID)m_rgReaderStates, (m_cReaders + 1) * sizeof(SCARD_READERSTATE_A));
#endif
			m_rgReaderStates[m_cReaders].szReader = pReader;
			m_rgReaderStates[m_cReaders].dwCurrentState = SCARD_STATE_UNAWARE;
			// Create the object.
#ifdef _WINDOWS
			ReaderPtr newReader = boost::make_shared<Reader>(m_host, m_hContext, std::wstring(pReader));
#else
			ReaderPtr newReader = boost::make_shared<Reader>(m_host, m_hContext, std::string(pReader));
#endif
			m_readers->Invoke("push", FB::variant_list_of(newReader));
			m_rgReaderStates[m_cReaders].pvUserData = (void*)(new ReaderPtr(newReader));
			// Advance to the next value.
			pReader = pReader + wcslen((wchar_t *)pReader) + 1;
			m_cReaders += 1;
		}
		m_thread = boost::thread(&WebCardAPI::threadRun, this);
		break;

	default:
		// TO DO: Check if other errors could happen
		break;
	}
}

void WebCardAPI::ReleaseReaders()
{
	LONG lRet = 0;

	m_thread.interrupt();
	SCardCancel(m_hContext);
	m_thread.join();

	// Free the memory.
	free(m_rgReaderStates);
#ifdef SCARD_AUTOALLOCATE
	lRet = SCardFreeMemory(m_hContext, m_pmszReaders);
#else
	free(m_pmszReaders);
#endif
	lRet = SCardReleaseContext(m_hContext);
}

void WebCardAPI::threadRun()
{
	LONG lRet = 0;
	char	pbTmp[] = "\x0\x0\x0";
	std::string atr;

	while (!boost::this_thread::interruption_requested())
	{
		lRet = SCardGetStatusChange(m_hContext, INFINITE, m_rgReaderStates, m_cReaders);
		if (boost::this_thread::interruption_requested())
			break;

		for (int i = 0; i < m_cReaders; i++)
		{
			if (m_rgReaderStates[i].dwEventState & SCARD_STATE_CHANGED)
			{
				ReaderPtr pReader = *(ReaderPtr*)(m_rgReaderStates[i].pvUserData);
				pReader->set_state(m_rgReaderStates[i].dwEventState);

				atr = std::string();
				if ((m_rgReaderStates[i].dwCurrentState & SCARD_STATE_EMPTY) &&
					(m_rgReaderStates[i].dwEventState & SCARD_STATE_PRESENT))
				{
					for (int c = 0; c < m_rgReaderStates[i].cbAtr; c++)
					{
						pbTmp[0] = ((m_rgReaderStates[i].rgbAtr[c] & 0xF0) > 0x90) ? (((m_rgReaderStates[i].rgbAtr[c] & 0xF0) >> 4) + 'A' - 10) : (((m_rgReaderStates[i].rgbAtr[c] & 0xF0) >> 4) + '0');
						pbTmp[1] = ((m_rgReaderStates[i].rgbAtr[c] & 0x0F) > 0x09) ? ((m_rgReaderStates[i].rgbAtr[c] & 0x0F) + 'A' - 10) : ((m_rgReaderStates[i].rgbAtr[c] & 0x0F) + '0');
						atr.append(pbTmp);
					}
					pReader->set_atr(atr);
				}
				else if ((m_rgReaderStates[i].dwCurrentState & SCARD_STATE_PRESENT) &&
					(m_rgReaderStates[i].dwEventState & SCARD_STATE_EMPTY))
				{
					pReader->set_atr(atr);
				}

				m_rgReaderStates[i].dwCurrentState = m_rgReaderStates[i].dwEventState;

				fire_statuschange(pReader);
				m_host->htmlLog("SCardGetStatusChange");
			}
		}
	}
}
