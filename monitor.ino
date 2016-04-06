//PINS
#define YELLOW 13
#define RED 12
#define BUZZER 11

//Alert levels
#define SAFE 0
#define WARN 1
#define DANGER 2



void setup() {
  pinMode(YELLOW , OUTPUT);
  pinMode(RED , OUTPUT);
  pinMode(BUZZER , OUTPUT);

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
  //alert(SAFE);
  //alert(WARN);
  //alert(DANGER);
  
}
