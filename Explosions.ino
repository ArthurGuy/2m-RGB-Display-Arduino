
void renderExplosions() {
  for (int i = 0; i < numExplosions; i++) {
    //If the explosion slot is in play render it
    if (explosionState[i]) {
      renderExplosion(explosion[i].x, explosion[i].y, explosion[i].size, explosion[i].colour);
    }
  }
}

void setupExplosionSlots() {
  for(int w=0; w < numExplosions; w++) {
    explosionState[w] = false;
  }
}

//Get the ID of a free slot that can hold an explosion
int getFreeExplosionSlot() {
    
    //See if any of the wave slots are available
    for(int w=0; w < numExplosions; w++) {
        if (explosionState[w] == false) {
            return w;
        }
    }
  
    //none available
    return -1;
}

void newExplosion(int i, int x, int y) {
  explosion[i].x          = x;
  explosion[i].y          = y;
  explosion[i].colour     = 0;
  explosion[i].size       = 0;
  explosion[i].lastChange = millis();

  explosionState[i] = true;
}

void destroyExplosion(int i) {
  explosionState[i] = false;
}

void updateExplosionState() {

  // Update each of the pixel on the screen
  for(int i=0; i < numExplosions; i++) {

    // Check when it was last updated and workout if its ready to be updated
    // The speed factor will delay the frequency of updates
    if (explosion[i].lastChange < (millis() - 50)) {
      explosion[i].lastChange = millis();

      //Move the spark on one position
      explosion[i].size = explosion[i].size + 1;
      
      //If they have reached the end reset the details
      if (explosion[i].size >= 10) {
        destroyExplosion(i);
      }
    }
    
  }
}

void renderExplosion(int x, int y, int m, int colour) {
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
