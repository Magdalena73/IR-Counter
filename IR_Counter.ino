/**** Counter using a dual 7-Segment-Display with common anoden and an Infrared Sensor Module.*****/
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
  Null();
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
void Null(){
  for(int i = 0; i<7;i++){
    digitalWrite(Seg_Array[i],HIGH);
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


void show_Digit(int digit)
{int i;
  switch (digit){
     case 0:
       for( i = 0; i<6;i++){
         digitalWrite(Seg_Array[i],LOW);
       }
       digitalWrite(Seg_Array[6],HIGH);
       break;
     case 1:
       Null();
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       break;
     case 2:
        Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[6],LOW);
       digitalWrite(Seg_Array[4],LOW);
       digitalWrite(Seg_Array[3],LOW);
       break; 
     case 3:
       Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[6],LOW);
       digitalWrite(Seg_Array[2],LOW);
       digitalWrite(Seg_Array[3],LOW);
       break; 
     case 4:
       Null();
       digitalWrite(Seg_Array[5],LOW);
       digitalWrite(Seg_Array[6],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       break; 
     case 5:
       Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[5],LOW);
       digitalWrite(Seg_Array[6],LOW);
       digitalWrite(Seg_Array[2],LOW);
       digitalWrite(Seg_Array[3],LOW);
       break; 
     case 6:
       Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[5],LOW);
       digitalWrite(Seg_Array[4],LOW);
       digitalWrite(Seg_Array[3],LOW);
       digitalWrite(Seg_Array[2],LOW);
       digitalWrite(Seg_Array[6],LOW);
       break;  
     case 7:
       Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       break;  
     case 8:
       for(i = 0; i<7;i++){
         digitalWrite(Seg_Array[i],LOW);
       }
       break; 
     case 9:
       Null();
       digitalWrite(Seg_Array[0],LOW);
       digitalWrite(Seg_Array[1],LOW);
       digitalWrite(Seg_Array[2],LOW);
       digitalWrite(Seg_Array[3],LOW);
       digitalWrite(Seg_Array[5],LOW);
       digitalWrite(Seg_Array[6],LOW);
       break;    
     default:
       Null();
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
