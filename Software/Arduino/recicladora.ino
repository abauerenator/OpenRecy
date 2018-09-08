#include <Servo.h>
#include "HX711.h"
#define LEDR 3
#define LEDG 6
#define LEDB 11
#define DOUT  A1
#define CLK  A0

#define MOTORENABLE 5
#define MOTOR1A A5
#define MOTOR1B A4
#define MOTOR2A A3
#define MOTOR2B A2
#define SALIDA 13
HX711 scale(DOUT, CLK);
float calibration_factor = 390; // factor de calibracion Celda
Servo servo1;
Servo servo2;
String data = "";
int length = 0;
int contador = 0;
int contador2 = 0;
int estadoBoton  = 0;
int estadoBotonAnt  = 0;
int peso = 0;
int pOk = 0;
int pokAnt = 0;
long t;
void fadeleds(int);
void rechazarBotella();
void aceptarBotella();
void transportadoraOn();
void transportadoraOff();
void verde();
void azul();
void transparente();
void moverBotella();
int pesar();
void colores(char);


void setup(){
 Serial.begin(115200);
 scale.set_scale();
 scale.tare(); 
 scale.set_scale(calibration_factor);
 servo1.attach(9);
 servo2.attach(10);
 pinMode(LEDR, OUTPUT);
 pinMode(LEDB, OUTPUT);
 pinMode(LEDG, OUTPUT);
 pinMode(MOTOR1A, OUTPUT);
 pinMode(MOTOR1B, OUTPUT);
 pinMode(MOTOR2A, OUTPUT);
 pinMode(MOTOR2B, OUTPUT);
 pinMode(SALIDA, OUTPUT);
 digitalWrite(MOTOR1A, LOW);
 digitalWrite(MOTOR1B, LOW);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW); 
 
 analogWrite(MOTORENABLE, 0);
 analogWrite(LEDR, 0);
 analogWrite(LEDG, 0);
 analogWrite(LEDB, 0);
 servo1.write(100);
 servo2.write(85); 
  digitalWrite(SALIDA, LOW);
}


void loop(){
  
  /*
  //Serial.println(contador, DEC);
  estadoBoton = digitalRead(BOTONF);
  if(estadoBoton != estadoBotonAnt){ if(estadoBoton == LOW){Serial.print("BF1\n");}delay(50);}
  estadoBotonAnt=estadoBoton;
 */
  pOk = pesar();
  if(pOk != pokAnt){ if(pOk == 1){Serial.print("pok\n");} if(pOk == 0){Serial.print("pno\n"); contador = 0;}}
  pokAnt=pOk;
  if(pOk == 1){contador++;}
  
 
  
 

  while (Serial.available()) {
    delay(3); 
    if (Serial.available() >0) {
      char c = Serial.read(); 
      data += c; 
    } 
  }
  
  
  
  
   if (data.length() >0) {
      Serial.println(data); //see what was received
      if(data == "fl"){fadeleds(5);}
      if(data == "av"){colores('g');
                       verde();
                       transportadoraOn();
                       aceptarBotella();
                       delay(2000);
                       transparente();
                       delay(1500);
                       transportadoraOff();
                       Serial.print("ok\n");
                       colores('n');
                       digitalWrite(SALIDA, HIGH);
                       delay(10);
                       digitalWrite(SALIDA, LOW);
                       }
      
      if(data == "at"){colores('w');
                       transparente();
                       transportadoraOn();
                       aceptarBotella();
                       delay(2000);
                       transparente();
                       delay(3000);
                       transportadoraOff();
                       Serial.print("ok\n");
                       colores('g');
                       digitalWrite(SALIDA, HIGH);
                       delay(10);
                       digitalWrite(SALIDA, LOW);
                       }
                       
      if(data == "aa"){colores('b');
                       azul();
                       transportadoraOn();
                       aceptarBotella();
                       delay(2000);
                       transparente();
                       delay(1500);
                       transportadoraOff();
                       Serial.print("ok\n");
                       colores('g');
                       digitalWrite(SALIDA, HIGH);
                       delay(10);
                       digitalWrite(SALIDA, LOW);
                       }
      if(data == "no"){rechazarBotella();}
      if(data == "vd"){verde();}
      if(data == "tr"){transparente();}
      if(data == "az"){azul();}
      if(data == "mb"){moverBotella();}
      if(data == "r"){colores('r');}
      if(data == "g"){colores('g');}
      if(data == "b"){colores('b');}
      if(data == "n"){colores('n');}
      if(data == "a"){colores('a');}
      if(data == "v"){colores('v');}
      if(data == "w"){colores('w');delay(5000);}
      data = "";
      
   }

 
 
  
   
  
}

void verde(){
 servo1.write(100);
 servo2.write(45); 
}

void transparente(){
 servo1.write(100);
 servo2.write(85); 
}


void azul(){
 servo1.write(140);
 servo2.write(90); 
}


void transportadoraOn(){
  
 analogWrite(MOTORENABLE, 255);
 digitalWrite(MOTOR1A, LOW);
 digitalWrite(MOTOR1B, HIGH);
}

void transportadoraOff(){
 
 digitalWrite(MOTOR1A, LOW);
 digitalWrite(MOTOR1B, LOW);
 analogWrite(MOTORENABLE, 0); 
  
  
}



void moverBotella(){
  
 if(contador == 4){
 analogWrite(MOTORENABLE, 170);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, HIGH);
 delay(50);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);}

 if(contador == 8){
 analogWrite(MOTORENABLE, 170);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, HIGH);
 delay(50);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);}

 if(contador == 12){
 analogWrite(MOTORENABLE, 170);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, HIGH);
 delay(50);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);}

 if(contador == 16){
 analogWrite(MOTORENABLE, 170);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, HIGH);
 delay(50);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);}


 if(contador == 20){
 
 digitalWrite(MOTOR2A, HIGH);
 digitalWrite(MOTOR2B, LOW);
 delay(50);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW); contador = 0;contador2++;}
 if(contador2 == 2){Serial.print("pno\n");delay(500);rechazarBotella();contador2 = 0;}
  
 
}


void aceptarBotella(){
  
 analogWrite(MOTORENABLE, 255);
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, HIGH);
 delay(1600);
 
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);
 
  
  
}

void rechazarBotella(){
 analogWrite(LEDR, 0); analogWrite(LEDG, 255); analogWrite(LEDB, 255);
 analogWrite(MOTORENABLE, 255);
 digitalWrite(MOTOR2A, HIGH);
 digitalWrite(MOTOR2B, LOW);
 delay(700);
 analogWrite(MOTORENABLE, 0); 
 digitalWrite(MOTOR2A, LOW);
 digitalWrite(MOTOR2B, LOW);
 Serial.print("px\n");
 
     
}


int pesar(){
  int pok = 0;
  peso = scale.get_units();
  //Serial.print(peso);
  //Serial.println();
  if(peso >= 10 && peso <= 30){ delayMicroseconds(50); peso = scale.get_units(); if(peso >= 10 && peso <= 30){ pok=1; fadeleds(6); moverBotella();}}else
  if(peso > 32 ){pok = 0; analogWrite(LEDR, 0); analogWrite(LEDG, 255); analogWrite(LEDB, 255);}
  
  else{analogWrite(LEDR, 255); analogWrite(LEDG, 255); analogWrite(LEDB, 255);pok = 0;}
  return(pok);
}




void fadeleds(int c){
  
  while(c > 0){
  
 for(int ledsBrillo = 0; ledsBrillo <= 50; ledsBrillo++){
 analogWrite(LEDR, ledsBrillo);
 analogWrite(LEDG, ledsBrillo);
 analogWrite(LEDB, ledsBrillo);
 delayMicroseconds(50);
 }

 for(int ledsBrillo = 50; ledsBrillo >= 0; ledsBrillo--){
  analogWrite(LEDR, ledsBrillo);
  analogWrite(LEDG, ledsBrillo);
  analogWrite(LEDB, ledsBrillo);
  delayMicroseconds(50);
 } 
 
 /*
 for(int ledsBrillo = 0; ledsBrillo <= 255; ledsBrillo++){
 analogWrite(LEDG, ledsBrillo);
 delayMicroseconds(50);
 }

 for(int ledsBrillo = 255; ledsBrillo >= 0; ledsBrillo--){
  analogWrite(LEDG, ledsBrillo);
  delayMicroseconds(50);
 } 
 
  
 for(int ledsBrillo = 0; ledsBrillo <= 255; ledsBrillo++){
 analogWrite(LEDR, ledsBrillo);
 delayMicroseconds(50);
 }

 for(int ledsBrillo = 255; ledsBrillo >= 0; ledsBrillo--){
  analogWrite(LEDR, ledsBrillo);
  delayMicroseconds(50);
 } 
 
 
 for(int ledsBrillo = 0; ledsBrillo <= 255; ledsBrillo++){
 analogWrite(LEDB, ledsBrillo);
 delayMicroseconds(50);
 }

 for(int ledsBrillo = 255; ledsBrillo >= 0; ledsBrillo--){
  analogWrite(LEDB, ledsBrillo);
  delayMicroseconds(50);
 } */
 c--;
  }
  
  
}



void colores(char c){
  if(c == 'r'){analogWrite(LEDR, 0);
               analogWrite(LEDG, 255);
               analogWrite(LEDB, 255);
               }
  if(c == 'g'){analogWrite(LEDG, 0);
               analogWrite(LEDR, 255);
               analogWrite(LEDB, 255);
               }
  if(c == 'b'){analogWrite(LEDB, 0);
               analogWrite(LEDG, 255);
               analogWrite(LEDR, 255);
               }
  if(c == 'n'){analogWrite(LEDB, 255);
               analogWrite(LEDG, 255);
               analogWrite(LEDR, 255);}
               
  if(c == 'a'){analogWrite(LEDR, 0);
               analogWrite(LEDG, 0);
               analogWrite(LEDB, 255);}
               
  if(c == 'v'){analogWrite(LEDR, 0);
               analogWrite(LEDG, 255);
               analogWrite(LEDB, 0);}
               
  if(c == 'w'){analogWrite(LEDR, 0);
               analogWrite(LEDG, 0);
               analogWrite(LEDB, 0);}
  
}

