//Definição PORTAS ESP - PONTE H
  #define MOTOR1F 12			//IN1
  #define MOTOR1B 13			//IN2
  #define MOTOR2F 27			//IN3
  #define MOTOR2B 33			//IN4

  //Definição PORTAS ESP - ULTRASSNICO
  #define TRIGGER 17
  //#define ECHO1 36
  #define ECHO 39

  //Definição PORTAS ESP32 - SEGUE LINHA
  #define SENSORD 16
  #define SENSORE 5

  //Inclusão do Servo
  #include <Servo.h>
  Servo ServoEmpilhadeira;

  //Inclusão do Bluetooth
  #include BluetoothSerial.h
  BluetoothSerial SerialBT;

  //Armazena o que vier do Bluetooth
  char ENTRADA;

  //Definição dos modos do carrinho
  int MODO;

  //Sensor Ultrassônico
  int TEMPO;
  int DIST;

  //Definição de valores de PWM para testes, melhor adequação dos motores e melhor adaptação aos circuitos propostos.
  int POT = 255

  void setup()
  {
    Seria.begin(115200);
    SerialBT.begin("ESP32"); //Nome do dispositivo
    pinMode(MOTOR1F, OUTPUT);
    pinMode(MOTOR1B, OUTPUT);
    pinMode(MOTOR2F, OUTPUT);
    pinMode(MOTOR2B, OUTPUT);
    pinMode(SENSORD, INPUT);
    pinMode(SENSORE, INPUT);
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO,INPUT);

    ServoEmpilhadeira.attach(2);
  }

  void loop()
  {
    if(MODO == 0)Bluetooth;
    if(MODO ==1)SLINHA;
  }
  void Bluetooth(){ 
    if(Serial.available()>0){
      ENTRADA = Serial.read(); //LEITURA DO CARACTER ENVIADO PELO APP

      switch(entrada){
        case 'F': //Frente
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
        break;

        case 'B': //Trás
        analogWrite(MOTOR1F, 0);
        analogWrite(MOTOR1B,POT);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,POT);
        break;

        case 'L': //Esquerda
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,0);
        break;

        case 'R': //Direita
        analogWrite(MOTOR1F, 0);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
        break;


      }
    }
  }

    void SLINHA(){
      if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == HIGH){ //Detectou a presença de uma linha nos dois censores, então os motores desligam
        analogWrite(MOTOR1F,0);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,0);
      }
      else if(digitalRead(SENSORD) == HIGH && digitalRead(SENSORE) == LOW){ //O SENSORD detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M2 liga para alinhar novamente
        analogWrite(MOTOR1F,0);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
      }
       else if(digitalRead(SENSORD) == LOW && digitalRead(SENSORE) == HIGH){ //O SENSORE detectou a presença de linha, então para que HOPE continue seguindo o caminho, o M1 liga para alinhar novamente
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,0);
        analogWrite(MOTOR2B,0);
      }
      else{ //Como não detectou a presença de linhas, HOPE segue o funcionamento padrão
        analogWrite(MOTOR1F,POT);
        analogWrite(MOTOR1B,0);
        analogWrite(MOTOR2F,POT);
        analogWrite(MOTOR2B,0);
      }
  }