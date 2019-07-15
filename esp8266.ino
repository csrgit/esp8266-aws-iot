#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include "ESP8266AWSImplementations.h"
#include "config.h"

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

char *ssid= SSID;
char *password= WIFIPASS;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WIFI
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion(AWS_ZONE);
  iotClient.setAWSEndpoint(AWS_ENDPOINT);
  iotClient.setAWSDomain(AWS_DOMAIN);
  iotClient.setAWSPath(AWS_PATH);
  iotClient.setAWSKeyID(AWS_KEYID);
  iotClient.setAWSSecretKey(AWS_SECRET);
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop(){
  char* shadow = "{\"state\":{\"reported\": {\"foobar\": \"barbar\"}}}";
  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);

  delay(60000);
}