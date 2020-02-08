#define motorPin0 2 //PWM ant-dx*
#define motorPin1 3 //PWM ant-sn*
#define motorPin2 4 //PWM post-dx*
#define motorPin3 5 //PWM post-dx*
#define enA0 24     //pinA motor ant-dx*
#define enB0 25     //pinB motor ant-dx*
#define enA1 28     //pinA motor ant-sn*
#define enB1 29     //pinB motor ant-sn*
#define enA2 32     //pinA motor post-dx*
#define enB2 33     //pinB motor post-dx*
#define enA3 36     //pinA motor post-sn*
#define enB3 37     //pinB motor post-sn*

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  //set PWM Pin 
  pinMode(motorPin0, OUTPUT);   //PWM ant-dx*
  pinMode(motorPin1, OUTPUT);   //PWM ant-sn*
  pinMode(motorPin2, OUTPUT);   //PWM post-dx*
  pinMode(motorPin3, OUTPUT);   //PWN post-sn*

  //define motor 1: ANT-DX*
  pinMode(enA0, OUTPUT);
  pinMode(enB0, OUTPUT);
  
  //define motor 1: ANT-SN*
  pinMode(enA1, OUTPUT);
  pinMode(enB1, OUTPUT);

  //define motor 1: POST-DX*
  pinMode(enA2, OUTPUT);
  pinMode(enB2, OUTPUT);

  //define motor 1: POST-DX*
  pinMode(enA3, OUTPUT);
  pinMode(enB3, OUTPUT);

  //After a call to analogWrite(), 
  //the pin will generate a steady rectangular wave of the specified duty cycle until the next call to analogWrite()
  //(or a call to digitalRead() or digitalWrite()) on the same pin.
}


  //function to control motor
  //speed is how fast the motor rotates
  //set motorPin, enA and enB for the motor we want to drive
  void control_motor(int speed, int motorPin, int enA, int enB){
      if(speed > 0){
          analogWrite(motorPin, speed);
          digitalWrite(enA, HIGH);
          digitalWrite(enB, LOW);
      }
      else if(speed < 0){
          analogWrite(motorPin, -speed);
          digitalWrite(enA, LOW);
          digitalWrite(enB, HIGH);
      }
      else{
          digitalWrite(enA, LOW);
          digitalWrite(enB, LOW);
      }
  }

  //In time loop, receive from serial and control 4 motors
  void loop() {
    static int speed[4];
    static char buff[30];
    int counter = 0;

    // read command from raspberry pi
    while(Serial.available()){
        buff[counter] = Serial.read();
        if (counter > 30 || buff[counter] == '*') {
            buff[counter] = '\0';
            speed[0]=atoi(strtok(buff,",")); //read cmd for ANT-DX
            speed[1]=atoi(strtok(NULL,",")); //read cmd for ANT-SN
            speed[2]=atoi(strtok(NULL,",")); //read cmd for POST-DX
            speed[3]=atoi(strtok(NULL,",")); //read cmd for POST-SN
        }
        else{
            counter++;
        }
    }

    // control motors
    control_motor(speed[0], motorPin0, enA0, enB0);
    control_motor(speed[1], motorPin1, enA1, enB1);
    control_motor(speed[2], motorPin2, enA2, enB2);
    control_motor(speed[3], motorPin3, enA3, enB3);

    // send messages to raspberry pi
    Serial.print(speed[0]); Serial.print(",");
    Serial.print(speed[1]); Serial.print(",");
    Serial.print(speed[2]); Serial.print(",");
    Serial.print(speed[3]); Serial.print(",");

    delay(100);
}
