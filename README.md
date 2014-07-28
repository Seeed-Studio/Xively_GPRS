Xively-GPRS
![image](http://www.tinkerforge.com/en/doc/_images/Kits/weather_station_xively_graphs_orig.jpg)

* **Xively** is an on-line database service allowing developers to connect sensor-derived data (e.g. energy and environment data from objects, devices & buildings) to the Web and to build their own applications based on that data.<br>
* the **Xively-GPRS** is a library that connecting to **Xively** with GPRS, you can have a try with a GPRS module(ex. [Seeed_GPRS_Sheild](http://www.seeedstudio.com/wiki/GPRS_Shield_V2.0))<br>

## Instruction:
The folowing we introduce how to use this library. <br>

the library include two sublibrary:<br>

* **GPRSClient** 

GPRSClient is a library to provide GPRS operation interface.such as:
	
	int join();
	char* getIPAddress();
	int connect(char* host, uint16_t port);
	...

* **Xively-GPRS** 

Xively-GPRS offer the basic API to help you upload/download data to the web. Only three APIs is available:
	  
	XivelyClient(GPRSClient& aClient);
	int get(XivelyFeed& aFeed, const char* aApiKey);
	int put(XivelyFeed& aFeed, const char* aApiKey);
	
## Usage ##
The above two libraries(**GPRSClient** and **Xively-GPRS**) should be placed under your Arduino libraries path(e.g. D:\Arduino\arduino-1.0.5\libraries),then you can have a try with the examples which are under Xively-GPRS/examples. Have fun!

----
This software is written by lawliet zou (![](http://www.seeedstudio.com/wiki/images/f/f8/Email-lawliet.zou.jpg)) for [Seeed Technology Inc.](http://www.seeed.cc) and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt/LICENSE for the details of MIT license.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed is a hardware innovation platform for makers to grow inspirations into differentiating products. By working closely with technology providers of all scale, Seeed provides accessible technologies with quality, speed and supply chain knowledge. When prototypes are ready to iterate, Seeed helps productize 1 to 1,000 pcs using in-house engineering, supply chain management and agile manufacture forces. Seeed also team up with incubators, Chinese tech ecosystem, investors and distribution channels to portal Maker startups beyond.

[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/Xively_GPRS)](https://github.com/igrigorik/ga-beacon)

