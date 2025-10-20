/*
 * FLAME DETECTION SYSTEM WITH ST7789V LCD
 * by Anuprabha Bag
 * Electronics and Communication Engineering
 * 
 * Components:
 * - Arduino Uno
 * - ST7789V 2-inch TFT LCD
 * - IR Flame Sensor
 * - Buzzer
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// ==================== HARDWARE CONFIGURATION ====================
// TFT LCD Pins
#define TFT_CS    10
#define TFT_DC    9
#define TFT_RST   8

// Sensor and Buzzer Pins
const int flameSensorPin = A0;
const int buzzerPin = 7;

// Flame Detection Threshold (CALIBRATE THIS!)
int flameThreshold = 500;
int sensorValue = 0;
bool flameDetected = false;
unsigned long lastAlertTime = 0;

// Initialize ST7789 TFT
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// ==================== SETUP ====================
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println(F("=========================================="));
  Serial.println(F("     FLAME DETECTION SYSTEM"));
  Serial.println(F("     by Anuprabha Bag"));
  Serial.println(F("=========================================="));
  
  // Initialize Buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  
  // Initialize TFT LCD
  Serial.println(F("Initializing ST7789V TFT..."));
  
  // For newer Adafruit ST7789 library - no return value
  tft.init(240, 320);  // Remove the ! check
  Serial.println(F("TFT initialized!"));
  
  tft.setRotation(2); // Adjust rotation: 0,1,2,3
  tft.fillScreen(ST77XX_BLACK);
  
  // Display Welcome Screen
  displayWelcomeScreen();
  delay(2500);
  
  // Display Main Interface
  displayMainInterface();
  
  Serial.println(F("System Ready!"));
  Serial.println(F("Commands: 'c'=calibrate, 't'=test buzzer"));
  Serial.print(F("Current threshold: "));
  Serial.println(flameThreshold);
}

// ==================== MAIN LOOP ====================
void loop() {
  // Read flame sensor
  sensorValue = analogRead(flameSensorPin);
  
  // Check Serial Commands
  if (Serial.available()) {
    handleSerialCommands();
  }
  
  // Check for flame detection
  if (sensorValue < flameThreshold) {
    if (!flameDetected) {
      flameDetected = true;
      lastAlertTime = millis();
      triggerAlarm();
    }
    // Continuous alert while flame detected
    if (millis() - lastAlertTime > 1000) {
      triggerAlarm();
      lastAlertTime = millis();
    }
  } else {
    if (flameDetected) {
      flameDetected = false;
      clearAlarm();
    }
  }
  
  // Update display
  updateDisplay();
  delay(300);
}

// ==================== DISPLAY FUNCTIONS ====================
void displayWelcomeScreen() {
  tft.fillScreen(ST77XX_BLUE);
  tft.setTextColor(ST77XX_WHITE);
  
  // Title
  tft.setTextSize(3);
  tft.setCursor(40, 40);
  tft.print("FLAME");
  tft.setCursor(30, 80);
  tft.print("DETECTOR");
  
  // Project Info
  tft.setTextSize(2);
  tft.setCursor(50, 130);
  tft.print("SYSTEM");
  
  // Creator Info
  tft.setTextSize(1);
  tft.setCursor(70, 180);
  tft.print("by Anuprabha");
  tft.setCursor(85, 195);
  tft.print("Bag");
  
  // Initialization status
  tft.setCursor(60, 240);
  tft.print("Initializing...");
  
  // Draw border
  tft.drawRect(5, 5, 230, 310, ST77XX_CYAN);
}

void displayMainInterface() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Header with border
  tft.drawRect(0, 0, 240, 320, ST77XX_WHITE);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(60, 15);
  tft.print("FIRE ALERT");
  
  // Sensor Value Section
  tft.drawRect(20, 50, 200, 70, ST77XX_BLUE);
  tft.setTextSize(1);
  tft.setCursor(30, 40);
  tft.print("SENSOR VALUE:");
  
  // Status Section
  tft.drawRect(20, 140, 200, 80, ST77XX_BLUE);
  tft.setTextSize(1);
  tft.setCursor(30, 130);
  tft.print("STATUS:");
  
  // Threshold Info
  tft.setTextSize(1);
  tft.setCursor(20, 240);
  tft.print("Threshold: ");
  tft.print(flameThreshold);
  
  // Instructions
  tft.setCursor(20, 255);
  tft.print("Monitor: 'c'=calibrate");
  tft.setCursor(20, 270);
  tft.print("Safe:>");
  tft.print(flameThreshold);
  tft.print(" Fire:<");
  tft.print(flameThreshold);
}

void updateDisplay() {
  // Update Sensor Value
  tft.fillRect(30, 65, 180, 40, ST77XX_BLACK);
  tft.setTextSize(3);
  
  // Color code based on value
  if (sensorValue < flameThreshold) {
    tft.setTextColor(ST77XX_RED);
  } else if (sensorValue < flameThreshold + 100) {
    tft.setTextColor(ST77XX_YELLOW);
  } else {
    tft.setTextColor(ST77XX_GREEN);
  }
  
  tft.setCursor(80, 65);
  if (sensorValue < 1000) tft.print(" ");
  tft.print(sensorValue);
  
  // Update Status
  tft.fillRect(30, 160, 180, 50, ST77XX_BLACK);
  tft.setTextSize(2);
  
  if (flameDetected) {
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(60, 160);
    tft.print("FIRE!");
    tft.setCursor(40, 185);
    tft.print("ALERT!");
  } else {
    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(70, 160);
    tft.print("SAFE");
    tft.setCursor(50, 185);
    tft.print("CLEAR");
  }
}

// ==================== ALARM FUNCTIONS ====================
void triggerAlarm() {
  Serial.print("🔥 FIRE DETECTED! Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Threshold: ");
  Serial.println(flameThreshold);
  
  // Visual Alarm - Flash Screen
  tft.fillScreen(ST77XX_RED);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(60, 140);
  tft.print("FIRE!");
  tft.setCursor(40, 170);
  tft.print("ALERT!");
  
  // Audio Alarm - Pulsing Buzzer
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(150);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  
  // Restore display after alarm
  delay(200);
  displayMainInterface();
}

void clearAlarm() {
  Serial.print("✅ Area Safe. Sensor: ");
  Serial.println(sensorValue);
  
  // Visual Confirmation
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setCursor(70, 140);
  tft.print("SAFE");
  tft.setCursor(50, 170);
  tft.print("CLEAR");
  
  delay(300);
  displayMainInterface();
}

// ==================== SERIAL COMMANDS ====================
void handleSerialCommands() {
  char command = Serial.read();
  
  switch (command) {
    case 'c': // Calibration mode
      calibrateSensor();
      break;
      
    case 't': // Test buzzer
      testBuzzer();
      break;
      
    case 'r': // Reset alarm
      flameDetected = false;
      digitalWrite(buzzerPin, LOW);
      Serial.println("Alarm reset manually");
      break;
      
    default:
      Serial.println("Unknown command. Use: c=calibrate, t=test, r=reset");
      break;
  }
}

void calibrateSensor() {
  Serial.println("\n=== CALIBRATION MODE ===");
  Serial.println("Instructions:");
  Serial.println("1. Keep flame AWAY from sensor - note NORMAL values");
  Serial.println("2. Bring flame CLOSE to sensor - note FIRE values");
  Serial.println("3. Set threshold between these values");
  Serial.println("4. Current threshold: " + String(flameThreshold));
  Serial.println("Taking 10 samples...");
  
  tft.fillScreen(ST77XX_MAGENTA);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(40, 100);
  tft.print("CALIBRATION");
  tft.setCursor(60, 130);
  tft.print("MODE");
  
  for (int i = 0; i < 10; i++) {
    sensorValue = analogRead(flameSensorPin);
    Serial.print("Sample ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(sensorValue);
    
    // Show on TFT
    tft.fillRect(80, 170, 100, 30, ST77XX_MAGENTA);
    tft.setCursor(80, 170);
    tft.print(sensorValue);
    
    delay(1000);
  }
  
  Serial.println("=== CALIBRATION COMPLETE ===");
  Serial.print("Current threshold: ");
  Serial.println(flameThreshold);
  Serial.println("To change: modify 'flameThreshold' variable in code");
  
  delay(2000);
  displayMainInterface();
}

void testBuzzer() {
  Serial.println("Testing buzzer...");
  
  tft.fillScreen(ST77XX_ORANGE);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(60, 140);
  tft.print("BUZZER");
  tft.setCursor(70, 170);
  tft.print("TEST");
  
  // Test pattern
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  
  Serial.println("Buzzer test complete!");
  delay(1000);
  displayMainInterface();
}