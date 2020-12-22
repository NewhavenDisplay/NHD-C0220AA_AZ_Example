/*****************************************************************************
 * 
/ Program for writing to NHD-C0220(AZ + AA) display Series with the NT7605 Controller.
/ This code is written for the Arduino Uno R3 using 4-bit Parallel Interface
/
/ Newhaven Display invests time and resources providing this open source code,
/ Please support Newhaven Display by purchasing products from Newhaven Display!

* Copyright (c) 2019, Newhaven Display International
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample code is responsible for ensuring its safe and correct operation
* and for any consequences resulting from its use.
* See the GNU General Public License for more details. 
* 
*****************************************************************************/

/****************************************************
*               Pinout on Arduino Uno               *
*****************************************************/

#define RS    8
#define RW    9
#define EPIN  10

const char text1[]={"  Newhaven Display  "};
const char text2[]={"Chip-On-Glass Module"};
const char text3[]={"2-Line 20-Characters"};
const char text4[]={"AZ+AA Series Display"};
const char text5[]={"    Please Enjoy    "};
const char text6[]={"    Responsibly :)  "};

/****************************************************
*                 Function Commands                  *
*****************************************************/

void latch(){                           // command to latch E
  digitalWrite(EPIN, HIGH);            
  delay(1);
  digitalWrite(EPIN, LOW); 
  delay(1);
}

void command(char i){
  PORTD = i;
  digitalWrite(RS, LOW);               // Command
  latch();                              // take upper 4 bits
  i = i<<4;                             // shift 4 bits
  PORTD = i;                            // Take lower 4 bits
  latch();
}
void data(char i){
  PORTD = i;
  digitalWrite(RS, HIGH);              // Data
  latch();                              // take upper 4 bits
  i = i<<4;                             // shift 4 bits
  PORTD = i;                            // Take lower 4 bits
  latch();
}

void disp_pic(){
  int i;
  for (i=0;i<20;i++){
    data(text1[i]);
    delay(10);
  }
   command(0xC0);
   for (i=0;i<20;i++){
    data(text2[i]);
    delay(10);
  }
   delay(1000);
   command(0x01);
  for (i=0;i<20;i++){
    data(text3[i]);
    delay(10);
  }
   command(0xC0);
   for (i=0;i<20;i++){
    data(text4[i]);
    delay(10);
  }
   delay(1000);
   command(0x01);
  for (i=0;i<20;i++){
    data(text5[i]);
    delay(10);
  }
   command(0xC0);
   for (i=0;i<20;i++){
    data(text6[i]);
    delay(10);
  }
   delay(1000);
   command(0x01);
  for (i=0;i<20;i++){
    data(0xFF);
    delay(10);
  }
   command(0xC0);
   for (i=0;i<20;i++){
    data(0xFF);
    delay(10);
  }
   delay(1000);
   command(0x01);
}

/****************************************************
*           Initialization For controller           *
*****************************************************/

void init1()
{
    PORTD = 0x20; // Put 0x20 onto port D
    latch();      // Wake Up
    delay(5);
    latch();      // Function Set
    delay(5);
    PORTD = 0x80;  //Place 0x80 onto port D
    latch();
    delay(5);
    command(0x0C);   // Display ON
    delay(5);
    command(0x06);    // Entry Mode Set
    delay(5);
    command(0x01);    // clear display
    delay(5);
    command(0x02);    //Return Home
}

/*****************************************************
*           Setup Function, to run once              *
*****************************************************/

void setup() {
  
  DDRD=0xFF; // Port D as output
  DDRB=0xFF; // Port B as output
  delay(100);
  init1();
}

/*****************************************************
*           Loop Function, to run repeatedly         *
*****************************************************/

void loop() {
   disp_pic();
   delay(100);
}
