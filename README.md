# 2023-2024-4GP-TAILHAN-FERNANDES
# Projet capteur avec jauge de contrainte de graphène
## Description générale : 
Nous sommes Amandine Tailhan et David Fernandes deux élèves à l'INSA Toulouse. Au cours de notre 4ème année nous avons reálisé ce projet capteurs donc l'objectif a été de déterminer les caractéristiques principales d'une jauge de contrainte low tech et de les comparer avec sa version conventionnelle ou "high tech". Pour réaliser cette comparaison nous avons créer un banc de test depuis 0. 

## Contenu : 
Dans ce github vous retrouverez tout le travail réalisé dans le contexte de ce projet capteur. Vous trouverez un dossier indépendant pour chaque partie de notre projet. 
**1. Code Arduino :** Vous trouverez un dossier appelé Arduino dans ce dossier vous trouverez les codes arduinos qui pilotent de manière indépendante chaqu'un des composants de notre banc de test et un code appelé "assemblage" qui pilote l'ensemble de notre banc de test. Dans chaque sous-dossier vous trouverez un schémas des branchements. <br>
**2. Shield dans KiCAD :** Dans le dossier KiCAD  vous trouverez le schémas du montage correspondant à notre banc de test : . Vous trouverez également le fichier .pcb que vous pourrez utiliser si vous voulez commander la PCB. La PCB permettra une meilleure installation des composants et peut s'avérer plus comfortable. Cependant, le montage pourra également être réalisé avec des breaboards et des branchements "à la main". <br>
**3. Impression 3D du support:** Notre banc de test utilise un support où l'on vient installer la jauge de contrainte à tester et le servo moteur qui nous servira à appliquer la contrainte sur le capteur. Dans ce dossier vous trouverai le modèle 3D de cette pièce (réalisé sur la version étuidient 10 de PTC Creo) ainsi que le fichier .stl qui vous permettra d'imprimer la pièce avec une imprimante 3D. Cette étape n'est pas obligatoire, vous pouvez très bien réaliser un support pour le capteur et le servo moteur chez vous. <br> 
**4. L'application bluetooth :** À l'aide de MIT App Inventor nous avons également réalisé une application compatible avec n'importe quel Android. Cette application permet la communication entre votre smartphone Android et le montage. Vous pourrez dans cette application visualiser les courbes de contraintes du capteur que vous étudiez. <br>

## Pré-requis : 
- Application Arduino, version : 
- Smartphone Android (si vous voulez visualiser les courbes de contraintes sur votre smartphone)
- Imprimante 3D (Si vous voulez imprimer le support qu'on propose si vous ne voulez le faire vous-même)
- Commander le PCB (optionnel), sinon 2 breadboards et des fils suffiront 
- Arduino UNO
- Capteur Bluetooth HC05 
- Servo-moteur SM-S2309S
- Encodeur rotatoire KY 040
- Potentiomètre digital MCP 4 1050
- OLED 2864
- Amplificateur opérationnel : LTC1050
- Résistances et condensateurs : voir schémas 
- Librairies Arduino : 

## Guide d'utilisation : 
### Montage :
1. Le premier pas, avant de démarrer, sera de réaliser le montage présenté ci-dessous : 
2. Nous vous recommandons fortement que vous installiez les composants un par un et que vous les testiez individuellement avec les programmes fournis dans /Arduino
[Image du schémas du montage]
1. Une fois les branchements effectués : brancher l'arduino UNO à votre PC 
2. Ouvrez le fichier assemblage.ino qui se trouve dans /Arduino/Assemblage
3. Sélectionnez votre Arduino UNO une fois le programme ouvert 
4. Lancez le code 

### Menu sur l'OLED : 
Lorsque vous alncez le code sur l'Arduino l'écran OLED s'allume. Sur l'écran OLED vous pourrez accéder à deux menus différents. Le premier menu permet de choisir quelle jauge de contrainte vous voulez mesurer : celle en graphène et la conventionnelle. Le deuxième menu affiche la valeur de la résistance R2 et l'option de recalibration de celle-ci. En effet, en fonction du crayon utilisée pour faire le capteur de graphène la résistance à l'état de repos peut être plus ou moins grande c'est pour celà qu'on a ajouté l'option de recalibration qui permet d'ajuster le gain du montage en modifiant la valeur de la résistance R2. <br>
Pour passer d'un menu à un autre il faut appuyer sur l'encodeur rotatoire. À l'intérieur de chaque menu pour se déplacer parmis les différentes options vous n'avez qu'à faire tourner l'encodeur. Ainsi pour mesurer la résistance de la jauge de contrainte en graphène il faut se placer dans le menu "Résistances" et sélectionner la résistance R graph. D'autre part, pour réaliser la calibration de la résistance R2 il faut se placer dans le menu "Calibration", sélectionner l'option "Recalibration" et appuyer sur l'encodeur 2s.

### Application :
1. Appariez votre smartphone avec votre module Bluetooth HC05, si un code est demandé tapez soit 0000 soit 1234
2. Téléchargez le fichier .exe sur votre smartphone en scannant le QR Code que vous trouverez dans le dossier /Application.
3. Une fois l'application installé dans votre Android il faudra que vous donniez les droits nécessaires à votre application afin qu'elle puisse détecter les appareils Bluetooth connectés à votre Android grâce aux paramètres. 
4. Ouvrez l'application sur votre smartphone puis cliquez sur le bouton : Devices list 
5. Sélectionnez le module HC05 
6. Normalement la courbe de contrainte de votre capteur s'affiche 
