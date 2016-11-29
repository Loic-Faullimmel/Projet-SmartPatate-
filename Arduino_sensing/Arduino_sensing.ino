//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 160  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;
int led;
int tension;
int somme;
float mesure[20];
int moyenne;

void setup()
{
  
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;

  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin

  Serial.begin(115200);

  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;         //-+

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  unsigned int d;

  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
   
    freq[d] = d;

  //   plot(v,0);              //-Display
 //    plot(results[d],1);
//     delayMicroseconds(1);
  }


  //PlottArray(1,freq,results); 
 
  
  TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)

/*----------------------------------------------------------------------------------MODIF------------------------------------------------------------------------------------*/

/*-------------------------CALCUL DE 20 VALEURS---------------------------------
   
   for(int j = 0; j < 20 ; j++)
   {
      mesure[j] = analogRead(A0);
      if(mesure[j] < 0)
      {
        mesure[j] = mesure[j]* -1;
      }
   }

   for(int y = 0; y < 20 ; y++)
   {
      somme = somme + mesure[y];
      Serial.println(somme);      
   }

   moyenne = somme / 20;

   
   /*Serial.print("Moyenne : ");
   Serial.println(moyenne);  */     

/*---------------------------------------------------------------------------------AFFICHAGE DES LEDS---------------------------------------------------------------------------------*/

/*------------------------------------------------TENTATIVE 5---------------------------------------*/

  
  tension = analogRead(A0);
  
  Serial.println(tension);
  

      if (tension >= 165 and tension <= 180)         
       {
             led = 0;
       }
  
      else if (tension > 180 and tension <= 199)
       {
             led = 1;
       }

      else if (tension >= 200)
       {
             led = 2;
       }

      else if (tension < 165)
       {
             led = 3;
       }


   switch (led) {
    
     case 0:
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      delay(1000);
       break;
       
     case 1:
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      delay(1000);
       break;

     case 2:
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        delay(50);
        digitalWrite(13,LOW);
        delay(50);
        digitalWrite(12, HIGH);
        delay(50);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        delay(50);
        digitalWrite(12,HIGH);
        digitalWrite(11, LOW);
        delay(50);
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        delay(1000);
        digitalWrite(13, LOW);
       break;
       

     case 3:
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

       break;
   }
   
/*------------------------------------------------TENTATIVE 4---------------------------------------*/
 
  /*
  
  Serial.println(analogRead(A0));

      if (analogRead(A0) <= 169)
       {
             digitalWrite(11, LOW);
             digitalWrite(12, LOW);
             digitalWrite(13, LOW); 
       }
    
      else if (analogRead(A0) >= 170 and analogRead(A0) <= 194)         
       {
             digitalWrite(11, HIGH);
             digitalWrite(12, LOW);
             digitalWrite(13, LOW);
       }
  
      else if (analogRead(A0) >= 195 and analogRead(A0) <= 204)
       {
             digitalWrite(11, HIGH);
             digitalWrite(12, HIGH);
             digitalWrite(13, LOW);
       }

      else if (analogRead(A0) >= 205)
       {
             digitalWrite(11, HIGH);
             digitalWrite(12, HIGH);
             digitalWrite(13, HIGH); 
       }*/

       
/*-----------------------------------------------TENTATIVE 3-----------------------------------------------------------*/


  /*   if (tension >= 185 and tension <= 240)         
       {
           {led = 1;}
       }

     else
       {
           {led = 2;}
       }
  

       switch (led) {
    
     case 1:
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
       break;
       
     case 2:
        digitalWrite(11,HIGH);
        delay(50);
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        delay(50);
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        delay(50);
        digitalWrite(12,HIGH);
        digitalWrite(13, LOW);
        delay(50);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        delay(50);
        digitalWrite(11, LOW);
       break;
     }   
*/

/*-----------------------------------------------TENTATIVE 2-----------------------------------------------------*/

/*
     if (analogRead(A0) >= 150 and analogRead(A0) <= 170)
      {
          {led=4;} 
      }
    
      else if (analogRead(A0) >= 180 and analogRead(A0) <= 195)         
       {
          {led=1;}
       }
  
     else if (analogRead(A0) >= 200 and analogRead(A0) <= 213)
       {
          {led=2;}
       }

     else if (analogRead(A0) >= 214 and analogRead(A0) <= 250)
      {
          {led=3;} 
      }

  
  switch (led) {
    
     case 1:
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
       break;
       
     case 2:
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
       break;

     case 3:
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
       break;
       
     case 4:
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
       break;

     default:
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
       break;

 }*/

 
} 

   
