#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for WebCard
#
#\**********************************************************/

set(PLUGIN_NAME "WebCard")
set(PLUGIN_PREFIX "WCA")
set(COMPANY_NAME "cardid")

# ActiveX constants:
set(FBTYPELIB_NAME WebCardLib)
set(FBTYPELIB_DESC "WebCard 1.0 Type Library")
set(IFBControl_DESC "WebCard Control Interface")
set(FBControl_DESC "WebCard Control Class")
set(IFBComJavascriptObject_DESC "WebCard IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "WebCard ComJavascriptObject Class")
set(IFBComEventSource_DESC "WebCard IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID a90aaca0-219c-5b05-bab4-701db28b74e7)
set(IFBControl_GUID add2af79-f23d-569f-8d5e-8c3e61a0b9be)
set(FBControl_GUID 078ef12e-a5ed-5374-9d3a-dbc93d57750e)
set(IFBComJavascriptObject_GUID d1510931-da68-5a60-8e4b-9913ec719abb)
set(FBComJavascriptObject_GUID 673c3945-57c2-5ce1-b78e-08078306f1e9)
set(IFBComEventSource_GUID ba2e59d8-8898-5a82-b2f3-d08f7d41bad2)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 96b12e7a-dbae-5ad6-890e-a4838a4b1109)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 42184184-0521-53b5-abff-078e49eb5ff4)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "cardid.WebCard")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "cardid/WebCard")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "cardid/WebCard_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "CardID.org")
set(FBSTRING_PluginDescription "Smart Card Browser Plugin")
set(FBSTRING_PLUGIN_VERSION "0.6.11")
set(FBSTRING_LegalCopyright "Copyright 2014 cardid.org")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "Smart Card Browser Plugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "WebCard")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "WebCard_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-webcard")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
