int In1Pin_1 = 9;
int In2Pin_1 = 10;
int PWMPin_1 = 3;

int In1Pin_2 = 11;
int In2Pin_2 = 12;
int PWMPin_2 = 5;

int triggerPort = 7;
int echoPort = 8;
int ledPort = 2;
int buttonPin = 4;
int powerLedPin = 13;

int pending = 6;
boolean fermati = false;
boolean attivo = false;

//  Parameters
//
int totPending = 6;
int maxSpeed = 140;
int turnSpeed = 120;
int currentSecureDistance = 0;
int secureDistance = 15;
int turnSecureDistance = 40;
int timeBeforeTurn = 1000;


// the setup routine runs once when you press reset:
void setup() {                
  
  attivo = false;
  
  currentSecureDistance = secureDistance;
  
  //  Sensors ports
  pinMode(buttonPin, INPUT);
  pinMode(powerLedPin, OUTPUT);
  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
  pinMode( ledPort, OUTPUT );
  
  //  Ruota sinistra
  //
  pinMode(In1Pin_1, OUTPUT);
  pinMode(In2Pin_1, OUTPUT);
  pinMode(PWMPin_1, OUTPUT);
  
  //  Ruota destra
  //
  pinMode(In1Pin_2, OUTPUT);
  pinMode(In2Pin_2, OUTPUT);
  pinMode(PWMPin_2, OUTPUT);
  
  Serial.begin( 9600 );
  
}

// the loop routine runs over and over again forever:
void loop() {
  
 boolean buttonState = digitalRead(buttonPin); 
 if (buttonState == HIGH) {     
    // turn LED on:    
    if (!attivo) {
      attivo = true;
      digitalWrite(powerLedPin, HIGH);  
    } else {
      
      attivo = false;
      currentSecureDistance = secureDistance;
      
      digitalWrite(ledPort, LOW);
      
      digitalWrite(In1Pin_1, HIGH);
      digitalWrite(In2Pin_1, HIGH);
      analogWrite(PWMPin_1, 0);
      digitalWrite(In1Pin_2, HIGH);
      digitalWrite(In2Pin_2, HIGH);
      analogWrite(PWMPin_2, 0);
    
      digitalWrite(powerLedPin, LOW);  
      delay(1000);
    }
  } 
 
  
  if (attivo) {
  
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  delayMicroseconds(2);
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
  long duration = pulseIn( echoPort, HIGH );
  long r = (duration / 2)/29.1;
  Serial.print( "durata: " );
  Serial.print( duration );
  Serial.print( " , " );
  Serial.print( "distanza: " );
  
  
  
  Serial.print( r );
  Serial.println( "cm" );
  if (r <= currentSecureDistance) {
    fermati = true;
    digitalWrite(ledPort, HIGH);
  } else {
    fermati = false;
    digitalWrite(ledPort, LOW);
  }
  
  
  if (!fermati && pending == 0) {
    
    currentSecureDistance = secureDistance;
    
    digitalWrite(In1Pin_1, HIGH);
    digitalWrite(In2Pin_1, LOW);
    analogWrite(PWMPin_1, maxSpeed);
    
    digitalWrite(In1Pin_2, LOW);
    digitalWrite(In2Pin_2, HIGH);
    analogWrite(PWMPin_2, maxSpeed);
    
    
  } else {
    
    if (currentSecureDistance == secureDistance) {
      digitalWrite(In1Pin_1, HIGH);
      digitalWrite(In2Pin_1, HIGH);
      analogWrite(PWMPin_1, 0);
      digitalWrite(In1Pin_2, HIGH);
      digitalWrite(In2Pin_2, HIGH);
      analogWrite(PWMPin_2, 0);
      delay(timeBeforeTurn);
      
      pending = totPending;
    }
    
    pending--;
    
    Serial.print( pending );
    
    
    if (pending < 0) {
      pending = 0;
    }
    
    
    currentSecureDistance = turnSecureDistance;
    
    digitalWrite(In1Pin_1, HIGH);
    digitalWrite(In2Pin_1, HIGH);
    analogWrite(PWMPin_1, 0);
    
    digitalWrite(In1Pin_2, HIGH);
    digitalWrite(In2Pin_2, LOW);
    analogWrite(PWMPin_2, turnSpeed);
  }

  delay(200);
  
  }

}
