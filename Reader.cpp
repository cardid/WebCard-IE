#include "Reader.h"

void Reader::connect(unsigned int sharemode)
{
	LONG lRet = 0;

	if ((lRet = SCardConnect(m_hContext, m_name.c_str(), (uint32_t)sharemode, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &m_hCard, &m_dwAP)) == SCARD_S_SUCCESS)
		lRet = SCardBeginTransaction(m_hCard);

	if (lRet != SCARD_S_SUCCESS)
		throw FB::script_error("error connecting to the card");
}

FB::variant Reader::transcieve(const FB::variant& apdu)
{
	long	lr;
	char*	pbTemp;
	size_t	i;
	char	pbSend[278];
	char	pbRecv[278];
	size_t	cbSend;
	size_t	cbRecv;
	size_t  cbBlock;
	char	pbTmp[] = "\x0\x0\x0";

	std::string apdu_resp;

	try {
		if (apdu.is_of_type<FB::JSObjectPtr>()) {
			// TO DO: For a JavaScript array, get elements
		}
		else {
			std::string apdu_send = apdu.convert_cast<std::string>();
			cbSend = apdu_send.length() / 2;
			pbTemp = (char*)apdu_send.c_str();

			for (i = 0; i < cbSend; i++)
			{
				if (*pbTemp > 0x60) *pbTemp -= 0x20; // Make uppercase
				pbSend[i] = (*pbTemp > 0x2F && *pbTemp < 0x3A) ? (*pbTemp - '0') << 4 : (*pbTemp - 'A' + 10) << 4;
				pbTemp += 1;
				if (*pbTemp > 0x60) *pbTemp -= 0x20; // Make uppercase
				pbSend[i] += (*pbTemp > 0x2F && *pbTemp < 0x3A) ? (*pbTemp - '0') : (*pbTemp - 'A' + 10);
				pbTemp += 1;
			}
		}
	}
	catch (...) {
		m_host->htmlLog("Transcieve: (unknown)");
	}

	cbRecv = 278;
	lr = SCardTransmit(m_hCard,
		(m_dwAP == SCARD_PROTOCOL_T0) ? (SCARD_PCI_T0) : (SCARD_PCI_T1),
		(LPCBYTE)pbSend, cbSend, NULL, (LPBYTE)pbRecv, (LPDWORD)&cbRecv);

	if (lr == SCARD_S_SUCCESS)
	{
		apdu_resp = std::string();
		if (pbRecv[cbRecv - 2] == 0x61)
		{
			do
			{
				pbTemp = pbRecv;
				if (pbRecv[cbRecv - 2] == 0x61)
					cbBlock = cbRecv - 2;
				else
					cbBlock = cbRecv;

				for (i = 0; i < cbBlock; i++)
				{
					pbTmp[0] = ((*pbTemp & 0xF0) > 0x90) ? (((*pbTemp & 0xF0) >> 4) + 'A' - 10) : (((*pbTemp & 0xF0) >> 4) + '0');
					pbTmp[1] = ((*pbTemp & 0x0F) > 0x09) ? ((*pbTemp & 0x0F) + 'A' - 10) : ((*pbTemp & 0x0F) + '0');
					apdu_resp.append(pbTmp);
					pbTemp++;
				}

				if (pbRecv[cbRecv - 2] == 0x61)
				{
					memcpy(pbSend, "\x00\xC0\x00\x00", 4);
					pbSend[4] = pbRecv[cbRecv - 1];
					cbSend = 5;
					cbRecv = 278;	// Including status bytes
					lr = SCardTransmit(m_hCard,
						(m_dwAP == SCARD_PROTOCOL_T0) ? (SCARD_PCI_T0) : (SCARD_PCI_T1),
						(LPCBYTE)pbSend, cbSend, NULL, (LPBYTE)pbRecv, (LPDWORD)&cbRecv);
				}
			} while (pbRecv[cbRecv - 2] == 0x61);
		}

		// The last or only block
		pbTemp = pbRecv;
		for (i = 0; i < cbRecv; i++)
		{
			pbTmp[0] = ((*pbTemp & 0xF0) > 0x90) ? (((*pbTemp & 0xF0) >> 4) + 'A' - 10) : (((*pbTemp & 0xF0) >> 4) + '0');
			pbTmp[1] = ((*pbTemp & 0x0F) > 0x09) ? ((*pbTemp & 0x0F) + 'A' - 10) : ((*pbTemp & 0x0F) + '0');
			apdu_resp.append(pbTmp);
			pbTemp++;
		}
	}

	return apdu_resp;
}

void Reader::disconnect()
{
	SCardEndTransaction(m_hCard, SCARD_LEAVE_CARD);
	SCardDisconnect(m_hCard, SCARD_LEAVE_CARD);
}

int Reader::get_state()
{
	return m_state;
}

void Reader::set_state(int value)
{
	m_state = value;
}

std::string Reader::get_atr()
{
	return m_atr;
}

void Reader::set_atr(const std::string& value)
{
	m_atr = value;
}