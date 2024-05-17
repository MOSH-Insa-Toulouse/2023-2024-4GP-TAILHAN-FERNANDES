import serial 

portserie = serial.Serial('COM3' , baudrate = 9600 , timeout=2)

fichier = open("C:/Users/david/Desktop/Asssemblage_composants_2/donnees_courbe_4B_4.txt" , 'w')

for i in range(125) : 
    donnees_arduino = portserie.readline().decode('ascii')
    print(donnees_arduino)
    fichier.write(donnees_arduino)

fichier.close()