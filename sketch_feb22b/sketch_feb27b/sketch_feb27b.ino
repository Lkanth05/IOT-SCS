#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;
SoftwareSerial ss(4, 5);
const char* ssid = "POCO";
const char* password = "wwwwwwww";
float latitude, longitude;
int year, month, date, hour, minute, second;
String date_str, time_str, lat_str, lng_str;
int pm;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        lat_str = String(latitude, 6);
        longitude = gps.location.lng();
        lng_str = String(longitude, 6);
      }
      if (gps.date.isValid()) {
        date_str = String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year());
      }
      if (gps.time.isValid()) {
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        minute = (minute + 30) % 60;
        hour = (hour + 5) % 24;
        pm = (hour >= 12) ? 1 : 0;
        hour = hour % 12;
        time_str = String(hour) + ":" + String(minute) + ":" + String(second) + (pm ? " PM" : " AM");
      }
    }
  }

  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  html += "<!DOCTYPE html><html><head><title>GPS DATA</title></head><body>";
  html += "<h1>GPS DATA</h1>";
  html += "<p><b>Location Details</b></p>";
  html += "<table><tr><th>Latitude</th><td>" + lat_str + "</td></tr>";
  html += "<tr><th>Longitude</th><td>" + lng_str + "</td></tr>";
  html += "<tr><th>Date</th><td>" + date_str + "</td></tr>";
  html += "<tr><th>Time</th><td>" + time_str + "</td></tr></table>";
  html += "</body></html>";

  client.print(html);
  delay(100); // You can remove this delay or replace it with a non-blocking delay
}
