
#include <OctoWS2811.h>

#define INFO_LED 13

const int numStrips    = 8;
const int ledsPerStrip = 125;
const int numSparks    = 100;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


IntervalTimer backgroundUpdateTimer;
IntervalTimer posUpdateTimer;



uint16_t backgroundIncrement;

int maxSpeed = 30; // 30 = slow, any less (bigger) and its jerky
int minSpeed = 7;  // 1 = very fast

int maxBrightness = 55;
int minBrightness = 2;

int columnCount[numStrips];

//Store the overal state of each spark
bool sparkState[numSparks];

int starPosition[2];
bool starOn = false;

struct {
     int pos;
     int speed;
     int colour;
     int strip;
     int brightness;
     unsigned long lastMove;
} spark[numSparks];



void setup() {

  Serial1.begin(115200);
  
  //Info LED
  pinMode(INFO_LED, OUTPUT);
  digitalWrite(INFO_LED, false);

  //Update the background animation
  backgroundUpdateTimer.begin(updateBackground, 40000);

  //Update the position of the falling pixels
  // The timing here isnt important as long as its fast enough to not miss an update
  posUpdateTimer.begin(updateSparkPos, 1000);

  // Reset the pixel counter for each of the columns
  resetColumnCounters();

  // Ensure the sparks are all disabed
  setupSparkSlots();
  
  leds.begin();

  turnAllOff();
  leds.show();

  Serial1.setTimeout(10);

}


void loop() {

  // Monitor the serial port for messages which will trigger effects
  // *E:4,20*  Star/explosion at position 4,20
  if (Serial1.available()) {
    if (Serial1.read() == '*') {
      int startChar = Serial1.read();

      // Star received
      if (startChar == 'E') {
        int x = Serial1.parseInt();
        int y = Serial1.parseInt();
        int endChar = Serial1.read();
        if (endChar == '*') {
          // Valid data received
          starPosition[0] = x;
          starPosition[1] = y;
          starOn = true;
        }
      } else if (startChar == 'S') {
        int x = Serial1.parseInt();
        int y = Serial1.parseInt();
        int endChar = Serial1.read();
        if (endChar == '*') {
          // Valid data received
          int slot = getFreeSparkSlot();
          if (slot >= 0) {
              newSpark(slot, x, y);
          }
        }
      }
      
    }

    //Clear any remaining data
    while (Serial.available()) {
      Serial.read();
    }
    
  }

  //time to run, 4,000 - 10,000 microseconds

  // Generate the pixel starting positions
  // doing it now will introduce some randomnesss to the starting positions
  int slot = getFreeSparkSlot();
  if (slot >= 0) {
      // Disable this function to only control over the serial port
      //newRandomSpark(slot);
  }


  updateLEDs();

  if (columnFull()) {
    resetColumnCounters();
  }

}



void updateLEDs() {

  // Clear the screen to begin with
  turnAllOff();

  // Display all the sparks
  renderSparks();

  // Display the filling up columns
  renderColumns();

  if (starOn) {
    drawStar(starPosition[0], starPosition[1], backgroundIncrement, 0);
  }

  // Now everything is in place update the screen
  leds.show();
}



int getRandomLedColour() {
  //if (random(0, 2) == 0) {
  //  return random(0, 15); //reds
  //}
  //return random(110, 120); // greens

  //return random(240, 300);   //purple
  //return random(0, 360);   //everything
  //return random(355, 20);  //reds
  return random(90, 140); //greens
  //return random(210, 240);  //blues
  //return random(110, 120); //greens - narrow
}


void updateBackground() {
  backgroundIncrement++;
  if (backgroundIncrement == 10) {
    backgroundIncrement = 0;
    starOn = false;
    //starPosition[0] = random(0, numStrips+1);
    //starPosition[1] = random(0, 80);
  }
}


// Background colour pattern
void rainbowCycle() {
  for (int r=0; r < numStrips; r++) {
    for(int i=0; i< ledsPerStrip; i++) {
      leds.setPixel((i + (ledsPerStrip * r)), makeColour(backgroundIncrement, 100, 2));
    }
  }
}


