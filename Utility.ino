
//Calculate an LEDs position on the grid from an x,y cordinate
int posFromCord(int x, int y) {
  //Are the cordinates out of bounds?
  if ((x < 0) || (y < 0) || (x >= 8) || y >= ledsPerStrip) {
    //Return a value just out of view so it isn't rendered
    return ledsPerStrip * numStrips;
  }
  return y + (ledsPerStrip * x);
}

void turnAllOff() {
  for (int i=0; i < ledsPerStrip * numStrips; i++) {
    leds.setPixel(i, 0);
  } 
}
