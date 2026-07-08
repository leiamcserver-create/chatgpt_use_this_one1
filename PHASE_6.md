## Phase 6: Pico 2 Firmware - Complete Serial Bridge

Phase 6 completes the Pico 2 side with a full serial command parser, GPIO control, and response handling. This finalizes the bidirectional bridge from browser to GPIO control.

### Features Implemented:

✅ **Serial Protocol Parser**
- Character-by-character buffering
- Line-based command detection
- Whitespace trimming
- Command parsing with sscanf
- Error handling and validation

✅ **GPIO Control**
- Dynamic GPIO initialization
- GPIO state tracking
- GPIO set command: `GPIO pin value`
- GPIO get command: `GETGPIO pin`
- Pin range validation (0-28)
- State persistence

✅ **Supported Commands**

| Command | Format | Response | Example |
|---------|--------|----------|---------|
| PING | `PING` | `OK PING` | Connectivity test |
| STATUS | `STATUS` | `OK STATUS RUNNING` | System status |
| GPIO | `GPIO pin value` | `OK GPIO pin` | Set GPIO pin 0-28 to HIGH/LOW |
| GETGPIO | `GETGPIO pin` | `OK GETGPIO pin state` | Query GPIO pin state (-1=uninitialized) |

✅ **Error Handling**
- Invalid GPIO pin detection
- Command format validation
- Unknown command response
- Parse error handling

### UART Hardware Connection:

```
Raspberry Pi Pico 2        ESP32-S2
─────────────────          ────────
GPIO0 (UART0 TX) ──────→  GPIO16 (RX)
GPIO1 (UART0 RX) ←──────  GPIO17 (TX)
GND              ──────→  GND
```

### Building Pico 2 Firmware:

**Prerequisites:**
- Pico SDK installed and PICO_SDK_PATH set
- ARM GCC toolchain
- CMake 3.12+

**Build:**
```bash
cd pico2
mkdir -p build
cd build
cmake ..
make
```

**Output:**
```
pico2/build/pico_firmware.uf2     # Flashed via USB Mass Storage
pico2/build/pico_firmware.elf     # Debug symbols
pico2/build/pico_firmware.hex     # Hex format
```

**Flash to Pico 2:**
1. Connect Pico 2 to USB while holding BOOTSEL button
2. Copy `.uf2` file to mass storage drive (RPI-RP2)
3. Pico will reboot and start firmware

### Testing GPIO Control:

**Via Web UI:**
1. Connect to WiFi: `FlipperWiFi`
2. Open `http://192.168.4.1`
3. Send command: `{"command":"GPIO","args":"25 1"}`
4. Browser console shows: `OK GPIO 25`
5. LED on Pico GPIO 25 lights up

**Via Serial Monitor:**
```bash
# Monitor Pico debug output
picocom /dev/ttyACM0 115200

# Send command to Pico via ESP32
# Type in browser console or use custom command input
```

### Message Flow Examples:

**Complete Flow: Browser → ESP32 → Pico → Response**

```
1. Browser sends WebSocket JSON:
   {"command":"GPIO","args":"25 1"}

2. ESP32 receives and parses JSON
   [WebSocket] Received: {"command":"GPIO","args":"25 1"}

3. Command router calls gpio_handler("25 1")
   [CMD] GPIO handler called

4. Handler sends UART command:
   [Serial Bridge] TX: GPIO 25 1

5. Pico receives character by character
   [Protocol] Received: GPIO 25 1

6. Pico parses and sets GPIO
   [GPIO] Initialized pin 25 as output
   [GPIO] Set pin 25 to 1

7. Pico sends response via UART
   [Serial] Output: OK GPIO 25

8. ESP32 receives response
   [Serial Bridge] RX: OK GPIO 25

9. ESP32 formats as JSON and sends via WebSocket
   [Router] Sending to WebSocket: {"status":"ok","message":"OK GPIO 25","source":"pico"}

10. Browser receives and displays
    [<<] {"status":"ok","message":"OK GPIO 25","source":"pico"}
```

### Complete Project Status:

```
Phase 1: Repository & Build Setup ✅
Phase 2: WiFi AP Mode ✅
Phase 3: Web Server & LittleFS ✅
Phase 4: WebSocket Communication ✅
Phase 5: UART Bridge Integration ✅
Phase 6: Pico 2 Firmware ✅
```

### Full Architecture Overview:

```
┌─────────────────────┐
│  Browser/Phone      │
│  (Web UI)           │
└──────────┬──────────┘
           │ WiFi (JSON)
           ↓
┌─────────────────────────────────┐
│  ESP32-S2 Flipper WiFi Board    │
├─────────────────────────────────┤
│ • WiFi AP (192.168.4.1)         │
│ • Web Server (Port 80)          │
│ • WebSocket (Port 81)           │
│ • Command Router                │
│ • Serial Bridge (UART1)         │
└──────────┬──────────────────────┘
           │ UART Serial (Plain Text)
           ↓
┌─────────────────────┐
│ Raspberry Pi Pico 2 │
├─────────────────────┤
│ • Serial Parser     │
│ • GPIO Controller   │
│ • State Tracking    │
└─────────────────────┘
```

### Repository Structure:
```
/
├── .github/workflows/build.yml
├── esp32/
│   ├── platformio.ini
│   ├── partitions.csv
│   ├── include/config.h
│   ├── src/
│   │   ├── main.cpp
│   │   ├── wifi.cpp/h
│   │   ├── webserver.cpp/h
│   │   ├── websocket.cpp/h
│   │   ├── serial_bridge.cpp/h
│   │   ├── command_router.cpp/h
│   │   └── (placeholders)
│   └── data/
│       ├── index.html
│       ├── app.js
│       └── style.css
├── pico2/
│   ├── CMakeLists.txt
│   └── src/
│       ├── main.cpp (GPIO tracking)
│       └── protocol.cpp/h (Full serial parser + GPIO)
├── README.md
├── PHASE_*.md (documentation for each phase)
└── UART_PROTOCOL.md
```

### Next Steps / Future Enhancements:

1. **Add more GPIO features:**
   - PWM control
   - Input pin reading
   - Interrupt handling

2. **Extend command set:**
   - ADC reading
   - Timer control
   - Memory status

3. **Advanced features:**
   - Command queueing
   - Response timeouts
   - State synchronization

4. **Testing & Hardening:**
   - Unit tests for command parsing
   - Stress testing with rapid commands
   - Recovery from disconnects

### Build Status: ✅ COMPLETE

All 6 phases successfully implemented. Full bidirectional bridge from browser to GPIO control via WiFi, WebSocket, and UART serial communication.
