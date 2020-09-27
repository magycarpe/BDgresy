//initialisation
#include<SoftwareSerial.h>
#include <Sleep_n0m1.h>
SoftwareSerial sim(10,11);

Sleep sleep;
unsigned long sleepTime;
int count = 0;

String number = "+33782597658";

float N=1;

float pourcentage=0;
float dmax=1430;

int h=0;
  const byte trigger1=6;
  const byte echo1=7;
  /*const byte trigger2=5;
  const byte echo2=4;
  const byte trigger3=9;
  const byte echo3=8;*/
  const unsigned long timeout = 25000UL;
  const float s_speed = 340.0/1000;

enum _parseState {
  PS_DETECT_COMMAND,
  PS_DATE,
  PS_HOUR,
};

byte state = PS_DETECT_COMMAND;
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
  
  //pinMode(2,OUTPUT);
  //digitalWrite(2,HIGH);
  //delay(10000);

  sleepTime = 7200000;
}

void loop() {

//h=heure();

if(count >= 1)
  {
    count = 0;
    //sim.println("AT+CFUN=0");
    Serial.print("sleeping ");
    Serial.println(sleepTime); 
    delay(100); //delay to allow serial to fully print before sleep
    sleep.pwrDownMode(); //set sleep mode
    sleep.sleepDelay(sleepTime); //sleep for: sleepTime
    
  }

  //sim.println("AT+CFUN=1");
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
  pourcentage=(1-(distance_mm/dmax))*100;
  Serial.println(pourcentage);
  
  sendmessage(pourcentage,N,distance_mm);
    

 /* while(detection==0){
    waitanswer();
  }
*/
    count++;
  
}

void sendmessage(float d,float N,float a){
  sim.println("AT+CMGF=1");
    delay(1000);
    sim.println("AT+CMGS=\"" + number + "\"");
    delay(1000);

    ShowSerialData();
    
    sim.println("le chalet numero " + String(N,1) + " est rempli a " + String(d,1) + " pourcent, et la distance est de " +String(a,1)+" mm ");
    delay(1000);
    
    sim.println((char)26);
    sim.write(0x1a);
    delay(1000);

    //detection=0;
    ShowSerialData();

  }

void ShowSerialData()
{
  while(sim.available()!=0)
  Serial.write(sim.read());
  delay(3000); 
}

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}

/*int heure(){
  int hour = 0;
  sim.println("AT+CCLK?");
  
  while(sim.available()) {
     byte b = sim.read();
     buffer[pos++] = b;
     
  if ( pos >= sizeof(buffer) )
    {resetBuffer();}


  switch (state) {
  case PS_DETECT_COMMAND: {
  if( pos == 6 && strcmp(buffer, "+CCLK:") == 0 ){
    resetBuffer();
    state=PS_DATE;
  }
  else{
      if ( b == '\n' )
    {resetBuffer();}
  }
  resetBuffer();
  }
  break;

  case PS_DATE:{
  if (b == ','){
    resetBuffer();
    state=PS_HOUR;
    }
  }
  break;

  case PS_HOUR:{
  if (b==':'){
    hour = atoi(buffer);
    resetBuffer();
    return hour;
    }
  }
  break;

  }
 }
}

void waitanswer(){
     while(sim.available() && detection == 0) {
     byte b = sim.read();
     buffer[pos++] = b;

  if ( pos >= sizeof(buffer) )
    {resetBuffer();}

  if ( b == '\n' )
        resetBuffer();
  else {        
        if ( pos == 8 && strcmp(buffer, "AT+CMTI:") == 0 ) {
          detection=1;
        }
    }
}
}*/
