Smart Card Browser Plugin
=========================

This component allows a Web page to interact with a smart card. You can download a signed version visiting http://plugin.cardid.org/

Usage
-----

Insert the plugin in the web page

```
<object id="webcard" type="application/x-webcard" width="0" height="0">
  <param name="onload" value="pluginLoaded" />
</object>
```

When the plugin loads you have a collection of readers, and events are fired when cards are inserted or removed

```
<script type="text/javascript">
  var reader_list;

  function pluginLoaded()
  {
    reader_list = webcard.readers;

    if (webcard.attachEvent) {
      webcard.attachEvent("onstatuschange", scard_readerevent);
    } else { 
      webcard.addEventListener("statuschange", scard_readerevent, false);
    }
  }

  function scard_readerevent(reader)
  {
    // React to reader.state
  }
</script>
```

_reader_list_ is a collection of _reader_ objects. The event also passes a _reader_ parameter.

```
reader.name;             // The name of the reader
reader.state;            // The new state of the reader
reader.atr;              // Answer To Reset given by the inserted card, if any
reader.connect();        // Call this to connect to the card
reader.transcieve(apdu); // Use this to send an APDU to the card hex encoded
reader.disconnect();     // Disconnect from the card when done
```

Development
-----------

The plugin uses the Firebreath (http://github.com/Firebreath) framework and provides a minimal wrapper around the basic smart card functions from the <a href="http://www.pcscworkgroup.com/">PC/SC framework</a>
