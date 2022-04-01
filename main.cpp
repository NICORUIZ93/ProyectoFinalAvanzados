
#include "DHT.h"
#include "I2CSlave.h"
#include "PinNames.h"
#include "Serial.h"
#include "mbed.h"
#include <cstring>
#include <string>

Serial pc(PA_9, PA_10);
DigitalOut led(PC_13);
DHT sensores(PA_0, DHT22);
I2CSlave slave(PB_9, PB_8);

int main() {

  pc.baud(9600);
  slave.address(0x30);
  char buf[2];
  char msg[] = "12345";
  char temperaura[6];
  char humedad[6];

  while (true) {

    int err = sensores.readData();

    sprintf(humedad, "%.1f", sensores.ReadHumidity());
    sprintf(temperaura, "%.1f", sensores.ReadTemperature(CELCIUS));
    pc.printf("H : %.2f ; t : %4.2f\n", sensores.ReadHumidity(),
              sensores.ReadTemperature(CELCIUS));

    strcat(humedad, ":");
    strcat(humedad, temperaura);
    pc.printf("%s\n", humedad);
    led = !led;

    int i = slave.receive();

    switch (i) {
    case I2CSlave::ReadAddressed:

      slave.write(humedad, strlen(humedad)); // Includes null char

      break;
    case I2CSlave::WriteGeneral:
      slave.read(buf, 10);
      pc.printf("Read G: %s\n", buf);
      break;
    case I2CSlave::WriteAddressed:
      slave.read(buf, 10);
      pc.printf("Read A: %s\n", buf);
      break;
    }

    ThisThread::sleep_for(1);
  }
}
