#include <stdio.h>
#include <assert.h>

typedef enum {
  NORMAL,
  LOW,
  HIGH
} RangeStatus;

RangeStatus checkRange(float value, float lowerLimit, float upperLimit) {
  return (value < lowerLimit) ? LOW : (value > upperLimit) ? HIGH : NORMAL;
}

void printStatus(const char* parameter, RangeStatus status) {
  const char* statusMessage = (status == LOW) ? "too low" : "too high";
  printf("%s is %s!\n", parameter, statusMessage);
}

int isBatteryParameterOk(float temperature, float soc, float chargeRate) {
  RangeStatus tempStatus = checkRange(temperature, 0, 45);
  RangeStatus socStatus = checkRange(soc, 20, 80);
  RangeStatus chargeRateStatus = checkRange(chargeRate, 0, 0.8);

  int isOk = 1;
  if (tempStatus != NORMAL) {
    printStatus("Temperature", tempStatus);
    isOk = 0;
  }
  if (socStatus != NORMAL) {
    printStatus("State of Charge", socStatus);
    isOk = 0;
  }
  if (chargeRateStatus != NORMAL) {
    printStatus("Charge Rate", chargeRateStatus);
    isOk = 0;
  }

  return isOk;
}

void runTests() {
  assert(isBatteryParameterOk(25, 70, 0.7));
  assert(!isBatteryParameterOk(50, 85, 0));
  assert(!isBatteryParameterOk(-5, 50, 0.5));
  assert(!isBatteryParameterOk(25, 15, 0.5));
  assert(!isBatteryParameterOk(25, 50, 1.0));
  printf("All tests passed.\n");
}

int main() {
  runTests();
  return 0;
}
