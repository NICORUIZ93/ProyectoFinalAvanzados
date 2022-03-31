
#include "DHT.h"
#include "PinNames.h"
#include "Serial.h"
#include "mbed.h"

Serial pc(PA_9, PA_10);
DigitalOut led(PC_13);
DHT sensores(PA_0, DHT22);
int main() {
  pc.baud(9600);
  while (true) {
    int err = sensores.readData();

    pc.printf("H : %.2f\n", sensores.ReadHumidity());
    ThisThread::sleep_for(1);
    pc.printf("t : %4.2f\n", sensores.ReadTemperature(CELCIUS));
    led = !led;
    pc.printf("hola\r\n");

    ThisThread::sleep_for(500);
  }
}
