# Smart Card Browser Plugin

This component allows a Web page to interact with a smart card. You can download a 
signed version visiting http://plugin.cardid.org/

## Usage

Insert the plugin in the web page

```
<object id="webcard" type="application/x-webcard" width="0" height="0">
  <param name="onload" value="pluginLoaded" />
</object>
```

When the plugin loads you have a collection of readers, and events are fired when 
cards are inserted or removed

```
<script type="text/javascript">
  function pluginLoaded() {
    if (webcard.attachEvent) {
      webcard.attachEvent("oncardinsert", cardInsert);
      webcard.attachEvent("oncardremove", cardRemove);
    } else { 
      webcard.addEventListener("cardinsert", cardInsert, false);
      webcard.addEventListener("cardremove", cardRemove, false);
    }
  }

  function cardInsert(reader) {
    // React to reader.state
  }

  function cardRemove(reader) {

  }
</script>
```

`webcard.readers` is a collection of `reader` objects. The events also pass a `reader` 
parameter.

```
reader.name;             // The name of the reader
reader.state;            // The new state of the reader
reader.atr;              // Answer To Reset given by the inserted card, if any
reader.connect();        // Call this to connect to the card
reader.transcieve(apdu); // Use this to send an APDU to the card hex encoded
reader.disconnect();     // Disconnect from the card when done
```

## Contributing

The plugin uses the [FireBreath](http://github.com/firebreath/FireBreath) framework 
and provides a minimal wrapper around the basic smart card functions from the 
[PC/SC Framework](http://www.pcscworkgroup.com)

To build locally, first clone the FireBreath project and make sure that you follow 
the instructions, read the blogs, ask in StackOverflow until you can build a basic 
plugin. Once your build environment is working, clone WebCard in your local 
Firebreath Projects folder and build it.

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