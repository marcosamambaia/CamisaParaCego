#include <Arduino.h>  // Biblioteca necessária para usar funções do Arduino

// Definição dos pinos dos sensores ultrassônicos
#define TRIG_ESQUERDO 12  // Sensor no ombro esquerdo
#define ECHO_ESQUERDO 13  

#define TRIG_DIREITO 14   // Sensor no ombro direito
#define ECHO_DIREITO 15  

#define TRIG_FRENTE 16    // Sensor frontal
#define ECHO_FRENTE 17  

#define TRIG_TRAS 18      // Sensor traseiro
#define ECHO_TRAS 19  

// Definição dos pinos dos motores de vibração
#define MOTOR_ESQUERDO 21 // Motor do ombro esquerdo
#define MOTOR_DIREITO 22  // Motor do ombro direito
#define MOTOR_FRENTE 23   // Motor frontal
#define MOTOR_TRAS 25     // Motor traseiro

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial

  // Configuração dos sensores ultrassônicos
  pinMode(TRIG_ESQUERDO, OUTPUT);
  pinMode(ECHO_ESQUERDO, INPUT);
  
  pinMode(TRIG_DIREITO, OUTPUT);
  pinMode(ECHO_DIREITO, INPUT);
  
  pinMode(TRIG_FRENTE, OUTPUT);
  pinMode(ECHO_FRENTE, INPUT);
  
  pinMode(TRIG_TRAS, OUTPUT);
  pinMode(ECHO_TRAS, INPUT);

  // Configuração dos motores de vibração
  pinMode(MOTOR_ESQUERDO, OUTPUT);
  pinMode(MOTOR_DIREITO, OUTPUT);
  pinMode(MOTOR_FRENTE, OUTPUT);
  pinMode(MOTOR_TRAS, OUTPUT);
}

// Função para medir distância de um sensor ultrassônico
int medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Retorna a distância calculada em cm
}

void loop() {
  // Medindo distância de cada sensor
  int distanciaEsquerdo = medirDistancia(TRIG_ESQUERDO, ECHO_ESQUERDO);
  int distanciaDireito = medirDistancia(TRIG_DIREITO, ECHO_DIREITO);
  int distanciaFrente = medirDistancia(TRIG_FRENTE, ECHO_FRENTE);
  int distanciaTras = medirDistancia(TRIG_TRAS, ECHO_TRAS);

  // Ativando os motores conforme a proximidade dos obstáculos
  digitalWrite(MOTOR_ESQUERDO, (distanciaEsquerdo < 50) ? HIGH : LOW);
  digitalWrite(MOTOR_DIREITO, (distanciaDireito < 50) ? HIGH : LOW);
  digitalWrite(MOTOR_FRENTE, (distanciaFrente < 50) ? HIGH : LOW);
  digitalWrite(MOTOR_TRAS, (distanciaTras < 50) ? HIGH : LOW);

  // Pequena pausa para estabilizar as leituras
  delay(100);
}