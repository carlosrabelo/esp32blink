# esp32blink

ESP32 firmware that blinks the built-in LED with serial diagnostic output for verifying newly purchased boards.

## Highlights

- Three-flash GPIO 2 self-test on boot, then a double-pulse heartbeat
- Prints chip, flash size, MAC, heap, and reset reason at 115200 baud
- Repeats uptime and free heap every 10 seconds so a hung board is obvious
- Configures upload and monitor port from `.env` without editing `platformio.ini`
- Auto-detects the board USB port with `make detect-port`
- Wraps PlatformIO behind `make flash`, `make monitor`, and `make erase`

## Prerequisites

- **PlatformIO** — install with `pipx install platformio` or `make install-pio`

## Installation

```bash
git clone git@github.com:carlosrabelo/esp32blink.git
cd esp32blink
cp .env.example .env
make deps     # install ESP32 platform and toolchain
```

## Usage

```bash
make flash    # compile and upload
make monitor  # open serial at 115200 baud
```

Expected serial output:

```
esp32blink — board check
  chip     ESP32 rev 1, 2 core(s) @ 240 MHz
  flash    4096 KB
  heap     294760 / 327212 bytes free
  mac      AA:BB:CC:DD:EE:FF
  reset    power-on
  led      GPIO 2 self-test done, heartbeat running

up 10s  heap 294000  gpio2 heartbeat
```

## Configuration

Copy `.env.example` to `.env` and adjust the port if auto-detection does not work:

```bash
UPLOAD_PORT=/dev/ttyUSB0
MONITOR_PORT=/dev/ttyUSB0
MONITOR_SPEED=115200
UPLOAD_SPEED=921600
```

To change the LED pin, edit `LED_PIN` in `src/main.cpp`:

```cpp
const int LED_PIN = 2; // GPIO number
```

## Development

```bash
make build        # compile firmware
make upload       # upload to device
make flash        # compile and upload
make monitor      # open serial monitor
make clean        # remove build artifacts
make deps         # install PlatformIO packages
make check        # run static analysis
make test         # run unit tests
make erase        # erase device flash
make detect-port  # auto-detect USB port and save to .env
make check-pio    # verify PlatformIO is installed
make install-pio  # install PlatformIO
```

## License

This project is licensed under the GNU General Public License v2.0 — see [LICENSE](LICENSE) for details.
