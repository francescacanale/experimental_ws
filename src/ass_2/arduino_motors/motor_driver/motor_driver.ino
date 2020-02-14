#define motorPin0 2 //PWM ant-sn
#define motorPin1 3 //PWM ant-dx
#define motorPin2 4 //PWM post-sn
#define motorPin3 5 //PWM post-dx
#define enA0 24     //pinA motor ant-sn
#define enB0 25     //pinB motor ant-sn
#define enA1 28     //pinA motor ant-dx
#define enB1 29     //pinB motor ant-dx
#define enA2 32     //pinA motor post-sn
#define enB2 33     //pinB motor post-sn
#define enA3 36     //pinA motor post-dx
#define enB3 37     //pinB motor post-dx
#define encoderA0 22
#define encoderB0 23
#define encoderA1 26
#define encoderB1 27
#define encoderA2 30
#define encoderB2 31
#define encoderA3 34
#define encoderB3 35

int stateA = 0;
int stateB = 0;
int counter = -1;
unsigned long t_start;
int vel = 0;
int sw = 0;
double actvel = 0;

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  //set PWM Pin
  pinMode(motorPin0, OUTPUT);   //PWM ant-sn
  pinMode(motorPin1, OUTPUT);   //PWM ant-dx
  pinMode(motorPin2, OUTPUT);   //PWM post-sn
  pinMode(motorPin3, OUTPUT);   //PWN post-dx

  //define motor 1: ANT-SN
  pinMode(enA0, OUTPUT);
  pinMode(enB0, OUTPUT);
  //define encoder 1: ANT-SN
  pinMode(encoderA0, INPUT);
  pinMode(encoderB0, INPUT);

  //define motor 2: ANT-DX
  pinMode(enA1, OUTPUT);
  pinMode(enB1, OUTPUT);
  //define encoder 2: ANT-DX
  pinMode(encoderA1, INPUT);
  pinMode(encoderB1, INPUT);

  //define motor 3: POST-SN
  pinMode(enA2, OUTPUT);
  pinMode(enB2, OUTPUT);
  //define encoder 3: POST-SN
  pinMode(encoderA2, INPUT);
  pinMode(encoderB2, INPUT);

  //define motor 4: POST-DX
  pinMode(enA3, OUTPUT);
  pinMode(enB3, OUTPUT);
  //define encoder 4: POST-DX
  pinMode(encoderA3, INPUT);
  pinMode(encoderB3, INPUT);

  //After a call to analogWrite(),
  //the pin will generate a steady rectangular wave of the specified duty cycle until the next call to analogWrite()
  //(or a call to digitalRead() or digitalWrite()) on the same pin.
}


//function to control motor
//speed is how fast the motor rotates
//set motorPin, enA and enB for the motor we want to drive
void control_motor(int speed, int motorPin, int enA, int enB) {
  if (speed > 0) {
    analogWrite(motorPin, speed);
    digitalWrite(enA, HIGH);
    digitalWrite(enB, LOW);
  }
  else if (speed < 0) {
    analogWrite(motorPin, -speed);
    digitalWrite(enA, LOW);
    digitalWrite(enB, HIGH);
  }
  else {
    digitalWrite(enA, LOW);
    digitalWrite(enB, LOW);
  }
}

//In time loop, receive from serial and control 4 motors
void loop() {
  static int speed[4];
  static char buff[30];
  int counter = 0;
  Serial.print("Hello");

  // read command from raspberry pi
  while (Serial.available()) {
    buff[counter] = Serial.read();
    if (counter > 30 || buff[counter] == '*') {
      buff[counter] = '\0';
      speed[0] = atoi(strtok(buff, ",")); //read cmd for ANT-SN
      speed[1] = atoi(strtok(NULL, ",")); //read cmd for ANT-DX
      speed[2] = atoi(strtok(NULL, ",")); //read cmd for POST-SN
      speed[3] = atoi(strtok(NULL, ",")); //read cmd for POST-DX
    }
    else {
      counter++;
    }
  }

  // control motors
  control_motor(speed[0], motorPin0, enA0, enB0);
  control_motor(speed[1], motorPin1, enA1, enB1);
  control_motor(speed[2], motorPin2, enA2, enB2);
  control_motor(speed[3], motorPin3, enA3, enB3);

  Serial.print(speed[0]); Serial.print(",");
  Serial.print(speed[1]); Serial.print(",");
  Serial.print(speed[2]); Serial.print(",");
  Serial.print(speed[3]); Serial.print(",");

  delay(100);
}

void checkA0() {
  int count;
  stateB = digitalRead(encoderB0);
  stateA = digitalRead(encoderA0);
  if (stateA != stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkB0() {
  int count;
  stateB = digitalRead(encoderB0);
  stateA = digitalRead(encoderA0);
  if (stateA == stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkA1() {
  int count;
  stateB = digitalRead(encoderB1);
  stateA = digitalRead(encoderA1);
  if (stateA != stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkB1() {
  int count;
  stateB = digitalRead(encoderB1);
  stateA = digitalRead(encoderA1);
  if (stateA == stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkA2() {
  int count;
  stateB = digitalRead(encoderB2);
  stateA = digitalRead(encoderA2);
  if (stateA != stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkB2() {
  int count;
  stateB = digitalRead(encoderB2);
  stateA = digitalRead(encoderA2);
  if (stateA == stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkA3() {
  int count;
  stateB = digitalRead(encoderB3);
  stateA = digitalRead(encoderA3);
  if (stateA != stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }

void checkB3() {
  int count;
  stateB = digitalRead(encoderB3);
  stateA = digitalRead(encoderA3);
  if (stateA == stateB) {
    counter++;
    count = 100;
  }
  else {
    counter--;
    count = -100;
  }
  if (counter % 100 == 0) {
    unsigned long t_fine = millis();
    unsigned long delta = t_fine - t_start;
    actvel = count / double(delta);
    t_start = millis();
  }
  }