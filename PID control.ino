int incoming;
float output1=0, output=0, iterm=0, iterm1=0, pout=0, pout1=0;
float x,y=0;
float k;
float val,val0,t,val2;
int val1;
int ht,ht1;
int preht=0;
int setpoint = 100;
int i =5;
float error = 0;
int kp = 10;
float ki = 5.5;
//char input[100];
//int b[] = {10,20,40,60,80,100,120,150,180,210,150,120,100,80,60};//st patno:235900000
int b[] = {10,20,40,60,80,100,120,150,180,210,240,270,302,330,360,390,412,390,360,330,302,270,240,210,180,150,120,100,80,60,40};//st probe aircraft no IA 1116
//int b[] = {10,20,40,60,80,100,120,150,180,210,240,270,315}

void setup() {
Serial.begin(9600);  
pinMode(6,OUTPUT);
pinMode(4,OUTPUT);
/*while(preht=0){
incoming = Serial.available();
  if(incoming>0)
  {
    String s  = Serial.readStringUntil('&');
    if(s!=0)
    {
      int val1 = s.toInt();
    }
    String s2 = Serial.readStringUntil(':');
    if(s2!= 0)
    {
      val2 = s2.toFloat(); 
    }
    }
     //val1 = Serial.parseFloat();
     //Serial.print("453");
      Serial.print(val1);
      Serial.println(val2);
      preht = val1;
}*/
}
void loop() {
incoming = Serial.available();
  if(incoming>0)
  {
 String s1= Serial.readStringUntil(':');
 //Serial.println(s1);
 if(s1!=0)
 {
  int a=s1.indexOf('&');
  if(a>0)
  {
   // Serial.println(a);
 int l =s1.length();
 //Serial.println(l);
 String s2=s1.substring(0,a);
 if(s2!=0)
 {
  ht1=s2.toInt(); 
 }
 while(m<2)
 { 
   preht = ht1;
   m++;
}
 if(ht1-preht<6)
  {
    ht = preht;
}
 }
 String s3= s1.substring(a+1);
 t=s3.toFloat();
 Serial.print(ht);
 Serial.print("    ");
 Serial.println(t);
 }
}
 
}
error = setpoint-ht;
if(setpoint>ht)
  {
   iterm = iterm + ki*error;
   output = kp*error + iterm;
   y = 0;
 x =  output-pout;  
   if(x<0)
   {
    x= -x;
   }
   //Serial.println(x);
   if(x<3.1)
   {
    digitalWrite(6,HIGH);
    digitalWrite(4,HIGH);
    //Serial.println(t);
   }
   else
   {
    digitalWrite(6,HIGH);
     }
     pout=output;
     }
  else
  {
   error = -error;
   x=0;
    iterm1 = iterm1 + ki*error;
   output1 = kp*error + iterm1;
   y =  output1-pout1;
   if(y<0)
   {
    y= -y;
   } 
 if(y<3.1) 
   {
    digitalWrite(4,HIGH);
   digitalWrite(6,HIGH);
   }
   else
   {
    digitalWrite(4,HIGH);
    digitalWrite(6,LOW);
}
    pout1 = output1;
  }
  if(x<2.9&&y<2.9)
  {
  i = i+1;
  setpoint = b[i];
  x = 0;
  y = 0;
  delay(5000);
  Serial.print(ht);
  Serial.println(0);
  Serial.print("    ");
  Serial.println(t);
  delay(5000);
 }
  preht = ht;
}
