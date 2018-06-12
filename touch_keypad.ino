#include <UTFT.h>
#include<UTouch.h>
int x,y;
extern uint8_t SmallFont[];

extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
UTFT myGLCD(CTE32HR,38,39,40,41);
UTouch myTouch(6,5,4,3,2);
void setup()
{Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  drawemergency();
  }
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
  {while((myTouch.dataAvailable()));
    a[counter]=9;
    counter++;
    }
    else if((x>=30) && (x<=80) && (y>=140) && (y<=180))
  {
    while((myTouch.dataAvailable()));
    a[counter]=6;
    counter++;
    }
     else if((x>=30) && (x<=80) && (y>=190) && (y<=230))
  {while((myTouch.dataAvailable()));
    a[counter]=3;
    counter++;
    }
     else if((x>=90) && (x<=140) && (y>=90) && (y<=130))
  {while((myTouch.dataAvailable()));
    a[counter]=8;
    counter++;
  }
 else if((x>=90) && (x<=140) && (y>=140) && (y<=180))
  {while((myTouch.dataAvailable()));
    a[counter]=5;
    counter++;
  }
   else if((x>=90) && (x<=140) && (y>=190) && (y<=230))
  {while((myTouch.dataAvailable()));
    a[counter]=2;
    counter++;
  }
 else if((x>=150) && (x<=200) && (y>=90) && (y<=130))
  {while((myTouch.dataAvailable()));
    a[counter]=7;
    counter++;
  }
  else if((x>=150) && (x<=200) && (y>=140) && (y<=180))
  {while((myTouch.dataAvailable()));
    a[counter]=4;
    counter++;
  }
  else if((x>=150) && (x<=200) && (y>=190) && (y<=230))
  {while((myTouch.dataAvailable()));
    a[counter]=1;
    counter++;
  }}
  if(counter==10){
  for(int p=0;p<10;p++)
  Serial.print(a[p]);
    Serial.println("");
    my.GLCD
    }}}
    void loop()
    {
      doemergency();
      
      }
