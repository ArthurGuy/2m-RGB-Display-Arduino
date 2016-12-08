

void renderColumns() {
  for(int i=0; i<numStrips; i++) {
    for(int y = (ledsPerStrip - 1); y > columnCount[i]; y--) {
      leds.setPixel(y + (ledsPerStrip * i), makeColour(getRandomLedColour(), 100, 10));
    }
  }
}


bool columnFull() {
  // Do any of the columns have less than 1 pixel left in them
  for(int i=0; i < numStrips; i++) {
    if (columnCount[i] <= 1) {
      return true;
    }
  }
  return false;
}

//Empty all the columns
void resetColumnCounters() {
  for(int i=0; i < numStrips; i++) {
    columnCount[i] = ledsPerStrip - 1;
  }
}
