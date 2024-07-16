#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
const char* ssid = "OPPO A5"; // ssid of your wifi
const char* password = "qwertyuiop"; // password of your wifi
float latitude, longitude;
int year, month, day, hour, minute, second;
String date_str, time_str, lat_str, lng_str;
int pm;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // connecting to wifi
  while (WiFi.status() != WL_CONNECTED) { // while wifi not connected
    delay(500);
    Serial.print("."); // print "...."
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address
}

void loop() {
  while (ss.available() > 0) // while data is available
    if (gps.encode(ss.read())) // read gps data
    {
      if (gps.location.isValid()) // check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude, 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude, 6); // longitude location is stored in a string
      }
      if (gps.date.isValid()) // check whether gps date is valid
      {
        date_str = "";
        day = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (day < 10)
          date_str = '0';
        date_str += String(day); // values of date, month and year are stored in a string
        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month); // values of date, month and year are stored in a string
        date_str += " / ";
        date_str += String(year); // values of date, month and year are stored in a string
      }
      if (gps.time.isValid()) // check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        minute = (minute + 30); // converting to IST
        if (minute > 59) {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5);
        if (hour > 23)
          hour = hour - 24; // converting to IST
        if (hour >= 12) // checking whether AM or PM
          pm = 1;
        else
          pm = 0;
        hour = hour % 12;
        if (hour < 10)
          time_str = '0';
        time_str += String(hour); // values of hour, minute and second are stored in a string
        time_str += " : ";
        if (minute < 10)
          time_str += '0';
        time_str += String(minute); // values of hour, minute and second are stored in a string
        time_str += " : ";
        if (second < 10)
          time_str += '0';
        time_str += String(second); // values of hour, minute and second are stored in a string
        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
      }
    }

  WiFiClient client = server.available(); // Check if a client has connected
  if (!client) {
    return;
  }
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>GPS DATA</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td </style> </head> <body> <h1 style=\"font-size:300%; text-align:center;\"> GPS DATA</h1>";
  s += "<p style=\"font-size:150%; text-align:center;\"><b>Location Details</b></p>";
  s += "<table style=\"width:50%; margin:auto;\">";
  s += "<tr> <th>Latitude</th> <td style=\"text-align:center;\">" + lat_str + "</td> </tr>";
  s += "<tr> <th>Longitude</th> <td style=\"text-align:center;\">" + lng_str + "</td> </tr>";
  s += "<tr> <th>Date</th> <td style=\"text-align:center;\">" + date_str + "</td> </tr>";
  s += "<tr> <th>Time</th> <td style=\"text-align:center;\">" + time_str + "</td> </tr>";
  s += "</table>";
  s += "<iframe src=\"https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3889.3287494673446!2d" + lng_str + "!3d" + lat_str + "!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x3bae38bc2bb37a81%3A0xcef960a370d38901!2sRajarajeswari%20College%20of%20Engineering!5e0!3m2!1sen!2sin!4v1720244418600!5m2!1sen!2sin\" width=\"100%\" height=\"600\" style=\"border:0;\" allowfullscreen=\"\" loading=\"lazy\" referrerpolicy=\"no-referrer-when-downgrade\"></iframe>";
  s += "</body> </html>";

  client.print(s); // all the values are sent to the webpage
  delay(100);
}
