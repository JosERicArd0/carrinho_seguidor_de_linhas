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

void evasao();

void setup() 
{
  // Definindo os motores e outros componentes como saídas
  pinMode(IN1, OUTPUT); // Saída para motor A              
  pinMode(IN2, OUTPUT); // Saí da para motor A              
  pinMode(IN3, OUTPUT); // Saída para motor B            
  pinMode(IN4, OUTPUT); // Saída para motor B            
  pinMode(ENA, OUTPUT); // Controle velocidade motor A             
  pinMode(ENB, OUTPUT); // Controle velocidade motor B 

  // Definindo os LEDs como saídas
  pinMode(LED_VERDE, OUTPUT); // LED verde
  pinMode(LED_VERMELHO, OUTPUT); // LED vermelho

  // Velocidades dos motores
  analogWrite(ENA, 90); // Controle PWM do motor A (0 a 255)            
  analogWrite(ENB, 85); // Controle PWM do motor B (0 a 255)              

  // Configura os pinos do sensor ultrassônico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(5000); // Aguarda 5 segundos antes de iniciar                   
}

void loop() 
{
  float dist_cm = distancia(); // Declara variável que armazena a distância do obstáculo  

  if (dist_cm < 20) // Se a distância for menor que 20 cm
  {
    // Acende o LED vermelho
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);


    // Desvia se encontrar um obstáculo
//     evasao();
  } 
  else 
  {
    // Apaga o LED vermelho
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);

    // Robô anda para frente se não houver obstáculos
    robo_frente();
  }                        
}

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

void robo_frente() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void robo_esquerda() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
}

void robo_parado() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   
}

void evasao() 
{
  robo_parado();
  delay(500); // Espera um pouco para garantir que o robô pare completamente
  
  
  // Verifica se ainda está com um obstáculo à frente
  if (distancia() < 20) 
  {
    // Se ainda estiver preso, tenta dar um giro pequeno
 //   robo_parado();
   // delay(500);
  //  robo_esquerda();
  //  delay(300);
  }