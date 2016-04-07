#include <ESP8266WiFi.h>

char ssid[] = "BTHub4-52R2";      // your network SSID (name)
char pass[] = "bfc24d8db3";   // your network password

int ledPin = 13;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {

  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200);
  delay(10);

 
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String respMsg = "";    // HTTP Response Message
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  int paramAfter = req.indexOf("=") + 1;
  String paramVal = req.substring(paramAfter);
  Serial.println("pos is:");
  Serial.println(paramAfter);
  Serial.println("val is:");
  Serial.println(paramVal);
  client.flush();
  Serial.println(paramVal.substring(0, 2));
  
  if (paramVal.substring(0, 2) == "on") {
    Serial.println("switch on");
    digitalWrite(ledPin, HIGH);
  }
  else if(paramVal.substring(0, 3) == "off") {
    Serial.println("switch off");
    digitalWrite(ledPin, LOW);
  }
  

 
  delay(30);
    
    
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";


  // Send the response to the client
  client.print(s);
  client.println("<!DOCTYPE html>"); //web page is made using HTML

  client.println("<html>");
  
  client.println("<head>");
  
  client.println("<title>Ethernet Tutorial</title>");
 
  client.println("</head>");
  
  client.println("<body>");
  client.println(digitalRead(ledPin));
  client.println("<a href='?status=on'>On</a> <a href='?status=off'>Off</a>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed

   client.flush();
  client.stop();
}


