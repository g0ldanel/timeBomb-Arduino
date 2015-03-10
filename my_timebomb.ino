#include <LiquidCrystal.h>
#include "FSM.h"
#include "myStates.h";
// constants won't change. They're used here to 
// set pin numbers:
const int btnNegro = 2;
const int btnVerde = 3;
const int btnRojo = 4;
unsigned char evento;

const int ledVerde =  6;      // the number of the LED pin
const int ledRojo =  5;      // the number of the LED pin
int ledState = LOW;
int tiempo = 15; //tiempo inicial, en minutos
short int comienzo = -1;
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
int fsm;
short int deactivating =0;
boolean desactivada = false;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledVerde, OUTPUT);      
  pinMode(ledRojo, OUTPUT);     
  // initialize the pushbutton pin as an input:
  pinMode(btnNegro, INPUT);     
  pinMode(btnVerde, INPUT);     
  pinMode(btnRojo, INPUT);    
  digitalWrite(btnNegro, HIGH);
  digitalWrite(btnVerde, HIGH);
  digitalWrite(btnRojo, HIGH);  
  
  lcd.begin(16, 2);
  
  FSM.begin(FSM_NextState,nStateMachine,FSM_State,nStateFcn,S_INITIAL);
}
  

void loop(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("airsoftBomb");
  lcd.setCursor(0,1);
  lcd.write("g0ldan a. 1");
  digitalWrite(ledRojo, HIGH);   // turn the LED on (HIGH is the voltage level)
  /*
  if(digitalRead(btnNegro)== LOW)
  {    
  //  lcd.write("boton negro");
    evento = bnegro;
  }  
  else
  {
    if(digitalRead(btnVerde)== LOW)
    {
//      lcd.write("boton verde");
      evento = bverde;
    }
    else
    {
      if(digitalRead(btnRojo)== LOW)
      {
//        lcd.write("boton rojo");
        evento = brojo;
      }
      
    }      
  }
  FSM.AddEvent(evento);
  FSM.Update();
  delay(100);   
**/
}


/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
void estadoinicial(void)
{
  digitalWrite(ledVerde,HIGH);
  digitalWrite(ledRojo,LOW); 
  tiempo = 15;  
  comienzo=-1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("airsoftBomb");
  lcd.setCursor(0,1);
  lcd.write("g0ldan a. 1");
}
void adjusting(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("airsoftBomb");
  lcd.setCursor(0,1);
  lcd.print("tiempo: " + String(tiempo));
    
}
void addTime(void)
{
  tiempo++;
  FSM.AddEvent(EV_BACK);
}
void subTime(void)
{
  tiempo--;
  FSM.AddEvent(EV_BACK);
}
void counting(void)
{
  if(comienzo==-1)
    comienzo == millis();
    
  int trestante = ((millis()-comienzo)/1000);
  
  if(trestante>(tiempo*60))
  {
    FSM.AddEvent(EV_BOOM);
  }
  else
  {      
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("BOMBA ACTIVADA");
    lcd.setCursor(0,1);
    lcd.print(String("[") + String(trestante/60) + String(":") + String(trestante%60));    
  }   
  
  parpadea();
  
  digitalWrite(ledRojo, ledState);
    
}
void failure(void)
{
  tiempo -=5;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("ERROR ERROR");
  lcd.setCursor(0,1);
  lcd.write("T - 5 MINUTOS");
  FSM.AddEvent(EV_BACK);
}
void deactivated(void)
{
  if(evento==bverde && deactivating == 0){
    deactivating= millis();}
    
  if(millis() - deactivating>=10000)
    FSM.AddEvent(EV_SUCCESS); 
   
  
}
void explosion(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("EXPLOSION");
  lcd.setCursor(0,1);
  lcd.write("   EXPLOSION");
}
  
void parpadea(void)
{
  if(ledState==LOW)
  {
    ledState=HIGH;
  }
  else
  {
    ledState=LOW;
  }
}
