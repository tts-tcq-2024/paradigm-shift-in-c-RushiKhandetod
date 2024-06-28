#include <stdio.h>
#include <assert.h>

typedef enum {
  NORMAL,
  LOW,
  HIGH
} RangeStatus;

typedef struct {
  RangeStatus temperature;
  RangeStatus soc;
  RangeStatus chargeRate;
} BatteryStatus;

RangeStatus checkRange(float value, float lowerLimit, float upperLimit) {
  if (value < lowerLimit) {
    return LOW;
  }
  if (value > upperLimit) {
    return HIGH;
  }
  return NORMAL;
}

BatteryStatus batteryStatus(float temperature, float soc, float chargeRate) {
  BatteryStatus status;
  status.temperature = checkRange(temperature, 0, 45);
  status.soc = checkRange(soc, 20, 80);
  status.chargeRate = checkRange(chargeRate, 0, 0.8);
  return status;
}

void printStatus(const char* parameter, RangeStatus status) {
  switch (status) {
    case LOW:
      printf("%s is too low!\n", parameter);
      break;
    case HIGH:
      printf("%s is too high!\n", parameter);
      break;
    default:
      break;
  }
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  BatteryStatus status = batteryStatus(temperature, soc, chargeRate);
  
  int result = 1;
  if (status.temperature != NORMAL) {
    printStatus("Temperature", status.temperature);
    result = 0;
  }
  if (status.soc != NORMAL) {
    printStatus("State of Charge", status.soc);
    result = 0;
  }
  if (status.chargeRate != NORMAL) {
    printStatus("Charge Rate", status.chargeRate);
    result = 0;
  }

  return result;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(!batteryIsOk(-5, 50, 0.5));
  assert(!batteryIsOk(25, 15, 0.5));
  assert(!batteryIsOk(25, 50, 1.0));
  printf("All tests passed.\n");
  return 0;
}
