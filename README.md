# Flipper Zero WiFi Dev Board Web Serial Bridge

## Project Overview

This is a reusable embedded project that creates firmware for the ESP32-S2 chip on the Flipper Zero WiFi Dev Board. It establishes a configurable WiFi web interface and communicates with a Raspberry Pi Pico 2 over UART.

### Architecture

```
Laptop/Phone Browser
        |
        | WiFi
        |
ESP32-S2 Flipper WiFi Dev Board
        |
        | UART serial
        |
Raspberry Pi Pico 2
```

## Requirements

### Hardware
- ESP32-S2 SAOLA-1 board (Flipper Zero WiFi Dev Board)
- Raspberry Pi Pico 2
- USB cable for flashing

### Software
- PlatformIO CLI or IDE
- Python 3.7+
- esp-idf tools
- ARM GCC toolchain for Pico 2

## Build Instructions

### ESP32-S2 Firmware

```bash
cd esp32
pio run
```

### Pico 2 Firmware

```bash
cd pico2
mkdir build
cd build
cmake ..
make
```

## Project Phases

### Phase 1: Repository & Build Setup ✅
- Repository structure
- PlatformIO configuration
- GitHub Actions workflow
- Minimal ESP32 firmware skeleton

### Phase 2: WiFi AP
- WiFi access point mode
- SSID and password configuration

### Phase 3: Web Server & LittleFS
- Static file hosting
- Web interface

### Phase 4: WebSocket Communication
- Real-time browser <-> ESP32 communication
- JSON protocol

### Phase 5: UART Bridge
- Serial communication with Pico 2
- Command routing

### Phase 6: Pico 2 Firmware
- Serial command parser
- GPIO and status commands

## Configuration

Edit `esp32/include/config.h` to configure WiFi, UART, and server settings.

## Communication Protocol

**Browser -> ESP32:** JSON commands
**ESP32 -> Pico 2:** Plain text commands
**Pico 2 -> ESP32:** Plain text responses
**ESP32 -> Browser:** JSON responses

## License

MIT