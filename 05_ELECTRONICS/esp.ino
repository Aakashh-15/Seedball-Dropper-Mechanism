// =========================================================================
// INTEGRATED SEEDBALL DISPENSER & MAVLINK TELEMETRY SYSTEM (UART/WIRED VERSION)
// =========================================================================

#include <ESP32Servo.h>
#include "mavlink/ardupilotmega/mavlink.h" 

// --- MAVLINK CONFIGURATION ---
const uint8_t SYSTEM_ID = 1;     
const uint8_t COMPONENT_ID = 1;  
unsigned long lastMavlinkTime = 0;

// --- ORIGINAL HARDWARE PIN CONFIGURATION ---
const int SERVO_A_PIN = 22;
const int SERVO_B_PIN = 23;

// ORIGINAL PINS Restored (Input-Only, REQUIRES EXTERNAL PULL-UP RESISTORS)
const int IR_A_START = 36; 
const int IR_A_END   = 39; 
const int IR_B_START = 34; 
const int IR_B_END   = 35; 
const int IR_NECK    = 32; // This pin DOES support internal pull-ups

// --- SERIAL PIN CONFIGURATION ---
// Serial2 is used for incoming drop commands (from Jetson/Pi)
const int CMD_RX_PIN = 16;
const int CMD_TX_PIN = 17;

// Serial1 is used for outgoing MAVLink telemetry (to Flight Controller)
const int MAVLINK_RX_PIN = 18;
const int MAVLINK_TX_PIN = 19;

Servo servoA;
Servo servoB;

// --- SYSTEM STATE VARIABLES ---
int activeFile = 1;
int targetAngle = 15;
unsigned long openTimeMs = 1000;

unsigned long dropStartTime = 0;
bool isDropping = false;
bool dropCommandReceived = false;
bool dropConfirmed = false;

unsigned long lastTestTrigger = 0;
const unsigned long testIntervalMs = 5000;

// Jamming State Flags
bool isSystemJammed = false;
String jamAlertMessage = "";

void setup() {
  // USB Debugging
  Serial.begin(115200);
  
  // UART for incoming drop commands (from onboard computer)
  Serial2.begin(115200, SERIAL_8N1, CMD_RX_PIN, CMD_TX_PIN);

  // UART for outgoing MAVLink (to Drone Flight Controller)
  Serial1.begin(57600, SERIAL_8N1, MAVLINK_RX_PIN, MAVLINK_TX_PIN);

  // 1. Initialize Servos
  servoA.attach(SERVO_A_PIN);
  servoB.attach(SERVO_B_PIN);
  servoA.write(0);
  servoB.write(0);

  // 2. Initialize Original IR Pins 
  // NOTE: 34, 35, 36, 39 use standard INPUT. You must wire external resistors!
  pinMode(IR_A_START, INPUT);
  pinMode(IR_A_END, INPUT);
  pinMode(IR_B_START, INPUT);
  pinMode(IR_B_END, INPUT);
  pinMode(IR_NECK, INPUT_PULLUP); // 32 can safely use internal

  Serial.println("System Ready. UART MAVLink Active (57600 baud).");
}

void loop() {
  handleUART();
  handleAutoTrigger();
  handleDropSequence();
  handleMavlink();
}

// ==========================================
// LOGIC FUNCTIONS
// ==========================================

void handleAutoTrigger() {
  if (millis() - lastTestTrigger >= testIntervalMs && !isDropping) {
    lastTestTrigger = millis();
    dropCommandReceived = true;
    Serial.println("\n--- AUTO TEST TRIGGER ---");
  }
}

void handleUART() {
  if (Serial2.available()) {
    String input = Serial2.readStringUntil('\n');
    int commaIndex = input.indexOf(',');
    if (commaIndex != -1 && !isDropping) {
      targetAngle = input.substring(0, commaIndex).toInt();
      openTimeMs = input.substring(commaIndex + 1).toInt();
      dropCommandReceived = true; 
      lastTestTrigger = millis(); 
      
      Serial.print("UART Command Received! New Angle: ");
      Serial.print(targetAngle);
      Serial.println(" degrees.");
    }
  }
}

void handleDropSequence() {
  unsigned long currentMillis = millis();

  if (dropCommandReceived && !isDropping) {
    isDropping = true;
    dropCommandReceived = false;
    dropConfirmed = false;
    dropStartTime = currentMillis;

    if (activeFile == 1) {
      servoA.write(targetAngle);
      Serial.print("Servo A opening to ");
    } else {
      servoB.write(targetAngle);
      Serial.print("Servo B opening to ");
    }
    Serial.println(targetAngle);
  }

  if (isDropping) {
    if (digitalRead(IR_NECK) == LOW) {
      dropConfirmed = true;
    }
    if (currentMillis - dropStartTime >= openTimeMs) {
      servoA.write(0); 
      servoB.write(0); 
      isDropping = false;
      Serial.println("Gate Closed.");
      
      evaluateJamLogic();
    }
  }
}

void evaluateJamLogic() {
  if (dropConfirmed) {
    Serial.println("Status: Drop successful.");
    return;
  }

  if (activeFile == 1) {
    if (digitalRead(IR_A_END) == LOW || digitalRead(IR_A_START) == LOW) {
      Serial.println("FAULT: File A Jammed. Switching to File B.");
      activeFile = 2;
      isSystemJammed = true;
      jamAlertMessage = "WARNING: FILE A JAMMED";
    } else {
      Serial.println("STATUS: File A Empty. Switching to File B.");
      activeFile = 2;
    }
  }
  else if (activeFile == 2) {
    if (digitalRead(IR_B_END) == LOW || digitalRead(IR_B_START) == LOW) {
      Serial.println("CRITICAL FAULT: File B Jammed. Module disabled.");
      isSystemJammed = true;
      jamAlertMessage = "CRITICAL: FILE B JAMMED";
    } else {
      Serial.println("STATUS: Module completely empty.");
    }
  }
}

// ==========================================
// MAVLINK TELEMETRY FUNCTIONS (UART VERSION)
// ==========================================

void handleMavlink() {
  if (isSystemJammed) {
    // Broadcast jamming alert every 2 seconds via UART
    if (millis() - lastMavlinkTime > 2000) {
      send_jamming_alert(jamAlertMessage.c_str());
      lastMavlinkTime = millis();
      Serial.println("MAVLink Sent via Wire: " + jamAlertMessage); 
    }
  } else {
    // Broadcast normal heartbeat every 1 second via UART
    if (millis() - lastMavlinkTime > 1000) {
      send_heartbeat();
      lastMavlinkTime = millis();
    }
  }
}

void send_jamming_alert(const char* alertText) {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_statustext_pack(SYSTEM_ID, COMPONENT_ID, &msg, MAV_SEVERITY_CRITICAL, alertText);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the payload down the physical wire
  Serial1.write(buf, len);
}

void send_heartbeat() {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_heartbeat_pack(SYSTEM_ID, COMPONENT_ID, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_PX4, MAV_MODE_FLAG_SAFETY_ARMED, 0, MAV_STATE_ACTIVE);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the payload down the physical wire
  Serial1.write(buf, len);
}