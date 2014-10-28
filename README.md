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

`reader_list` is a collection of `reader` objects. The event also passes a `reader` 
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

Copyright 2012-2014 CardID Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
