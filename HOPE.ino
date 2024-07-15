#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ESP32Servo.h>

//Definição PORTAS ESP - PONTE H
  #define ENA 14
  #define MOTOR1F 12			//IN1
  #define MOTOR1B 13			//IN2
  #define MOTOR2F 27			//IN3
  #define MOTOR2B 33			//IN4
  #define ENB 32
 
//Definição SENSORES SL
  #define SENSORE 16
  #define SENSORD 5

BluetoothSerial SerialBT;

// Pino GPIO conectado ao servo motor
const int servoPin = 2;

// Objeto Servo para controlar o servo motor
Servo myServo;

bool useFirstCode = true;
bool stopRequested = false;
unsigned long stopTime = 0;
int POT = 200;

void setup() {
  SerialBT.begin("HOPE"); // Bluetooth

  //Motores
  pinMode(ENA, OUTPUT);
  pinMode(MOTOR1F, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2F, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(ENA, HIGH);  
  digitalWrite(ENB, HIGH);

  //SENSORES
  pinMode(SENSORE, INPUT);
  pinMode(SENSORD, INPUT);

  //SERVO
  myServo.attach(servoPin);
}

void loop() {
  if (SerialBT.available()) { //Configuração Bluetooth
    char signal = SerialBT.read();
    switchCode(signal);
  }

  if (useFirstCode) {
    Bluetooth();
  } else {
    SL();
  }
}
void switchCode(char signal) {
  if (signal == 'W') {
    useFirstCode = false;
  } else if (signal == 'w') {
    useFirstCode = true;
  } 
}
void SL(){
    if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == HIGH){ //Não detectou a presença de linha, funcionamento padrão, segue o movimento
        digitalWrite(MOTOR1F,HIGH);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,HIGH);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("FRENTE");
      }

    if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == LOW){ //O SENSORD detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M2 liga para alinhar novamente
        digitalWrite(MOTOR1F,LOW);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,HIGH);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("DIREITA");
      }

    if(digitalRead(SENSORD) == LOW && digitalRead(SENSORE) == HIGH){ //O SENSORE detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M1 liga para alinhar novamente
        digitalWrite(MOTOR1F,HIGH);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,LOW);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("ESQUERDA");
      }

    if(digitalRead(SENSORD) == LOW && digitalRead(SENSORE) == LOW)//Detectou a presença de linha em ambos sensores, MOFF
      { 
        digitalWrite(MOTOR1F,LOW);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,LOW);
        digitalWrite(MOTOR2B,LOW);
        myServo.write(180);
        Serial.println("PARADO");
      }
  }

void Bluetooth(){
    char ENTRADA = SerialBT.read();
      switch(ENTRADA){
        case 'S': //Parado
        digitalWrite(MOTOR1F,LOW);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,LOW);
        digitalWrite(MOTOR2B,LOW);
        //Serial.println("Parado");
        break;

        case 'F': //Frente
        digitalWrite(MOTOR1F,HIGH);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,HIGH);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("Frente");
        break;

        case 'B': //Trás
        digitalWrite(MOTOR1F,LOW);
        digitalWrite(MOTOR1B,HIGH);
        digitalWrite(MOTOR2F,LOW);
        digitalWrite(MOTOR2B,HIGH);
        Serial.println("Tras");
        break;

        case 'L': //Esquerda
        digitalWrite(MOTOR1F,HIGH);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,LOW);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("Esquerda");
        break;

        case 'R': //Direita
        digitalWrite(MOTOR1F,LOW);
        digitalWrite(MOTOR1B,LOW);
        digitalWrite(MOTOR2F,HIGH);
        digitalWrite(MOTOR2B,LOW);
        Serial.println("Direita");
        break;

        case 'H':// Mover o servo para a posição 0 graus
        myServo.write(0);
        break;

        case 'J':// Mover o servo para a posição 180 graus
        myServo.write(180);
        break;

        default:
        break;
      }
  }
