#include <Arduino.h>
#include <FastLED.h>
#define NumeroLeds 105

byte efecto = 0;
byte numeroEfectos = 3;

const int pinConexion = 6;
unsigned long inicio = 0;
unsigned long duracion = 50;
unsigned long duracionLarga = 1500;
unsigned long cambioEfecto = 30000;
unsigned long proximoCambio = 0;
byte brillo = 1;
double paso = sqrt(2);
byte numeroColores = 7;
byte colorActual = 0;
byte nivelesBrillo = 7;

CRGB leds[NumeroLeds];
CRGB colores[] = {0x0000ff, 0x00ff00, 0xff0000, 0x00ffff, 0xff00ff, 0xffff00, 0xffffff};

void CambioColor();
void subeBajaBrillo();
void coloresConsecutivos();
void ledCorredor();

void setup()
{
  // Iniciar puerto serie
  Serial.begin(115200);
  Serial.println("Reseteando");
  LEDS.addLeds<WS2812B, pinConexion, RGB>(leds, NumeroLeds);
  LEDS.setBrightness(84);
  proximoCambio = millis() + cambioEfecto;
}
void fadeall()
{
  for (int i = 0; i < NumeroLeds; i++)
  {
    leds[i].nscale8(250);
  }
}

void loop()
{
  if (millis() >= proximoCambio)
  {
    efecto++;
    proximoCambio += cambioEfecto;
  }
  if (efecto > numeroEfectos)
  {
    efecto = 0;
  }
  switch (efecto)
  {
  case 0:
    CambioColor();
    break;

  case 1:
    subeBajaBrillo();
    break;

  case 2:
    coloresConsecutivos();
    break;

  case 3:
    ledCorredor();
    break;

  default:
    break;
  }
}

void CambioColor()
{
  static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for (int i = 0; i < NumeroLeds; i++)
  {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
  Serial.print("x");

  // Now go in the other direction.
  for (int i = (NumeroLeds)-1; i >= 0; i--)
  {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
}

void subeBajaBrillo()
{
  LEDS.clear();
  for (byte i = 0; i < numeroColores; i++)
  {
    brillo = 1;
    for (byte j = 0; j < nivelesBrillo; j++)
    {
      LEDS.setBrightness(brillo);
      LEDS.showColor(colores[i]);
      brillo *= 2 + 1;
      delay(200);
    }

    /* code */
  }
}

void ledCorredor()
{
  LEDS.clearData();
  for (byte i = 0; i < numeroColores; i++)
  {
    for (byte j = 0; j < NumeroLeds; j++)
    {
      leds[j] = colores[i];
      LEDS.show();
      delay(50);
    }
  }
}

void coloresConsecutivos()
{
  LEDS.clearData();
  for (byte i = 0; i < numeroColores; i++)
  {
    LEDS.showColor(colores[i]);
    delay(3750);
  }
}
