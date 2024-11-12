#include <Arduino.h>
#include <ZMPT101B.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "EmonLib.h"
#include <driver/adc.h>

#define ADC_INPUT 34
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

EnergyMonitor emon1;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ZMPT101B zmpt101b(27); // Connect ZMPT101B signal pin to GPIO 27

unsigned long lastMeasurement = 0;

void setup() {
    Serial.begin(115200);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    analogReadResolution(10);

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.display();

    display.setCursor(0, 0);
    display.println("Energy monitor!");
    display.display();
    delay(1000);

    // Initialize current sensor
    emon1.current(ADC_INPUT, 30); // Calibration for current sensor
}

float calculateVoltageRMS() {
    int numSamples = 1000;
    float sumOfSquares = 0.0;

    for (int i = 0; i < numSamples; i++) {
        float voltageSample = zmpt101b.getVoltageDC(); // Using getVoltageDC as RMS replacement
        sumOfSquares += voltageSample * voltageSample;
        delayMicroseconds(1000); // Sample delay to mimic AC signal
    }

    float meanOfSquares = sumOfSquares / numSamples;
    return sqrt(meanOfSquares); // RMS voltage
}

void loop() {
    float voltageRMS = calculateVoltageRMS();
    double current = 0;
    unsigned long currentMillis = millis();

    Serial.print("Voltage RMS: ");
    Serial.print(voltageRMS, 2);
    Serial.println(" V");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Voltage:");
    display.print(voltageRMS, 2);
    display.println(" V");

    // Measure current every 100 ms
    if (currentMillis - lastMeasurement > 100) {
        current = emon1.calcIrms(1480); // Calculate RMS current
        Serial.print("Current RMS: ");
        Serial.print(current, 2);
        Serial.println(" A");
        lastMeasurement = millis();
    }

    display.setTextSize(2);
    display.println("Current:");
    display.print(current, 2);
    display.println(" A");
    display.display();

    delay(100);
}