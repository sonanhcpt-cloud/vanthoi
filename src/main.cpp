#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

// Simple chat UI + TTS placeholder for ESP32-2432S028 (dark theme, Nguyễn Sơn)

TFT_eSPI tft = TFT_eSPI();

// Configs (changeable)
const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASS = "YOUR_PASS";
const char* GOOGLE_API_KEY = "YOUR_GOOGLE_API_KEY";
const char* STARTUP_GREETING = "Xin chào, tôi là Nguyễn Sơn, rất vui được giúp bạn!";

int y_cursor = 20;

// Simple state machine for face expression
enum FaceState { SLEEP, LISTEN, SPEAK, HAPPY };
FaceState face = SLEEP;
unsigned long last_blink = 0;
bool blink_state = false;

void draw_face(FaceState s) {
  // draw a simple cute face in assets replaced by text placeholders
  int cx = tft.width() - 50;
  int cy = tft.height() - 30;
  int r = 20;
  tft.fillCircle(cx, cy, r, TFT_BLACK);
  tft.drawCircle(cx, cy, r, TFT_WHITE);
  // eyes
  if (s == LISTEN) {
    // surprised eyes
    tft.fillCircle(cx-7, cy-5, 3, TFT_WHITE);
    tft.fillCircle(cx+7, cy-5, 3, TFT_WHITE);
  } else if (s == SPEAK) {
    tft.fillCircle(cx-7, cy-6, 4, TFT_WHITE);
    tft.fillCircle(cx+7, cy-6, 4, TFT_WHITE);
  } else { // SLEEP or HAPPY
    if (blink_state) {
      tft.drawLine(cx-12, cy-4, cx-2, cy-4, TFT_WHITE);
      tft.drawLine(cx+2, cy-4, cx+12, cy-4, TFT_WHITE);
    } else {
      tft.fillCircle(cx-7, cy-6, 3, TFT_WHITE);
      tft.fillCircle(cx+7, cy-6, 3, TFT_WHITE);
    }
  }
  // mouth
  if (s == HAPPY) {
    tft.drawArc(cx, cy+2, 8, 4, 20, 160, TFT_WHITE);
  } else if (s == SPEAK) {
    tft.fillEllipse(cx, cy+4, 6, 3, TFT_WHITE);
  } else {
    tft.drawLine(cx-4, cy+4, cx+4, cy+4, TFT_WHITE);
  }
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 10);
  tft.println(STARTUP_GREETING);
  y_cursor = 40;
  face = SLEEP;
  last_blink = millis();
}

void addMessage(const char* who, const char* msg) {
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(10, y_cursor);
  tft.printf("%s: ", who);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print(msg);
  y_cursor += 20;
  if (y_cursor > tft.height() - 40) {
    tft.fillScreen(TFT_BLACK);
    y_cursor = 20;
  }
}

unsigned long last_tick = 0;
void loop() {
  // blinking effect every 4s
  if (millis() - last_blink > 4000) {
    blink_state = true;
    last_blink = millis();
  }
  if (blink_state && millis() - last_blink > 200) {
    blink_state = false;
  }

  // For demo: simulate listening and speaking every 10s
  if (millis() - last_tick > 10000) {
    last_tick = millis();
    face = LISTEN;
    draw_face(face);
    delay(1200);
    addMessage("Bạn", "Xin chao XiaoZhi");
    face = SPEAK;
    draw_face(face);
    addMessage("Nguyễn Sơn", "Xin chào, tôi là Nguyễn Sơn. Tôi có thể giúp gì cho bạn?");
    delay(1500);
    face = HAPPY;
    draw_face(face);
  }
}
