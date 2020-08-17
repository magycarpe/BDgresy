//initialisation
#include<SoftwareSerial.h>
#include <Sleep_n0m1.h>
SoftwareSerial sim(10,11);

Sleep sleep;
unsigned long sleepTime;
int count = 0;


String number = "+33753611098";

float N=1;

float d=0;

int h=0;
  const byte trigger1=6;
  const byte echo1=7;
  /*const byte trigger2=5;
  const byte echo2=4;
  const byte trigger3=9;
  const byte echo3=8;*/
  const unsigned long timeout = 25000UL;
  const float s_speed = 340.0/1000;

char buffer[80];
byte pos = 0;
int detection=0;

void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  pinMode(trigger1, OUTPUT);
  digitalWrite(trigger1, LOW);
  pinMode(echo1, INPUT);

  /*pinMode(trigger2, OUTPUT);
  digitalWrite(trigger2, LOW);
  pinMode(echo2, INPUT);

  pinMode(trigger3, OUTPUT);
  digitalWrite(trigger3, LOW);
  pinMode(echo3, INPUT);*/

  sleepTime = 30000;
}

void loop() {
sim.println("AT+CFUN=1");

if(count >= 1)
  {
    count = 0;
    sim.println("AT+CFUN=0");
    Serial.print("sleeping ");
    Serial.println(sleepTime); 
    delay(100); //delay to allow serial to fully print before sleep
    digitalWrite(2,LOW);
    sleep.pwrDownMode(); //set sleep mode
    sleep.sleepDelay(sleepTime); //sleep for: sleepTime
    
  }

  delay(10000);
  digitalWrite(trigger1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1,LOW);   
  



  long mesure1 = pulseIn(echo1,HIGH,timeout);
  /*  digitalWrite(trigger2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2,LOW);
  long mesure2 = pulseIn(echo2,HIGH,timeout);  
  digitalWrite(trigger3,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3,LOW); 
  long mesure3 = pulseIn(echo3,HIGH,timeout);*/

  float distance_mm = (mesure1/2.0)*s_speed /*+(mesure2/2.0)*s_speed + (mesure3/2.0)*s_speed*/;
  Serial.println("distance=");
  Serial.print(distance_mm/*/3*/);
  Serial.println("mm");

  d=map(distance_mm,700,1700,100,0);
  
  sendmessage(d,N);

  count++;
  
}

void ShowSerialData()
{
  while(sim.available()!=0)
  Serial.write(sim.read());
  delay(3000); 
}

void sendmessage(float d,float N){
  if (sim.available())
    Serial.write(sim.read());
 
  sim.println("AT");
  delay(1000);
 
  sim.println("AT+CPIN?");
  delay(1000);
 
  sim.println("AT+CREG?");
  delay(1000);
 
  sim.println("AT+CGATT?");
  delay(1000);
 
  sim.println("AT+CIPSHUT");
  delay(1000);
 
  sim.println("AT+CIPSTATUS");
  delay(2000);
 
  sim.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  sim.println("AT+CSTT=\"freemms\",\"\",\"\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  sim.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
 // sim.println("AT+CIFSR");//get local IP adress
 // delay(2000);
 
 // ShowSerialData();
 
  sim.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  sim.println("AT+CIPSTART=\"TCP\",\"gre'sy.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  sim.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://gre'sy.com/getData.php?&point=" + String(N) +"&niveau="+String(d);
  Serial.println(str);
  sim.println(str);
  
  delay(4000);
  ShowSerialData();
 
  sim.println((char)26);//sending
  delay(5000);
  sim.println();
 
  ShowSerialData();
 
  sim.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}
