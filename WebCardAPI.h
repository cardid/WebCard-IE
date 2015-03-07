/**********************************************************\

  Auto-generated WebCardAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "WebCard.h"
#include "Reader.h"

#ifndef H_WebCardAPI
#define H_WebCardAPI


class WebCardAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn WebCardAPI::WebCardAPI(const WebCardPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    WebCardAPI(const WebCardPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        // Read-only property
        registerProperty("readers",
                         make_property(this,
                                       &WebCardAPI::get_readers));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &WebCardAPI::get_version));

        InitializeReaders();
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn WebCardAPI::~WebCardAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~WebCardAPI() {
		ReleaseReaders();
	};

    WebCardPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
	FB::JSObjectPtr get_readers();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Event helpers
    FB_JSAPI_EVENT(cardpresent, 1, (const FB::variant&));
	FB_JSAPI_EVENT(cardremoved, 1, (const FB::variant&));

	void InitializeReaders();
	void ReleaseReaders();

protected:
	void threadRun();

private:
    WebCardWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

	SCARDCONTEXT m_hContext;
	LPTSTR  m_pmszReaders;
#if defined(linux) || defined(_WINDOWS)
    LPSCARD_READERSTATE m_rgReaderStates;
#else
	LPSCARD_READERSTATE_A m_rgReaderStates;
#endif
	int m_cReaders;
	FB::JSObjectPtr m_readers;
	boost::thread m_thread;
};

#endif // H_WebCardAPI

