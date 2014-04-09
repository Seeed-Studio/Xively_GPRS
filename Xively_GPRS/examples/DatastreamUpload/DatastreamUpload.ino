#include <GPRSClient.h>
#include <Xively.h>
#include <SoftwareSerial.h>

#define PIN_TX 7
#define PIN_RX 8

// Your Xively key to let you upload data
//char xivelyKey[] = "YOUR_XIVELY_API_KEY";
char xivelyKey[] = "niUYuSJkjqyzPFwnWqpApm7lLNv8fInUD6ijAoRrikqKFWbg";

// Define the strings for our datastream IDs
char sensorId[] = "Sound";
XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(571464242, datastreams, 1 /* number of datastreams */);

char apn[] = "cmnet";
GPRSClient gprs(PIN_TX,PIN_RX,19200,apn,NULL,NULL);
XivelyClient xivelyclient(gprs);

int sensorPin = A1;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();
  gprs.init();
  
  while(false == gprs.join()) {
    Serial.println("connect error");
    delay(2000);
  }
  // successful DHCP
  Serial.print("IP = ");
  Serial.println(gprs.getIPAddress());
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  //int sensorValue = 333;//for debug
  datastreams[0].setFloat(sensorValue);
  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
  Serial.println("Uploading it to Xively");

  int ret = xivelyclient.put(feed, xivelyKey);
  if(true == ret){
    Serial.println("update success!");
  }else{
    Serial.println("update failed!");
  }
  Serial.println();
  delay(10*1000);
}

