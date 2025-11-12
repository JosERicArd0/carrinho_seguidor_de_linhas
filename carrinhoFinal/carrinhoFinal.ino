#define TRIGGER_PIN 3  // Pino Trigger do sensor na porta 3       
#define ECHO_PIN    2  // Pino Echo do sensor na porta 2

// definindo as portas onde estão conectados os motores 
#define IN1 7  //Pinos motor A (Direita)        
#define IN2 6  //Pinos motor A (Direita)                
#define IN3 5  //Pinos motor B (Esquerda)                    
#define IN4 4  //Pinos motor B (Esquerda)   

#define ENA 10  //Pino velocidade motor A (Enable A)              
#define ENB 11  //Pino velocidade motor B (Enable B)  

#define LED_VERDE 9 // Pino do LED verde
#define LED_VERMELHO 8  // Pino do LED vermelho

#define sensorE A0 // Pino do sensor IV esquerdo
#define sensorD A1 // Pino do sensor IV direito

void setup() 
{
  // Definindo os motores e outros componentes como saídas
  pinMode(IN1, OUTPUT); // Saída para motor A              
  pinMode(IN2, OUTPUT); // Saí da para motor A              
  pinMode(IN3, OUTPUT); // Saída para motor B            
  pinMode(IN4, OUTPUT); // Saída para motor B            
  pinMode(ENA, OUTPUT); // Controle velocidade motor A             
  pinMode(ENB, OUTPUT); // Controle velocidade motor B 

  //  Definindo os sensores IV
  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);

  // Definindo os LEDs como saídas
  pinMode(LED_VERDE, OUTPUT); // LED verde
  pinMode(LED_VERMELHO, OUTPUT); // LED vermelho

  // Configura os pinos do sensor ultrassônico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(5000); // Aguarda 5 segundos antes de iniciar                   

int POT = 70; // Velocidade dos motores (padrões por enquanto)

}

void loop() 
{
modoSeguidorLinha(); // def. do sensor IV

distancia_cm(); // def. do ultrassônico
}

///////////////////////////////////////////////////////////////////
void modoSeguidorLinha() // sensores IV
{
  if (digitalRead(sensorE) == HIGH && digitalRead(sensorD) == HIGH)
  { // detectou a linha preta nos dois sensores
    robo_parado();
  }
  
  if (digitalRead(sensorE) == HIGH && digitalRead(sensorD) == LOW)
  { // detectou a linha preta na esquerda
    robo_direita();
  }

  if (digitalRead(sensorE) == LOW && digitalRead(sensorD) == HIGH)
  { // detectou a linha preta na direita
    robo_esquerda();
  }

  if (digitalRead(sensorE) == LOW && digitalRead(sensorD) == LOW)
  { // não detectou nenhuma linha preta
    robo_frente();

///////////////////////////////////////////////////////////////////////
void robo_frente() // direções 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, POT); // Aplica a potência definida ao motor A
  analogWrite(ENB, POT); // Aplica a potência definida ao motor B

}

void robo_esquerda() //Direções
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 

  analogWrite(ENA, POT); // Aplica a potência definida ao motor A
  analogWrite(ENB, POT); // Aplica a potência definida ao motor B

}

void robo_direita() //Direções
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 

  analogWrite(ENA, POT); // Aplica a potência definida ao motor A
  analogWrite(ENB, POT); // Aplica a potência definida ao motor B

}

void robo_parado() //Direções
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  

  analogWrite(ENA, 0); // Aplica a potência definida ao motor A
  analogWrite(ENB, 0); // Aplica a potência definida ao motor B
 
}
/////////////////////////////////////////////////////////////

void distancia_cm()
{
float dist_cm = distancia(); // Declara variável que armazena a distância do obstáculo  

  if (dist_cm <= 20) // Se a distância for menor que 20 cm
  {
    // Acende o LED vermelho
  led_stop();
  robo_parado(); 
  } 
  
  if  (dist_cm >= 20)
  {
    // acende o LED verde
  led_on();
  robo_frente();
  }                         
  }
}

/////////////////////////////////////////////////////////

float distancia() 
{
  // Envia o pulso para o sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN, LOW);

  // Lê o tempo que o sinal de retorno (ECHO) leva
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula a distância em centímetros (velocidade do som: 343 m/s ou 29 microsegundos/cm)
  float distance = (duration / 2.0) / 29.1;

  return distance; 
}

void led_on()
{
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);
}

void led_stop()
  {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
