// Protocol definitions for Phase 5

## Message Flow:

### WebSocket Command to Pico:
```
Browser (JSON)
  ↓
WebSocket Server
  ↓ parse JSON
Command Router
  ↓ execute handler
UART Bridge
  ↓ plain text
Pico 2
```

Example:
```json
// Browser sends
{
  "type": "command",
  "command": "GPIO",
  "args": "25 1"
}

// ESP32 sends to Pico via UART
GPIO 25 1

// Pico responds via UART
OK GPIO 25

// ESP32 sends back to browser via WebSocket
{
  "status": "ok",
  "message": "OK GPIO 25",
  "source": "pico"
}
```

### Supported Commands:

#### PING
- Browser → ESP32: `{"command":"PING"}`
- ESP32 → Pico: `PING`
- Pico → ESP32: `OK PING`
- ESP32 → Browser: `{"status":"ok","message":"OK PING"}`

#### STATUS
- Browser → ESP32: `{"command":"STATUS"}`
- ESP32 → Pico: `STATUS`
- Pico → ESP32: `OK STATUS RUNNING`
- ESP32 → Browser: `{"status":"ok","message":"OK STATUS RUNNING"}`

#### GPIO pin value
- Browser → ESP32: `{"command":"GPIO","args":"25 1"}`
- ESP32 → Pico: `GPIO 25 1`
- Pico → ESP32: `OK GPIO 25`
- ESP32 → Browser: `{"status":"ok","message":"OK GPIO 25"}`

## UART Configuration (config.h):
- Pin RX: GPIO 16
- Pin TX: GPIO 17
- Baud: 115200
- Format: 8N1 (8 bits, no parity, 1 stop bit)

## Pico 2 Configuration:
- UART0 on GPIO0 (TX) and GPIO1 (RX)
- Baud: 115200
- Connect: ESP32 TX (GPIO17) → Pico RX (GPIO1)
- Connect: ESP32 RX (GPIO16) → Pico TX (GPIO0)
