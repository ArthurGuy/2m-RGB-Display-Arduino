



int colour = makeColour(120, 100, 8);


void renderText(){

  // Loop through each character in the message
  // Each character consists of 5 columns and one empty column as the space
  for (unsigned int charIndex=0; charIndex < messageLength; charIndex++) {
    
    // Convert each letter into an index for the font lookup table
    int alphabetIndex = msg[charIndex]- ' ';
    if (alphabetIndex < 0) alphabetIndex=0;

    for (int col=0; col < 5; col++) {
   
      // Loop through the rows of leds and render the line of the character
      // Each character has 7 rows
      for(int row=0; row <= 7; row++) {

        // Calculate the position for each pixel
        // column number of the character, what character we are on and the general offset
        int rowPosition = col + (charIndex * 6) + textIncrement;

        // Only render the character if it is in range of the display
        if ((rowPosition >= 0) && (rowPosition < ledsPerStrip)) {
          if (bitRead(alphabets[alphabetIndex][col], (7 - row)) == 1) {
            leds.setPixel((ledsPerStrip * row) + rowPosition, colour);
          }
        }
      }
    }
    
  }

}
/*
int stripLookup[8] = {
  ledsPerStrip-1,
  (ledsPerStrip*2)-1,
  (ledsPerStrip*3)-1,
  (ledsPerStrip*4)-1,
  (ledsPerStrip*5)-1,
  (ledsPerStrip*6)-1,
  (ledsPerStrip*7)-1,
  (ledsPerStrip*8)-1
};

void renderVerticalText() {

  for (unsigned int charIndex=0; charIndex < sizeof(msg); charIndex++) {
    // Convert each letter into an index for the font lookup table
    int alphabetIndex = msg[charIndex]- ' ';
    if (alphabetIndex < 0) alphabetIndex=0;
    
    // vertical text
    // Loop through the 8 columns of leds
    for (int col=0; col < 8; col++) {
   
      // Loop through the 5 columns that makeup each character
      for(int row=0; row < 5; row++) {
        
        if (bitRead( alphabets[alphabetIndex][row], col ) == 1) {
          leds.setPixel(stripLookup[2 + row] - (8 - col) - ((sizeof(msg) - charIndex) * 7) + (textIncrement), colour);
        }
      }
    }

  }
}
*/

