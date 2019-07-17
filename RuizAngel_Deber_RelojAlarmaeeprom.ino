/* UNIVERSIDAD TECNICA DEL NORTE
 *         FICA-CIERCOM
 *  NOMBRE: ANGEL RUIZ
 *  TEMA: Realizar un sistema reloj con alarma almacenada en la EEPROM.
 * 
 */
#include  <LiquidCrystal.h>
#include <TimerOne.h>
#include<EEPROM.h>
#include <MsTimer2.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);// pines de la lcd
int i = 0;
int a = 0;
int j = 0;
int ff = 0;
String dato;
int minu = 0;
int hora = 0;
int MinE = 0;
int HoraE = 0;
int zumbador =7;// pin para el buzzer
int frecuencia = 100; // la frecuecia que va a tener el buzzer

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  lcd.begin(16, 2);
  Timer1.initialize(1000000);// el tiempo de ejecucion del timer 1
  Timer1.attachInterrupt(contador);// se inicia la interrupcion con el timer 1 del metodo contador
  MsTimer2::set(1000, talarma); // para dar inicio a la alarma 
  attachInterrupt(0, horas, RISING);
  attachInterrupt(1, minutos, RISING);
  minu = EEPROM.read(0);// para que lea en la posicion que tiene en la eeprom
  hora = EEPROM.read(1);// para que lea en la posicion que tiene en la eeprom
}

void loop() { Se llama a todos los metodos utilizados para hacer funcionar el sistema
  minutos();
  horas();
  configalarm();
  delay(500);
  segundos();
  Stop();
  alarma();

  if (hora > 23) {
    hora = 0;
  }

  lcd.setCursor(9, 0);
  lcd.print("HORA");
  lcd.setCursor(2, 0);
  lcd.print(':');
  lcd.setCursor(5, 0);
  lcd.print(':');
  lcd.setCursor(8, 0);
  lcd.print(' ');
  lcd.setCursor(0, 1);
  lcd.print("ALARMA PRO");
  lcd.setCursor(11, 1);
  lcd.print(HoraE);
  lcd.setCursor(13, 1);
  lcd.print(":");
  lcd.setCursor(15, 1);
  lcd.print(MinE);
}

void contador() {// metodo del contador para el reloj
  i++;
  if (i == 10) {
    EEPROM.write(0, minu); //se guarda el dato en la eeprom
    EEPROM.write(1, hora); //se guarda el dato en la eeprom
  }
  if (i > 59) {
    i = 0;
    minu++;
  }
  if (minu > 59) {
    minu= 0;
    hora++;
  }
}

void segundos() { // metodo para los segundos del reloj
  if (i < 10) {
    lcd.setCursor(6, 0);
    lcd.print(0);
    lcd.setCursor(7, 0);
    lcd.print(i);
  }
  else {
    lcd.setCursor(6, 0);
    lcd.print(i);
  }
}

void minutos() {// metodo para los minutos del reloj
  if (minu < 10) {
    lcd.setCursor(3, 0);
    lcd.print(0);
    lcd.setCursor(4, 0);
    lcd.print(minu);
  }
  else {
    lcd.setCursor(3, 0);
    lcd.print(minu);
  }
}

void horas() { //metodo para las horas del reloj
  if (hora< 10) {
    lcd.setCursor(0, 0);
    lcd.print(0);
    lcd.setCursor(1, 0);
    lcd.print(hora);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(hora);
  }
}

void alarma() { //metodo realizado para la alarma 
  if (a == 1) {
    if (minu == MinE && hora == HoraE && i == 0 ) {
      MsTimer2::start(); // se da inicio a la alarma
      tone(zumbador, frecuencia);// se le asigna la frecuncia al tono para alarma
      j = 0;
    }
    if (j == 21) {
      j = 0;
      MinE++;
      Serial.print("Alarma nueva: ");
      Serial.print(HoraE);
      Serial.print(':');
      Serial.print(MinE);
      MsTimer2::stop();
    }
  }
  else {
    Serial.print("ALARMA APAGADA");
    noTone(zumbador);
    a = 1;
    MsTimer2::stop();// se detiene la alarma
    j = 0;
  }
}

void configalarm() { // metodo en donde se ingresa los parametros para de la alarma 
  if (ff == 0) {
    Serial.println("Ingrese la Hora");
    delay(2000);
    if (Serial.available() > 0) {
      dato = Serial.readString();
      HoraE = dato.toInt();
      EEPROM.write(3, HoraE);//se guarda el dato en la posicion 3 de la eeprom
      delay(1000);
      ff = 1;
    }
  }
  if (ff == 1) {
    Serial.println(' ');
    Serial.println("Ingrese los minutos");
    delay(2000);
    if (Serial.available() > 0) {
      dato = Serial.readString();
      MinE = dato.toInt();
      EEPROM.write(4, MinE);//se guarda el dato en la posicion 4 de la eeprom
      delay(1000);
      ff = 2;
    }
  }
  if (ff == 2) {
    Serial.println(' ');
    Serial.println("Alarma activa es: ");
    Serial.print(EEPROM.read(3));//se lee el dato en la posicion 3 de la eeprom
    Serial.print(':');
    Serial.print(EEPROM.read(4));//se lee el dato en la posicion 4 de la eeprom
    ff = 3;
  }
}

void talarma() {
  j++;
}

void ho() {
  hora++;
}
void mi() {
  minu++;
}

void Stop() {// metodo que se utiliza para parar la alarma
  if ( digitalRead(2) == LOW)
    a = 0;
  if ( digitalRead(2) == HIGH)
    a = 1;
}
