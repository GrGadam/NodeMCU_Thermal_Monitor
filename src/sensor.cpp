#include "sensor.hpp"

int32_t  temperature, humidity = 0;
DHT dht(5, DHT11);
uint32_t s = 0;
char *timestring = nullptr;
char *str = nullptr;

void update_vars() {
    temperature = static_cast<int>(dht.readTemperature(false, true));
    humidity = static_cast<int>(dht.readHumidity());
}