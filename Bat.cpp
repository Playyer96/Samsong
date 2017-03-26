#include "Bat.h"
#include <SPI.h>

Bat::Bat() {

  xPosition = 480;
  
  yPosition = random(20, 180);

  batColor = 'B';
}
