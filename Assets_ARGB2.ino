#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "walk_assets.h"
int state = 1;
int count = 0;
void setup()
{
  GD.begin();
  LOAD_ASSETS();
  Serial.begin(9600);
}

void loop()
{

  static uint8_t i = 0;
  static uint8_t j = 0;
  static int16_t z = 488;
  static uint16_t k = 0;
  static int16_t xspeed = 2;
  static int16_t xdir = -1;

  GD.Clear();
  GD.Begin(BITMAPS);
  /*
    if (xdir == -1) {
      GD.cmd_translate(F16(16), F16(0));
      GD.cmd_scale(F16(-1), F16(1));
      GD.cmd_translate(F16(-16), F16(0));
      GD.cmd_setmatrix();
    }
  */
  //GD.cmd_scale(F16(1), F16(1));
  //GD.cmd_setmatrix();
  GD.Vertex2ii(z, k + 136, WALK_HANDLE, j);
/*
  if (state == 1) {
    GD.Vertex2ii(30, 136, Golpe_HANDLE, j);
  }
  if (state == 0) {
    GD.Vertex2ii(30, 136, Idle_HANDLE, j);
  }

  if (state == 2) {
    GD.Vertex2ii(30, 180, Muerte_HANDLE, j);
  }*/
  GD.swap();

  // Animation speed
  i++;
  if (i == 20) {
    i = 0;
    j = (j + 1) % 2;
    count += 1;

  }
  if (count == 4) {
    state = 2;
  }
  if (count == 5) {
    state = 0;
    count = 0;
  }

  // movex and movey speed screen's size is 480x272
  z = z + xspeed * xdir;
  if (z < 0 ) {
    xdir = 1;
  }
  if (z <= 0
     ) {
    z = 488;
  }
}

