//**************************************************************
//***Program name;- 3X3X3 P29_0010******************************
//***ALL code written by Robin E. Stephens G8XEU****************
//***Program written in c++ for micro controller type***********
//*** ATMEGA328P, which in turn controls 27 LED's***************
//***layers all neg connected via 3pins A1 A2 A3****************
//***27 leds connected in columns. 9 pins.0-8 to controller*****
//Libraries are kept to a minimum so you can see what's going on*
//**************************************************************

#define layer_on  0
#define layer_off 1
#define Top_layer A1
#define Mid_layer A2
#define Bot_layer A3
void setup()
{
  DDRD = B11111111;// pins D7 - D0 output
  DDRB = B00000001; // pin D8 output
  DDRC = B00101111;// A5 A3 A2 A1 A0=output.(A4=speed controller input)
  for (byte f = 0; f < 8; f++)
  {
    PORTC = B00100001;
    delay(20);
    PORTC = B00100000;// A5 left high for speed controller power
    delay(60);
  }
}

void loop()
{
  // LED parameters are, 1st para = rotation.
  // 2nd para = B1111 is
  // 1st bit = 1 go off after display or not.
  // 2nd3rd4th bit is layer left on or not
  // 3rd para ="012345678" indicates which colomn
  // 9=blank. in lots of three.
  // 258
  // 147
  // 036 where led 0 is closest to xtal.

  display_leds(8, B1111, "012246678840"); // X
  display_leds(2, B1111, "012999012999147999147999678999678"); // H
  display_leds(4, B1111, "012012258258876876630630"); //Square
  display_leds(4, B1100, "048048246246"); //pendulum bottom
  display_leds(4, B1110, "048048246246"); //pendulum bottom middle
  display_leds(4, B1111, "048048246246"); //pendulum bottom middle top
  display_leds(4, B1111, "012258876630"); //fast outside wall
  display_leds(2, B1001, "000111222555888777666333"); //Spiral
  display_leds(2, B1010, "000111222555888777666333"); //Spiral down
  display_leds(2, B1100, "000111222555888777666333"); //Spiral down
  display_leds(1, B1111, "444999444999444999444"); //centre flash
  display_leds(4, B1111, "666777888555222111000333"); //singles edges
  led_display01(1); led_display01(2);
  display_leds(3, B1100, "028286860602"); //Corners
  display_leds(3, B1110, "028286860602"); //Corners
  display_leds(4, B1111, "028286860602"); //Corners
  display_leds(6, B1111, "157573731315"); //Centres
  display_leds(2, B0111, "012345678345"); //all on
  display_leds(6, B1111, "012345678345"); //wave side to side
  display_leds(6, B1111, "036147258147"); //wave back to back
  display_leds(2, B0111, "098395296197"); //fill outside columns
  display_leds(6, B1111, "098395296197"); //round clockwise
  display_leds(6, B1111, "098197296395"); //round anti clockwise
  display_leds(4, B1111, "098395296197"); //round clockwise
  display_leds(4, B1111, "098197296395"); //round anti clockwise
  display_leds(2, B1111, "098395296197"); //round clockwise
  display_leds(2, B1111, "098197296395"); //round anti clockwise

  display_leds(2, B0111, "012345678");  //all on
  for (byte loop = 0; loop < 5; loop++) //up down loop
  {
    display_leds(1, B0001, "999"); // top on
    display_leds(1, B0010, "999"); // mid on
    display_leds(1, B0100, "999"); // bot on
    display_leds(1, B0010, "999"); // mid on
  }

  for (byte loop = 0; loop < 9; loop++) //on off loop
  {
    display_leds(1, B0000, "999"); // off
    display_leds(1, B0111, "999"); // on
  }
  led_display01(3);
}

// LED control routine
void display_leds(byte rotations, byte lay_id, String LED_IDstr)
{
  for (byte rtn = 0; rtn < rotations; rtn++)
  {
    for (byte layer = Top_layer; layer <= Bot_layer; layer++)
      digitalWrite(layer, layer_off - bitRead(lay_id, layer - Top_layer));

    for (byte loop = 0; loop < LED_IDstr.length() / 3; loop++)
    {
      for (byte innerloop = 0; innerloop < 3; innerloop++)
        digitalWrite(LED_IDstr.charAt(loop * 3 + innerloop) - 48, 1);
      delaycontrol(); delaycontrol();
      if (bitRead(lay_id, 3)) for (byte innerloop = 0; innerloop < 3; innerloop++)
          digitalWrite(LED_IDstr.charAt(loop * 3 + innerloop) - 48, 0);
    }
    if (bitRead(lay_id, 3))
      for (byte loop = Top_layer; loop <= Bot_layer; loop++)
        digitalWrite(loop, layer_off);
  }
}
void delaycontrol()// Delay controlled by 10k potentiometer
{
  int delspeed = map(analogRead(A4), 0, 1023, 125, 10);
  delay(delspeed);
}

void led_display01(byte looprun)
{
  for (byte rtn = Top_layer; rtn <= Bot_layer; rtn++)
  {
    digitalWrite(rtn, 0);
    for (byte loop = 0; loop < looprun; loop++)
    {
      for (byte leds = 0; leds < 9; leds++)
      {
        digitalWrite(leds, 1);
        delaycontrol();
        digitalWrite(leds, 0);
      }
    }
    digitalWrite(rtn, layer_off);
  }
}
