 #include <QTRSensors.h>
#define i1 3//left motorclockwise
#define i2 4//left anti
#define i3 5//right anti
#define i4 6//rightmotorclockwise
#define MIDDLE_SENSOR 3
#define NUM_SENSORS  8     // number of sensors used
#define TIMEOUT       4  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   8 
#define turnspeed 100
#define kp 0.01
#define kd 0.06
#define ki 0.0001
int M1= 220;
int M2= 220;
int motorspeed=0;
int lasterror;
int intergral=0;
int left_speed=0;
int right_speed=0;
unsigned int position=0;

QTRSensorsAnalog qtrrc((unsigned char[]) {0,1,2,3,4,5,6,7} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensors[NUM_SENSORS];
void manual_calibration() {

  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate();
    delay(20);
  }}
void setup() {
  // put your setup code here, to run once:
  pinMode(i1,OUTPUT);
    pinMode(i2,OUTPUT);
      pinMode(i3,OUTPUT);
        pinMode(i4,OUTPUT);   manual_calibration();
}void line_follow()
  {  
qtrrc.read(sensors);
position=qtrrc.readLine(sensors);
int  error=position-3500;
 position=qtrrc.readLine(sensors);
intergral+=error;
motorspeed=(kp*error)+(error-lasterror)*kd+intergral*ki;
lasterror=error;
 
 left_speed=M2-motorspeed;
 right_speed=M1+motorspeed;

if(left_speed<0)
{left_speed=0;
}

if(right_speed>255)
{
  right_speed=255;
 }
analogWrite(i1,left_speed);
analogWrite(i4,right_speed);}

void loop() {  
  qtrrc.read(sensors);
  while(1)
  {qtrrc.read(sensors);
 line_follow();
 if(sensors[3]<400&&sensors[4]<400&&sensors[0]<400&&sensors[7]<400)
 break;
 if(sensors[7]>700||sensors[0]>700)
 break;
 }
   position = qtrrc.readLine(sensors);
int  error = position - 3500;
if(error>20)
{analogWrite(i4,200);
analogWrite(i1,0);//turn left
}
if(error<(-20))
{
 analogWrite(i4,0);
analogWrite(i1,200);//turn right
}}

