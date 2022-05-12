#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#endif
#include <esp8266-google-home-notifier.h>

const char* ssid     = "<ชื่อ WiFi>";
const char* password = "<รหัสผ่าน WiFi>";
int reed_s = D2;
int flag = 0;
GoogleHomeNotifier ghn1;
GoogleHomeNotifier ghn2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  pinMode(reed_s, INPUT_PULLUP);
  Serial.print("connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP

  const char displayName1[] = "Living room";
  const char displayName2[] = "Kitchen room";

  Serial.println("connecting to Google Home...1");
  if (ghn1.device(displayName1, "th") != true) {
    Serial.println(ghn1.getLastError());
    return;
  }
  Serial.print("found Google Home(");
  Serial.print(ghn1.getIPAddress());
  Serial.print(":");
  Serial.print(ghn1.getPort());
  Serial.println(")");

  Serial.println("connecting to Google Home...2");
  if (ghn2.device(displayName2, "th") != true) {
    Serial.println(ghn2.getLastError());
    return;
  }
  Serial.print("found Google Home(");
  Serial.print(ghn2.getIPAddress());
  Serial.print(":");
  Serial.print(ghn2.getPort());
  Serial.println(")");
  ghn1.notify("ระบบแจ้งเตือนประตูเริ่มทำงาน");
  ghn2.notify("ระบบแจ้งเตือนประตูเริ่มทำงาน");
  Serial.println("Setup Done");
}
void loop() {
  if ((digitalRead(reed_s) == LOW) && ( flag == 0  )) {
    ghn1.notify("ประตูห้องถูกปิด");
    ghn2.notify("ประตูห้องถูกปิด");
    Serial.println("Door Closed");
    flag = 1;
  }
  if ((digitalRead(reed_s) == HIGH) && ( flag == 1) ) {
    ghn1.notify("ประตูห้องถูกเปิด");
    ghn2.notify("ประตูห้องถูกเปิด");
    Serial.println("Door Opened");
    flag = 0;
  }
  delay(1000);
}

