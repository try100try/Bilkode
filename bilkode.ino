//Hvis du har nogen som helst spørgsmål til min kode spørger du mig bare i timen og jeg vil med glæde svare på dine spørgsmål.

//Pins til afstandsmåleren, hvor 11 er den der modtager echo mens 12 er den der udskyder lydbølgen
#define trigPin 12
#define echoPin 11
//Duration er mængden af tid der gik før at den modtog lydbølgen, distance er værdien som bliver udregned med lydbølgen.
long duration;
int distance;
//Pins til LED lys. (jeg bruger analog pins for at spare plads)
int red = A3; 
int yellow = A2; 
int green = A1; 
int blue = A0; 
//Jeg bruger librariet LiquidCrystal, som hjælper med at gøre koden til min LCD skærm kortere og simplere.
#include <LiquidCrystal.h>
//Her kalder jeg dens pins (information)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Når man kører programmet for første gang er det denne function der bliver kaldt
void setup() {
//Her bliver der bare deklareret output og input på de two lydbølge banditter.
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
//Raten på Arduinoen trader information med SerialMonitoren på.
Serial.begin(9600);
digitalWrite(blue,HIGH);

  lcd.begin(16, 2);
  //Text jeg vil have stående på min LCD skærm.
  lcd.print("Afstand i cm!");


}
//Det er funktionen der hele tiden bliver kaldt
void loop() {
//Det er her at der bliver målt afstand, det sker ved at jeg sender nogle lydbølger afsted som kort tid efter bliver modtaget og der bliver så udregnet hvor langt det var.
digitalWrite(trigPin,LOW);
delayMicroseconds(2);

digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);
//pulseIn er en funktion der siger hvor lang tid det tog for trigPin at blive LOW igen, og grunden til at der er delay på 10 millisekunder er hvis man mister lydbølgen så kan programmet stadig køre.
duration = pulseIn(echoPin,HIGH);
//Grunden til at 0.034 blev valgt er fordi at det er lydens hast i mikrosekunder, som derefter bliver divideret med 2 fordi at det skal både frem og tilbage.
distance = duration*0.034/2;
//Her bliver der printet distance til konsollen, så jeg kan læse hvad det er.
Serial.print("Distance: ");
Serial.println(distance);
//Her skriver jeg bare at mine LED lys skal tænde baseret på distance, så hvis man kommer tæt på en væg bliver lysene tændt.
delay(100);
//Distance er i centimeter btw,jo lavere distance er, jo flere LED lys bliver tændt og der er en rangliste af hvor slemme de er, blå er altid tændt, grøn er et stykke væk, gul er tæt på, rød er farligt tæt på.
if (distance<=60){
digitalWrite(green,HIGH);
} else {digitalWrite(green,LOW);}

if (distance<=40){
digitalWrite(yellow,HIGH);
} else {digitalWrite(yellow,LOW);}

if (distance<=20){
digitalWrite(red,HIGH);
} else {digitalWrite(red,LOW);}

//setCursor er hvor der skal skrives noget text, x,y værdier. Når y=0 er den øverst, når y=1 er den nederst.
    lcd.setCursor(0, 1);
//Den printer afstanden som bliver givet af lydsensoren på setcursors plads.
    lcd.print(distance);
//Det er ligesom at skrive background() i draw i javascript, den renser bare canvas så der ikke står wack tal i baggrunden og roder, så man kan rent faktisk læse teksten der bliver givet nu).
//LCD'et der bliver brugt i programmet er 16 blokke lange og 2 høje, men hvis du bruger en anden LCD skærm skal du nok ændre mængden af mellemrum i min lcd.print("mellemrum"x16) linje.
lcd.print("                ");
//Delayen gør det hele bare lidt bedre og mere smooth, da hurtig tekst er svær tekst :()
delay(250);
  
}
