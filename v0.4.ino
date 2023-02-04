  ///Teleskop Motor Steuerung///
 ///Telescope motor control ///
/// Meade telescope v0.4   ///

#include "FastLED.h"

#define LED_COUNT 1
#define LED_PIN 12
#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7

CRGB leds[LED_COUNT];

int motorSpeedA = 0;
int motorSpeedB = 0;


  //Arduino pin numbers
const int SW_pin = 2; //digital pin connected to switch output
const int X_pin = 0; //analog pin connected to X output
const int Y_pin = 1; //analog pin connected to Y output
const int led_pin = 13;//led data pin



void setup() {

  //motor setup
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

  //led setup
    pinMode(SW_pin, INPUT);
    pinMode(led_pin, OUTPUT);
    digitalWrite(SW_pin, HIGH);
  //Serial.begin(115200); //UNCOMMENT FOR DEBUG 
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
    FastLED.setBrightness(20);
  //"Boot Animation" makes it look more professional
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(5000);
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(500);
}

void loop() {
 
  //////////////////////////////////
  //Uncomment above for monitoring//
  //////////////////////////////////
  //serial monitoring
    //Serial.print(digitalRead(SW_pin));
    //Serial.print("\n");
    //Serial.print("X-axis: ");
    //Serial.print(analogRead(X_pin));
    //Serial.print("\n");
    //Serial.print("Y-axis: ");
    //Serial.println(analogRead(Y_pin));
    //Serial.print("\n\n");
    
    //motor status
      //Serial.print("Alt Motor: ");{
      //if ((digitalRead(in1)== (HIGH) && (digitalRead(in2) == (LOW))))
      //   Serial.print("UP");
      //else if ((((digitalRead(in2)== (HIGH) && (digitalRead(in1) == (LOW))))))
      //  Serial.print("DOWN");
 
// Serial.print(digitalRead(in1));
  //  Serial.print("X-axis: ");
   // Serial.print(analogRead(X_pin));
   // Serial.print("X-axis: ");
   // Serial.print(analogRead(X_pin));
  //  Serial.print("X-axis: ");
 
  ////////////////////////////////////
  //STOP UNCOMMENTING HERE FOR DEBUG//
  ////////////////////////////////////
 
 
  //motor control loop
    int xAxis = analogRead(A0); // Read Joysticks X-axis
    int yAxis = analogRead(A1); // Read Joysticks Y-axis
      
  //Y-axis forward and backward control (alt motor)
    if (yAxis < 420) {
        
  //set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

        
  //convert the Y-axis readings to PWM value
    motorSpeedA = map(yAxis, 420, 0, 0, 255);
      }

    else if (yAxis > 600) {

        
  //set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

      
  //convert the Y-axis readings to PWM value
    motorSpeedA = map(yAxis, 600, 1023, 0, 255);
      }
      
  //X-axis forward and backward control (z motor)
    if (xAxis < 420) {
        

        
  //set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

        
  //convert X-axis readings to PWM value
    motorSpeedB = map(xAxis, 420, 0, 0, 255);
      }


    else if (xAxis > 600) {

        

        
  //set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

        
  //convert X-axis readings to PWM value
    motorSpeedB = map(xAxis, 600, 1023, 0, 255);
      }

      
  //no input motors off
    else {
    motorSpeedB = 0;
      }

  //buzz prevent
    if (motorSpeedA < 1) {
        motorSpeedA = 0;
      }
    if (motorSpeedB < 1) {
      motorSpeedB = 0;
      }
    analogWrite(enA, motorSpeedA);// Send PWM signal to motor A
    analogWrite(enB, motorSpeedB);// Send PWM signal to motor B
{
  //status led
    if ((analogRead(X_pin) > 600) || (analogRead(X_pin) < 420) || (analogRead(Y_pin) > 600) || (analogRead(Y_pin) < 420))
  {
    leds[0] = CRGB::Blue;
    FastLED.show();

  }
    else
  {
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(50);
  }
}
}
