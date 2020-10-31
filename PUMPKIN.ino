
int LEFT_EYE = 5;
int RIGHT_EYE = 6;
int TEETH_0 = 9;  // centermost teeth
int TEETH_1 = 10;
int TEETH_2 = 11;
int TEETH_3 = 12;
int TEETH_4 = 13;
int TEETH_DELAY = 250;
float MORSE_MULT = 150.0;

unsigned long eyesStartTime = 0;  // timestamp to measure against w/ currentTime
unsigned long teethStartTime = 0;
unsigned long currentTime = 0;  // timestamp which helps track elapsed time w/ startTime
// Morse code "happy halloween!"
// .... .- .--. .--. -.--       .... .- .-.. .-.. --- .-- . . -. -.-.--
int message[64] = {1,1,1,1, 4, 1, 2, 4, 1, 2, 2, 1, 4, 1, 2, 2, 1, 4, 2, 1, 2, 2, 4, 1, 1, 1, 1, 4, 1, 2, 4, 1, 2, 1, 1, 4, 1, 2, 1, 1, 4, 2, 2, 2, 4, 1, 2, 2, 4, 1, 4, 1, 4, 2, 1, 4, 2, 1, 2, 1, 2, 2, 2,4};
int msgIdx = 0;
int currentEyeDuration;
bool eyeLit;
int numTeethLit = 0;



void setup() {
  // put your setup code here, to run once:
  delay(100);
  pinMode(LEFT_EYE, OUTPUT);  // left eye
  pinMode(RIGHT_EYE, OUTPUT);  // right eye
  pinMode(TEETH_0, OUTPUT);
  pinMode(TEETH_1, OUTPUT);
  pinMode(TEETH_2, OUTPUT);
  pinMode(TEETH_3, OUTPUT);
  pinMode(TEETH_4, OUTPUT);

  digitalWrite(LEFT_EYE, HIGH);
  digitalWrite(RIGHT_EYE, HIGH);
  digitalWrite(TEETH_0, HIGH);
  digitalWrite(TEETH_1, HIGH);
  digitalWrite(TEETH_2, HIGH);
  digitalWrite(TEETH_3, HIGH);
  digitalWrite(TEETH_4, HIGH);

  currentEyeDuration = message[msgIdx] * MORSE_MULT;
  eyeLit = true;
  eyesStartTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  if(currentTime - eyesStartTime > currentEyeDuration){
    // Light duration elapsed. 
    // If currently lit, go dark.
    msgIdx +=1;
    if (msgIdx >= 64){
      msgIdx = 0;
    }
    if (message[msgIdx] == 4){
      digitalWrite(LEFT_EYE, LOW);
      digitalWrite(RIGHT_EYE, LOW);
      eyeLit = false;
    }else{
      digitalWrite(LEFT_EYE, HIGH);
      digitalWrite(RIGHT_EYE, HIGH);
      eyeLit = true;
    }
    eyesStartTime = millis();
    currentEyeDuration = message[msgIdx] * MORSE_MULT;
  }
  if (currentTime - teethStartTime > TEETH_DELAY){
    if (numTeethLit == 0 ){
      digitalWrite(TEETH_0, HIGH);
      numTeethLit = 1;
    } else if (numTeethLit == 1){
      digitalWrite(TEETH_1, HIGH);
      numTeethLit = 2;
    }else if (numTeethLit == 2){
      digitalWrite(TEETH_2, HIGH);
      numTeethLit = 3;
    }else if (numTeethLit == 3){
      digitalWrite(TEETH_3, HIGH);
      numTeethLit = 4;
    }else if (numTeethLit == 4){
      digitalWrite(TEETH_4, HIGH);
      numTeethLit = 5;
    }else{
      digitalWrite(TEETH_0, LOW);
      digitalWrite(TEETH_1, LOW);
      digitalWrite(TEETH_2, LOW);
      digitalWrite(TEETH_3, LOW);
      digitalWrite(TEETH_4, LOW);
      numTeethLit = 0;
    }
     teethStartTime = millis();
  }
    
}
