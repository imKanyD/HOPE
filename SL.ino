//Definição PORTAS ESP - PONTE H
  #define ENA 14
  #define MOTOR1F 12			//IN1
  #define MOTOR1B 13			//IN2
  #define MOTOR2F 27			//IN3
  #define MOTOR2B 33			//IN4
  #define ENB 32

//Definição PORTAS ESP32 - SEGUE LINHA
  #define SENSORE 16
  #define SENSORD 5

//Definição de valores de PWM para testes, melhor adequação dos motores e melhor adaptação aos circuitos propostos.
  int POT = 250;

void setup(){
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(MOTOR1F, OUTPUT);
    pinMode(MOTOR1B, OUTPUT);
    pinMode(MOTOR2F, OUTPUT);
    pinMode(MOTOR2B, OUTPUT);
    pinMode(SENSORD, INPUT);
    pinMode(SENSORE, INPUT);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);

    Serial.begin(9600);

  }

 void loop(){
    if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == HIGH){ //Não detectou a presença de linha, funcionamento padrão, segue o movimento
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
        Serial.println("FRENTE");
      }

    if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == LOW){ //O SENSORD detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M2 liga para alinhar novamente
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,0);
        Serial.println("DIREITA");
      }

    if(digitalRead(SENSORD) == LOW && digitalRead(SENSORE) == HIGH){ //O SENSORE detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M1 liga para alinhar novamente
        analogWrite(MOTOR1F,0);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
        Serial.println("ESQUERDA");
      }

    if(digitalRead(SENSORD) == LOW && digitalRead(SENSORE) == LOW)//Detectou a presença de linha em ambos sensores, MOFF
      { 
        analogWrite(MOTOR1F,0);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,0);
        Serial.println("PARADO");
      }
  }