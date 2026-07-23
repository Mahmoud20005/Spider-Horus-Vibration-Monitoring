#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// ==============================
// Network Configuration
// ==============================
const char* ssid = "MMG";
const char* password = "mmg12345";
const char* laptop_IP = "192.168.137.1";   // Replace with your computer's IP address
const int udpPort = 12345;
WiFiUDP udp;

// ==============================
// Hardware Configuration
// ==============================
const int MPU = 0x68;
const int RED_LED_PIN = 18;
const int BUZZER_PIN = 19;

// Vibration threshold (G)
const float VIBRATION_THRESHOLD = 0.5;

// Variable used to store the calibrated gravity reference
float baselineG = 0.0;

void setup() {

  // Disable brownout detector to avoid unexpected resets
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  Wire.begin();

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(RED_LED_PIN, HIGH);
    delay(100);
    digitalWrite(RED_LED_PIN, LOW);
    delay(100);
    Serial.print(".");
  }

  // =====================================
  // Automatic sensor calibration
  // The sensor must remain stationary
  // =====================================
  Serial.println("\nCalibrating sensor...");

  float sumG = 0;

  for (int i = 0; i < 100; i++) {

    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);

    int16_t AcX = Wire.read() << 8 | Wire.read();
    int16_t AcY = Wire.read() << 8 | Wire.read();
    int16_t AcZ = Wire.read() << 8 | Wire.read();

    float gX = AcX / 16384.0;
    float gY = AcY / 16384.0;
    float gZ = AcZ / 16384.0;

    sumG += sqrt(sq(gX) + sq(gY) + sq(gZ));

    delay(10);
  }

  // Store the average gravity value as a reference
  baselineG = sumG / 100.0;

  Serial.print("Calibration completed. Baseline = ");
  Serial.println(baselineG);

  // Startup indication
  for (int i = 0; i < 3; i++) {

    tone(BUZZER_PIN, 2000);

    digitalWrite(RED_LED_PIN, HIGH);

    delay(100);

    noTone(BUZZER_PIN);

    digitalWrite(RED_LED_PIN, LOW);

    delay(100);
  }

  Serial.println("[SYSTEM READY] Spider Horus is running.");
}

void loop() {

  // Read accelerometer data
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  // Convert raw data to acceleration (G)
  float gX = AcX / 16384.0;
  float gY = AcY / 16384.0;
  float gZ = AcZ / 16384.0;

  // Calculate the total acceleration magnitude
  float totalG = sqrt(sq(gX) + sq(gY) + sq(gZ));

  // Remove the gravity component to obtain vibration only
  float pureVibration = abs(totalG - baselineG);

  // Ignore very small vibrations (noise filtering)
  if (pureVibration < 0.015)
    pureVibration = 0.0;

  // Activate the alarm if the threshold is exceeded
  if (pureVibration > VIBRATION_THRESHOLD) {

    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);

  } else {

    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // Send vibration data to the Python application via UDP
  udp.beginPacket(laptop_IP, udpPort);
  udp.print(pureVibration);
  udp.endPacket();

  // Sampling rate: approximately 100 Hz
  delay(10);
}
