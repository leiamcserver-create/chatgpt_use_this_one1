#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>

void wifi_init();
void wifi_stop();
bool wifi_is_ready();
uint8_t wifi_get_station_count();

#endif // WIFI_H
