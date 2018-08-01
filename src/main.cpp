#include <Arduino.h>
#include <esp_system.h>

const int LED_PIN = 2;

static const char *resetReasonName(esp_reset_reason_t reason) {
    switch (reason) {
        case ESP_RST_POWERON:   return "power-on";
        case ESP_RST_EXT:       return "external pin";
        case ESP_RST_SW:        return "software";
        case ESP_RST_PANIC:     return "panic";
        case ESP_RST_INT_WDT:   return "interrupt watchdog";
        case ESP_RST_TASK_WDT:  return "task watchdog";
        case ESP_RST_WDT:       return "watchdog";
        case ESP_RST_DEEPSLEEP: return "deep-sleep";
        case ESP_RST_BROWNOUT:  return "brownout";
        case ESP_RST_SDIO:      return "sdio";
        default:                return "unknown";
    }
}

static void printMac() {
    const uint64_t mac = ESP.getEfuseMac();
    Serial.printf("  mac      %02X:%02X:%02X:%02X:%02X:%02X\n",
                  (uint8_t)(mac >> 0),
                  (uint8_t)(mac >> 8),
                  (uint8_t)(mac >> 16),
                  (uint8_t)(mac >> 24),
                  (uint8_t)(mac >> 32),
                  (uint8_t)(mac >> 40));
}

static void printIdentity() {
    Serial.println();
    Serial.println("esp32blink — board check");
    Serial.printf("  chip     %s rev %d, %u core(s) @ %u MHz\n",
                  ESP.getChipModel(),
                  ESP.getChipRevision(),
                  ESP.getChipCores(),
                  ESP.getCpuFreqMHz());
    Serial.printf("  flash    %u KB\n", ESP.getFlashChipSize() / 1024);
    Serial.printf("  heap     %u / %u bytes free\n",
                  ESP.getFreeHeap(),
                  ESP.getHeapSize());
    printMac();
    Serial.printf("  reset    %s\n", resetReasonName(esp_reset_reason()));
}

void setup() {
    Serial.begin(115200);
    delay(50);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    printIdentity();
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}
