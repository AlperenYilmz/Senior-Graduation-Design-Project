#include <LiquidCrystal.h>
#include <LiquidMenu.h>

const int periodBase=200;   // base period in us, can also be added to settings
const int pulseOut=9;
const int FIRE=4;
const int enter=0;
const int back=1;
const int up=2;
const int down=3;
const int left=11;
const int right=10;   // assessing pins
const int weldSense=A0;   // voltage sense pin for welding

int num1=2;
int num2=5;
int num3=3;
int DCY1=20;
int DCY2=50;
int DCY3=30;   // initialization of values

int lastButtonStateEnter = HIGH;
int lastButtonStateDown = HIGH;
int lastButtonStateRight = HIGH;
int lastButtonStateLeft = HIGH;
int lastButtonStateBack = HIGH;
int lastButtonStateUp = HIGH;
int lastButtonStateFire = HIGH;   // this button logic is for falling edge detection of buttons

LiquidCrystal lcd(13, 12, 8, 7, 6, 5);    // initializing LCD

// Lines
LiquidLine Settings(0, 0, "Settings");
LiquidLine Header(0,1,"(Enter to set)");
LiquidLine CurrentValuesPulses1(0, 0, "n1=", num1, " n2=", num2);
LiquidLine CurrentValuesPulses2(0, 1, "n3=", num3);
LiquidLine CurrentValuesDuties1(0, 0, "DC1=", DCY1, " DC2=", DCY2);
LiquidLine CurrentValuesDuties2(0, 1, "DC3=", DCY3);
LiquidLine n1(0, 0, "# of N1=", num1);
LiquidLine n2(0, 0, "# of N2=", num2);
LiquidLine n3(0, 0, "# of N3=", num3);
LiquidLine DC1(0, 1, "Duty Cycle 1=", DCY1);
LiquidLine DC2(0, 1, "Duty Cycle 2=", DCY2);
LiquidLine DC3(0, 1, "Duty Cycle 3=", DCY3);

// Screens from lines
LiquidScreen SettingsScreen(Settings, Header);
LiquidScreen PulsesScreen(CurrentValuesPulses1, CurrentValuesPulses2);
LiquidScreen DutiesScreen(CurrentValuesDuties1, CurrentValuesDuties2);
LiquidScreen Pulse1(n1, DC1);
LiquidScreen Pulse2(n2, DC2);
LiquidScreen Pulse3(n3, DC3);

// Menus from screens
LiquidMenu MainMenu(lcd, SettingsScreen, PulsesScreen, DutiesScreen);
LiquidMenu SettingsMenu(lcd, Pulse1, Pulse2, Pulse3);
LiquidMenu DisplayMenu(lcd, PulsesScreen, DutiesScreen);

// System from menus
LiquidSystem menu_system(MainMenu, SettingsMenu, DisplayMenu);

// Increase & Decrease functions for n & DC values
void increase_n1()
{
  if(num1==15)
  return;
  else
  num1++;
  menu_system.softUpdate();
}

void decrease_n1()
{
  if(num1==0)
  return;
  else
  num1--;
  menu_system.softUpdate();
}

void increase_n2()
{
  if(num2==15)
  return;
  else
  num2++;
  menu_system.softUpdate();
}

void decrease_n2()
{
  if(num2==0)
  return;
  else
  num2--;
  menu_system.softUpdate();
}

void increase_n3()
{
  if(num3==15)
  return;
  else
  num3++;
  menu_system.softUpdate();
}

void decrease_n3()
{
  if(num3==0)
  return;
  else
  num3--;
  menu_system.softUpdate();
}

void increase_DC1()
{
  if(DCY1>=90)
  DCY1=90;
  else
  DCY1+=10;
  menu_system.softUpdate();
}

void decrease_DC1()
{
  if(DCY1<=10)
  DCY1=10;
  else
  DCY1-=10;
  menu_system.softUpdate();
}

void increase_DC2()
{
  if(DCY2>=90)
  DCY2=90;
  else
  DCY2+=10;
  menu_system.softUpdate();
}

void decrease_DC2()
{
  if(DCY2<=10)
  DCY2=10;
  else
  DCY2-=10;
  menu_system.softUpdate();
}

void increase_DC3()
{
  if(DCY3>=90)
  DCY3=90;
  else
  DCY3+=10;
  menu_system.softUpdate();
}

void decrease_DC3()
{
  if(DCY3<=10)
  DCY3=10;
  else
  DCY3-=10;
  menu_system.softUpdate();
}


void setup()
{
  lcd.begin(16,2);
  pinMode(pulseOut, OUTPUT);
  pinMode(FIRE, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);

  menu_system.set_focusPosition(Position::RIGHT);   // cursor set to right

  n1.attach_function(1, increase_n1);   // attaching inrease & decrease functions for n & DC values 
  n1.attach_function(2, decrease_n1);   // these will be called by up & down buttons

  n2.attach_function(1, increase_n2);
  n2.attach_function(2, decrease_n2);

  n3.attach_function(1, increase_n3);
  n3.attach_function(2, decrease_n3);

  DC1.attach_function(1, increase_DC1);
  DC1.attach_function(2, decrease_DC1);

  DC2.attach_function(1, increase_DC2);
  DC2.attach_function(2, decrease_DC2);

  DC3.attach_function(1, increase_DC3);
  DC3.attach_function(2, decrease_DC3);

  menu_system.update();
}

void loop()
{
  int bStatEnter=digitalRead(0);
  int bStatLeft=digitalRead(11);
  int bStatRight=digitalRead(10);
  int bStatDown=digitalRead(3);
  int bStatUp=digitalRead(2);
  int bStatBack=digitalRead(1);
  int bStatFire=digitalRead(4);
  int senseRead=analogRead(weldSense);

  // checking button inputs
  if (lastButtonStateRight == HIGH && bStatRight == LOW)
  menu_system.next_screen();
  lastButtonStateRight=bStatRight;

  if (lastButtonStateLeft == HIGH && bStatLeft == LOW)
  menu_system.previous_screen();
  lastButtonStateLeft=bStatLeft;

  if (lastButtonStateUp == HIGH && bStatUp == LOW)
  menu_system.call_function(1);
  lastButtonStateUp=bStatUp;

  if (lastButtonStateDown == HIGH && bStatDown == LOW)
  menu_system.call_function(2);
  lastButtonStateDown=bStatDown;

  if (lastButtonStateEnter == HIGH && bStatEnter == LOW)
  {
    if(menu_system.get_currentScreen() == &SettingsScreen)    // if current screen is settings, go to settings menu 
    menu_system.change_menu(SettingsMenu);

    
    if((menu_system.get_currentScreen() == &PulsesScreen) || (menu_system.get_currentScreen() == &DutiesScreen))    // if current screen is on either of displays, enter does not register
    delayMicroseconds(1);
    else
    menu_system.switch_focus(true);   // on other screens (settings screens in this case), enter changes focus of cursor
  }
  lastButtonStateEnter=bStatEnter;

  if (lastButtonStateBack == HIGH && bStatBack == LOW)
  menu_system.change_menu(MainMenu);
  lastButtonStateBack=bStatBack;

  if (lastButtonStateFire == HIGH && bStatFire == LOW)
  goBoom();
  lastButtonStateFire=bStatFire;

  if(senseRead)
  delay(5);
}

void goBoom()
{
  for(int i=0; i<num1; i++)
  sendPulse(DCY1);

  for (int i=0; i<num2; i++)
  sendPulse(DCY2);

  for (int i=0; i<num3; i++)
  sendPulse(DCY3);
}

void sendPulse(int DC)
{
  digitalWrite(pulseOut, HIGH);
  delayMicroseconds(periodBase*DC/100);    // max value for delayMicroseconds is around 16000, for longer delays, use "delay"
  digitalWrite(pulseOut, LOW);
  delayMicroseconds(periodBase*(100-DC)/100);
}