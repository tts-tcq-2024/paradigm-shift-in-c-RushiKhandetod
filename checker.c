#include <stdio.h>
#include <assert.h>

typedef enum {
  NORMAL,
  LOW,
  HIGH
} RangeStatus;

RangeStatus checkRange(float value, float lowerLimit, float upperLimit) {
  if (value < lowerLimit) {
    return LOW;
  }
  if (value > upperLimit) {
    return HIGH;
  }
  return NORMAL;
}

void printStatus(const char* parameter, RangeStatus status) {
  if (status == LOW) {
    printf("%s is too low!\n", parameter);
  } else if (status == HIGH) {
    printf("%s is too high!\n", parameter);
  }
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  RangeStatus tempStatus = checkRange(temperature, 0, 45);
  RangeStatus socStatus = checkRange(soc, 20, 80);
  RangeStatus chargeRateStatus = checkRange(chargeRate, 0, 0.8);

  int isOk = (tempStatus == NORMAL) && (socStatus == NORMAL) && (chargeRateStatus == NORMAL);

  if (tempStatus != NORMAL) {
    printStatus("Temperature", tempStatus);
  }
  if (socStatus != NORMAL) {
    printStatus("State of Charge", socStatus);
  }
  if (chargeRateStatus != NORMAL) {
    printStatus("Charge Rate", chargeRateStatus);
  }

  return isOk;
}

void runTests() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(!batteryIsOk(-5, 50, 0.5));
  assert(!batteryIsOk(25, 15, 0.5));
  assert(!batteryIsOk(25, 50, 1.0));
  printf("All tests passed.\n");
}

int main() {
  runTests();
  return 0;
}
