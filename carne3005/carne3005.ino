int people;
int state;

#define trigPin 13
#define echoPin 12
#define trigPin2 8
#define echoPin2 7

int timer = 0;
int timer2 = 0;
int timerWater = 0;
int ledCounter = 0;

int ledTimer = 0;

boolean establishedContact = false;

boolean entered = false;
boolean left = false;

void setup() {

  pinMode(5, OUTPUT);
  digitalWrite(1, HIGH);
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(6, OUTPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  //relay
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
}

void loop() {

  checkSensor();

    if (left && !entered) {

      if(people > 0){
        people --;
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        Serial.write(people);
        emptyWater();
        delay(1000);
        left = false;
        entered = false;
      } 
      

    }
    if (entered && !left) {

      people ++;
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);
      Serial.write(people);
      fillWater();
      delay(1000);
      left = false;
      entered = false;

    }
    if (!entered && !left) {

      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      //delay(500);

    }

 analogWrite(5, ledCounter);
  
  ledCounter += 5;
  
  if((millis() - ledTimer) >= 1000){
  
    //Serial.println(people);
    ledTimer = millis();
  
  }
 
}

void checkSensor() {

  long duration, distance, nextDistance;
  long duration2, distance2, nextDistance2;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  nextDistance = (duration / 2) / 29.1;

  if (timer == 0) {

    distance = nextDistance;

  }

  if (distance < 8) {  // This is where the LED On/Off happens

    if (timer == 0) {

      timer = millis();

    }

  }

  if ((timer != 0) && (millis() - timer >= 800)) {

    timer = 0;

  }

  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  nextDistance2 = (duration2 / 2) / 29.1;

  if (timer2 == 0) {

    distance2 = nextDistance2;

  }

  if (distance2 < 8) {  // This is where the LED On/Off happens

    if (timer2 == 0) {

      timer2 = millis();

    }

  }

  if ((timer2 != 0) && (millis() - timer2 >= 800)) {

    timer2 = 0;

  }


  if (distance < 100 && distance > 0) {

    if (distance2 < 100 && distance2 > 0) {
//      Serial.print(distance);
//      Serial.print(" ");
//      Serial.print(distance2);
//      Serial.print(" ");
//      Serial.print(state);
//
//      Serial.println();
      //Serial.print(distance2);
    }
    //Serial.print(distance2);
  }

  if (distance < 8 && distance > 0) {

    if (distance2 > 8) {

      entered = true;
      left = false;

    }

  }

  if (distance2 < 8 && distance2 > 0)
  {

    if (distance > 8) {

      entered = false;
      left = true;

    }

  }

  if (distance2 > 8 && distance > 8) {

    entered = false;
    left = false;

  }

  delay(100);

}

void emptyWater() {

  digitalWrite(9, LOW);
  delay(6000);
  digitalWrite(9, HIGH);

}

void fillWater(){

  analogWrite(6, 123);
  delay(4000);
  analogWrite(6, 0);

}




