#include <Arduino.h>  // Biblioteca necessária para usar funções do Arduino

// Definição dos pinos dos sensores ultrassônicos HC-SR04
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

// Configuração dos canais PWM no ESP32
#define PWM_FREQUENCIA 5000 // Frequência de PWM
#define PWM_RESOLUCAO 8     // Resolução de 8 bits (valores de 0 a 255)

// Função para medir distância dos sensores ultrassônicos
int medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH); // Captura o tempo do pulso do sensor
  return duration * 0.034 / 2; // Retorna a distância calculada em cm
}

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial

  // Configuração dos sensores ultrassônicos como entrada e saída
  pinMode(TRIG_ESQUERDO, OUTPUT);
  pinMode(ECHO_ESQUERDO, INPUT);
  
  pinMode(TRIG_DIREITO, OUTPUT);
  pinMode(ECHO_DIREITO, INPUT);
  
  pinMode(TRIG_FRENTE, OUTPUT);
  pinMode(ECHO_FRENTE, INPUT);
  
  pinMode(TRIG_TRAS, OUTPUT);
  pinMode(ECHO_TRAS, INPUT);

  // Configuração dos motores de vibração como saída PWM
  ledcSetup(0, PWM_FREQUENCIA, PWM_RESOLUCAO);
  ledcSetup(1, PWM_FREQUENCIA, PWM_RESOLUCAO);
  ledcSetup(2, PWM_FREQUENCIA, PWM_RESOLUCAO);
  ledcSetup(3, PWM_FREQUENCIA, PWM_RESOLUCAO);

  // Associação dos motores aos canais PWM
  ledcAttachPin(MOTOR_ESQUERDO, 0);
  ledcAttachPin(MOTOR_DIREITO, 1);
  ledcAttachPin(MOTOR_FRENTE, 2);
  ledcAttachPin(MOTOR_TRAS, 3);
}

void loop() {
  // Medindo distância de cada sensor
  int distanciaEsquerdo = medirDistancia(TRIG_ESQUERDO, ECHO_ESQUERDO);
  int distanciaDireito = medirDistancia(TRIG_DIREITO, ECHO_DIREITO);
  int distanciaFrente = medirDistancia(TRIG_FRENTE, ECHO_FRENTE);
  int distanciaTras = medirDistancia(TRIG_TRAS, ECHO_TRAS);

  // Mapeando intensidade da vibração (quanto mais perto, maior a vibração)
  int intensidadeEsquerdo = map(distanciaEsquerdo, 50, 5, 0, 255);
  int intensidadeDireito = map(distanciaDireito, 50, 5, 0, 255);
  int intensidadeFrente = map(distanciaFrente, 50, 5, 0, 255);
  int intensidadeTras = map(distanciaTras, 50, 5, 0, 255);

  // Limitando intensidade mínima e máxima da vibração para conforto do usuário
  intensidadeEsquerdo = constrain(intensidadeEsquerdo, 0, 255);
  intensidadeDireito = constrain(intensidadeDireito, 0, 255);
  intensidadeFrente = constrain(intensidadeFrente, 0, 255);
  intensidadeTras = constrain(intensidadeTras, 0, 255);

  // Aplicando intensidade nos motores usando PWM (LEDC no ESP32)
  ledcWrite(0, intensidadeEsquerdo);
  ledcWrite(1, intensidadeDireito);
  ledcWrite(2, intensidadeFrente);
  ledcWrite(3, intensidadeTras);

  Serial.print("Esq: "); Serial.print(distanciaEsquerdo);
  Serial.print(" | Dir: "); Serial.print(distanciaDireito);
  Serial.print(" | Frontal: "); Serial.print(distanciaFrente);
  Serial.print(" | Traseiro: "); Serial.println(distanciaTras);

  delay(100); // Pequena pausa para estabilizar leituras
}