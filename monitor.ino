                                                                                                                                             //PINS
#define GREEN 13
#define RED 12
#define BUZZER 11
#define YELLOW 10
#define FSR 0

//Alert levels
#define SAFE 0 //Normal Heart-Rate (possibly implies good health)
#define WARN 1 //Above or below average - May have adverse consequences at a later time
#define DANGER 2 //Heart-Rate very high or low - Could mean cardiac arrest, heart attack OR other adverse cardia event.

#define FAST 120
#define HNORM 70
#define LNORM 50
#define SLOW 30



int level = SAFE;
float heartRate = (HNORM+LNORM)/2.0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW , OUTPUT);
  pinMode(RED , OUTPUT);
  pinMode(BUZZER , OUTPUT);
  pinMode(FSR , INPUT);
}

void alert(int level) {
   digitalWrite(RED , LOW);
   digitalWrite(YELLOW , LOW);
   digitalWrite(GREEN , LOW);
   analogWrite(BUZZER , LOW);
  switch (level) {
    case SAFE:
      digitalWrite(GREEN , HIGH);
      analogWrite(BUZZER, LOW);
      break;
    case WARN:
      digitalWrite(YELLOW , HIGH);
      analogWrite(BUZZER, LOW);
      break;
    case DANGER:
      digitalWrite(RED, HIGH);
      analogWrite(BUZZER , 3);
      tone(BUZZER, 500);
      break;
    default:
      alert(SAFE);//I think safe is a good default
      break;
  }
}

boolean warn(float heartRate){
  return heartRate > HNORM && heartRate < FAST || heartRate < LNORM && heartRate > SLOW;
}

boolean danger(float heartRate){
  return heartRate >= FAST || heartRate <= SLOW;  
}

void loop() {
  float current = millis();
  int beats = 0;
  while (current + 1000 > millis()) {
    float reading = analogRead(FSR);
    if (reading > 0) {
      beats++;
    }
    delay(100);
  }
  heartRate +=  (beats * 60);
  heartRate /= 2;
  Serial.println(heartRate);

  if(warn(heartRate)){
    alert(WARN);
  }
  else if(danger(heartRate)){
    alert(DANGER);
  }
  else{
    alert(SAFE);
  }
}
