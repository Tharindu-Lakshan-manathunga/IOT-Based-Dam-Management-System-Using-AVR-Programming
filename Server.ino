//http://192.168.4.1/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "Tharindu";
const char* password = "12345678";
 
ESP8266WebServer server(80);
String serialData;
String serialDataH="0";// variable for humidity
String serialDataT="0";// variable for humidity
String serialDataW="0";
void handleRoot() {
  String html = "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<meta http-equiv=\'refresh\' content=\'2\'>"
    "<style>"
      "body {"
        "background-color: #F8F8F8;"
        "font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif;"
        "color: #333333;"
        "margin: 0;"
        "padding: 0;"
      "}"
      "h2 {"
        "font-size: 40px;"
        "color: #2c3e50;"
        "margin-top: 50px;"
      "}"
      "p {"
        "font-size: 30px;"
        "margin-top: 20px;"
      "}"
      "button {"
        "background-color: #4CAF50;"
        "border: none;"
        "color: white;"
        "padding: 10px 20px;"
        "text-align: center;"
        "text-decoration: none;"
        "display: inline-block;"
        "font-size: 20px;"
        "margin-top: 20px;"
        "margin-right: 10px;"
        "border-radius: 5px;"
        "cursor: pointer;"
      "}"
      "button:hover {"
        "background-color: #3e8e41;"
      "}"
      "a {"
        "text-decoration: none;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<center>"
      "<h2>Dam Gate Controlling System</h2>"
      "<p>Temperature: <span style=\"color:#3498db;\">"+serialDataT+" C</span></p>"
      "<p>Humidity: <span style=\"color:#3498db;\">"+serialDataH+"%</span></p>"
      "<p>Water Level: <span style=\"color:#3498db;\">"+serialDataW+"%</span></p>"
      "<h2>Gate</h2>"
      "<a href=\"on\"><button style=\"background-color:#3498db;\">Open</button></a>"
      "<a href=\"off\"><button style=\"background-color:#e74c3c;\">Close</button></a>"
    "</center>"
  "</body>"
  "</html>";
  server.send(200, "text/html", html);
}

void on() {
  Serial.print(1);
  handleRoot();
}
void off() {
  Serial.print(0);
  handleRoot();
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/on", on);
  server.on("/off", off);
  server.begin();
}
 
void loop() {
  server.handleClient();
  if (Serial.available() > 0) {
    serialData = Serial.readStringUntil('\n');
  }
  int separatorIndex = serialData.indexOf(','); // find the index of the first separator character
  int secondSeparatorIndex = serialData.indexOf(',', separatorIndex + 1); // find the index of the second separator character
  if (separatorIndex >= 0 && secondSeparatorIndex >= 0) { // if both separators found
    serialDataH = serialData.substring(0, separatorIndex); // extract the humidity value
    serialDataT = serialData.substring(separatorIndex + 1, secondSeparatorIndex); // extract the temperature value
    serialDataW = serialData.substring(secondSeparatorIndex + 1); // extract the weight value
  }
}



