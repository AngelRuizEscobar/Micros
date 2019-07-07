/*UNIVERSIDAD TECNICA DEL NORTE
 * FICA-CIERCOM
 * NOMBRE: ANGEL RUIZ
 * TEMA: REALIZAR UN SISTEMA DOMOTICO EN EL CUAL SE ENCIENDAN 5 LUCES DE DORMITORIOS
 * EN EL HORARIO NOCTURNO PARA LO CUAL EL SISTEMA DEBE ACTIVARSE CON UNA CONTRASEÑA Y
 * PARA EL HORARIO NOCTURO SE LO REALIZO CON UN PULSADOR SIMULANDO A UN LDR PARA EL EFECTO DE
 * NOCHE Y DIA.
 * 
 */
String pasw;
boolean validar;
int pulse=5;
int j;
int funcion=0;
int leds=0;
void setup() {
  Serial.begin(9600);//comunicacion serial
  attachInterrupt(0,funcionamiento,LOW);
  pinMode(10,OUTPUT);// pin de led1
  pinMode(9,OUTPUT);//pin de led2
  pinMode(8,OUTPUT);//pin de led3
  pinMode(7,OUTPUT);//pin de led4
  pinMode(6,OUTPUT);//pin de led5
  pinMode(5,INPUT);// pin del pulsador
  //Serial.println("Ingrese la Contrasenia");
}
void loop() {
  if(funcion==1){
  if(Serial.available()>0){// se verifica que haya un valor mayor a cero para continuar con rl programa
    pasw=Serial.readString();// se obtiene lo que se ingresa en el seria
    if(pasw.length()!=4){// se verifica si la contraseña es mayor a 4 digitos
      Serial.println("La contrasenia es mayor a 4 digitos");
      }else{
        validar=pasw.equals("AARE");// la clase que se redistro para el sistema
        if(validar==true){// valida si la contraseña es verdadera
          Serial.println("Contrasenia Valida");
           
          }else{// caso contrario si la contraseña es incorrecta se imprime un mensaje.
            Serial.println("Contrasenia Incorrecta");
            }
            
        }
    }
  }
  
  if(leds==1){// si el led esta en 1 realiza la siguiente codicion
    j=digitalRead(pulse);// lee el pulso que se esta dando
          if(j==HIGH){// si el pulso esta en alto prende los leds o las luces de los dormitorios cuando esta en la noche
          analogWrite(10,random(0, 255));
          analogWrite(9, random(0, 255));
          analogWrite(8, random(0, 255));
          analogWrite(7, random(0, 255));
          analogWrite(6, random(0, 255));
          delay(100);
            }else{// caso contrario las apaga cuando ya no esta el pulso en alto o esta de dia 
                digitalWrite(10,LOW);
                analogWrite(10,LOW);
                analogWrite(9,LOW);
                analogWrite(8,LOW);
                analogWrite(7,LOW);
                analogWrite(6,LOW);
                delay(100);
              }
    }
    
  }


void funcionamiento(){// void de funionamiento
  switch(funcion){// switch de la funcion a realizar
    case 0:// en el case 1 va a pedir que ingrese la contrasenia para activar el sistema.
    Serial.println("Ingrese la contrasenia");
    funcion++;
    break;
    }
  }
