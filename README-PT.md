# esp32blink

Firmware para ESP32 que pisca o LED embutido com saída de diagnóstico serial para verificar placas recém-adquiridas.

## Destaques

- Auto-teste de três flashes no GPIO 2 no boot, depois um heartbeat de pulso duplo
- Exibe chip, tamanho da flash, MAC, heap e motivo do reset a 115200 baud
- Repete uptime e heap livre a cada 10 segundos para um hang ficar óbvio
- Configura porta de upload e monitor via `.env` sem editar o `platformio.ini`
- Detecta a porta USB da placa com `make detect-port`
- Encapsula o PlatformIO em `make flash`, `make monitor` e `make erase`

## Pré-requisitos

- **PlatformIO** — instale com `pipx install platformio` ou `make install-pio`

## Instalação

```bash
git clone git@github.com:carlosrabelo/esp32blink.git
cd esp32blink
cp .env.example .env
make deps     # instala a plataforma ESP32 e o toolchain
```

## Uso

```bash
make flash    # compila e faz upload
make monitor  # abre serial a 115200 baud
```

Saída serial esperada:

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

## Configuração

Copie `.env.example` para `.env` e ajuste a porta se a detecção automática não funcionar:

```bash
UPLOAD_PORT=/dev/ttyUSB0
MONITOR_PORT=/dev/ttyUSB0
MONITOR_SPEED=115200
UPLOAD_SPEED=921600
```

Para alterar o pino do LED, edite `LED_PIN` em `src/main.cpp`:

```cpp
const int LED_PIN = 2; // número do GPIO
```

## Desenvolvimento

```bash
make build        # compila o firmware
make upload       # faz upload para o dispositivo
make flash        # compila e faz upload
make monitor      # abre o monitor serial
make clean        # remove artefatos de build
make deps         # instala pacotes PlatformIO
make check        # executa análise estática
make test         # executa testes unitários
make erase        # apaga a flash do dispositivo
make detect-port  # detecta a porta USB e grava no .env
make check-pio    # verifica se o PlatformIO está instalado
make install-pio  # instala o PlatformIO
```

## Licença

Este projeto está licenciado sob a GNU General Public License v2.0 — veja o arquivo [LICENSE](LICENSE) para detalhes.
