/**** Counter using a dual 7-Segment-Display with common anodes and an Infrared Sensor Module.*****/
/***** MStronik.blog *****************************************************************************/
// Define the cathode pins for the 7-Segment Display:
#define a 10
#define b 9
#define c 2
#define d 4
#define e 3
#define f 6
#define g 5

// define the anodes:
int Dig1 = 7;
int Dig2 = 8;

int Seg_Array[7] = {a,b,c,d,e,f,g};
int SensorPin = A0;
int SensorValue;
int counter, units, tenths;

bool flag_count, last_state;

void setup() {
  counter = 0;
  flag_count = LOW;
  pinMode(SensorPin, INPUT);
  for( int i = 0; i<7;i++){
    pinMode(Seg_Array[i], OUTPUT);
  } 
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  all_OFF();
  //Serial.begin(9600);
}

void loop() {
  unsigned long start_time;
  
  SensorValue = analogRead(SensorPin);
 //Serial.println(SensorValue);
  tenths = int(counter/10);
  units = int(counter%10);
  if (SensorValue < 800){
    flag_count = HIGH;
    counter++;
    if(counter > 99)
       counter = 0;
    }
  else{
    flag_count = LOW;
    }
   
  if (last_state != flag_count)
    start_time = millis();
    for(unsigned long t_elapsed = 0; t_elapsed < 500; t_elapsed = millis()-start_time){
      show_Tenths(tenths);
      delay(10);
      show_Units(units);
      delay(10);
      }   
  last_state = flag_count;  
}

/***************** FUNCTIONS ******************************************/
void all_OFF(){
  for(int i = 0; i<7;i++){
    digitalWrite(Seg_Array[i],HIGH);
  }
}

void all_ON (){
  for(int i = 0; i<7;i++){
    digitalWrite(Seg_Array[i],LOW);
  }
}

void show_Tenths(int digit)
{
  digitalWrite(Dig1, LOW);
  digitalWrite(Dig2, HIGH);
  show_Digit(digit);
}

void show_Units(int digit)
{
  digitalWrite(Dig1, HIGH);
  digitalWrite(Dig2, LOW);
  show_Digit(digit);
}

// if cathode pin is HIGH: Segment will be OFF !
// Seg_Array[] = {a, b, c, d, e, f, g}
//         index: 0, 1, 2, 3, 4, 5, 6
void show_Digit(int digit)
{int i;
  switch (digit){
     case 0:
       all_ON();
       // turn OFF Segment G:
       digitalWrite(Seg_Array[6],HIGH);
       break;
     case 1:
       all_OFF();
       // turn ON Segment B and C:
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       break;
     case 2:
       all_ON();
       // turn OFF Segment C and F:
       digitalWrite(Seg_Array[2],HIGH);
       digitalWrite(Seg_Array[5],HIGH);
       break; 
     case 3:
       all_ON();
       // turn OFF Segment E and F:
       digitalWrite(Seg_Array[4],HIGH);
       digitalWrite(Seg_Array[5],HIGH);
       break; 
     case 4:
       all_ON();
       // turn OFF Segment A, D and E:
       digitalWrite(Seg_Array[0],HIGH);
       digitalWrite(Seg_Array[3],HIGH);
       digitalWrite(Seg_Array[4],HIGH);
       break; 
     case 5:
       all_ON();
       // turn OFF Segment B and E:
       digitalWrite(Seg_Array[1],HIGH);
       digitalWrite(Seg_Array[4],HIGH);
       break; 
     case 6:
       all_ON();
       // turn OFF Segment B:
       digitalWrite(Seg_Array[1],HIGH);
       break;  
     case 7:
       all_OFF();
       // turn ON Segment A, B and C:
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       break;  
     case 8:
       all_ON();
       break; 
     case 9:
       all_ON();
       // turn OFF Segment E:
       digitalWrite(Seg_Array[4],HIGH);
       break;    
     default:
       all_OFF();
       break;              
  }
  
}
/*Alternative function for the 7-Segment-Display:
void Display_Num(int digit){
  if((digit != 1)||(digit != 4))
     {Null();
     digitalWrite(Seg_Array[0],LOW);}
  else if ((digit != 5)||(digit != 6))
     { Null();
     digitalWrite(Seg_Array[1],LOW);}
  else if ((digit != 2))
     { Null();
     digitalWrite(Seg_Array[2],LOW);}   
  else if ((digit != 1)||(digit != 4)||(digit != 7))
     {Null(); 
     digitalWrite(Seg_Array[3],LOW);} 
  else if ((digit == 0)||(digit == 2)||(digit == 6)||(digit == 8))
     {Null(); 
     digitalWrite(Seg_Array[4],LOW);}
  else if ((digit != 1)||(digit != 2)||(digit != 3)||(digit != 7))
     {Null(); 
     digitalWrite(Seg_Array[5],LOW);}   
  else if ((digit != 0)||(digit != 1)||(digit != 2)||(digit != 7))
     {Null(); 
     digitalWrite(Seg_Array[6],LOW);}        
}
*/
