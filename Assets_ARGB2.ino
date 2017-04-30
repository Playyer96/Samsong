#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "assets.h"
#include "Bat.h"
#include "Samsong.h"

Samsong samsong;

int x;
int state = 0;
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
  GD.Begin(LINES);
  //GD.ColorRGB(255, 255, 0);
  GD.LineWidth(12 * 8);
  GD.Begin(LINE_STRIP);
  drawWave();
  GD.ColorRGB(255, 255, 255);

  x++;

  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 0,BackgroundS_HANDLE);
  GD.Vertex2ii(z, k + 136, mAmarillo_HANDLE, j);

  // if (state == 1)
  // {
  //   GD.Vertex2ii(30, 136, Golpe_HANDLE, j);
  // }

  if (state == 0)
  {
    GD.Vertex2ii(30, 136, Idle_HANDLE, j);
  }

  // if (state == 2)
  // {
  //   GD.Vertex2ii(30, 180, Muerte_HANDLE, j);
  // }
  GD.swap();

  // Animation speed
  i++;
  if (i == 20)
  {
    i = 0;
    j = (j + 1) % 2;
    count += 1;
  }
  if (count == 1)
  {
    state = 0;
  }
  // if (count == 5)
  // {
  //   state = 0;
  //   count = 0;
  // }

  // movex and movey speed screen's size is 480x272
  z = z + xspeed * xdir;
  if (z < 0)
  {
    xdir = 1;
  }
  if (z <= 0)
  {
    z = 488;
  }
}

void drawAttack()
{
  if (samsong.attack == 'B')
  {

  }
}

void drawWave()
{
  GD.Vertex2ii(140 + x - 10, 40);
  GD.Vertex2ii(140 + x + 20, 60);
  GD.Vertex2ii(140 + x + 40, 100);
  GD.Vertex2ii(140 + x + 40, 140);
  GD.Vertex2ii(140 + x + 25, 180);
  GD.Vertex2ii(140 + x + 10, 200);
  GD.Vertex2ii(140 + x - 10, 220);
}
