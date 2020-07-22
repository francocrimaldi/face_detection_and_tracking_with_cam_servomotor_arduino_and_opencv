#include <Servo.h> 

#define     baudrate                  9600    
#define     servopinx                 9
//posizione iniziale del servomotore    
#define     servocenterx              90
//spostamento servomotore asse X
#define     distancex                 1

int data;
int LSB;
int MSB;

//posizione del servomotore
int pos = 0;  
     
Servo myservo; 

void setup() 
{
	Serial.begin(baudrate);
	
	myservo.attach(servopinx);
	myservo.write(servocenterx); 
}

void loop() 
{
	//wait data to serial
	while(Serial.available() <= 0); // attesa dei dati d'ingresso dalla seriale

  	//2 byte from serial
  	if(Serial.available() >= 2)  
    	{
      		LSB = Serial.read();  
      
      		MSB = Serial.read();
      
      		//central point of face
		data = word(MSB, LSB);
		
		pos = myservo.read();
      
      		if(data >= 160)
      		{
        		pos += distancex;
      		}
      		else if(data < 160)
      		{
        		pos -= distancex;
      		}
      
      		if(pos <= 0)
      		{
        		pos = 0;
      		}
      		else if(pos >= 170)
      		{
        		pos = 170;
      		}
      
      		myservo.write(pos);
      		
		Serial.println("Position of servomotor is: ");
      		Serial.println(pos); 
	}
}
