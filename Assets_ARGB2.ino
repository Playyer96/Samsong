#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "assets.h"
#include "Bat.h"
#include "Samsong.h"

Samsong samsong;

int waveSpeed = 5;
int state = 0;
int count = 0;
int score = 000;
char input = ' ';
static int rn = random(30, 190);
static int rnBat = random(0, 3);
static int posy[20];
static int posx[20];
int posxwave[20];
boolean activewave[20];
static boolean active[20];
static int colorWave[20];
static int batColor[20];
static int randomColor[20];
static int BatActive = 0;
static int waveactive = 0;
static int cooldownbat = 120;
static int wavelimit = 480;
static int tiempo = 120;

static boolean Lost = false;
static int Vidas = 3;

int outputPin = 7;
int inputPin = A2;
int inputPin2 = A3;
int inputPin3 = A4;

int pinAmarillo = 420;
int pinRojo = 420;

void setup()
{
  GD.begin();
  LOAD_ASSETS();
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  Serial.begin(9600);
}

void loop()
{

  if (Serial.available() > 0)
  {
    input = Serial.read();
  }

  digitalWrite(outputPin, 255);

  if (Lost == false)
  {

    tiempo = tiempo + 1;
    static uint8_t i = 0;
    static uint8_t j = 0;
    static int16_t z = 2;
    static uint16_t k = 0;
    static int16_t xspeed = 2;
    static int16_t xdir = -1;

    GD.Clear();

    GD.Begin(BITMAPS);
    GD.Vertex2ii(0, 0, background_HANDLE);

    if (state == 1)
    {
      GD.Vertex2ii(30, 136, Golpe_HANDLE, j);
    }

    if (state == 0)
    {
      GD.Vertex2ii(30, 136, Idle_HANDLE, j);
    }

    if (state == 2)
    {
      GD.Vertex2ii(30, 180, Muerte_HANDLE, j);
    }

    if (Vidas >= 3)
    {
      GD.Vertex2ii(350, 15, face_HANDLE);
      GD.Vertex2ii(393, 15, face_HANDLE);
      GD.Vertex2ii(436, 15, face_HANDLE);
    }
    else if (Vidas == 2)
    {
      GD.Vertex2ii(350, 15, faceX_HANDLE);
      GD.Vertex2ii(393, 15, face_HANDLE);
      GD.Vertex2ii(436, 15, face_HANDLE);
    }
    else if (Vidas == 1)
    {
      GD.Vertex2ii(350, 15, faceX_HANDLE);
      GD.Vertex2ii(393, 15, faceX_HANDLE);
      GD.Vertex2ii(436, 15, face_HANDLE);
    }
    else
    {
      GD.Vertex2ii(350, 15, faceX_HANDLE);
      GD.Vertex2ii(393, 15, faceX_HANDLE);
      GD.Vertex2ii(436, 15, faceX_HANDLE);
      state == 2;
      Lost = true;
    }

    GD.cmd_text(60, 15, 24, OPT_CENTER, "SCORE:");
    GD.cmd_number(140, 15, 24, OPT_CENTER, score);

    rn = random(30, 190);
    rnBat = random(0, 3);

    if (tiempo >= cooldownbat)
    {

      posy[BatActive] = rn;
      posx[BatActive] = 480;
      randomColor[BatActive] = rnBat;
      active[BatActive] = true;
      BatActive++;

      if (BatActive == 19)
      {
        BatActive = 0;
      }
      tiempo = 0;
    }

    for (int x = 0; x < 19; x++)
    {
      if (randomColor[x] == 0)
        batColor[x] = 'a';
      else if (randomColor[x] == 1)
        batColor[x] = 'r';
      else if (randomColor[x] == 2)
        batColor[x] = 'b';

      if (active[x] == true)
      {
        if (batColor[x] == 'a')
          GD.ColorRGB(255, 255, 0);
        else if (batColor[x] == 'r')
          GD.ColorRGB(255, 0, 0);
        else if (batColor[x] == 'b')
          GD.ColorRGB(0, 0, 255);

        GD.Vertex2ii(posx[x], posy[x], mAmarillo_HANDLE, j);
        posx[x] = posx[x] - z;

        if (posx[x] <= 140)
        {
          posx[x] = 480;
          Vidas--;
          active[x] = false;
        }
      }
    }

    if (input == 'a' || input == 'r' || input == 'b')
    {
      state++;
      colorWave[waveactive] = input;
      posxwave[waveactive] = 140;
      activewave[waveactive] = true;
      waveactive++;
      input = 'k';
      if (waveactive == 19)
      {
        waveactive = 0;
      }
    }

    for (int x = 0; x < 19; x++)
    {
      if (activewave[x] == true)
      {
        if (colorWave[x] == 'a')
          GD.ColorRGB(255, 255, 0);
        else if (colorWave[x] == 'r')
          GD.ColorRGB(255, 0, 0);
        else if (colorWave[x] == 'b')
          GD.ColorRGB(0, 0, 255);

        GD.Vertex2ii(posxwave[x], 30, wave_HANDLE);
        posxwave[x] = posxwave[x] + waveSpeed;
        if (posxwave[x] >= 480)
        {
          posxwave[x] = 140;
          activewave[x] = false;
        }
      }
    }

    for (int x = 0; x < 19; x++)
    {
      if (activewave[x] == true)
      {
        for (int xBat = 0; xBat < 19; xBat++)
        {
          if (active[xBat] == true)
          {
            if (posxwave[x] >= posx[xBat])
            {
              if (colorWave[x] == batColor[xBat])
              {
                posxwave[x] = 140;
                activewave[x] = false;
                active[xBat] = false;
                score = score + 10;
              }
              else if (colorWave[x] != batColor[xBat])
              {
                posxwave[x] = 140;
                activewave[x] = false;
              }
            }
          }
        }
      }
    }

    GD.swap();
    //Serial.println(input);
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
    if (count == 5)
    {
      state = 0;
      count = 0;
    }
  }
  else if (Lost = true)
  {
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.ColorRGB(128, 128, 128);
    GD.Vertex2ii(0, 0, background_HANDLE);
    GD.Vertex2ii(30, 180, Muerte_HANDLE);
    GD.ColorRGB(255, 255, 255);
    GD.cmd_text(240, 116, 31, OPT_CENTER, "Game Over");
    GD.cmd_text(200, 145, 24, OPT_CENTER, "Score: ");
    GD.cmd_number(290, 145, 24, OPT_CENTER, score);
    GD.cmd_text(240, 180, 24, OPT_CENTER, "Tap to continue");

    GD.swap();
  }
}
