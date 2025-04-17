#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define LED_PIN 2

Adafruit_BME680 bme;

TaskHandle_t BME680TaskHandle = NULL;
TaskHandle_t LEDTaskHandle = NULL;

void BME680Task(void *pvParameters);
void LEDTask(void *pvParameters);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  while (!Serial);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME680 sensor! Check wiring.");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);

  xTaskCreate(
      BME680Task,
      "BME680 Sensor Task Active",
      4096,
      NULL,
      1,
      &BME680TaskHandle);

  xTaskCreate(
      LEDTask,
      "LED Task Active",
      2048,
      NULL,
      2,
      &LEDTaskHandle);
}

void loop() {
  // Empty loop 
}

void BME680Task(void *pvParameters) {
  while (1) {
    unsigned long endTime = bme.beginReading();

    if (endTime == 0) {
      Serial.println("Failed to start reading");
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }

    vTaskDelay(pdMS_TO_TICKS(100));

    if (!bme.endReading()) {
      Serial.println("Failed to complete reading");
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }

    Serial.println("BME Reading Started");
    Serial.printf("Temperature: %.2f °C\n", bme.temperature);
    Serial.printf("Humidity: %.2f %%\n", bme.humidity);
    Serial.printf("Pressure: %.2f hPa\n", bme.pressure / 100.0);
    Serial.printf("Gas Resistance: %.2f kohm\n", bme.gas_resistance / 1000.0);
    Serial.printf("Approximate Altitude: %.2f m\n", bme.readAltitude(SEALEVELPRESSURE_HPA));

    vTaskDelay(pdMS_TO_TICKS(2000));

//    vTaskResume(LEDTaskHandle);
//    vTaskSuspend(NULL);
  }
}

void LEDTask(void *pvParameters) {
  while (1) {
    Serial.println("LED Blink Started");
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(2000));
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(2000));

//    vTaskResume(BME680TaskHandle);
//    vTaskSuspend(NULL);
  }
}
