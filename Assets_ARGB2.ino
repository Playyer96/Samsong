#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "walk_assets.h"
#include "Bat.h"
#include "Samsong.h"

Samsong samsong;

int x;

void setup() {
  GD.begin();
  LOAD_ASSETS();

}

void loop() {

  GD.Clear();
  GD.Begin(LINES);
  GD.ColorRGB(255, 255, 0);
  GD.LineWidth(12 * 8);
  GD.Begin(LINE_STRIP);
  drawWave();
  GD.swap();

  x ++;
  
}

void drawAttack() {
  if (samsong.attack == 'B') {

  }
}

void drawWave() {
  GD.Vertex2ii(140 + x - 10, 40); GD.Vertex2ii(140 + x + 20, 60);
  GD.Vertex2ii(140 + x + 40, 100); GD.Vertex2ii(140 + x + 40, 140);
  GD.Vertex2ii(140 + x + 25, 180); GD.Vertex2ii(140 + x + 10, 200);
  GD.Vertex2ii(140 + x - 10, 220);
}
