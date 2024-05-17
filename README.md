# 2023-2024-4GP-TAILHAN-FERNANDES
# Projet capteur avec jauge de contrainte de graphène
## Description générale : 
  Nous sommes Amandine Tailhan et David Fernandes, deux élèves de l'INSA Toulouse. Dans le cadre de notre quatrième année, nous avons entrepris un projet sur les capteurs. Notre objectif principal était de déterminer les caractéristiques principales d'une jauge de contrainte low-tech et de les comparer avec sa version conventionnelle, qualifiée de "high-tech". Ce projet vise à répondre à la question suivante : *"Ne pourrait-on pas obtenir parfois les mêmes résultats avec une technologie low-tech qu'avec une technologie high-tech ?"*
<br> <br>
Pour réaliser cette comparaison, nous avons conçu un banc de test à partir de zéro. Sur ce dépôt GitHub, vous trouverez tous les outils et codes que nous avons développés pour répondre à cette question. Enfin, à la fin de ce dépôt, vous découvrirez la réponse à notre problématique.

## Contenu : 
Dans ce github vous retrouverez tout le travail réalisé dans le contexte de ce projet capteur. Vous trouverez un dossier indépendant pour chaque partie de notre projet. <br> <br>
**1. Code Arduino :** Vous trouverez un dossier appelé Arduino dans lequel se trouvent les différents codes arduinos qui pilotent de manière indépendante chacun des composants de notre banc de test et un code appelé "Assemblage_composants" qui pilote l'ensemble de notre banc de test. Dans chaque sous-dossier vous trouverez un schémas des branchements. <br>
**2. Shield dans KiCAD :** Dans le dossier KiCAD  vous trouverez le schéma du montage avec les différents branchements correspondant à notre banc de test : . Vous trouverez également le fichier .pcb que vous pourrez utiliser si vous voulez commander le PCB. La réalisation du PCB permet un meilleur agencement des composants ajoutant ainsi un confort d'utilisation. Cependant, le montage pourra également être réalisé avec des breadboards et des branchements "à la main". <br>
**3. Impression 3D du support:** Notre banc de test utilise un support où l'on vient installer la jauge de contrainte à tester et le servo moteur qui nous servira à appliquer la contrainte sur le capteur. Dans ce dossier vous trouverez le modèle 3D de cette pièce (réalisé sur la version étudiant 10 de PTC Creo) ainsi que le fichier .stl qui vous permettra d'imprimer la pièce avec une imprimante 3D. Cette étape n'est pas obligatoire, vous pouvez très bien réaliser un support pour le capteur et le servo moteur chez vous et ainsi faire votre propre banc de test. <br> 
**4. L'application bluetooth :** À l'aide du logiciel MIT App Inventor nous avons également réalisé une application compatible avec n'importe quel téléphone Android. Cette application permet la communication entre votre smartphone Android et le circuit. Vous pourrez dans cette application visualiser les courbes de contraintes du capteur que vous étudiez. <br>
**5. Datasheet du capteur Low Tech :** Dans le dossier datasheet, vous aurez accès aux informations techniques importantes relatives au capteur. Cela inclut la sensibilité du capteur de graphite pour divers types de crayons tels que F, HB, B, 2B et 4B. Vous y trouverez également des graphiques détaillant la variation relative de résistance en fonction de la déformation selon l'axe z en situation de tension et de compression.
**6. Présentation finale de notre projet :** Vous trouverez parmi les dépôts un document PowerPoint intitulé "Présentation_projet.pptx". Dans ce PowerPoint, nous présentons notre démarche, les différentes étapes du projet, ainsi que des images et une vidéo illustrant le résultat final de notre projet. Cette vidéo pourra vous aider à mieux comprendre et à mieux visualiser l'assemblage de toutes les pièces, c'est pourquoi nous vous invitons à y jeter un œil.


## Pré-requis : 
- Application Arduino, version : >2.1
- Arduino UNO
- Librairies Arduino : Adafruit_SSD1306.h / SPI.h / Servo.h / SoftwareSerial.h
- Smartphone Android (si vous voulez visualiser les courbes de contraintes sur votre smartphone)
- Imprimante 3D (Si vous voulez imprimer le support qu'on propose si vous ne voulez pas faire vous-même le banc de test)
- Commander le PCB (optionnel), sinon 2 breadboards et des fils suffiront 
- Capteur Bluetooth HC05 
- Servo-moteur SM-S2309S
- Encodeur rotatoire KY 040
- Potentiomètre digital MCP 4 1050
- OLED 2864
- Amplificateur opérationnel : LTC1050
- Résistances et condensateurs : voir schémas 

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
  Lorsque vous lancez le code sur l'Arduino l'écran OLED s'allume. Sur l'écran OLED vous pourrez accéder à deux menus différents. Le premier menu permet de choisir quelle jauge de contrainte vous voulez mesurer : celle en graphène et la conventionnelle. Le deuxième menu affiche la valeur de la résistance R2 et l'option de recalibration de celle-ci. En effet, en fonction du crayon utilisée pour faire le capteur de graphène la résistance à l'état de repos peut être plus ou moins grande c'est pour celà qu'on a ajouté l'option de recalibration qui permet d'ajuster le gain du montage en modifiant la valeur de la résistance R2. <br> <br>
Pour passer d'un menu à un autre il faut appuyer sur l'encodeur rotatoire. À l'intérieur de chaque menu pour se déplacer parmis les différentes options vous n'avez qu'à faire tourner l'encodeur. Ainsi pour mesurer la résistance de la jauge de contrainte en graphène il faut se placer dans le menu "Résistances" et sélectionner la résistance R graph. D'autre part, pour réaliser la calibration de la résistance R2 il faut se placer dans le menu "Calibration", sélectionner l'option "Recalibration" et appuyer sur l'encodeur 2s.

### Application :

1. Appariez votre smartphone avec votre module Bluetooth HC05. Si un code est demandé, tapez soit 0000 soit 1234.
2. Téléchargez le fichier .exe sur votre smartphone en scannant le QR Code que vous trouverez dans le dossier /Application.
3. Une fois l'application installée sur votre Android, accordez les droits nécessaires à votre application afin qu'elle puisse détecter les appareils Bluetooth connectés à votre Android via les paramètres.
4. Ouvrez l'application sur votre smartphone, puis cliquez sur le bouton : Devices list.
5. Sélectionnez le module HC05.
6. Normalement, la courbe de contrainte de votre capteur s'affiche.
7. Pour afficher la bonne courbe, vous devez introduire manuellement la valeur de R2 (lue sur l'écran OLED, menu : Calibration), puis cliquez sur le bouton "Actualiser R2".
8. L'application vous permet également d'arrêter ou de lancer la rotation du servo-moteur avec les boutons : Moteur ON / Moteur OFF.

### Banc de test :

Veuillez trouver ci-dessous une image de notre banc de test : <br> <br>

Au centre, vous pouvez observer la pièce principale qui jouera le rôle de support pour notre banc d'essai. À sa droite est positionné le servo-moteur, accompagné du capteur de graphite. À gauche, se trouve l'Arduino UNO et juste au-dessus de celui-ci s'étend notre montage électrique intégré dans le PCB.

Pour réaliser ce banc de test, suivez les étapes suivantes :

#### Support :
1. Vissez l'Arduino UNO sur le support.
2. Réalisez le PCB.
3. Effectuez toutes les soudures nécessaires.
4. Installez le PCB sur l'Arduino. (L'étape de 2 à 4 peut être remplacée par l'utilisation d'un breadboard et de câbles.)
5. Placez le servo-moteur ; les fils du servo-moteur sont à droite du support.
6. Vissez les deux pinces du capteur à gauche du servo-moteur.
7. Sur les "bras" du servo-moteur, vissez un bras suffisamment long pour atteindre le capteur de graphite (4-5cm).
    - Éteignez l'alimentation du servo-moteur.
    - Tournez ses bras dans le sens opposé des aiguilles d'une montre jusqu'au maximum.
    - Maintenant, enlevez le "bras" du servo-moteur et ajustez-le de manière à ce qu'il fasse un angle compris entre -50 et -20 degrés par rapport à l'axe horizontal.
    - Mesurez cet angle et rentrez-le dans le code Arduino dans la variable : angle_min.
    - Ajustez la variable angle_max de manière à ce que le bras du servo-moteur dépasse le capteur.

#### Acquisition de données :
1. Après vérification que tout fonctionne convenablement, fermez le logiciel Arduino (en mémorisant le port sur lequel votre Arduino UNO est connecté).
2. Dans le dossier /Acquisition_donnees, créez un document vide .txt.
3. Ouvrez le code python "enregistrement_donnees.py" que vous trouverez dans : /Acquisition_donnees.
4. Changez le chemin du fichier par le chemin du fichier .txt que vous avez créé.
5. Lancez le code python.
6. Laissez le code tourner jusqu'à la fin.
7. Les données sont normalement stockées dans le fichier .txt (ATTENTION : notez les valeurs de n pour lesquelles le capteur est au repos).

#### Traitement de données :
1. Ouvrez les fichiers .txt avec Excel en choisissant "," comme séparateur de colonne.
2. Effacez toutes les lignes pour lesquelles le capteur est au repos.
3. Ordonnez votre tableau par déformation_z_cm croissante.
4. Enregistrez les données dans le tableau/feuille qui vous paraît pertinent, dans le fichier donnees_courbes.
5. Les courbes sont automatiquement générées dans la feuille : Ensemble.
