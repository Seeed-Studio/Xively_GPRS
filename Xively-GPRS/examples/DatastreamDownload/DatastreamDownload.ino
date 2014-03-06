#include <GPRSClient.h>
#include <Xively.h>
#include <SoftwareSerial.h>

#define PIN_TX 7
#define PIN_RX 8

// Your Xively key to let you upload data
char xivelyKey[] = "niUYuSJkjqyzPFwnWqpApm7lLNv8fInUD6ijAoRrikqKFWbg";

// Define the string for our datastream ID
char sensorId[] = "Sound";

XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(571464242, datastreams, 1 /* number of datastreams */);

char apn[] = "cmnet";
GPRSClient gprs(PIN_TX,PIN_RX,19200,apn,NULL,NULL);
XivelyClient xivelyclient(gprs);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Reading from Xively example");
  Serial.println();
  
  gprs.init();
  while(false == gprs.join()) {
    Serial.println("connect error");
    delay(2000);
  }

  // successful DHCP
  Serial.print("IP =");
  Serial.println(gprs.getIPAddress());
}

void loop() {
  int ret = xivelyclient.get(feed, xivelyKey);
  if (ret > 0){
    Serial.println("Datastream is...");
    Serial.println(feed[0]);
    Serial.print("Temperature is: ");
    Serial.println(feed[0].getFloat());
  }

  Serial.println();
  delay(15000UL);
}

