
class StateChange{
  private:     
    int buttonPin, ledPin, buttonPushCounter, buttonState, lastButtonState;
  
  public:
    StateChange(int bp, int lp){
      buttonPin = bp;
      ledPin = lp;
      pinMode(buttonPin, INPUT);
      pinMode(ledPin, OUTPUT);
      buttonPushCounter = 0;
      buttonState = 0;
      lastButtonState= 0;
    }
    void start(){
      digitalWrite(ledPin, LOW);
    }
    void looping(){
      buttonState = digitalRead(buttonPin);
      if (buttonState != lastButtonState) {
        if (buttonState == HIGH) {
          delay(500);
          buttonPushCounter++;
          Serial.println("on");
          Serial.print("number of button pushes:  ");
          Serial.println(buttonPushCounter);
        } 
        else {
          Serial.println("off"); 
        }
      }
      lastButtonState = buttonState;
    
      if (buttonPushCounter % 2 == 1) {
        digitalWrite(ledPin, HIGH);
      } else {
       digitalWrite(ledPin, LOW);
      }
    }
    
};

#include <Servo.h>

const int ledPinPower = 13;
const int ledPinKey = 12;
const int ledPinComplete = 11;

const int switchPinPower = 10;
const int switchPinKey = 9;
const int switchPinMinotaur = 8;

const int servoPinPlayer = 7;
const int servoPinDoor = 6;
const int servoPinMinotaur = 5;

const int switchPinAttack = 4;

const int ledPinHealthA = 3;
const int ledPinHealthB = 2;
const int ledPinHealthC = 1;
const int ledPinHealthD = 0;

bool isGameOn, isKeyTaken, isMinotaurDead;
int ledStateKey, ledStateComplete, servoStateDoor, servoStatePlater, servoStateMinotaur, ledStateHealthA, ledStateHealthB, ledStateHealthc, ledStateHealthD;
Servo servoDoor, servoPlayer, servoMinotaur;
StateChange power(switchPinPower, ledPinPower);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPinKey, OUTPUT);
  pinMode(switchPinKey, INPUT);

  servoDoor.attach(servoPinDoor);
  void start();
}

void start(){
  power.start();
 

  isGameOn = false;
  isMinotaurDead = false;
  isKeyTaken = false;
  
  ledStateKey = HIGH;
  int servoStateDoor = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  power.looping();
  
  if(digitalRead(ledPinPower) == LOW){
    Serial.println("the round has not began");
    start();
  }
  else{
    isGameOn = true;
    Serial.println("the game has began");
    //player goes up to the key
    if(digitalRead(switchPinKey) == HIGH && isKeyTaken == false){
      isKeyTaken = true;
      ledStateKey = LOW;
      // servo to open door activate
      servoStateDoor = 180;   
    }
  }

  if(isGameOn == true){
    digitalWrite(ledPinKey, ledStateKey);
    servoDoor.write(servoStateDoor);
  }
  else{
    digitalWrite(ledPinKey, LOW);
    servoDoor.write(0);   
  }

  
  
}
