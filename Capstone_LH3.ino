#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX

// Output pins for the motors
int IN1 =5;
int IN2 = 6;
int IN3 = 4;
int IN4 = 3;
int Speed = 204;

// output pin for the pump
int PUMP1 = 11;
int PUMP2 = 12;
int EN_PUMP = 13;

// output pin for the base motor
int BASE1 = 14;
int BASE2 = 15;
int EN_BASE = 16;

// output pin for the base motor
int TOP1 = 17;
int TOP2 = 18;
int EN_TOP = 19;

// Received data via bluetooth
char data;
char check_data;
int stop_pressed = 0;
int btVal;

void setup() {
 // Declare output?
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(EN_PUMP, OUTPUT);
  pinMode(BASE1, OUTPUT);
  pinMode(BASE2, OUTPUT);
  pinMode(EN_BASE, OUTPUT);
  pinMode(TOP1, OUTPUT);
  pinMode(TOP2, OUTPUT);
  pinMode(EN_TOP, OUTPUT);
// Initial output value (during initialization?)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN_PUMP, LOW);
  digitalWrite(BASE1, LOW);
  digitalWrite(BASE2, LOW);
  digitalWrite(EN_BASE, LOW);
  digitalWrite(TOP1, LOW);
  digitalWrite(TOP2, LOW);
  digitalWrite(EN_TOP, LOW);
//Set the baud rate to your Bluetooth module.
  Bluetooth.begin(9600);
  Serial.begin(9600); 
  Serial.println("Waiting for command..."); 
}

void loop()
{
 while (Bluetooth.available())
 {  
  {  
      data = Bluetooth.read();
      Serial.print(data);             
  } 
    
  switch (data) 
   {
      case 'F':                                
        forward();
        break;

      case 'B':                 
        reverse();
        break;

      case 'L':         
        left();
        break;
        
      case 'R':                     
        right();
        break;
        
      case 'S':                                            
        stoprobot();
        break;  

      case 'P':                                            
        pumpON();
        break;
      
      case 'p':                                            
        pumpOFF();
        break;

      case 'M':                                            
        Base_Forward();
        break;
      
      case 'm':                                            
        Base_Reverse();
        break;
      
      case 'N':                                            
        Base_Stop();
        break;

      case 'T':                                            
        Top_Forward();
        break;
      
      case 't':                                            
        Top_Reverse();
        break;
     
      case 'Q':                                            
        Top_Stop();
        break;
    
      case 'A':  // Put button character for path A in '' that corresponds to app, press button once (not hold) like the pump
        // Actual path needs calibration
        // Plant 1
        left();
        delay(2000); //2000ms=2s time delay holds left function on for 2s (turn left for 2s)
        forward();
        delay(5000); //5s forward
        left();
        delay(2000);
        forward();
        delay(1000);
        // Put code for the arm movement?
        pumpON();
        delay(5000);
        pumpOFF();

        // Check if the stop button is pressed during previous actions
        // is there a better way? Buttons pushed while running delays might result in buffer overflow
        while (Bluetooth.available()) {
          check_data = Bluetooth.read();
          if (check_data == 'S') {  // Emergency stop
            stop_pressed = 1;
            break;
          }
        }
        if (stop_pressed == 1) {
          stop_pressed = 0;
          break;
        }
        
        // Code to check if path A button pressed again to pause???

        // Plant 2
        reverse();
        delay(1000);
        left();
        delay(3000);
        forward();
        delay(2000);
        left();
        delay(3000);
        forward();
        delay(1000);
        // Put code for the arm movement?
        pumpON();
        delay(5000);
        pumpOFF();

        // Check again if stop button is pressed...

        // Plant 3, etc....

        break;


  }

 } 
 
                                                              
   if (Bluetooth.available() < 0)                              
    {
     //Serial.println("No Bluetooth Data ");          
    }
  
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stoprobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void pumpON()
{
  digitalWrite(PUMP1, HIGH);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN_PUMP, HIGH);
}

void pumpOFF()
{
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN_PUMP, LOW);
}

void Base_Forward()
{
  digitalWrite(BASE1, HIGH);
  digitalWrite(BASE2, LOW);
  digitalWrite(EN_BASE, HIGH);
}

void Base_Reverse()
{
  digitalWrite(BASE1, LOW);
  digitalWrite(BASE2, HIGH);
  digitalWrite(EN_BASE, HIGH);
}

void Base_Stop()
{
  digitalWrite(BASE1, LOW);
  digitalWrite(BASE2, LOW);
  digitalWrite(EN_BASE, LOW);
}


void Top_Forward()
{
  digitalWrite(TOP1, HIGH);
  digitalWrite(TOP2, LOW);
  digitalWrite(EN_TOP, HIGH);
}

void Top_Reverse()
{
  digitalWrite(TOP1, LOW);
  digitalWrite(TOP2, HIGH);
  digitalWrite(EN_TOP, HIGH);
}

void Top_Stop()
{
  digitalWrite(TOP1, LOW);
  digitalWrite(TOP2, LOW);
  digitalWrite(EN_TOP, LOW);
}
