//Inclure la librairie stepper.h et ds1302
  #include <Stepper.h>
  #include <stdio.h>
  #include <DS1302.h>
  #define STEPS 100
  int Steps2Take = 0;
 
  //Créer une instance de la classe stepper
  //Le moteur (fils 1 2 3 4) est branché sur les sorties 2 3 4 5 de l'Arduino (et sur GND, +V)
  Stepper stepper_avant(STEPS, 2, 4, 3, 5);     // Sens horaire
  Stepper stepper_arriere(STEPS, 5, 3, 4, 2);  // Sens anti-horaire 

  int nombre_heure_ouverte = 16; //de 6h à 22h
  int nombre_heure_fermee = 8; //de 22h à 6h
  int nombre_de_tour = 7; //nombre de rotation du moteur pas à pas
  
void setup()
 {               
  Serial.begin(9600);     // 9600 bps
  }

void loop(){
      Serial.println("Fermeture de la porte");
      fermer_porte();

      Serial.print("Ouverture dans ");
      Serial.print(calcul_delay(nombre_heure_fermee)/1000/60/60);
      Serial.print(" heures.");
      delay(calcul_delay(nombre_heure_fermee));

      Serial.println("Ouverture de la porte");
      ouvrir_porte();

      Serial.print("Fermeture dans ");
      Serial.print(calcul_delay(nombre_heure_ouverte)/1000/60/60);
      Serial.print(" heures.");
      
      delay(calcul_delay(nombre_heure_ouverte));
}


void ouvrir_porte(){
  int nbStep = calcul_nbStep(nombre_de_tour);
    stepper_avant.setSpeed(300);
    stepper_avant.step(nbStep);  //Ca tourne
 }

 void fermer_porte(){
  int nbStep = calcul_nbStep(nombre_de_tour);
    stepper_arriere.setSpeed(300);
    stepper_arriere.step(nbStep);  //Ca tourne
 }

 int calcul_nbStep(int tour){
 //1 tour = 2048steps
  return 2048*tour; 
 }

 long calcul_delay(int nbHeure){
  //1h = 60 minutes = 60 × 60 secondes = 3600 secondes = 3600 × 1000 milliseconds = 3,600,000 ms
  long a = nbHeure*3600000;
  return a;
 }
