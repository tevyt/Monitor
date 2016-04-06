//PINS
#define YELLOW 13
#define RED 12
#define BUZZER 11
#define FSR 0

//Alert levels
#define SAFE 0
#define WARN 1
#define DANGER 2

#define FAST 150
#define NORMAL 80
#define SLOW   30



int level = SAFE;
float heartRate = NORMAL;
  
void setup() {
  Serial.begin(9600);
  pinMode(YELLOW , OUTPUT);
  pinMode(RED , OUTPUT);
  pinMode(BUZZER , OUTPUT);
  pinMode(FSR , INPUT);
}

void alert(int level){
  switch(level){
    case SAFE:
      digitalWrite(YELLOW , HIGH);
      break;
    case WARN:
      digitalWrite(RED , HIGH);
      break;
    case DANGER:
      analogWrite(BUZZER , 3);
      break;
    default:
      alert(SAFE);//I think safe is a good default
      break;
  }
}

void loop() { 
  float current = millis();
  int beats = 0;
  while(current + 1000 > millis()){
    float reading = analogRead(FSR);
    if(reading > 0){
      beats++; 
    }
    delay(100);
  }
  heartRate +=  (beats * 60);
  heartRate /= 2;
  Serial.println(heartRate);
}
