#include <ESP8266WiFi.h>

// WiFi Configuration
const char* ssid = "Dinh";
const char* password = "12121212";

// Create Server
WiFiServer server(80);

int output_pin = 5; // (GPIO5 = output D1)

void setup() {

  Serial.begin(115200);
  delay(10);

  // GPIO5
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, 0);
  // WiFi Connection 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start server
  server.begin();
  Serial.println("Start Server");

  // In dia chi IP
  Serial.println(WiFi.localIP());
}

void loop() {

  // Check Client Connection
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Client send data
  Serial.println("New client ");
  while(!client.available()){
    delay(1);
  }

  // Read client data
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Check which is the connection
  if (req.indexOf("/on") != -1){
    digitalWrite(output_pin, 1);
  }
  else if (req.indexOf("/off") != -1) {
    digitalWrite(output_pin, 0);
  }

  client.flush();

  // Prepare HTML page to response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "</head>";
  s += "<div class=\"container\">";
  s += "<h1>Led Control</h1>";
  s += "<div class=\"row\">";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-primary\" type=\"button\" value=\"On\" onclick=\"on()\"></div>";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-danger\" type=\"button\" value=\"Off\" onclick=\"off()\"></div>";
  s += "</div></div>";
  s += "<script>function on() {$.get(\"/on\");}</script>";
  s += "<script>function off() {$.get(\"/off\");}</script>";

  // Send information to client
  client.print(s);
  delay(1);
  Serial.println("Client Disconnection");

}
