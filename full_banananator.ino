//BUTTON 
int  buttonPin = 2;    // the pin that the pushbutton is attached to
// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;
bool buttonPressedRecently = false;
unsigned long startTime = 0;
unsigned long interval = 5000;

//SERVO
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;

//STEPPER
const int stepPin = 3; //pin for counting steps
const int dirPin = 4; //pin for determining direction


void setup() {
  Serial.begin(9600); // initialize serial communication
  
  //BUTTON
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  
  //SERVO
  myservo.attach(7);  // attaches the servo on pin 7 to the servo object
  Servo myservo;  // create servo object to control a servo

  //STEPPER
  pinMode(stepPin,OUTPUT); // Sets the two pins as Outputs
  pinMode(dirPin,OUTPUT);

}

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);
  delay(50);
  //MACHINE IS ON STANDBY
  
  if ((buttonPressedRecently == true) & (millis () - startTime >= interval)){
        
        buttonPressedRecently = false;
        Serial.println("time out");
        
        if (buttonPushCounter <= 5){
          // CIRCLE
          Serial.println("CIRCLE");
          
          //stepper on for 5 fast cycles
          digitalWrite(dirPin,HIGH);
          for (int x = 0; x<1000; x++){
            digitalWrite(stepPin, LOW);
            delayMicroseconds(1000);
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1000);
          }

          
          int pos1 = 0;    // variable to store the servo position
          int pos2 = 70;
          //SERVO does 10 sweeps of 5 diff settings
          for (int i=0; i<5; i++){
            for (pos = pos1; pos <= pos2; pos += 1) { // goes from 0 degrees to 70 degrees
              // in steps of 1 degree
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(250);                       // waits 250ms for the servo to reach the position
            }
            for (pos = pos2; pos >= pos1; pos -= 1) { // goes from 180 degrees to 0 degrees
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(250);                       // waits 250ms for the servo to reach the position
            }
            pos1 = pos1 + 7;
            pos2 = pos2 - 7;
          }
          myservo.write(pos); // reset servo position to zero


          
        }else{
          //generates SQUARE
          Serial.println("SQUARE");
          //stepper on for 1 slow cycle
          digitalWrite(dirPin,HIGH);
          for (int x = 0; x<200; x++){
            digitalWrite(stepPin, LOW);
            delayMicroseconds(10000);
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(10000);
          }
          //SERVO does 1 sweep
          for (pos = 0; pos <= 70; pos += 1) { // goes from 0 degrees to 70 degrees
              // in steps of 1 degree
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(500);                       // waits 500ms for the servo to reach the position
            }
        myservo.write(pos); // reset servo position to zero

         
        }
        buttonPushCounter = 0;
      }

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
      if (buttonState == HIGH) {
        
      // if the current state is HIGH then the button went from off to on:
      if (buttonPressedRecently == false) {
        startTime = millis();
        buttonPressedRecently = true;
        
      } else {
        buttonPushCounter ++;
      }

      
      //Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
      Serial.println(buttonPressedRecently);
      } else {
        
        // if the current state is LOW then the button went from on to off:
        //Serial.println("off");
      }
    
    
    // Delay a little bit to avoid bouncing
    delay(10);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

}
