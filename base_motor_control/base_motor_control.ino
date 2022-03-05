#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
}
void loop() {
 if (irrecv.decode(&results)) {
   Serial.println(results.value, HEX);                 
   irrecv.resume(); // Receive the next value
 }
}
-----
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
int receiver = 11;           // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
void setup()   
{
 Serial.begin(9600);
 Serial.println("IR Receiver Button Decode"); 
 irrecv.enableIRIn(); // Start the receiver
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
}
void loop()  
{
 if (irrecv.decode(&results))                 // have we received an IR signal?
 {
   switch(results.value)                      //case starts
 {
 case 0xC1AA0DF2:                                                //MOVEMENT -FORWARD
                 digitalWrite(2,HIGH);
                 digitalWrite(3,LOW);
                 digitalWrite(4,HIGH);
                 digitalWrite(5,LOW);  
                 break;
 case 0xC1AA4DB2:                                                 //MOVEMENT- BACKWARD
                 digitalWrite(2,LOW);
                 digitalWrite(3,HIGH);
                 digitalWrite(4,LOW);
                 digitalWrite(5,HIGH);
                 break;
 case 0xC1AACD32:                                                 //MOVEMENT- LEFT
                 digitalWrite(2,LOW);
                 digitalWrite(3,HIGH);
                 digitalWrite(4,HIGH);
                 digitalWrite(5,LOW);
                 break;
 case 0xC1AA8D72:                                                 //MOVEMENT- RIGHT
                 digitalWrite(2,HIGH);
                 digitalWrite(3,LOW);
                 digitalWrite(4,LOW);
                 digitalWrite(5,HIGH);
                 break;
 case 0xC1AA11EE:                                                 //MOVEMENT- stop
                 digitalWrite(2,LOW);
                 digitalWrite(3,LOW);
                 digitalWrite(4,LOW);
                 digitalWrite(5,LOW);
                 break;            
 default:                                           //incase you pressed other buttons
                 Serial.println(" other button   ");
 }                                                  // case ends
 delay(100);                                        // to not get immediate repeat
 irrecv.resume();                                   // receive the next value
 }  
}

 #define outputA 6
 #define outputB 7

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
