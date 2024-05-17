#include <Adafruit_SSD1306.h> // Bibliothèque pour contrôler l'écran OLED
#include <SPI.h>              // Bibliothèque pour l'utilisation du potentiometre
#include <Servo.h>            // Bibliothèque pour le servo moteur
#include <SoftwareSerial.h>   // Bibliothèque pour connecter le module bluetooth

//Définition des variables OLED
#define nombreDePixelsEnLargeur 128         // Largeur en pixel de l'écran OLED
#define nombreDePixelsEnHauteur 64          // Hauteur en pixel de l'écran OLED
#define brocheResetOLED         -1          // Réinitialisation de l'OLED partagée avec l'Arduino (valeur à -1 pour indiquer qu'aucun numéro de pin spécifique n'est utilisé)
#define adresseI2CecranOLED     0x3C        // Adresse de l'écran OLED sur le bus I2C (généralement égal à 0x3C ou 0x3D)
#define tailleDeCaractere 1                 // Taille des caractères sur l'écran OLED

#define DEBUG
#define CALIBRATION // Si partie non commentée dans la suite du code alors la calibration est automatique sinon la variable potentiometre = 2

//Définition des variables pour l'encodeur rotatif
#define encoder0PinA  2  // Définition de la broche A de sortie CLK de l'encodeur 0. Attention : ne pas utiliser une autre broche pour l'horloge car nous utilisons une interruption
#define encoder0PinB  4  // Définition de la broche B de sortie DT de l'encodeur 0
#define encoderSwitchPin  5 // Définition de la broche associée à l'interrupteur de l'encodeur
volatile unsigned int encoder0Pos = 0;
volatile unsigned int dernier_encodeur = 0;
volatile bool changer = true ; 
volatile int menu = 0; 
boolean buttonWasUp = true;

//Définition des paramètres du Flex sensor
const int flexPin = A1;      // Broche connectée à la sortie du diviseur de tension
//Constantes à modifier en fonction de la conception du projet
const float VCC = 5;      // Tension sur la ligne 5V de l'Arduino
const float R_DIV = 26700.0;  // Résistance utilisée pour créer un diviseur de tension
const float flatResistance = 25000.0; // Résistance lorsque le capteur est plat
const float bendResistance = 100000.0;  // Résistance à 90° de flexion

//Définition de la variable stockant la mesure de la jauge de contrainte en graphène 
int sensorValue ; 

//Définition des variables de choix menu déroulant
volatile int R_mesuree; // Variable volatile contenant la mesure de R, prenant la valeur 1 (pour la résistance du graphène) ou 0 (pour la résistance du Flex Sensor)
volatile float calibre ; 

//Définition des variables du potentiomètre
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
const int ssMCPin = 10; // Définition de la sélection d'esclave pour le potentiomètre digital
#define WAIT_DELAY 200
int potentiometre = 30; // Valeur comprise entre 1 et 256
volatile float R2 ;
float V_ADC ;
float RJC ; 

//Définition des variables du servo moteur
Servo myservo;  // Création d'un objet servo pour contrôler un servo
                // Un maximum de huit objets servo peut être créé
int pin_servo_moteur = 3 ; // Attention, broche qui doit contenir un "~" sur l'Arduino
int Servo_App_Value = 1; 
float R = 6.2 ; // Longueur du bras du servo-moteur (en cm)
int angle_0 = 0 ; // Angle du servo-moteur à la position de repos (en degrés)
int angle_max = 75 ; // Angle du servo-moteur à la position max (en degrés)
const float pi = 3.14159 ;
int pos = angle_0;    // Variable pour enregistrer la position du servo-moteur
bool isRunning = true;

//Définition des variables pour le module Bluetooth
//byte Rbyte_BT ; // Valeur de la résistance à envoyer au module Bluetooth
#define rxPin 7 // Définition de la broche 7 comme broche de réception pour la communication série avec le Bluetooth HC-05. Attention, la broche TX du HC-05 doit être connectée à cette broche
#define txPin 8 // Définition de a broche 8 comme branche de transmission pour la communication série avec le Bluetooth HC-05. Attention, la broche RX du HC-05 doit être connectée à cette broche
SoftwareSerial bluetooth_serial (rxPin ,txPin); // Initialisation avec les pin rx et tx d'une communication série logicielle pour la communication avec le module Bluetooth

//Définition d'un entier pour l'enregistrement des données au format csv
int n = 0 ; 

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED); // Initialisation OLED

//Fonction potentiomètre
void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // Ecriture SPI de la commande et des données vers le circuit MCP connecté à la broche ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); // Voir https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // Met la broche ss à l'état bas 
  
  SPI.transfer(cmd);        // Envoie le code de la commande
  SPI.transfer(data);       // Envoie la valeur associée
  
  digitalWrite(ssPin, HIGH); // Remet la broche ss à l'état haut pour déselectionner le circuit
  SPI.endTransaction();      // Fin de la transaction SPI
}

//Calibration de la résistance R2 avec le potentiomètre
void Calibration() {
    //Configuration du potentiomètre
    pinMode (ssMCPin, OUTPUT); // Définition du mode de la broche ssMCPin comme sortie
    digitalWrite(ssMCPin, HIGH); // Désactivation de la puce SPI en mettant la broche ssMCPin à l'état haut
    SPI.begin(); // Initialisation de la communication SPI

    //Calibration de valeur de resistance mesurée pour que la valeur mesurée de A0 soit autour de 2.5V
    sensorValue = analogRead(A0);
    SPIWrite(MCP_WRITE, potentiometre, ssMCPin); 
    delay (WAIT_DELAY);

#ifdef CALIBRATION
  while ((sensorValue<400 || sensorValue>700) && (potentiometre > 1 && potentiometre<256) ) {
    if (sensorValue<400 && potentiometre > 0) {potentiometre = potentiometre - 1 ;}
    else {if (potentiometre<256 && sensorValue>700) {potentiometre = potentiometre + 1 ;}}
    Serial.println("CALIBRATION");
    Serial.println(potentiometre);
    SPIWrite(MCP_WRITE, potentiometre, ssMCPin);
    sensorValue = analogRead(A0);
    delay (WAIT_DELAY);
  }
#endif  

#ifndef CALIBRATION
  potentiometre = 255 ; 
  SPIWrite(MCP_WRITE, potentiometre, ssMCPin); 
#endif  
}

//La routine de configuration s'exécute une seule fois lorsque vous appuyez sur le bouton de réinitialisation
void setup() {
  //Configuration OLED
  ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED);  // Initialisation de l'écran
  ecranOLED.clearDisplay();                                    // Efface de l'intégralité du buffer de l'écran OLED
  ecranOLED.setTextSize(tailleDeCaractere);                    // Taille des caractères (1:1, puis 2:1, puis 3:1)
  ecranOLED.setCursor(0, 0);                                   // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche de l'écran OLED
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);        // Couleur du texte, couleur du fond

  //Configuration encodeur rotatif
  pinMode(encoder0PinA, INPUT);           // Configure la broche A de l'encodeur en entrée
  digitalWrite(encoder0PinA, HIGH);       // Active la résistance pull-up pour la broche A de l'encodeur
  pinMode(encoder0PinB, INPUT);           // Configure la broche B de l'encodeur en entrée
  digitalWrite(encoder0PinB, HIGH);       // Active la résistance pull-up pour la broche B de l'encodeur 
  attachInterrupt(0, doEncoder, RISING);  // Attache l'interruption à la broche 0 pour l'encodeur
  pinMode (encoderSwitchPin, INPUT_PULLUP);

  //Initialisation de la communication série à 9600 bits par seconde
  Serial.begin(9600);
  Serial.println(F("n,Pos,Deformation_z_cm,Sensorvalue,RJC")) ; 

  //Configuration du module Bluetooth 
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  bluetooth_serial.begin(9600);

  //Configuration du potentiomètre
  pinMode (ssMCPin, OUTPUT); // Définition du mode de la broche ssMCPin comme sortie
  digitalWrite(ssMCPin, HIGH); // Désactivation de la puce SPI en mettant la broche ssMCPin à l'état haut
  SPI.begin();  // Initialisation de la communication SPI

  //Calibration de la valeur de la résistance mesurée pour que la valeur mesurée de A0 soit autour de 2.5V
  sensorValue = analogRead(A0);
  
  //Calibration de la resistance R2 avec le potentiomètre
  Calibration();
  R2 = potentiometre * 31500/255; // Supposition que la relation est lineaire, valeur de R2

  //Initialisation du servo moteur
  myservo.attach(pin_servo_moteur);

  //Configuration du Flex Sensor 
  pinMode(flexPin, INPUT); // Définition de la broche flexPin (A1) en mode lecture (pour le Flex Sensor)
}



//Boucle infinie
void loop() {
  n++ ; 
  int t1 = millis();

  //Gestion du servo-moteur
  if (bluetooth_serial.available() > 0) {
    String command = bluetooth_serial.readStringUntil('\n');
    if (command.equals("start")) {
      isRunning = true;
    } else if (command.equals("stop")) {
      isRunning = false;
    }
  }
  if (isRunning) {
    if (pos == angle_max) {pos = -pos ;}
    if (pos == -angle_0) {pos = -pos ;}
    myservo.write(abs(pos));              // Indique au servo-moteur de se rendre à la position stockée dans la variable 'pos'
    pos = pos + 1 ;
    delay(0) ; 
  }


  //Lecture de la valeur d'entrée sur la broche analogique 0 (capteur de graphène)
  sensorValue = analogRead(A0);

  //Affichage de la valeur de la résistance mesurée
  V_ADC = 5.0/1023.0 * sensorValue ; // Valeur mesurée par A0 en volt
  RJC = abs((1 + 100000/R2)*100000*5/V_ADC-110000)/1000 ; // Valeur de la résistance de graphène nommée RJC en kohms
  Serial.print(n);
  Serial.print(F(","));
  Serial.print(abs(pos));
  Serial.print(F(","));
  Serial.print(R*(sin((24-pos)*pi/180)));
  Serial.print(F(","));
  Serial.println(sensorValue);
  Serial.print(F(","));
  Serial.println(RJC); // Affichage de la valeur de RJC en kohms
  
  //Gestion du Flex Sensor
  int ADCflex = analogRead(flexPin);

  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);

  //Gestion du menu deroulant (encodeur rotatif)
  if (digitalRead(encoderSwitchPin) == LOW && !(menu==1 && changer==0)) {
    if (menu==0) {menu = 1 ;} 
    else {menu=0;}
    delay(50) ; 
  }

  //Gestion de l'écran OLED
  ecranOLED.clearDisplay();                                   // Efface tout le contenu du tampon de l'écran OLED
  ecranOLED.setTextSize(tailleDeCaractere);                   // Taille des caractères 

  if (encoder0Pos != dernier_encodeur) {
    if (changer == 1) {changer = false ;}
    else {changer = true;}
  }
  
  R2 = potentiometre * 31500/255; // En supposant que relation lineaire, valeur de R2

  //Gestion du menu de l'encodeur rotatif (choix résistance et calibre)
  if(menu == 0) {
    if (changer) { //Menu du choix de résistances
      R_mesuree = 1 ; // Mesure de la résistance de graphène
      ecranOLED.setCursor(0, 0); // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche de l'écran
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);    // Couleur du texte, couleur du fond
      ecranOLED.println("Resistances(Mohms):");  
      ecranOLED.setCursor(0, tailleDeCaractere * 10);          // Gestion de la taille de l'affichage de l'écriture
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);    // Couleur du texte, couleur du fond
      ecranOLED.println("R graph:");                        
      ecranOLED.setCursor(tailleDeCaractere * 10 * 5, tailleDeCaractere * 10);
      ecranOLED.println(int(RJC/1000));
      ecranOLED.setCursor(0, tailleDeCaractere * 10 * 2);
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);    // Couleur du texte, couleur du fond
      ecranOLED.println("R flex:");
      ecranOLED.setCursor(tailleDeCaractere * 10 * 5, tailleDeCaractere * 10 *2);
      ecranOLED.print((Rflex/1000000.0) , 3);
    }
    else { 
      R_mesuree = 0 ; // Mesure de la résistance du Flex Sensor
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);     
      ecranOLED.println("Resistances(Mohms):");  
      ecranOLED.setCursor(0, tailleDeCaractere * 10);
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);     
      ecranOLED.println("R graph:");                              
      ecranOLED.setCursor(tailleDeCaractere * 10 * 5, tailleDeCaractere * 10);
      ecranOLED.println(int(RJC/1000));                         // Affichage de valeur de résistance du Flex Sensor
      ecranOLED.setCursor(0, tailleDeCaractere * 10 * 2);
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);       
      ecranOLED.println("R flex:");
      ecranOLED.setCursor(tailleDeCaractere * 10 * 5, tailleDeCaractere * 10 *2);
      ecranOLED.print((Rflex/1000000.0) , 3);
    }
  }
  else {
    if (changer) { //Menu Calibre
      ecranOLED.setCursor(0, 0); // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche de l'écran OLED
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);   
      ecranOLED.println("Calibre R2:");  
      ecranOLED.setCursor(0, tailleDeCaractere * 10);  
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);    
      ecranOLED.println("R2 (kohms):");                        
      ecranOLED.setCursor(tailleDeCaractere * 10 * 6, tailleDeCaractere * 10);
      ecranOLED.println(abs(int(potentiometre * 31.500/255)));
      ecranOLED.setCursor(0, tailleDeCaractere * 10 * 2);
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);         
      ecranOLED.println("Recalibration");
    }
    else {
      ecranOLED.setCursor(0, 0); 
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);    
      ecranOLED.println("Calibre R2:");  
      ecranOLED.setCursor(0, tailleDeCaractere * 10);  
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);    
      ecranOLED.println("R2 (kohms):");                        
      ecranOLED.setCursor(tailleDeCaractere * 10 * 6, tailleDeCaractere * 10);
      ecranOLED.println(abs(int(potentiometre * 31.500/255)));
      ecranOLED.setCursor(0, tailleDeCaractere * 10 * 2);
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);       
      ecranOLED.println("Recalibration");

      //Programme de recalibration : permet à l'utilisateur de changer la valeur du potentiomètre R2
      if (digitalRead(encoderSwitchPin) == LOW) {
        potentiometre = 30 ; 
        Calibration();
      }
    }
  }
  dernier_encodeur = encoder0Pos ; 
  ecranOLED.display();

  //Module Bluetooth
  //Détermination de la valeur envoyée au module Bluetooth
  if (R_mesuree==1) { //Capteur graphène
    byte Rbyte_BT = map(analogRead(A0),0,1024,0,255) ; // Transformation d'une valeur codée sur 10 bits en une valeur codée sur 8 bits
    //Serial.println(Rbyte_BT);
    bluetooth_serial.write(Rbyte_BT) ; // Envoie d'un octet au module Bluetooth via la communication série
    delay(50);
    int t2 = millis() ; 
    //Serial.println (t2 - t1);
  }
  else { //Flex Sensor
    byte Rbyte_BT = map(ADCflex , 0,1024,0,255) ; 
    bluetooth_serial.write(Rbyte_BT) ; 
    delay(40);
  }

  //delay(100);  // Délai de 100ms entre les lectures pour assurer la stabilité
}

//Encodeur rotatif
//Mise à jour de la position de l'encodeur en fonction de l'état de la broche associée à la sortie B
void doEncoder() {
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}