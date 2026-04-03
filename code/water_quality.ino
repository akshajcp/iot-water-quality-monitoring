// IoT Water Quality Monitoring System
// Author: Akshaj C P
// Features: Temperature, Turbidity, TDS monitoring with ESP32, Blynk, and OLED

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Water Quality Monitoring"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK  18
#define OLED_DC   2
#define OLED_CS   5
#define OLED_RST  4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK,
                         OLED_DC, OLED_RST,
                         OLED_CS);

// Temperature sensor (DS18B20)
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Sensor pins
#define TURBIDITY_PIN 35
#define TDS_PIN 32

// Alert pins
#define LED_PIN 27
#define BUZZER_PIN 14

float temp = 0;
float turbidity = 0;
float tds = 0;

BlynkTimer timer;

// Function to read sensors and update system
void sendData() {

  // Read temperature
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

  // Read turbidity
  int turbRaw = analogRead(TURBIDITY_PIN);
  turbidity = (turbRaw / 4095.0) * 100.0;

  // Read TDS
  int tdsRaw = analogRead(TDS_PIN);
  tds = (tdsRaw / 4095.0) * 1000.0;

  // Check danger conditions
  bool danger = (temp < 20 || temp > 32 || turbidity > 60 || tds > 500);

  digitalWrite(LED_PIN, danger);
  digitalWrite(BUZZER_PIN, danger);

  // Send data to Blynk
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, 7.0); // Placeholder for pH
  Blynk.virtualWrite(V2, turbidity);
  Blynk.virtualWrite(V3, tds);

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.print("Turbidity: ");
  display.print(turbidity);
  display.println(" %");

  display.print("TDS: ");
  display.print(tds);
  display.println(" ppm");

  if (danger) {
    display.println("ALERT!");
  }

  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  sensors.begin();

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Run sendData every 2 seconds
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
