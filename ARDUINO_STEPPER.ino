#define A 2
#define B 3
#define C 4
#define D 5
#define E 8
#define F 9
#define G 10
#define H 11
#define button1 6
#define button2 7
#define buttonHome 12
#define cursa1 2150
#define cursa2 6750 
//#define led 13

unsigned int step_break = 1;
bool pos1[4];
bool pos2[4];
int j = 0;
int k = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonStateHome = 0;
int p1 = 0;
int p2 = 0;
int state = 0;

void setup(){
Serial.begin(9600);
pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
pinMode(D,OUTPUT);
pinMode(E,OUTPUT);
pinMode(F,OUTPUT);
pinMode(G,OUTPUT);
pinMode(H,OUTPUT);
pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
pinMode(buttonHome,INPUT_PULLUP);
//pinMode(led,OUTPUT);
initialize();
}

void write1(){
digitalWrite(A,pos1[0]);
digitalWrite(B,pos1[1]);
digitalWrite(C,pos1[2]);
digitalWrite(D,pos1[3]);
}

void write2(){
digitalWrite(E,pos2[0]);
digitalWrite(F,pos2[1]);
digitalWrite(G,pos2[2]);
digitalWrite(H,pos2[3]);
}

void initialize(){
  pos1[0] = 1;
  write1();
  delay(step_break);
  pos1[1]= 1;
  write1();
  delay(step_break);
    pos2[0] = 1;
  write2();
  delay(step_break);
  pos2[1]= 1;
  write2();
  delay(step_break);
}

void onestepAB1(){
  for (int i = 0;i < sizeof(pos1); i++){
       if (pos1[i]==1){      
      if (i == sizeof(pos1) - 1){
          pos1[0] = 1;
          break;         
      }       
      if (i == 0 and pos1[sizeof(pos1) - 1] == 1){
            pos1[sizeof(pos1) - 1] = 0;
            break;            
      }          
      if (pos1[i+1]==1) {
                pos1[i]=0;
                break;                
      } else {
                  pos1[i+1]=1;
                  break;               
        }      
    }    
  }  
}

void onestepBA1(){

  for (int i = (sizeof(pos1)-1); i >= 0; i--){
    
    if (pos1[i]==1){
      
      if (i == 0){
          pos1[sizeof(pos1)-1] = 1;
          break;
      } 

      if (i == sizeof(pos1)-1 and pos1[0] == 1){
            pos1[0] = 0;
            break;
      }
        
      if (pos1[i-1]==1) {
                pos1[i]=0;
                break;
      } else {
                pos1[i-1]=1;
                break;
        } 
        
    }
    
  }
  
}

void onestepAB2(){

  for (int i = 0;i < sizeof(pos2); i++){
    
    if (pos2[i]==1){
      
      if (i == sizeof(pos2) - 1){
          pos2[0] = 1;
          break;         
      } 
      
      if (i == 0 and pos2[sizeof(pos2) - 1] == 1){
            pos2[sizeof(pos2) - 1] = 0;
            break;            
      }
          
      if (pos2[i+1]==1) {
                pos2[i]=0;
                break;                
      } else {
                  pos2[i+1]=1;
                  break;               
        } 
            
    }
    
  }
  
}

void onestepBA2(){

  for (int i = (sizeof(pos2)-1); i >= 0; i--){
    
    if (pos2[i]==1){
      
      if (i == 0){
          pos2[sizeof(pos2)-1] = 1;
          break;
      } 

      if (i == sizeof(pos2)-1 and pos2[0] == 1){
            pos2[0] = 0;
            break;
      }
        
      if (pos2[i-1]==1) {
                pos2[i]=0;
                break;
      } else {
                pos2[i-1]=1;
                break;
        } 
        
    }
    
  }
  
}

void loop(){
  
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonStateHome = digitalRead(buttonHome);
  if (buttonState1 == LOW){
    if (state == 0){
      p1 = j + cursa1;
    while (j != p1){
      
     if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }
    }
    state = 1;   
  } else if (state == 2){
    p1 = j - cursa1;
    p2 = k - cursa2;
    while ((j != p1) || (k != p2)){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }

    if (k < p2) {
      onestepBA2();
      write2();
      delay(step_break);
      k++;
    }
    if (k > p2){
        onestepAB2();
        write2();
        delay(step_break);
        k--;
    }

   }
   p1 = j + cursa1;
    while (j != p1){
      
     if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }
    }
    state = 1;
  }
  }
  if (buttonState2 == LOW){

    if (state == 0){      
      p1 = j + cursa1;
      p2 = k + cursa2;
   while (k != p2){
      
    if (k < p2) {
      onestepBA2();
      write2();
      delay(step_break);
      k++;
    }
    if (k > p2){
        onestepAB2();
        write2();
        delay(step_break);
        k--;
    }

   }

   while (j != p1){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }
    
   }
    state = 2;
   } else if (state == 1){
    p1 = j - cursa1;
    p2 = k + cursa2;
    while ((j != p1) || (k != p2)){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }

    if (k < p2) {
      onestepBA2();
      write2();
      delay(step_break);
      k++;
    }
    if (k > p2){
        onestepAB2();
        write2();
        delay(step_break);
        k--;
    }

   }
   p1 = j + cursa1;
   while (j != p1){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }
    
   }
state = 2;
  }

}
if (buttonStateHome == LOW){
  if (state == 1){
    p1 = j - cursa1; 
    while (j != p1){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }
   }
   state = 0;
  } else if (state == 2){
    p1 = j - cursa1;
    p2 = k - cursa2;
    while ((j != p1) || (k != p2)){
      
    if (j < p1) {
      onestepAB1();
      write1();
      delay(step_break);
      j++;
    }
    if (j > p1){
      onestepBA1();
      write1();
      delay(step_break);
      j--;
    }

    if (k < p2) {
      onestepBA2();
      write2();
      delay(step_break);
      k++;
    }
    if (k > p2){
        onestepAB2();
        write2();
        delay(step_break);
        k--;
    }
   }
   state = 0;
  }  
}
}
/*  if (a == 1 and b == 1 and c == 0 and d == 0){
  a = 0;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 0 and b == 1 and c == 0 and d == 0){
  c = 1;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 0 and b == 1 and c == 1 and d == 0){
  b = 0;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 0 and b == 0 and c == 1 and d == 0){
  d = 1;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 0 and b == 0 and c == 1 and d == 1){
  c = 0;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 0 and b == 0 and c == 0 and d == 1){
  a = 1;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 1 and b == 0 and c == 0 and d == 1){
  d = 0;
  write(a,b,c,d);
  delay(step_break);
  }
  if (a == 1 and b == 0 and c == 0 and d == 0){
  b = 1;
  write(a,b,c,d);
  delay(step_break);
  }*/
  /*write(1,0,0,0);
delay(step_break);
write(1,1,0,0);
delay(step_break);
write(0,1,0,0);
delay(step_break);
write(0,1,1,0);
delay(step_break);
write(0,0,1,0);
delay(step_break);  
write(0,0,1,1);
delay(step_break);
write(0,0,0,1);
delay(step_break);
write(1,0,0,1);
delay(step_break); */
