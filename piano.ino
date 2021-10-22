// do0, re1, mi2, fa3, so4, ra5, shi6, do7
int melody[] = { 131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523};
int melody_len = sizeof(melody) / sizeof(int);

int song[100];
int speeds[100];
int length = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
    for (int i = 0; i < melody_len; i++) {
      pinMode(i + 2, OUTPUT);
    }
}

void loop() {
  length = 0;
  int speed = 100;
  int tempSpeed = speed;
  int leftSpeedCount = -1;
  boolean accelerates = false;
  
  while (Serial.available() > 1) {
    int key = Serial.read();
    bool controlsSpeed = key == 'a' || key == 'r';
    if (controlsSpeed) {
      leftSpeedCount = 3;
      accelerates = key == 'a';
    }
    if (leftSpeedCount > -1) {
       speed += accelerates ? -10 : 10;
       speed = max(10, speed);
       tempSpeed = speed;
       leftSpeedCount--;
    }

    if (key == '-') {
      tempSpeed += speed;
    } else if (!controlsSpeed) {
      song[length] = key - 49;
      speeds[length] = tempSpeed;
      length++;
      tempSpeed = speed;
    }
  }

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < melody_len; j++) {
      digitalWrite(j + 2, LOW);
    }
    if (song[i] > -1) {
      tone(13, melody[song[i]], speeds[i] * 3);
      digitalWrite(song[i] + 2, HIGH);
    }
    else {
      delay(speeds[i] * 2);
    }
    delay(speeds[i] * 4);
  }
  delay(1000);
}
