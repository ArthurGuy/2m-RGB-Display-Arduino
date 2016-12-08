

void drawStar(int x, int y, int m, int colour) {
  // m = magnitude, 0 to 10
  if (m == 0) {
    leds.setPixel(posFromCord(x, y), makeColour(colour, 100, 50));
  } else if (m > 10) {
    return;
  } else {

    //Manually calculate the brigness as a linear dropoff isnt ideal
    int brightness = 50;
    if (m == 2) {
      brightness = 40;
    } else if (m == 3) {
      brightness = 30;
    } else if (m == 4) {
      brightness = 20;
    } else if (m == 5) {
      brightness = 10;
    } else if (m == 6) {
      brightness = 8;
    } else if (m == 7) {
      brightness = 6;
    } else if (m == 8) {
      brightness = 4;
    } else if (m == 9) {
      brightness = 2;
    } else if (m == 10) {
      brightness = 1;
    }
    
    leds.setPixel(posFromCord(x, y-m), makeColour(colour, 100, brightness)); //top
    leds.setPixel(posFromCord(x+m, y), makeColour(colour, 100, brightness)); //right
    leds.setPixel(posFromCord(x, y+m), makeColour(colour, 100, brightness)); //bottom
    leds.setPixel(posFromCord(x-m, y), makeColour(colour, 100, brightness)); //left

    if (m > 2) {
      leds.setPixel(posFromCord(x+(m/2)+1, y-(m/2)-1), makeColour(colour, 100, brightness)); //top-right
      leds.setPixel(posFromCord(x+(m/2)+1, y+(m/2)+1), makeColour(colour, 100, brightness)); //bottom-right
      leds.setPixel(posFromCord(x-(m/2)-1, y+(m/2)+1), makeColour(colour, 100, brightness)); //bottom-left
      leds.setPixel(posFromCord(x-(m/2)-1, y-(m/2)-1), makeColour(colour, 100, brightness)); //top-left
    }
  }
}
