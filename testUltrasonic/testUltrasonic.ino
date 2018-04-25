#include <NewPing.h>

#define TRIGGER_PIN  A0
#define ECHO_PIN     A1

#define TRIGGER_PIN2  A2
#define ECHO_PIN2     A3

#define MAX_DISTANCE 30

int dis1;
int dis2;
boolean disBackToZero = false;
int count = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(500);
  dis1 = sonar.ping_cm();
  dis2 = sonar2.ping_cm();

  if(dis1 == 0){
    disBackToZero = true;
  }
  
  if (dis1 > 0 && disBackToZero == true) {
    delay(500);
    count++;
    disBackToZero = false;
  }

  Serial.print("Dis1: ");
  Serial.print(" ");
  Serial.print(dis1);
  Serial.print("Dis2: ");
  Serial.print(dis2);
  Serial.println("cm");
  Serial.print(count);
}
