#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <string.h>
// OLED WINDOW 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   13
#define OLED_CLK   14
#define OLED_DC    5
#define OLED_CS    15
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


const char* ssid = "myAccessPoint";
const char* password = "myPassword";

ESP8266WebServer server(80);

HTTPClient myclient;

// JOY STICK
#define VRX_PIN 2  //D4 joystick module X-axis pin
#define SW_PIN 0 //D3  // joystick module button pin



void handleRoot() {
  String html = "<html><body><h1>Hello, World!</h1></body></html>";
  server.send(200, "text/html", html);
}


void setup() {
  Serial.begin(9600);
  delay(10);
  //OLED 
  if(!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.display();
  

  // Set WiFi mode to access point
  WiFi.mode(WIFI_AP);
  
  // Configure access point
  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.print("Access point ");
  Serial.print(ssid);
  Serial.println(" started.");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Setup web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started.");
  // Interfacing IP adress to OLED
  display.setCursor(5,20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("IP:");
  display.setCursor(22,20);
  display.println(WiFi.softAPIP());
  display.display();

  // JOYSTICK
  pinMode(SW_PIN, INPUT_PULLUP); 
}

void loop() {
  // draw Methods //
  DisplayNetowrkInfo();
  display.display();
  int buttonState = digitalRead(SW_PIN); // read button state
  int xValue = digitalRead(VRX_PIN); // read X-axis value
  //Serial.println(buttonState);

  moveDown(xValue);
  MoveUp(buttonState);
  //Serial.println(xValue);
  delay(250);
  server.handleClient();
}

// JOYSTICK CONTROLLER FUNCTIONS HERE 
int moveDown(int x){
  if( x == 0 ){
    Serial.println("DOWN");
    return 1;
  }
  else{
    return 0;
  }
}

int MoveUp(int y){
  if(y == 0){
    // GO BOTTOM
    Serial.println("UP");
    delay(20);
    return 1;
  }
  return 0;
}


// BULDING THE DOWNLOAD PARAT HERE 
// FUNCTIONS HERE 
/*
void downlaodFunction() {
  //wifi connection here 
   // Replace with your network credentials

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Replace with the URL of the file you want to download
  String URL = "https://tinyurl.com/57eu86ny";
  myclient.HTTPClient::begin(URL);

  int httpCode = myclient.GET();

  if (httpCode == HTTP_CODE_OK) {
    Serial.println("File downloaded successfully.");

    File file = SPIFFS.open("/file.txt", "w"); // Replace with the filename you want to save the file as

    if (!file) {
      Serial.println("Failed to create file.");
      return;
    }

    int totalBytes = myclient.getSize();
    int bytesRead = 0;

    uint8_t buffer[1024];
    WiFiClient *stream = myclient.getStreamPtr();

    while (myclient.connected() && (bytesRead < totalBytes)) {
      int len = stream->available();
      if (len > 0) {
        int bytesToRead = std::min(len, (int)sizeof(buffer));
        int bytesReadThisTime = stream->readBytes(buffer, bytesToRead);
        file.write(buffer, bytesReadThisTime);
        bytesRead += bytesReadThisTime;
      }
    }

    file.close();
    Serial.println("File saved.");
  } else {
    Serial.println("Failed to download file.");
  }

  myclient.end();

  delay(60000); // Wait for 1 minute before downloading the file again
  }
*/





//Interface Functions 
void DisplayNetowrkInfo()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Network");
  display.drawRect(0, 15, 100, 55, SSD1306_WHITE);
  //display.display();
}

void DrawFilledRectangle()
{
  display.clearDisplay();  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Filled Rectangle");
  display.fillRect(0, 15, 90, 45, SSD1306_WHITE);
  display.display();
  delay(2000);
  
}
void DrawRoundRectangle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Round Rectangle");
  display.drawRoundRect(0, 15, 90, 45, 10, SSD1306_WHITE);
  display.display();
  delay(5000);
}
void DrawFilledRoundRectangle()
{
  display.clearDisplay();  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Filled Round Rect");
  display.fillRoundRect(0, 15, 90, 45, 10, SSD1306_WHITE);
  display.display();
  delay(2000);
  
}
void DrawCircle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Circle");
  display.drawCircle(30, 36, 25, SSD1306_WHITE);
  display.display();
  delay(2000);
}
void DrawFilledCircle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Filled Circle");
  display.fillCircle(30, 36, 25, SSD1306_WHITE);
  display.display();
  delay(2000);
  
}
void DrawTriangle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Triangle");
  display.drawTriangle(30, 15, 0, 60, 60, 60, SSD1306_WHITE);
  display.display();
  delay(2000);  
}
void DrawFilledTriangle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Filled Triangle");
  display.fillTriangle(30, 15, 0, 60, 60, 60, SSD1306_WHITE);
  display.display();
  delay(2000);
}

