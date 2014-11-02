# Smart Card Browser Plugin

This component allows a Web page to interact with a smart card. If you just 
want to use the plugin, you can download installers [for Windows](http://plugin.cardid.org/webcard.msi) or [for Mac OS X](http://plugin.cardid.org/webcard.dmg). 
In Mac OS X you also need to install [Smart Card Services](http://smartcardservices.macosforge.org/)

## Usage

Insert the plugin in the web page

```
<object id="webcard" type="application/x-webcard" width="0" height="0">
  <param name="onload" value="pluginLoaded" />
</object>
```

When the plugin loads you have a collection of readers, and events are fired 
when cards are inserted or removed

```
<script type="text/javascript">
  function pluginLoaded() {
    if (webcard.attachEvent) {
      webcard.attachEvent("oncardpresent", cardPresent);
      webcard.attachEvent("oncardremoved", cardRemoved);
    } else { 
      webcard.addEventListener("cardpresent", cardPresent, false);
      webcard.addEventListener("cardremoved", cardRemoved, false);
    }
  }

  function cardPresent(reader) {
    reader.connect(2); // 1-Exclusive, 2-Shared
    console.log("ATR : " + reader.atr);
    var apdu = "FFCA000000";
    var resp = reader.transcieve(apdu);
    console.log("UID : " + resp);
    reader.disconnect();
  }

  function cardRemoved(reader) {

  }
</script>
```

`webcard.readers` is a collection of `reader` objects. The events also pass a 
`reader` parameter

```
reader.name;             // The name of the reader
reader.atr;              // Answer To Reset given by the inserted card, if any
reader.connect();        // Call this to connect to the card
reader.transcieve(apdu); // Use this to send an APDU to the card hex encoded
reader.disconnect();     // Disconnect from the card when done
```

## Contributing

The plugin uses the [FireBreath](http://github.com/firebreath/FireBreath) 
framework and provides a minimal wrapper around the basic smart card functions 
from the [PC/SC Framework](http://www.pcscworkgroup.com)

To build locally, first clone the FireBreath project and make sure that you 
follow the instructions, read the blogs, ask in StackOverflow until you can 
build a basic plugin. Once your build environment is working, clone WebCard in 
your local Firebreath Projects folder and build it.

## License

The MIT License (MIT)

Copyright (c) 2014 CardID Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.