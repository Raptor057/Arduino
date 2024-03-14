/////////////////////////// INDUSTRUINO LCD //////////////////////////////
#include <UC1701.h>

#define LCD_BACKLIGHT_PIN 26  // PWM output pin that the LED backlight is attached to

static UC1701 lcd;

// A custom glyphs (a Gt)...
static const byte G[] = { B00011110, B00100001, B00100001, B00101001, B00011010 };
static const byte t[] = { B00111100, B01001000, B00000000, B00000000, B00000000 };

// initialize the LCD related signals and variables
void lcdSetup() {
  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);      // LCD backlight
  lcd.begin();
  // Add glyphs at positions "0" and "1" of the ASCII table...
  lcd.createChar(0, G);
  lcd.createChar(1, t);

  // print Gt glyph
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.write(1);
}

// display a message that indicates the TCP server
// result
void lcdResponse(uint8_t response, uint8_t data) {
  lcd.setCursor(5, 5);
  switch (response) {
    case 0: lcd.print("NO RESPONSE "); break;
    case 1: lcd.print("SUCCESS     "); break;
    case 2: lcd.print("FAILURE     "); break;
    case 3: lcd.print("DISCONNECTED"); break;
    case 4: lcd.print("NO DATA     "); break;
  }
  lcd.print(" (" + String(data) + ")");
}

// display the device's RTC MAC address
void lcdMac(byte mac[6]) {
  lcd.setCursor(0, 1);
  lcd.print("MAC ");
  for (int u = 0; u < 6; u++) {
    lcd.print(mac[u], HEX);
    if (u < 5) lcd.print(":");
  }
}

// display the assigned IP address
void lcdIP() {
  lcd.setCursor(0, 2);
  lcd.print("IP ");
  lcd.print(ethLocalIP());
}

// display the offline status that indicates the device
// has no connection
void lcdOffline() {
  lcd.setCursor(0, 3);
  lcd.print("STATUS: OFFLINE   ");
  analogWrite(LCD_BACKLIGHT_PIN, 0);
}

// display the connecting status that indicated the
// device is trying to reach the remote server
void lcdConnecting() {
  lcd.setCursor(0, 3);
  lcd.print("STATUS: CONNECTING");
}

// display the connected status that indicates the device
// is waiting for the test bench trigger signal
void lcdConnected() {
  lcd.setCursor(0, 3);
  lcd.print("STATUS: CONNECTED   ");
  analogWrite(LCD_BACKLIGHT_PIN, 255);
}

// display an animated "character" to indicate the device
// is looping
void lcdIndicator() {
  static char chars[4] = { '|', '/', '-', '\\' };
  static int charIndex = 0;
  lcd.setCursor(10, 0);
  lcd.print(chars[charIndex]);
  charIndex = (charIndex + 1) % 4;
  //lcd.print(1 == 0 ? "NO" : "SI");
}

// update the LCD brightness intensity
void lcdUpdateBrightness() {
  static int brightness = 0;
  analogWrite(LCD_BACKLIGHT_PIN, brightness = (brightness + 20)%255);
}

void lcdCounter() {
  static int c = 0;
  lcd.setCursor(0, 6);
  lcd.print(++c);
}

void lcdCounter2() {
  static int c = 0;
  lcd.setCursor(50, 6);
  lcd.print(++c);
}
