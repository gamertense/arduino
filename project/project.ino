int count = 0;
int trig = 0;
#include <NewPing.h> // We use NewPing to control the Ultrasonic Sensors - You'll need to install this library from the library manager if you donb't already have it.
#define  t1  A0  // Trigger pin on Ultrasonic Sensor 1
#define  e1  A1  // Echo pin on Ultrasonic Sensor 1
#define  t2  A2  // Trigger pin on Ultrasonic Sensor 2
#define  e2  A3  // Echo pin on Ultrasonic Sensor 2
#define maxDist 400 // the max distance for the ultrasonic pulse

NewPing eyeR(t2, e2, maxDist ); // Initialise Ultrasonic sensor 2
NewPing eyeL(t1, e1, maxDist ); // Initialise Ultrasonic sensor 1

int distance1, distance2;
int currentState = -1;
float nextBlink = millis() + 1000;

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  // put your setup code here, to run once:
  for (int pin = 2; pin <= 9; pin++) {
    pinMode(pin, OUTPUT);
  }
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, HIGH);
    //    delay(100);
  }
}

void setonoff(byte state) {
  for (int i = 0; i < 4; i++) {
    int a = ((state >> i & 0x01) == 0x01 ? HIGH : LOW);
    digitalWrite(i + 2, a);
  }
}

void loop() {
  // Ping the Left eye with a recursion of 5
 distance1 = eyeL.ping_median( );
 Serial.print("dis1 = ");
 Serial.println(distance1);
 // Delay 500ms before we ping the right eye, so we don't get conflicting results
 // delay(10);
 // Ping the Right eye with recursion of 5
 distance2 = eyeR.ping_median( );
 Serial.print("dis2 = ");
 Serial.println(distance2);

  float difference = ( distance2 - distance1 );
  // if ( abs( difference ) < 250 || (distance1 == 0 && distance2 == 0 ) )
  // {
  //   closeEye();
  //   currentState = 0;
  // }
  // Now if distance1 is greater than distance2 and distance1 is also greater than 0, then we want to look right
  if ( distance2 < distance1 && distance1 > 0)
  {
  }
  // Now if distance2 is greater than distance1 and distance2 is also greater than 0, then we want to look left
  else if ( distance1 < distance2 && distance2 > 0 )
  {
    currentState = 2;
  }

  // delay the loop for 250ms to ensure the eyes have time to display correctly
  //  delay(250);

  count += 1;
  if ((count <= 100) && (trig == 0))
  { if (count == 100) {
      trig = 1;
      count = 0;

    }
    ShowEye_Left();
  }
  if ((count <= 20) && (trig == 1))
  { if (count == 20) {
      trig = 0;
      count = 0;

    }
    closeEye();
  }

}
void ShowEye_Left() {
  byte charactor[4]  =  {0b00000110,
                         0b00001101,
                         0b00001001,
                         0b00000110,
                        };
  // put your main code here, to run repeatedly:
  for (int i = 0 ; i < 4; i++) {
    setonoff(charactor[i]);
    digitalWrite(i + 6, LOW);
    delay(1);
    digitalWrite(i + 6, HIGH);
  }
}

void ShowEye_Right() {
  byte charactor[4]  =  {0b00000110,
                         0b00001011,
                         0b00001001,
                         0b00000110,
                        };
  // put your main code here, to run repeatedly:
  for (int i = 0 ; i < 4; i++) {
    setonoff(charactor[i]);
    digitalWrite(i + 6, LOW);
    delay(1);
    digitalWrite(i + 6, HIGH);
  }
}

void closeEye() {
  byte charactor[4]  =  {0b00000000,
                         0b00001111,
                         0b00001111,
                         0b00000000,
                        };
  // put your main code here, to run repeatedly:
  for (int i = 0 ; i < 4; i++) {
    setonoff(charactor[i]);
    digitalWrite(i + 6, LOW);
    delay(1);
    digitalWrite(i + 6, HIGH);
  }
}




