#include<UTFT.h>
#include<UTouch.h>
#include<TinyGPS++.h>
#include<SoftwareSerial.h>
SoftwareSerial serial_connection(10,9);
TinyGPSPlus gps;
#include<Wire.h>
#include <APDS9960.h> //Download Code Library Below
#define APDS9960_INT    19 // Needs to be an interrupt pin
//APDS9960 apds = APDS9960();
int isr_flag = 0;
const int MPU_addr=0x68;
double AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; 
uint32_t timer; //it's a timer, saved as a big-ass unsigned int.  We use it to save times from the "micros()" command and subtract the present time in microseconds from the time stored in timer to calculate the time for each loop.
long compAngleX, compAngleY; //These are the angles in the complementary filter
#define degconvert 57.2957786
long accelX,accelY,accelZ;
float gForceX,gForceY,gForceZ;
//int minvalue=265;
//int maxvalue=402;
long gyroX,gyroY,gyroZ;
float rotX,rotY,rotZ;
int z;
UTFT myGLCD(CTE32HR,38,39,40,41);
UTouch myTouch(6,5,4,3,2); 
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
long k;
extern unsigned int bird01[0x41A];
extern unsigned int ABESEClogo[];
extern unsigned int leftarrow[];
extern unsigned int rightarrow[];
int x, y;
char currentPage, selectedUnit;
//Ultrasonic Sensor
//const int VCC1 = 13;
//const int VCC2 = 12;
//const int VCC3 = 11;
//const int VCC4 = 10;
const int trigPin1 = 8;
const int trigPin2 = 11;
const int trigPin3 = 12;
const int trigPin4 = 13;
const int echoPin1 = 15;
const int echoPin2 = 16;const int echoPin3 = 17;const int echoPin4 = 18;
long duration1;
int distanceInch1, distanceCm1;
long duration2;
int distanceInch2, distanceCm2;long duration3;
int distanceInch3, distanceCm3;long duration4;
int distanceInch4, distanceCm4;
// RGB LEDs
const int redLed = 10;
const int greenLed = 9;
const int blueLed = 8;
int xR=38;
int xG=38;
int xB=38;
// Floppy Bird
int xP = 319;
int yP = 100;
int yB = 30;
int fallRateInt = 0;
float fallRate =0;
int score=0;
const int button = 14;
int buttonState = 0;


void setup() {
// Initial setup
serial_connection.begin(9600);
 Serial.begin(115200);
 Wire.begin();
  // attachInterrupt(4, interruptRoutine, FALLING); 
   //Serial.println();
 // Serial.println("--------------------------------");
  //Serial.println("14CORE | GESTURE TEST W/D APDS-9960");
 // Serial.println("--------------------------------");
  
//  attachInterrupt(4, interruptRoutine, FALLING);   // Initialize interrupt service routine
  //if ( apds.init() ) { 
  
   //Serial.println("APDS-9960 initialization complete"); // Initialize APDS-9960 (configure I2C and initial values)
  //} else {
   // Serial.println("Error APDS Initialization");
 // }
  //if ( apds.enableGestureSensor(true) ) {
    //Serial.println("Gesture sensor is now running");
  //} else {
   // Serial.println("Error APDS Initialization");
//  }
 recordAccelinitial();
 //setmpuangle();
 // setupMPU();
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  // Defining Pin Modes
  //pinMode(VCC1, OUTPUT);//13
   //pinMode(VCC2, OUTPUT);// 10VCC
  //pinMode(VCC3, OUTPUT);
  //pinMode(VCC4, OUTPUT);
     pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
   pinMode(A8, INPUT);
   pinMode(A9, INPUT);
  pinMode(trigPin1, OUTPUT); //8 Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // 12Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); //8 Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);
   pinMode(trigPin3, OUTPUT); //8 Sets the trigPin as an Output
  pinMode(echoPin3, INPUT);
   pinMode(trigPin4, OUTPUT); //8 Sets the trigPin as an Output
  pinMode(echoPin4, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
 // pinMode(APDS9960_INT, INPUT); 
  //digitalWrite(VCC1, HIGH);
    //digitalWrite(VCC2, HIGH);
    //digitalWrite(VCC3, HIGH);
    //digitalWrite(VCC4, HIGH);// +5V - Pin 13 as VCC
  drawHomeScreen();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
  selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches
}
void interruptRoutine() {
  isr_flag = 1;
// handleGesture();
}
/*void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
      //  Serial.println("UP");
        break;
      case DIR_DOWN:
        //Serial.println("DOWN");
        break;
      case DIR_LEFT:
       //Serial.println("LEFT");
      digitalWrite(12,HIGH);
      myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
          delay(500);
           myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
          delay(500);
           myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
        //Serial.println("LEFT");
        //digitalWrite(8,HIGH);
      //delay(3000);
      digitalWrite(12,LOW);
        break;
      case DIR_RIGHT:

      
        //Serial.println("RIGHT");
    
      
        digitalWrite(13,HIGH);
       myGLCD.drawBitmap(410,250,30,23,rightarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(408,248,445,280);
          delay(500);
           myGLCD.drawBitmap(410,250,30,23,rightarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(410,248,445,280);
         delay(500);
           myGLCD.drawBitmap(410,250,30,23,rightarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(408,248,445,280);
      // delay(3000);
       digitalWrite(13,LOW);
        break;
      case DIR_NEAR:
      {delay(10);}//  Serial.println("NEAR");
        break;
      case DIR_FAR:
      {delay(10);}  //Serial.println("FAR");
        break;
      default:
        {delay(10);}//Serial.println("NONE");
    }
  }
}*/
void gpsspeedometer()
{
  {if(serial_connection.available())
{
  gps.encode(serial_connection.read());}
  if(gps.location.isUpdated())
  {Serial.println(gps.speed.kmph());
    }
    int q;
    q=gps.speed.kmph();
     myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(q,CENTER, 250, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("km/h ",300, 250);  //Serial.println(c);         // print the character
  //return c;
    
  }
}
void speedometer()
{
   Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

  if (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(c,CENTER, 250, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("km/h ",300, 250);  //Serial.println(c);         // print the character
  //return c;
  }

  delay(500);
  }

  
  void setmpuangle()
  { {
  // Set up MPU 6050:
 // Wire.begin();
  #if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
  #else
    TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
  #endif

  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
 // Serial.begin(115200);
  delay(100);

  //setup starting angle
  //1) collect the data
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //2) calculate pitch and roll
  double roll = atan2(AcY, AcZ)*degconvert;
  double pitch = atan2(-AcX, AcZ)*degconvert;

  //3) set the starting angle to this pitch and roll
  double gyroXangle = roll;
  double gyroYangle = pitch;
  double compAngleX = roll;
  double compAngleY = pitch;

  //start a timer
  timer = micros();
}

    }
    void anglecalculate()
    {
      {
//Now begins the main loop. 
  //Collect raw data from the sensor.
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  double dt = (double)(micros() - timer) / 1000000; //This line does three things: 1) stops the timer, 2)converts the timer's output to seconds from microseconds, 3)casts the value as a double saved to "dt".
  timer = micros(); //start the timer again so that we can calculate the next dt.

  //the next two lines calculate the orientation of the accelerometer relative to the earth and convert the output of atan2 from radians to degrees
  //We will use this data to correct any cumulative errors in the orientation that the gyroscope develops.
  double roll = atan2(AcY, AcZ)*degconvert;
  double pitch = atan2(-AcX, AcZ)*degconvert;

  //The gyroscope outputs angular velocities.  To convert these velocities from the raw data to deg/second, divide by 131.  
  //Notice, we're dividing by a double "131.0" instead of the int 131.
  double gyroXrate = GyX/131.0;
  double gyroYrate = GyY/131.0;

  //THE COMPLEMENTARY FILTER
  //This filter calculates the angle based MOSTLY on integrating the angular velocity to an angular displacement.
  //dt, recall, is the time between gathering data from the MPU6050.  We'll pretend that the 
  //angular velocity has remained constant over the time dt, and multiply angular velocity by 
  //time to get displacement.
  //The filter then adds a small correcting factor from the accelerometer ("roll" or "pitch"), so the gyroscope knows which way is down. 
  compAngleX = 0.99 * (compAngleX + gyroXrate * dt) + 0.01 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.99 * (compAngleY + gyroYrate * dt) + 0.01 * pitch; 

   myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(compAngleX,CENTER, 80, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("0",300, 80);
  //W00T print dat shit out, yo!
  Serial.print(compAngleX);Serial.print("\t");
  //delay(50);
  //Serial.print(compAngleY);Serial.print("\n");
//delay(50);
}}
void setupMPU()
{Wire.beginTransmission(0b1101000);
Wire.write(0x6B);
Wire.write(0b00000000);
Wire.endTransmission();
Wire.beginTransmission(0b1101000);
Wire.write(0x1B);
Wire.write(0x00000000);
Wire.endTransmission();
Wire.beginTransmission(0b1101000);
Wire.write(0x1C);
Wire.write(0b00000000);
Wire.endTransmission();
  
  }
   void recordAccelinitial()
{
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
while(Wire.available()<6);
accelX=Wire.read()<<8|Wire.read();
accelY=Wire.read()<<8|Wire.read();
accelZ=Wire.read()<<8|Wire.read();
Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
while(Wire.available()<6);
gyroX=Wire.read()<<8|Wire.read();
gyroY=Wire.read()<<8|Wire.read();
gyroZ=Wire.read()<<8|Wire.read();
//int xang=map(accelX,minvalue,maxvalue,-90,90)
//int x=RAD_TO_DEG*(atan2)
// double dt = (double)(micros() - timer) / 1000000; //This line does three things: 1) stops the timer, 2)converts the timer's output to seconds from microseconds, 3)casts the value as a double saved to "dt".
  //timer = micros(); 
double roll = atan2(accelY, accelZ)*degconvert;
  double pitch = atan2(-accelX, accelZ)*degconvert;
  //double gyroXrate = GyroX/131.0;
  //double gyroYrate = GyroY/131.0;
  //compAngleX = 0.99 * (compAngleX + gyroXrate * dt) + 0.01 * roll; // Calculate the angle using a Complimentary filter
  //compAngleY = 0.99 * (compAngleY + gyroYrate * dt) + 0.01 * pitch; 
  double gyroXangle = roll;
  double gyroYangle = pitch;
  double compAngleX = roll;
  double compAngleY = pitch;
  timer = micros();

//processAccelData();
  }
  long recordAccelRegisters()
{
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
while(Wire.available()<6);
accelX=Wire.read()<<8|Wire.read();
accelY=Wire.read()<<8|Wire.read();
accelZ=Wire.read()<<8|Wire.read();
Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
while(Wire.available()<6);
gyroX=Wire.read()<<8|Wire.read();
gyroY=Wire.read()<<8|Wire.read();
gyroZ=Wire.read()<<8|Wire.read();
//int xang=map(accelX,minvalue,maxvalue,-90,90)
//int x=RAD_TO_DEG*(atan2)
 double dt = (double)(micros() - timer) / 1000000; //This line does three things: 1) stops the timer, 2)converts the timer's output to seconds from microseconds, 3)casts the value as a double saved to "dt".
  timer = micros(); 
double roll = atan2(accelY, accelZ)*degconvert;
  double pitch = atan2(-accelX, accelZ)*degconvert;
  double gyroXrate = gyroX/131.0;
  double gyroYrate = gyroY/131.0;
  compAngleX = 0.99 * (compAngleX + gyroXrate * dt) + 0.01 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.99 * (compAngleY + gyroYrate * dt) + 0.01 * pitch; 
  return compAngleX;

//processAccelData();
  }
  
 void processAccelData()
 {
  gForceX=accelX/16384.0;
  gForceY=accelY/16384.0;
  gForceZ=accelZ/16384.0;
  
  }
  void recordGyroRegisters()
  { Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
while(Wire.available()<6);
gyroX=Wire.read()<<8|Wire.read();
gyroY=Wire.read()<<8|Wire.read();
gyroZ=Wire.read()<<8|Wire.read();
processGyroData();
    
    }
    void processGyroData()
    {
      rotX=gyroX/131.0;
      rotY=gyroY/131.0;
      rotZ=gyroZ/131.0;
      }

      void printorientation()
      { //processGyroData();
         myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(k,CENTER, 80, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("x",300, 80);
        
        }

void drawHomeScreen()
{myGLCD.setBackColor(0,0,0 ); //setting background color to black
//myGLCD.setColor(255,255,255);//Setting color for font//white colour 
//myGLCD.setFont(BigFont);//setting font size 
//myGLCD.print("ABES Engineering College,GZB",CENTER,10);//print font in center of the screen and 10 pixels down y-axis
//myGLCD.setColor(255,0,0);//set color to red,as only red required R is set to 255 and G ,B are set to zero
//myGLCD.drawLine(0,32,480,32);//line in red color on 32 pixels down on y-axis and covering complete X-axis of 480 pixels. 
myGLCD.setColor(255,255,255);//font color back to white
myGLCD.setFont(BigFont);
myGLCD.print("TEAM PROTAGONISTS",CENTER,15);//print font in center of the screen and 41 pixels down y-axis
//myGLCD.setFont(BigFont);
//myGLCD.print("choose option",CENTER,64);//print font in center of the screen and 64 pixels down y-axis
myGLCD.drawBitmap(0,0,60,84,ABESEClogo);
myGLCD.drawBitmap(420,0,60,84,ABESEClogo);



//BUTTON- DISTANCE SENSOR
  myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,90,225,130);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,90,225,130);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("Distance ",40,102);

 //button RGB led controlss
 //same procedure for these two buttons
  myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(255,90,450,130);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(255,90,450,130);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("RGB LED",270,102);

//button for game
  myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,140,225,180);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,140,225,180);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("Birduino",55,152);

//orientation data
   myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(255,140,450,180);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(255,140,450,180);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("Orientation",270,152);


  //Emergency
   myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(255,190,450,230);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(255,190,450,230);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("Emergency",270,202);


  //Vehicle details
  myGLCD.setColor(16,167,103);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,190,225,230);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,190,225,230);//outlining above created rectangle with white color
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("Vehicle details",55,202);
  }
  //draw frame function
  void drawFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
}
//====================================================
void drawemergency()
{myGLCD.setBackColor(0,0,0 );
 myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (20, 20, 80, 66);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (20, 20, 80, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 38, 35);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Edit number", 100, 38);
  myGLCD.setFont(BigFont);
//print 9
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,90,80,130);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,90,80,130);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("9",53,100);

  // print 8
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(90,90,140,130);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(90,90,140,130);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("8",110,100);
// print 7
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(150,90,200,130);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(150,90,200,130);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("7",168,100);

  //print 6
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,140,80,180);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,140,80,180);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("6",53,150);

  //print 5
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(90,140,140,180);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(90,140,140,180);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("5",113,150);

 //print 4
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(150,140,200,180);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(150,140,200,180);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("4",168,150);

    //print 3
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(30,190,80,230);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(30,190,80,230);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("3",53,200);

   //print 2
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(90,190,140,230);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(90,190,140,230);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("6",110,200);

   //print 1
   myGLCD.setColor(255,0,0);//this combination of RGB will give like leaf Green Color
  myGLCD.fillRoundRect(150,190,200,230);//setting dimension of rectangle for filling the above set color
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(150,190,200,230);//outlining above created rectangle with white color
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16,167,103);
  myGLCD.print("1",168,200);
  }

  void doemergency()
  {int counter=0;
  int a[10];
  while(counter!=10)
  { if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
  if((x>=30) && (x<=80) && (y>=90) && (y<=130))
  {
    a[counter]=9;
    counter++;
    }
     if((x>=30) && (x<=80) && (y>=140) && (y<=180))
  {
    a[counter]=6;
    counter++;
    }
     if((x>=30) && (x<=80) && (y>=190) && (y<=230))
  {
    a[counter]=3;
    counter++;
    }
     if((x>=90) && (x<=140) && (y>=90) && (y<=130))
  {
    a[counter]=8;
    counter++;
  }
     if((x>=90) && (x<=140) && (y>=140) && (y<=180))
  {
    a[counter]=5;
    counter++;
  }
   if((x>=90) && (x<=140) && (y>=190) && (y<=230))
  {
    a[counter]=2;
    counter++;
  }
  if((x>=150) && (x<=200) && (y>=90) && (y<=130))
  {
    a[counter]=7;
    counter++;
  }
  if((x>=150) && (x<=200) && (y>=140) && (y<=180))
  {
    a[counter]=4;
    counter++;
  }
   if((x>=150) && (x<=200) && (y>=190) && (y<=230))
  {
    a[counter]=1;
    counter++;
  }}
  for(int p=0;p<10;p++)
  Serial.print(a[p]);
    
    }}
void drawDistanceSensor() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (20, 20, 80, 66);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (20, 20, 80, 66);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 38, 35);
  //myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 100, 38);
  //myGLCD.setFont(BigFont);
  //myGLCD.print("Ultrasonic Sensor", CENTER, 70);
  //myGLCD.print("HC-SR04", CENTER, 96);
  //myGLCD.setColor(0, 255, 0);
  //myGLCD.drawLine(20,120,460,120);
  //myGLCD.setBackColor(0, 0, 0);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.setFont(SmallFont);
  //myGLCD.print("Select Unit", 10, 134);
  //myGLCD.setFont(BigFont);
  //myGLCD.print("Distance:", 130, 150);
  //myGLCD.setColor(223, 77, 55);
  //myGLCD.fillRoundRect (10, 155, 90, 183);
  //myGLCD.setColor(225, 255, 255);
  //myGLCD.drawRoundRect (10, 155, 90, 183);
  //myGLCD.setBackColor(223, 77, 55);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.print("cm", 33, 160);
  //myGLCD.setColor(223, 77, 55);
  //myGLCD.fillRoundRect (10, 193, 90, 221);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.drawRoundRect (10, 193, 90, 221);
  //myGLCD.setBackColor(223, 77, 55);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.print("inch", 17, 200);
  //myGLCD.setBackColor(0, 0, 0);
  //myGLCD.setFont(SmallFont);
  //myGLCD.print("by innovation department", CENTER, 240);  
}

void drawbatteryindicator()
{
   myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (20, 20, 80, 66);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (20, 20, 80, 66);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 38, 35);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 100, 38);
  myGLCD.print("Gyro", CENTER, 50);
   myGLCD.print("Acceloremeter", CENTER, 200);
  
  
  
  
  
  }


  void getspeed() {
  // Clears the trigPin
 // digitalWrite(trigPin1, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  //digitalWrite(trigPin1, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  //distanceCm1= duration1*0.034/2;
  //distanceInch1= distanceCm1/2.53;
  // Prints the distance in centimeters
  //if (selectedUnit == '0' && distanceCm1 <=400) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(z,CENTER, 250, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("km/h ",300, 250);
    
  
  }
  
 void getDistance()
 {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distanceCm1= duration1*0.034/2;
  distanceInch1= distanceCm1/2.53;
  
   //
   digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distanceCm2= duration2*0.034/2;
  distanceInch2= distanceCm2/2.53;
  
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calcuating the distance
  distanceCm3= duration3*0.034/2;
  distanceInch3= distanceCm3/2.53;
  
  // Prints the distance in centimeters
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration4 = pulseIn(echoPin4, HIGH);
  // Calculating the distance
  distanceCm4= duration4*0.034/2;
  distanceInch4= distanceCm4/2.53;
  
  if ( distanceCm1 <=300) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm1,100, 250, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ",215, 250);
  }else{
   // myGLCD.setBackColor()
     
     myGLCD.setBackColor(0,0,0);
 myGLCD.fillRoundRect(100,250,150,300); 
  myGLCD.setFont(BigFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("CLEAR",100, 250);
  }
    if ( distanceCm2 <=300)
    {myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm2,290, 250, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ",395, 250);
    }else{
       myGLCD.setBackColor(0,0,0);
 myGLCD.fillRoundRect(280,240,340,300); 
  myGLCD.setFont(BigFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("CLEAR",290, 250);
  }
     if ( distanceCm3 <=300)
     {myGLCD.setFont(SevenSegNumFont);
     myGLCD.setColor(0, 0, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm3,290, 120, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ",395, 120);
     }
      else{
        myGLCD.setBackColor(0,0,0);
 myGLCD.fillRoundRect(280,110,340,170); 
  myGLCD.setFont(BigFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("CLEAR",290, 120);
  }if ( distanceCm4 <=300)
    {myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(255, 0, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm4,100, 120, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ",215, 120);
    }

  else{ myGLCD.setBackColor(0,0,0);
 myGLCD.fillRoundRect(280,110,340,170);
  myGLCD.setFont(BigFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("CLEAR",100, 120);}
  }
 /* // Prints the distance in inches
  if (selectedUnit == '1' && distanceCm1 <=360) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceInch,130, 175, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("inch", 235, 178);
  }*/ 
  //delay(10);


void drawLedControl() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (20, 20, 80, 66);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (20, 20, 80, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 38, 35);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 100, 38);
  myGLCD.setFont(BigFont);
  myGLCD.print("RGB LED Control", CENTER, 70);
  myGLCD.print("LED Color:", 10, 105);
  myGLCD.print("R", 10, 155);
  myGLCD.print("G", 10, 195);
  myGLCD.print("B", 10, 235);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0,95,480,95); 
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(30, 138, 420, 148); // R - Slider
  myGLCD.drawRect(30, 178, 420, 188);
  myGLCD.drawRect(30, 218, 420, 228);  
}
void setLedColor() {
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();        
    // Area of the Red color slider
    if( (y>=130) && (y<=156)) {
      xR=x; // Stores the X value where the screen has been pressed in to variable xR
      if (xR<=38) { // Confines the area of the slider to be above 38 pixels
        xR=38;
      }
      if (xR>=303){ /// Confines the area of the slider to be under 310 pixels
        xR=303;
      }
    }
    // Area of the Green color slider
    if( (y>=170) && (y<=196)) {
      xG=x;
      if (xG<=38) {
        xG=38;
      }
      if (xG>=303){
        xG=303;
      }
    }
    // Area of the Blue color slider
    if( (y>=210) && (y<=236)) {
      xB=x;
      if (xB<=38) {
        xB=38;
      }
      if (xB>=303){
        xB=303;
      }
    }    
  }
  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
  int xRC = map(xR,38,310,0,255);
  int xGC = map(xG,38,310,0,255);
  int xBC = map(xB,38,310,0,255);
  
  // Sends PWM signal to the pins of the led
  analogWrite(redLed, xRC);
  analogWrite(greenLed, xGC);
  analogWrite(blueLed, xBC);
  
  // Draws a rectangle with the latest color combination 
  myGLCD.setColor(xRC, xGC, xBC);
  myGLCD.fillRoundRect(175, 87, 310, 119);
  
  // Draws the positioners
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xR,139,(xR+4),147); // Positioner
  myGLCD.setColor(xRC, 0, 0);
  myGLCD.fillRect(31, 139, (xR-1), 147);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xR+5), 139, 309, 147);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xG,179,(xG+4),187);
  myGLCD.setColor(0, xGC, 0);
  myGLCD.fillRect(31, 179, (xG-1), 187);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xG+5), 179, 309, 187);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xB,219,(xB+4),227);
  myGLCD.setColor(0, 0, xBC);
  myGLCD.fillRect(31, 219, (xB-1), 227);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xB+5), 219, 309, 227);
}
//====================================================
void drawGround() {
  myGLCD.setColor(221,216,148);
  myGLCD.fillRect(0, 215, 319, 239);
  myGLCD.setColor(47,175,68);
  myGLCD.fillRect(0, 205, 319, 214);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.print("Score:",5,250);
  myGLCD.setFont(SmallFont);
  myGLCD.print("innovation department", 140, 250); 
}
void drawPilars(int x, int y) {
   
    if (x>=270){
      myGLCD.setColor(0, 200, 20);
      myGLCD.fillRect(318, 0, x, y-1);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawRect(319, 0, x-1, y);
      myGLCD.setColor(0, 200, 20);
      myGLCD.fillRect(318, y+81, x, 203);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawRect(319, y+80, x-1, 204); 
    }
    else if( x<=268) {
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x+51, 0, x+53, y);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x+49, 1, x+1, y-1);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x+50, 0, x, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x-1, 0, x-3, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x+51, y+80, x+53, 204);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x+49, y+81, x+1, 203);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x+50, y+80, x, 204);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x-1, y+80, x-3, 204);
  }
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(score, 100, 220);
}
void drawBird(int y) {
  if(y<=219) {
    myGLCD.drawBitmap (50, y, 35, 30, bird01);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRoundRect(50,y,85,y-6);
    myGLCD.fillRoundRect(50,y+30,85,y+36);
  }
  else if(y>=200) {
    myGLCD.drawBitmap (50, 200, 35, 30, bird01);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRoundRect(50,200,85,200-6);
    myGLCD.fillRoundRect(50,200+30,85,200+36);
  }
}
void gameOver() {
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("GAME OVER", CENTER, 40);
  myGLCD.print("Score:", 100, 80);
  myGLCD.printNumI(score,200, 80);
  myGLCD.print("Restarting...", CENTER, 120);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(2,CENTER, 150);
  delay(1000);
  myGLCD.printNumI(1,CENTER, 150);
  delay(1000);
  myGLCD.setColor(114, 198, 206);
  myGLCD.fillRect(0,0,319,239);
  drawBird(30);
  drawGround();
  delay(1000);
}
//====================================================
void restartGame() {
  delay(1000);
  gameOver();
  xP=319;
  yB=30;
  fallRate=0;
  score=0;
}
//========== The loop section ========
void loop() { 

  // if( isr_flag == 1 ) {
    //detachInterrupt(4);
//    handleGesture();
    //isr_flag = 0;
    //attachInterrupt(4, interruptRoutine, FALLING);
 // }
   setupMPU();
  recordAccelRegisters();
  //recordGyroRegisters();
// z= speedometer();
 // Serial.println(z);
  // Home Screen
  if (currentPage == '0'){
    gpsspeedometer();//home screen address 0
 // {if( isr_flag == 1 ) {
   // detachInterrupt(4);
//    handleGesture();
    //isr_flag = 0;
   // attachInterrupt(4, interruptRoutine, FALLING);
  //}
     //speedometer();
   // getspeed();
   // myGLCD.drawBitmap(0,0,60,84,ABESEC_logo);
    if (myTouch.dataAvailable())//if we touch this statement gets true
    {
      myTouch.read();//read touch data
      x=myTouch.getX(); // X coordinate where the screen has been pressed
      y=myTouch.getY(); // Y coordinates where the screen has been pressed
      // If we press the Distance Sensor Button 
      if ((x>=30) && (x<=225) && (y>=90) && (y<=130))//coordinates of distance sensor rectangle box
      {
        drawFrame(30, 90, 225, 130); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        drawDistanceSensor(); // It is called only once, because in the next iteration of the loop, this above if statement will be false so this funtion won't be called. This function will draw the graphics of the first example.
      }
      // If we press the RGB LED Control Button 
      if ((x>=255) && (x<=450) && (y>=90) && (y<=130)) {
        drawFrame(255, 90, 450, 130);
        currentPage = '2';
        myGLCD.clrScr();
        drawLedControl();
      }  

      // If we press the orientation Control Button 
      if ((x>=255) && (x<=450) && (y>=140) && (y<=180)) {
        drawFrame(255, 140, 450, 180);
        currentPage = '4';
        myGLCD.clrScr();
        drawbatteryindicator();
      }  
      // If we press the Birduino Game Button
      if ((x>=30) && (x<=225) && (y>=140) && (y<=180)) {
        drawFrame(30, 140, 225, 180);
        currentPage = '3';
        myGLCD.clrScr();
        myGLCD.setColor(114, 198, 206);
        myGLCD.fillRect(0,0,319,239);
        drawGround();
        drawPilars(xP,yP);
        drawBird(30);
        delay(1000);
      }

      if((x>=30) && (x<=225) && (y>=190) && (y<=230))
      {
         myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
          delay(500);
           myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
          delay(500);
           myGLCD.drawBitmap(40,250,30,22,leftarrow);
         delay(500);
         myGLCD.setColor(0,0,0);
          myGLCD.fillRoundRect(38,248,80,280);
        }

//emergency button
     if((x>=255) && (x<=450) && (y>=190) && (y<=230))
      {
         //myGLCD.drawBitmap(410,250,30,23,rightarrow);
         //delay(500);****//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
         //myGLCD.setColor(0,0,0);
         // myGLCD.fillRoundRect(408,248,445,280);
         // delay(500);
          // myGLCD.drawBitmap(410,250,30,23,rightarrow);
         //delay(500);
         //myGLCD.setColor(0,0,0);
         // myGLCD.fillRoundRect(410,248,445,280);
         // delay(500);
          // myGLCD.drawBitmap(410,250,30,23,rightarrow);
         //delay(500);
         //myGLCD.setColor(0,0,0);
         // myGLCD.fillRoundRect(408,248,445,280);
         drawFrame(255,190,450,230);
         currentPage='5';
         myGLCD.clrScr();
         drawemergency();
         doemergency();
        }
    }
  }
  // Distance Sensor Example
  if (currentPage == '1') {    
      getDistance(); // Gets distance from the sensor and this function is repeatedly called while we are at the first example in order to print the lasest results from the distance sensor
      if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
       
        // If we press the Centimeters Button
        if ((x>=10) && (x<=135) &&(y>=90) && (y<=163)) {
          selectedUnit = '0';
        }
        // If we press the Inches Button
        if ((x>=10) && (x<=135) &&(y>=173) && (y<=201)) {
          selectedUnit = '1';
        }
        // If we press the Back Button
        if ((x>=20) && (x<=80) &&(y>=20) && (y<=66)) {
          drawFrame(20, 20, 80, 66);
          currentPage = '0'; // Indicates we are at home screen
          myGLCD.clrScr();
          drawHomeScreen(); // Draws the home screen
        }
      }
  }
  
  // RGB LED Control 
  if (currentPage == '2') {
    setLedColor();
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        
        //Back button
        if ((x>=20) && (x<=80) &&(y>=20) && (y<=66)) {
          drawFrame(20, 20, 80, 66);
          currentPage = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          // Turns the LED off
          analogWrite(redLed, 0);
          analogWrite(greenLed, 0);
          analogWrite(blueLed, 0);
        }
    }
  }
//==== This section of the code, for the game example, is explained in my next tutorial
  // Birduino Game
if (currentPage=='4')
{setupMPU(); 
 k=2*recordAccelRegisters();
  //recordGyroRegisters();
  printorientation();
 // setmpuangle();
  //anglecalculate();
  
  }

  
  if (currentPage == '3') {
    //delay(1);
    xP=xP-3;
    drawPilars(xP, yP);
    
    yB+=fallRateInt;
    fallRate=fallRate+0.4;
    fallRateInt= int(fallRate);
    if (yB>=220) {
      yB=220;
    }
    if(yB>=180 || yB<=0){
      restartGame();
    }
    if((xP<=85) && (xP>=30) && (yB<=yP-2)){
      restartGame();
    }
    if((xP<=85) && (xP>=30) && (yB>=yP+60)){
      restartGame();
    }
    drawBird(yB);
    
    if (xP<=-51){
      xP=319;
      yP = rand() % 100+20;
      score++;
    }
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        if ((x>=0) && (x<=319) &&(y>=50) && (y<=239)) {
          fallRate=-5;
        }
    }
    buttonState = digitalRead(button);
    if (buttonState == HIGH) {
      fallRate=-5;
      }
  }
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        if ((x>=20) && (x<=80) &&(y>=20) && (y<=66)) {
          drawFrame(20, 20, 80, 66);
          currentPage = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          analogWrite(redLed, 0);
          analogWrite(greenLed, 0);
          analogWrite(blueLed, 0);
        }
    }
}
