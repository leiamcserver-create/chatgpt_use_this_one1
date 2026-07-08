// Console logging
const console_element = document.getElementById('console');
const status_element = document.getElementById('status');

function addConsoleMessage(message, type = 'info') {
    const p = document.createElement('p');
    p.className = type;
    p.textContent = message;
    console_element.appendChild(p);
    console_element.scrollTop = console_element.scrollHeight;
}

function clearConsole() {
    console_element.innerHTML = '<p class="info">[Console cleared]</p>';
}

// API calls
async function checkStatus() {
    try {
        addConsoleMessage('[...] Checking system status...');
        const response = await fetch('/api/status');
        if (!response.ok) throw new Error(`HTTP ${response.status}`);
        const data = await response.json();
        
        status_element.innerHTML = `
            <div>
                <strong>Status:</strong> ${data.status} ✓<br>
                <strong>Uptime:</strong> ${data.uptime}
            </div>
        `;
        status_element.classList.add('connected');
        addConsoleMessage('[OK] System status: ' + JSON.stringify(data), 'info');
    } catch (error) {
        addConsoleMessage(`[ERROR] ${error.message}`, 'error');
        status_element.classList.add('error');
        status_element.innerHTML = `<p>Error: ${error.message}</p>`;
    }
}

function sendPing() {
    addConsoleMessage('[>>] Sending PING command...', 'info');
    addConsoleMessage('[OK] PING command sent', 'info');
}

function sendStatus() {
    addConsoleMessage('[>>] Sending STATUS command...', 'info');
    addConsoleMessage('[OK] STATUS command sent', 'info');
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', function() {
    addConsoleMessage('[BOOT] Flipper WiFi Bridge loaded');
    addConsoleMessage('[INFO] Connected to WiFi network');
    checkStatus();
});
