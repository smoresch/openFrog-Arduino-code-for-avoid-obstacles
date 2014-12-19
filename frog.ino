//  OpenFrog project by Moreschi Simone -moreschisimone@gmail.com-
//
// Using Arduino UNO
// From 2014


//  Pins for left wheel
//
//  Pin 0-255 for go forward
int left_wheel_pin_forward = 9;
//  Pin 0-255 for go backward
int left_wheel_pin_backward = 10;
//  Pin 0-255 for speed
int left_wheel_pin_speed = 3;

//  Pins for right wheel
//
//  Pin 0-255 for go forward
int right_wheel_pin_forward = 12;
//  Pin 0-255 for go backward
int right_wheel_pin_backward = 11;
//  Pin 0-255 for speed
int right_wheel_pin_speed = 5;



//  HC-SR04 (Distance sensor)
//
int triggerPort = 7;
int echoPort = 8;



//  Led port for STOP lights
//
int stops_led_pin = 2;



//  Pin for on/off button
//
int buttonPin = 4;


//  Pin for system on/off (Using button pin 4)
//
int powerLedPin = 13;


//  System variables
//
boolean stopRobot = false;
boolean systemOn = false;
int currentSecureDistance = 0;

//  Parameters
//
//  Basic settings
int maxSpeed = 140;  //  Speed when robot go forward (0-255)
int turnSpeed = 120;  //  Speed when robot turn right/left (0-255)
int secureDistance = 15;  //  cm
int turnSecureDistance = 40;  //  cm
int timeBeforeTurn = 1000;  //  Time in milliseconds for start turn when robot detect obstacles and stops

//  Advanced settings
//
int pending = 6;  //  Current number of pending turn action 
int totPending = 6;   //  Minimum number of arduino loops for turn the robot when detect obstacles. After this number of loops robot continue to detect distance for detect if it can go forward or continue to turn for avoid obstacles. The degrees the robot turns depends from: this variables, turn speed and main loop delay.
          
//  Seup the arduino ONE board
//
void setup() {                
 
  systemOn = false;
  currentSecureDistance = secureDistance;
  
  //  Setting up pins
  //
  pinMode(buttonPin, INPUT);
  pinMode(powerLedPin, OUTPUT);
  pinMode(triggerPort, OUTPUT );
  pinMode(echoPort, INPUT );
  pinMode(stops_led_pin, OUTPUT );
  pinMode(left_wheel_pin_forward, OUTPUT);
  pinMode(left_wheel_pin_backward, OUTPUT);
  pinMode(left_wheel_pin_speed, OUTPUT);
  pinMode(right_wheel_pin_backward, OUTPUT);
  pinMode(right_wheel_pin_forward, OUTPUT);
  pinMode(right_wheel_pin_speed, OUTPUT);
  
  Serial.begin( 9600 );  
}


//  Arduino loop
//
void loop() {
  
   boolean buttonState = digitalRead(buttonPin); 
   
   //  If button is pressing now, check the button state, if button is not pressed in this moment jump this code
   //
   if (buttonState == HIGH) {     
  
      // System is ON, turn arduino systemON led to ON
      //
      if (!systemOn) {
        
        systemOn = true;
        digitalWrite(powerLedPin, HIGH);  
        
      } else {
        
        systemOn = false;
        currentSecureDistance = secureDistance;
        
        digitalWrite(stops_led_pin, LOW);
        digitalWrite(left_wheel_pin_forward, HIGH);
        digitalWrite(left_wheel_pin_backward, HIGH);
        analogWrite(left_wheel_pin_speed, 0);
        digitalWrite(right_wheel_pin_backward, HIGH);
        digitalWrite(right_wheel_pin_forward, HIGH);
        analogWrite(right_wheel_pin_speed, 0);
        digitalWrite(powerLedPin, LOW);  
        delay(1000);
      }
    } 
 
  
    //  System is ON detect obstacles and move robot!
    //
    if (systemOn) {
    
        //  Get distance from obstacle
        //
        digitalWrite( triggerPort, LOW );
        delayMicroseconds(2);
        digitalWrite( triggerPort, HIGH );
        delayMicroseconds(10);
        digitalWrite( triggerPort, LOW );
        long duration = pulseIn( echoPort, HIGH );
        long r = (duration / 2) / 29.1;
        Serial.print( "Distance from obstacle is: " );
        Serial.print( r );
        Serial.println( "cm" );
        if (r <= currentSecureDistance) {
          stopRobot = true;
          digitalWrite(stops_led_pin, HIGH);
        } else {
          stopRobot = false;
          digitalWrite(stops_led_pin, LOW);
        }
  
        
        if (!stopRobot && pending == 0) {
          
            //  No obstacles detected and no turn action pending, go forward!
            //
            currentSecureDistance = secureDistance;
            
            digitalWrite(left_wheel_pin_forward, HIGH);
            digitalWrite(left_wheel_pin_backward, LOW);
            analogWrite(left_wheel_pin_speed, maxSpeed);
            
            digitalWrite(right_wheel_pin_forward, HIGH);
            digitalWrite(right_wheel_pin_backward, LOW);
            analogWrite(right_wheel_pin_speed, maxSpeed);
          
          
        } else {
    
            if (currentSecureDistance == secureDistance) {
                //  Stop the wheels, HUB-ee wheels have break mode, set ON forward and backward direction, set speed = 0. In this way if your robot is not in horyzontal position don't move.
                //
                digitalWrite(left_wheel_pin_forward, HIGH);
                digitalWrite(left_wheel_pin_backward, HIGH);
                analogWrite(left_wheel_pin_speed, 0);
                digitalWrite(right_wheel_pin_backward, HIGH);
                digitalWrite(right_wheel_pin_forward, HIGH);
                analogWrite(right_wheel_pin_speed, 0);
                delay(timeBeforeTurn);
                
                //  Set number of minimum loop for turn the robot left
                //
                pending = totPending;
            }
      
            pending--;
            if (pending < 0) {
              pending = 0;
            }
    
            currentSecureDistance = turnSecureDistance;
    
            //  Turn the robot left
            //
            digitalWrite(left_wheel_pin_forward, HIGH);
            digitalWrite(left_wheel_pin_backward, HIGH);
            analogWrite(left_wheel_pin_speed, 0);
            
            digitalWrite(right_wheel_pin_backward, HIGH);
            digitalWrite(right_wheel_pin_forward, LOW);
            analogWrite(right_wheel_pin_speed, turnSpeed);
      }

      //  Main delay
      //
      delay(200);
  
  }

}
