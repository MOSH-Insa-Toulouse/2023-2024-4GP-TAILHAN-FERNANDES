#include <SoftwareSerial.h>
#include <Servo.h> //Servo moteur


//Variables module Bluetooth
//byte Rbyte_BT ; //Valeur de la résistance a envoyer au bluetooth
#define rxPin 8 //Broche 11 en tant que RX, raccorder sur TX du HC-05
#define txPin 7 //Broche 10 en tant que RX, raccorder sur TX du HC-05
#define baudrate 9600
SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial
int i = 0 ;

//Variables servo moteur
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
int pos = 0;    // variable to store the servo position
int pin_servo_moteur = 3 ; //attention doit contenir un "~" sur l'arduino
int Servo_App_Value = 1; 
int angle = 0;
bool isRunning = false;

void setup(){
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
    
  mySerial.begin(baudrate);
  Serial.begin(baudrate);

  //Initialisation du servo moteur
  myservo.attach(pin_servo_moteur);
}

void loop(){
  if (mySerial.available() > 0) {
    char command = mySerial.read();
    
    if (command == 'start') { // Si la commande est de démarrer
      isRunning = true;
    } else if (command == 'stop') { // Si la commande est d'arrêter
      isRunning = false;
      myServo.write(0); // Arrêtez le servo moteur
    }
  }
  
  if (isRunning) {
    // Faites tourner le servo moteur en continu ici
    myServo.write(angle);
    delay(15); // Attendez un peu avant de passer à l'angle suivant
    angle += 1; // Augmentez l'angle
    if (angle > 180) {
      angle = 0; // Réinitialisez l'angle à 0 une fois qu'il atteint 180 degrés
    }
  }



 
 /*
  if (Serial.available()>0){
    char commande =Serial.read();

    if (commande == '1'){
      myservo.write(0);
    }else if (commande == '0') {
      myservo.write(90);
    }
  }
  */

 /*
  if (Serial.available() > 0){
    char commande = Serial.read();
    if (commande == '1'){
      digitalWrite(pin_servo_moteur, HIGH);
    } else if (commande == '0') {
      digitalWrite(pin_servo_moteur, LOW);
    }
  }
  */

  //int i = 0; 
	char someChar[32] ={0};
	//when characters arrive over the serial port...

  /*
	while (Serial.available()) { //Check if there is an available byte to read
	   do{
		someChar[i++] = Serial.read(); //Conduct a serial read in pin 10 and 11?
		delay(3);		
	   }while (Serial.available() > 0);
	   
	   mySerial.println(someChar); 
	   Serial.println(someChar); 
	}
	while (mySerial.available()) {
		Serial.print((char)mySerial.read());
	}
  */
 /* 
  if (Serial.available()) {
    Servo_App_Value = Serial.read() ; 
    Serial.println("lu") ; 
  }
  if (Servo_App_Value == 1) {
    if (abs(pos) == 55) {pos = -pos ;}
    myservo.write(abs(pos));              // tell servo to go to position in variable 'pos'
    pos = pos + 1 ;
    delay(15) ;
  }

  i++ ; 
  if (i == 250) {i = 0 ; }
  mySerial.write(i) ; 
  delay(200) ; 

*/
}