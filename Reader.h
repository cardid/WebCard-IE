// Reader.h
#include <string>
#include "JSAPIAuto.h"

#ifdef __APPLE__
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#else
#include <winscard.h>
#endif

#ifndef H_Reader
#define H_Reader


FB_FORWARD_PTR(Reader);
class Reader : public FB::JSAPIAuto
{
#ifdef _WINDOWS
	std::wstring m_name;
#else
	std::string m_name;
#endif

public:
#ifdef _WINDOWS
	Reader(const FB::BrowserHostPtr& host, const unsigned int hContext, const std::wstring& name) :
#else
	Reader(const FB::BrowserHostPtr& host, const unsigned int hContext, const std::string& name) :
#endif
		m_hContext(hContext), m_name(name), m_host(host)
	{
		registerMethod("connect", FB::make_method(this, &Reader::connect));
		registerMethod("disconnect", FB::make_method(this, &Reader::disconnect));
		registerMethod("transcieve", FB::make_method(this, &Reader::transcieve));
		registerAttribute("name", name, true);
		registerProperty("state", make_property(this, &Reader::get_state));
		registerProperty("atr", make_property(this, &Reader::get_atr));
	}
	void connect(unsigned int sharemode);
	void disconnect();
	FB::variant transcieve(const FB::variant& apdu);
	int get_state();
	void set_state(int value);
	std::string get_atr();
	void set_atr(const std::string& value);

private:
	FB::BrowserHostPtr m_host;
	SCARDCONTEXT m_hContext;
	SCARDHANDLE m_hCard;
	DWORD m_dwAP;
	unsigned long m_state;
	std::string m_atr;
};

#endif // H_Reader