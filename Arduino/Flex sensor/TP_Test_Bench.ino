#include <Servo.h>

#define PIN_SERVO 11
#define PIN_FLEX_SENSOR A0

Servo myservo;

int pos = 0;
int pos_max = 150;
int pos_min = 20;
 
void setup() {
  Serial.begin(9600);  
  myservo.attach(PIN_SERVO);
}

void measure(){
  Serial.println(analogRead(PIN_FLEX_SENSOR));
  delay(50); 
}

void loop() {

   for (pos = pos_min; pos <= pos_max; pos += 1) { 
    myservo.write(pos);           
    measure();
  }
  
  for (pos = pos_max; pos >= pos_min; pos -= 1) { 
    myservo.write(pos);          
    measure();
  }
  
}


