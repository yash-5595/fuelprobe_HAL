#include <LiquidCrystal.h>
#include <FreqCounter.h>
// initialize the library with the numbers of the interface pins(apt)
LiquidCrystal lcd(3,4,9,10,11,12);
//LiquidCrystal lcd(12,11,10,9,4,3);
int pin1=8;
int Buz=7;
int state1;
float x1,x2,y1,y2;
float a[17];
int b[17];
int p,i;
float c[] = {101.4,102.8,106.8,110.8,115.0,119.0,123.1,129.3,135.3,141.4,147.4,153.9,160.0,165.8,171.2,177.2,179.3};//st patno:235900000
int d[] = {10,20,40,60,80,100,120,150,180,210,240,270,302,330,360,390,412};//st patno:235900000
int e[] = {};//FMT
int f[] = {};//MMT
int g[] = {};//RMT
int h[] = {};//AT
int sensorPin = A2;
float value=0;
float vo=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode (pin1, INPUT);
  pinMode (Buz, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Select Probe");
 delay(3000);
 //lcd.clear();
 lcd.setCursor(3,0);
 lcd.print("ok");
 lcd.clear();
 value=0;
 value = analogRead(sensorPin);
 vo=((value*5.1)/1025);
 if ( vo >4.8 && vo<5.2)          //FT PROBE
{
   for(i=0;i<sizeof(e);i++)
   {
    b[i] = e[i];
     }
   }
if(vo >3.5 && vo<4.2)              //MT PROBE
    {      
     for(i=0;i<sizeof(f);i++)
   {
    b[i] = f[i];
     }  
    }
if ( vo >2.5 && vo<3.2)                    //ST PROBE
{
   for(i=0;i<sizeof(d);i++)
   {
    b[i] = d[i];
     }
}
  if(vo >1.5 && vo<2.2)                 //AT PROBE
    {      
      for(i=0;i<sizeof(h);i++)
   {
    b[i] = h[i];
     }
      }
      if(vo >0 && vo<1.2)                 //RT PROBE
    {      
      for(i=0;i<sizeof(g);i++)
   {
    b[i] = g[i];
     }  
}
lcd.setCursor(0,0);
lcd.print("Rated timeperiod");
//lcd.clear();
 lcd.setCursor(0,0);
 int l=0;
 while(l<17){
  if(Serial.available()>0){
   float p = Serial.parseFloat();
    if(p>0)
    {
    a[l]=p;
    lcd.setCursor(0,1);
    lcd.print(l);
        l++;
}
    }
    }
    }
void loop()
{
  //float a[] = {100.7,102.6,106.5,110.2,114.2,118.1,122.0,127.7,133.2,139.3,144.8,150.8,158.3,162.1,167.2,173.2,177.6};
  //int b[] = {10,20,40,60,80,100,120,150,180,210,240,270,302,330,360,390,427};
  float ht;
  float frq;
  FreqCounter::f_comp=10;
  FreqCounter::start(1000);
  while (FreqCounter::f_ready == 0) 
  frq=FreqCounter::f_freq; //Sets the 'frq' variable as the measured frequency
  frq=frq*1;
  lcd.setCursor(0,1);
  lcd.print("T:       us   ");
  lcd.setCursor(2, 1);
  //lcd.print(frq);
  double t=(1/frq)*1000000;
  lcd.print(t);
  //delay(2000); //Prints this measured frequency
  //delay(100);
  ///value=0;
  //value = analogRead(sensorPin);
  //vo=((value*5.1)/1025);
  //Serial.println(vo);

  state1= digitalRead(pin1);
  int j=0;
  for (int i=0; i<17; i++)
   { j=i+1;
     if ( t>=a[i] && t<=a[j])
        { y1=a[i];
          y2=a[j];
          x1=b[i];
          x2=b[j];
        }
   }  
  ht1=(((x2-x1)/(y2-y1))*(t-y1))+x1; //linear equation for value scaling
  while(m<2 && ht1!=0 && ht1<500)
  {
    preht=ht1;
    m++;
  }
  
  float p = preht-ht1;
  if(p<0)
  {
    p = -p;
  }
  if(p<4)
  {
  
  ht = ht1; 
  }
  Serial.print(ht);
  Serial.print("&");
  Serial.print(t);
  Serial.println(":");
  Serial.flush();
  preht = ht;
  if ( vo >4.8 && vo<5.2)          //FT PROBE

 {
  //state1= digitalRead(pin1);
  if (state1==HIGH)
   {
     lcd.setCursor(15,1);
     lcd.print ('L');
     digitalWrite(Buz, LOW);
   }
   else
   {
    lcd.setCursor(15,1);
    lcd.print(' ');
    //delay(100);
   digitalWrite(Buz, HIGH);
   }
  lcd.setCursor(0,0);
  lcd.print("FMT:");
  lcd.setCursor(4,0);
  lcd.print("HT=       mm");
  lcd.setCursor(7,0);
  //ht=((t-98.80)/0.183);
    lcd.print(ht);   
 }
  
  if(vo >3.5 && vo<4.2)              //MT PROBE
    {      
      lcd.setCursor(0,0);
      lcd.print("MMT:");
      lcd.setCursor(4,0);
      lcd.print("HT=       mm");
      lcd.setCursor(7,0);
      //ht=((4.908*t)-482.7)-3; //ht=((t-100.8)/0.201);
      lcd.print(ht); 
     lcd.setCursor(15,1);
     lcd.print(' ');  
     digitalWrite(Buz, LOW);
      //delay(100);
   }
if ( vo >2.5 && vo<3.2)                    //ST PROBE

{
   if (state1==HIGH)
   {
     lcd.setCursor(15,1);
     lcd.print ('L');
     digitalWrite(Buz, LOW);
   }
   else
   {
    lcd.setCursor(15,1);
    lcd.print(' ');
    digitalWrite(Buz, HIGH);
   }
  lcd.setCursor(0,0);
  lcd.print("ST1:");
  lcd.setCursor(4,0);
  lcd.print("HT=       mm");
  lcd.setCursor(7,0);
  //ht=((5.292*t)-531.1)+8;//ht=((t-100.0)/0.194);
  lcd.print(ht);  
     
}
   if(vo >1.5 && vo<2.2)                 //AT PROBE
    {      
      lcd.setCursor(0,0);
      lcd.print("AT1:");
      lcd.setCursor(4,0);
      lcd.print("HT=       mm");
      lcd.setCursor(7,0);
      //ht=((t-100.3)/0.128);
      lcd.print(ht);   
      //delay(100);
      lcd.setCursor(15,1);
     lcd.print(' '); 
     digitalWrite(Buz, LOW);
      }
      if(vo >0 && vo<1.2)                 //RT PROBE
    {      
      lcd.setCursor(0,0);
      lcd.print("RMT:");
      lcd.setCursor(4,0);
      lcd.print("HT=       mm");
      lcd.setCursor(7,0);
      //ht=((t-100.5)/0.255);
      lcd.print(ht);   
      //delay(100);
      lcd.setCursor(15,1);
      lcd.print(' '); 
      digitalWrite(Buz, LOW);
      }
}
