int basetime;
int pls=0;
int state=0;
int printtime=0;
unsigned int ledctr=0;
unsigned int a0read;

void setup()
{
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(3,LOW);
  Serial.println("WAITING CAP. VOLTAGE TO CHARGE UP !");
  
  for (int i=0;i<4;i++)
  {
    while (analogRead(A0)<30)
    {
      Serial.print("WAITING CAP. VOLTAGE TO CHARGE UP ! :"); 
      Serial.println(a0read);
      delay(1000);
    }
  }
  Serial.println("CAP. VOLTAGE LOOKS NORMAL!");
  
  basetime=micros(); 
}

void loop()
{
  if (((int)micros()-basetime)>=1000)
  {
    basetime+=1000;

    ledctr++;
    if (ledctr>=500)  // toggle LED every half seconds
    { 
        ledctr=0;        
        if (pls==0)
        {
          digitalWrite(13,HIGH);
          pls=1;
        }
        else
        {
          digitalWrite(13,LOW);
          pls=0;
          printtime=1;
        }
    }
    
    a0read=analogRead(A0);
    if (printtime!=0)
    {  
        printtime=0;  // normally every second prints the reading
        if ((a0read>=30)&&(a0read<=100))
        Serial.println(a0read);
    }

    if (a0read<30)
    {  //if shorted, prints it immediately -within 1 ms
        printtime=0; pls=0; ledctr=0;
        Serial.println(a0read);
        Serial.println("output is shorted");
        delay(2000);
        int pulsewh=500;
        int pulsewl=1000;
        basetime=micros();
        for (int i=0;i<3;i++)
        {
          digitalWrite(3,HIGH);
          while (((int)micros()-basetime)<pulsewh) {} //wait 100us
          basetime+=pulsewh;
          
//          digitalWrite(3,LOW); 
//          while (((int)micros()-basetime)<pulsewl) {} //wait 100us
//          basetime+=pulsewl;
        }
        digitalWrite(3,LOW); 

        
        for (int i=0;i<4;i++)
        {
          while (analogRead(A0)<30)
          {
            Serial.print("WAITING CAP. VOLTAGE TO CHARGE UP ! :"); 
            Serial.println(a0read); delay(1000);
          }
        }
    }
    if (a0read>100)
    {
        printtime=0; pls=0; ledctr=0;
        Serial.println(a0read);
        Serial.println("MOSFETs are not blocking");
        delay(250); //if MOSFET is shorted prints it immediately - within 1 ms
        basetime=micros();
    }
     
  }
}