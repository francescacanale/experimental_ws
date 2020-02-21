//Defining the pin for the motors and their encoders
#define motorPin0 2  //PWM ant-sn
#define motorPin1 3  //PWM ant-dx
#define motorPin2 4  //PWM post-sn
#define motorPin3 5  //PWM post-dx
#define enA0 24      //pinA motor ant-sn (from arduino to motor -->)
#define enB0 25      //pinB motor ant-sn
#define enA1 28      //pinA motor ant-dx
#define enB1 29      //pinB motor ant-dx
#define enA2 32      //pinA motor post-sn
#define enB2 33      //pinB motor post-sn
#define enA3 36      //pinA motor post-dx
#define enB3 37      //pinB motor post-dx
#define encoderA0 22 //pinA encoder ant-sn (from encoder to arduino <--)
#define encoderB0 23 //pinB encoder ant-sn
#define encoderA1 26 //pinA encoder ant-dx
#define encoderB1 27 //pinB encoder ant-dx
#define encoderA2 30 //pinA encoder post-sn
#define encoderB2 31 //pinB encoder post-sn
#define encoderA3 34 //pinA encoder post-sn
#define encoderB3 35 //pinB encoder post-sn

#define LOOPTIME 100 //to manage communication with the serial

int counterG[4] = {0,0,0,0};                                //counter used in the comparison of the states of each motor
int countAnt[4] = {0,0,0,0};                                // to store the previous value of each counter, used in computePWM()
int PWM_val[4] = {0,0,0,0};                                 //values of the PWM wave
unsigned long t_start;
unsigned long lastMilli = 0;                                // loop timing 
unsigned long lastMilliPrint[4] = {0,0,0,0};                // loop timing
double speed_act[4] = {0.0,0.0,0.0,0.0};                    // RPM
double speed_req[4] = {0.0,0.0,0.0,0.0};                    // speed requestued
double Kp = 16.0;                                           // PID Proportional control Gain
double Kd = 4.0;                                            // PID Derivitave control Gain
double last_error[4] = {0.0,0.0,0.0,0.0};                   // to store the previous value of each error


void setup() {
  Serial.begin(115200);           // Set up Serial library at 115200 bps
  
  // Setup the motors and link the interrupt function to the corresponding function
  set_motors(motorPin0, enA0, enB0, encoderA0, encoderB0);
  attachInterrupt(digitalPinToInterrupt(encoderA0), checkA0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB0), checkB0, CHANGE);
  set_motors(motorPin1, enA1, enB1, encoderA1, encoderB1);
  attachInterrupt(digitalPinToInterrupt(encoderA1), checkA1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB1), checkB1, CHANGE);
  set_motors(motorPin2, enA2, enB2, encoderA2, encoderB2);
  attachInterrupt(digitalPinToInterrupt(encoderA2), checkA2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB2), checkB2, CHANGE);
  set_motors(motorPin3, enA3, enB3, encoderA3, encoderB3);
  attachInterrupt(digitalPinToInterrupt(encoderA3), checkA3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB3), checkB3, CHANGE);
  
  t_start = millis();
  Serial.println("Arduino is ready");
}

void set_motors(int motorPin, int enA, int enB, int encoderA, int encoderB) {
  
  // Define the functionality of each pin 
  pinMode(motorPin, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
}

// In time loop, receive from serial and control 4 motors
void loop() {
  static int speed[4];
  static char buff[30];
  int counter = 0;
  
  // Read commands from Raspberry Pi
  while (Serial.available()) {
    buff[counter] = Serial.read();
    if (counter > 30 || buff[counter] == '*') {
      buff[counter] = '\0';
      speed[0] = atoi(strtok(buff, ",")); // read cmd for ANT-SN
      speed[1] = atoi(strtok(NULL, ",")); // read cmd for ANT-DX
      speed[2] = atoi(strtok(NULL, ",")); // read cmd for POST-SN
      speed[3] = atoi(strtok(NULL, ",")); // read cmd for POST-DX
    }
    else {
      counter++;
    }
  }
  
  // Control the motors
  control_motor(speed[0], motorPin0, enA0, enB0);
  control_motor(speed[1], motorPin1, enA1, enB1);
  control_motor(speed[2], motorPin2, enA2, enB2);
  control_motor(speed[3], motorPin3, enA3, enB3);
  
  // Compute RPM and PWM for each motors
  computePWM(speed);
  delay(100);
}

// Function to control the rotation sign setting the PWM wave
void control_motor(int speed, int motorPin, int enA, int enB) {
  if (speed > 0) {
    digitalWrite(enA, HIGH);
    digitalWrite(enB, LOW);
  }
  else if (speed < 0) {
    digitalWrite(enA, LOW);
    digitalWrite(enB, HIGH);
  }
  else {
    digitalWrite(enA, LOW);
    digitalWrite(enB, LOW);
  }
}

//Function to compute the RPM and the PWM
void computePWM(int speed[]) {
  if((millis() - lastMilli) >= LOOPTIME)   {  // Condition to ensure serial availability
   lastMilli = millis();
   
   // Ideal requested speed
   speed_req[0]=((double)speed[0])/(500.0);
   speed_req[1]=((double)speed[1])/(500.0);
   speed_req[2]=((double)speed[2])/(500.0);
   speed_req[3]=((double)speed[3])/(500.0);
   
   // RPM 
   speed_act[0] = (double)(((double)(counterG[0] - countAnt[0])*(1000.0/(double)LOOPTIME))/(double)(320.0));
   speed_act[1] = (double)(((double)(counterG[1] - countAnt[1])*(1000.0/(double)LOOPTIME))/(double)(320.0));
   speed_act[2] = (double)(((double)(counterG[2] - countAnt[2])*(1000.0/(double)LOOPTIME))/(double)(320.0));
   speed_act[3] = (double)(((double)(counterG[3] - countAnt[3])*(1000.0/(double)LOOPTIME))/(double)(320.0));
   
   // Store the last value of each counter
   countAnt[0] = counterG[0];
   countAnt[1] = counterG[1];
   countAnt[2] = counterG[2];
   countAnt[3] = counterG[3];
   
   // Compute the effective velocity command computed through PID controller
   PWM_val[0] = updatePid(PWM_val[0], speed_req[0], abs(speed_act[0]), 0);
   PWM_val[1] = updatePid(PWM_val[1], speed_req[1], abs(speed_act[1]), 1);                        //speed: 0-800
   PWM_val[2] = updatePid(PWM_val[2], speed_req[2], abs(speed_act[2]), 2);                        //RPM: 0-2 
   PWM_val[3] = updatePid(PWM_val[3], speed_req[3], abs(speed_act[3]), 3);
   
   analogWrite(motorPin0, PWM_val[0]);
   printMotorInfo(motorPin0, speed_act[0], PWM_val[0], 0);   
   analogWrite(motorPin1, PWM_val[1]);
   printMotorInfo(motorPin1, speed_act[1], PWM_val[1], 1);
   analogWrite(motorPin2, PWM_val[2]);
   printMotorInfo(motorPin2, speed_act[2], PWM_val[2], 2);
   analogWrite(motorPin3, PWM_val[3]);
   printMotorInfo(motorPin3, speed_act[3], PWM_val[3], 3);
   
  // After a call to analogWrite(),
  // the pin will generate a steady rectangular wave of the specified duty cycle until the next call to analogWrite()
  // (or a call to digitalRead() or digitalWrite()) on the same pin.
  }
}

void printMotorInfo(int motorPin, double speed_act, int PWM_val, int i)  {        // Display data
 if((millis() - lastMilliPrint[i]) >= 500) {                     
   lastMilliPrint[i] = millis();
   Serial.print("["); Serial.print((motorPin-1)); Serial.print("] ");
   Serial.print("speed: "); Serial.print(speed_req[i]);
   Serial.print(" RPM: "); Serial.print(speed_act); Serial.print("  PWM:"); Serial.print(PWM_val);Serial.println(">>");          
 }
}

int updatePid(int command, double targetValue, double currentValue, int k) {         // compute PWM value
  double pidTerm = 0.0;                                                             
  double error = 0.0;                                                               
  error = (double) (fabs(targetValue) - fabs(currentValue)); 
  pidTerm = (Kp * error) + (Kd * (error - last_error[k]));                            // PD correction                
  last_error[k] = error;
  return constrain(command + int(pidTerm), 0, 255);
}

// These function share a common counter which increase if the FIRST (in case of A0 and B0) wheel is rotating in clockwise direction
// and decrease if the wheel is rotating in an anticlockwise direction
void checkA0() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB0);
  stateA = digitalRead(encoderA0);
  if (stateA != stateB) {
    counterG[0]++;
  }
  else {
    counterG[0]--;
  }
}

void checkB0() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB0);
  stateA = digitalRead(encoderA0);
  if (stateA == stateB) {
    counterG[0]++;
  }
  else {
    counterG[0]--;
  }
}

void checkA1() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB1);
  stateA = digitalRead(encoderA1);
  if (stateA != stateB) {
    counterG[1]++;
  }
  else {
    counterG[1]--;
  }
}

void checkB1() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB1);
  stateA = digitalRead(encoderA1);
  if (stateA == stateB) {
    counterG[1]++;
  }
  else {
    counterG[1]--;
  }
}

void checkA2() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB2);
  stateA = digitalRead(encoderA2);
  if (stateA != stateB) {
    counterG[2]++;
  }
  else {
    counterG[2]--;
  }
}

void checkB2() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB2);
  stateA = digitalRead(encoderA2);
  if (stateA == stateB) {
    counterG[2]++;
  }
  else {
    counterG[2]--;
  }
}

void checkA3() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB3);
  stateA = digitalRead(encoderA3);
  if (stateA != stateB) {
    counterG[3]++;
  }
  else {
    counterG[3]--;
  }
}

void checkB3() {
  int stateA = 0;
  int stateB = 0;
  stateB = digitalRead(encoderB3);
  stateA = digitalRead(encoderA3);
  if (stateA == stateB) {
    counterG[3]++;
  }
  else {
    counterG[3]--;
  }
}
