## Phase 4: WebSocket Real-time Communication

Phase 4 adds bidirectional WebSocket communication for real-time command execution between the browser and ESP32.

### Features Implemented:

✅ **WebSocket Server (WebSocketsServer library)**
- Runs on port 81
- Handles multiple client connections
- JSON command protocol
- Automatic client connection/disconnection handling
- Welcome message on connect

✅ **JSON Command Protocol**
```json
// Browser → ESP32
{
  "type": "command",
  "command": "PING",
  "args": ""
}

// ESP32 → Browser
{
  "status": "ok",
  "command": "PING",
  "message": "Command executed"
}
```

✅ **Web UI Enhancements**
- WebSocket connection indicator (green/red dot)
- Real-time status updates
- Command buttons (PING, STATUS)
- Custom command input
- Auto-reconnect on disconnect
- Color-coded console messages
- Live console output

✅ **Integration**
- WebSocket runs in main loop
- Command router handles JSON commands
- Clean separation of concerns
- No blocking operations

### Communication Flow:

```
Browser (JavaScript WebSocket Client)
         ↓ (JSON via ws://192.168.4.1:81)
ESP32 (WebSocketsServer)
         ↓ (Command Router)
Registered Command Handler
         ↓ (executes handler)
Response sent back via JSON
         ↓
Browser console updates
```

### Building & Testing Phase 4:

1. **Build firmware:**
   ```bash
   cd esp32
   pio run
   ```

2. **Flash:**
   ```bash
   pio run -t uploadfs      # Flash LittleFS
   pio run -t upload        # Flash firmware
   pio device monitor -p /dev/ttyUSB0
   ```

3. **Access web UI:**
   - WiFi: `FlipperWiFi` / `flipper123`
   - URL: `http://192.168.4.1`
   - WebSocket connects automatically
   - Click PING/STATUS buttons to send commands

### Expected Console Output:
```
[WebSocket] Server on port 81
[WebSocket] Connection URL: ws://192.168.4.1:81
[WebSocket] Client #0 connected from 192.168.4.x
[WebSocket] Received from #0: {"type":"command","command":"PING","args":""}
[WebSocket] Command: PING
[CMD] PING executed
```

### Browser Console Output:
```
[BOOT] Flipper WiFi Bridge loaded
[INFO] Connected to WiFi network
[...] Checking system status...
[...] Connecting to WebSocket...
[OK] WebSocket connected!
[>>] Sending: PING
[<<] {"status":"ok","command":"PING","message":"Command executed"}
```

### Build Status:
- ✅ Compiles without errors
- ✅ WebSocket integration
- ✅ JSON command protocol
- ✅ Real-time communication
- ✅ Auto-reconnect on disconnect
- ✅ Modular design maintained
- ✅ Ready for Phase 5

### Repository Structure:
```
esp32/
├── src/
│   ├── websocket.cpp/h     # WebSocket server
│   ├── main.cpp            # Integrated with websocket_handle()
│   └── ...
├── data/
│   ├── app.js              # WebSocket client with auto-reconnect
│   ├── index.html          # Updated UI with WS indicator
│   └── style.css           # Updated styles
└── platformio.ini          # Already has WebSocketsServer
```

### Next: Phase 5 - UART Bridge
Integration of serial communication with Pico 2 via UART. Commands received via WebSocket will be forwarded to Pico 2 over UART and responses will be sent back through WebSocket.

Connection will be: Browser → ESP32 WebSocket → UART → Pico 2 → UART → ESP32 WebSocket → Browser
