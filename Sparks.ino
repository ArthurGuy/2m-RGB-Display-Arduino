
void renderSparks() {
  for (int i = 0; i < numSparks; i++) {
    //If the spark is in play render it
    if (sparkState[i]) {
      if ((spark[i].pos > 0) && (spark[i].brightness > 5)) {
        //Add a tail to the pixel as long as it isnt to dimm
        leds.setPixel(spark[i].pos-1 + (ledsPerStrip * spark[i].strip), makeColour(spark[i].colour, 100, 3));
      }
      leds.setPixel(spark[i].pos + (ledsPerStrip * spark[i].strip), makeColour(spark[i].colour, 100, spark[i].brightness));
    }
  }
}


void updateSparkPos() {

  // Update each of the pixel on the screen
  for(int i=0; i < numSparks; i++) {

    // Check when it was last updated and workout if its ready to be updated
    // The speed factor will delay the frequency of updates
    if (spark[i].lastMove < (millis() - spark[i].speed)) {
      spark[i].lastMove = millis();

      //Move the spark on one position
      spark[i].pos = spark[i].pos + 1;

      //Move sideways
      //if (random(0, 15) == 1) {
      //  spark[i].strip = spark[i].strip + 1;
      //}

      //If they have reached the end reset the details
      if (spark[i].pos >= ledsPerStrip) {
        destroySpark(i);
        //newRandomSpark(i);
      }

      // If they have reached the top of the full column stack 
      //  reset the pixel and increment the counter
      if (spark[i].pos >= columnCount[spark[i].strip]) {
        //columnCount[spark[i].strip]--;
        //newRandomSpark(i);
      }

    }
    
  }

}

void destroySpark(int i) {
  sparkState[i] = false;
}

void newRandomSpark(int i) {
  spark[i].pos        = 0;
  spark[i].speed      = random(minSpeed, maxSpeed+1);
  spark[i].colour     = getRandomLedColour();
  spark[i].strip      = random(0, numStrips);
  spark[i].brightness = map(spark[i].speed, minSpeed, maxSpeed, maxBrightness, minBrightness);
  spark[i].lastMove   = millis();

  sparkState[i] = true;
}


void newSpark(int i, int x, int y) {
  spark[i].pos        = y;
  spark[i].speed      = random(minSpeed, maxSpeed+1);
  spark[i].colour     = getRandomLedColour();
  spark[i].strip      = x;
  spark[i].brightness = map(spark[i].speed, minSpeed, maxSpeed, maxBrightness, minBrightness);
  spark[i].lastMove   = millis();

  sparkState[i] = true;
}

//Get the ID of a free slot that can hold a spark
int getFreeSparkSlot() {
    
    //See if any of the wave slots are available
    for(int w=0; w < numSparks; w++) {
        if (sparkState[w] == false) {
            return w;
        }
    }
  
    //none available
    return -1;
}

void setupSparkSlots() {
  for(int w=0; w < numSparks; w++) {
    sparkState[w] = false;
  }
}


