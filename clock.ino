#include <SevSeg.h>

SevSeg sevseg;

// Starting time
int hours = 0;
int minutes = 0;
int seconds = 0;

unsigned long previousMillis = 0;

void setup() {
  byte numDigits = 4;

  byte digitPins[] = {12, 9, 8, 6};
  byte segmentPins[] = {11, 7, 4, 2, 1, 10, 5, 3};

  bool resistorsOnSegments = true;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevseg.begin(
    COMMON_CATHODE,
    numDigits,
    digitPins,
    segmentPins,
    resistorsOnSegments,
    updateWithDelays,
    leadingZeros,
    disableDecPoint
  );

  sevseg.setBrightness(90);

  previousMillis = millis();
}

void loop() {
  // Refresh the display constantly
  sevseg.refreshDisplay();

  unsigned long currentMillis = millis();

  // One second has passed
  if (currentMillis - previousMillis >= 1000) {
    previousMillis += 1000;

    seconds++;

    // 60 seconds -> next minute
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }

    // 60 minutes -> next hour
    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }

    // 24 hours -> midnight
    if (hours >= 13) {
      hours = 1;
    }
  }

 int time = 100* hours + 10 * minutes + seconds;

sevseg.setNumber(time, 2);
}