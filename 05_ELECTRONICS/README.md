# ESP32 Seedball Dispenser — MAVLink Telemetry System

An ESP32-based firmware for an automated seedball dispensing mechanism integrated with MAVLink telemetry. The system controls two servo-actuated gates, monitors dispensing via IR sensors, detects jams, and reports status to a drone flight controller over UART.

---

## Repository Structure

```
esp.ino                  # Main Arduino firmware for the ESP32
LOGIC_FLOW-CHART.png     # System logic and decision flowchart
POWER_FLOW-CHART.png     # Power distribution diagram
```

---

## Hardware Overview

### Power Distribution

The system is powered by a **12V LiPo battery**, split across two independent buck converters:

| Rail | Voltage | Powers |
|------|---------|--------|
| Logic | 12V → 3.5V | ESP32 MCU, IR Sensor Array (×5) |
| Servo | 12V → 5V | Servo A (Gate 1), Servo B (Gate 2) |

### Pin Configuration

| Pin | Role |
|-----|------|
| GPIO 22 | Servo A |
| GPIO 23 | Servo B |
| GPIO 36 | IR Sensor — File A Start *(external pull-up required)* |
| GPIO 39 | IR Sensor — File A End *(external pull-up required)* |
| GPIO 34 | IR Sensor — File B Start *(external pull-up required)* |
| GPIO 35 | IR Sensor — File B End *(external pull-up required)* |
| GPIO 32 | IR Sensor — Neck *(internal pull-up)* |
| GPIO 16/17 | Serial2 RX/TX — UART command input (from Jetson/Pi) |
| GPIO 18/19 | Serial1 RX/TX — MAVLink output (to Flight Controller) |

---

## System Logic

### Initialization
On power-up, the ESP32 initializes servos to the closed position (0°), configures IR sensor pins, and starts two UART interfaces — one for incoming drop commands and one for outgoing MAVLink telemetry.

### Main Loop
Each loop cycle runs four handlers in sequence:

1. **`handleUART()`** — Listens on Serial2 for drop commands in the format `<Angle>,<Time>` from an onboard computer (Jetson/Pi). Parses and sets the target servo angle and open duration.

2. **`handleAutoTrigger()`** — Fires a test drop every 5 seconds automatically if the system is idle, useful for bench testing without an external controller.

3. **`handleDropSequence()`** — Opens the active servo gate to the target angle, monitors the neck IR sensor to confirm a ball passed through, then closes the gate after the timer expires.

4. **`handleMavlink()`** — Sends a MAVLink **HEARTBEAT** at 1 Hz during normal operation, or a **CRITICAL STATUSTEXT** alert at 0.5 Hz if a jam is detected.

### Jam Detection (`evaluateJamLogic`)
After each drop, the system evaluates whether the drop was successful:
- If the neck sensor confirmed a ball passed → **Drop successful**, return to loop.
- If IR sensors on the active file are blocked → **Jam detected**, flag set, alert broadcast via MAVLink.
- If IR sensors are clear → **File empty**, switch to the next file.
- If both files are jammed → **System disabled**, critical alert sent continuously.

---

## MAVLink Telemetry

Communication is over **Serial1 at 57600 baud** (wired UART to the flight controller).

| Condition | Message Type | Rate |
|-----------|-------------|------|
| Normal operation | `HEARTBEAT` | 1 Hz |
| Jam detected | `STATUSTEXT` (CRITICAL severity) | 0.5 Hz |

---

## Dependencies

- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) — Servo control for ESP32
- [MAVLink (ArduPilotMega)](https://github.com/ArduPilot/mavlink) — MAVLink message packing/serialization

---

## Building & Flashing

1. Install the **Arduino IDE** with ESP32 board support.
2. Install the `ESP32Servo` library via the Library Manager.
3. Place the `mavlink/` header library in your Arduino `libraries/` folder.
4. Select **ESP32 Dev Module** as the target board.
5. Set baud rate to `115200` for Serial monitor.
6. Upload `esp.ino` to the board.

---

## Troubleshooting

**Servos not moving**
Check that the 5V servo rail is powered independently. Do not power servos from the ESP32's 3.3V pin.

**IR sensors always reading LOW**
GPIO pins 34, 35, 36, and 39 are input-only and do not support internal pull-ups. External pull-up resistors (10kΩ) must be wired to these pins.

**No MAVLink messages received by flight controller**
Verify Serial1 TX (GPIO 19) is connected to the flight controller's RX pin, and that both ends are configured to **57600 baud**.

**Auto-trigger firing unexpectedly**
The auto-test trigger fires every 5 seconds by default (`testIntervalMs = 5000`). Increase this value or disable the `handleAutoTrigger()` call for production use.

---

## Future Work / Roadmap

- [ ] Add support for more than two servo files/gates
- [ ] Implement MAVLink command reception to trigger drops remotely from GCS
- [ ] Add a low-ball warning threshold based on IR sensor timing
- [ ] Store jam events and drop counts in non-volatile memory (NVS/EEPROM)
- [ ] Add WiFi/OTA firmware update support for field deployment
- [ ] Expose system state via MAVLink `NAMED_VALUE_INT` for GCS dashboard display
