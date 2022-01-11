//Autoren: Loic and Morel
//Standard-Include-Files
#include <stdio.h>
#include <regc515c.h>
#include <stdint.h>
#include "bool.h"

 //Diese Include-Datei macht alle Funktionen der
 //AkSen-Bibliothek bekannt.
 //Unbedingt einbinden!
 #include <stub.h>
 #define FA1
 #include"fa.h"

 //refreshing and output string on display
 void outputString(char* string);
 void start();
 void followLine();
 void weg();
 void geradeaus();
 void turnRight();
 void turnLeft();
 void abliefern();

//Hauptprogram Routine
#define wert1 100
#define wert2 100
#define wertlicht1 30
#define wertlicht2 30
#define slepi 150
#define optoSensorRechts 0
#define optoSensorLinks 7
#define motorRechts 1
#define motorLinks 2
#define motorVorwaerts 0
#define motorRueckwaerts 1
#define standardSpeed 10

char Muster2D[10][7];
char x, y, xs = 0, ys = 0, k;
char hweg[20];
char rweg[] = "HHHHHHHH";
char i = 0;
char Muster1D[] =
"xFxxxFxx.x.x.xF..x..Fxx.x.xxx..x..xx.x.x.xF..x..Fxx.x.xxx..x..xx.x.x.x";
char richtung[] = "SWNOSW";
char Muster2D[10][7];
char count = 0;

void outputString(char* string) {
	lcd_cls();
	lcd_puts(string);
	
}

 void start() {
 motor_richtung(1, 0);
 motor_richtung(2, 0);
 while ((analog(optoSensorRechts) > wertlicht1 &&
		analog(optoSensorLinks) > wertlicht1)) {
	}
 followLine();

}

 void rechts() {
  motor_richtung(motorRechts, 0);
  motor_richtung(motorLinks, 0);
  motor_pwm(motorRechts, 0);
  motor_pwm(motorLinks, standardSpeed);
  sleep(1000);
  while (analog(optoSensorLinks) < wert2);
  motor_pwm(1, 0);
  followLine();
  }


	 void geradeaus() {
	  motor_pwm(1, 8);
	  motor_pwm(3, 8);
	  sleep(700);
	  motor_pwm(1, 0);
	  motor_pwm(3, 0);
	  followLine();
	 
 }
	  void turnLeft() {
	  motor_richtung(motorRechts, 0);
	  motor_richtung(motorLinks, 0);
	  motor_pwm(motorRechts, standardSpeed);
	  motor_pwm(motorLinks, 0);
	  sleep(1000);
	  while (analog(optoSensorRechts) < wert1);
	  motor_pwm(motorRechts, 0);
	  followLine();
	 
 }
 void umdrehen() {
	 motor_richtung(motorRechts, 0);
	 motor_richtung(motorLinks, 0);
	 motor_pwm(motorRechts, 0);
	 motor_pwm(motorLinks, standardSpeed);
	 weg();
	 sleep(1000);
	 while (analog(optoSensorLinks) < wert2);
	 motor_pwm(motorLinks, 0);
	 count++;
	 followLine();
	
}


 void abliefern() {
	followLine();
	motor_pwm(motorRechts, 0);
	motor_pwm(motorLinks, 0);
	motor_richtung(2, 1);
	motor_pwm(2, 3);
	umdrehen();
	sleep(900);
	motor_richtung(motorRechts, 1);
	motor_richtung(motorLinks, 1);
	motor_pwm(motorRechts, standardSpeed);
	motor_pwm(motorLinks, standardSpeed);
	sleep(200);
	motor_pwm(motorRechts, 0);
	motor_pwm(motorLinks, 0);
	motor_richtung(2, 0);
	motor_pwm(2, 3);
	turnRight();
	
}

 void weg() {
	 for (x = 0; x <= 10; x++)
	 {
		 for (y = 0; y < 7; y++)
			 {
			 if (Muster1D[i] == ’x’)
				 Muster2D[x][y] = 70;
			else if (Muster1D[i] == ’.’)
				 Muster2D[x][y] = 71;
			 else if (Muster1D[i] == ’F’)
				 Muster2D[x][y] = 72;
			 else if (Muster1D[i] == ’#’)
				 Muster2D[x][y] = 73;
			 i++;
			 }
		}
	if (dif() == 1)
		 Muster2D[9][1] = 1;
	else
		 Muster2D[9][5] = 1;
	for (i = 0; i < 70; i++)
		 {
		 for (x = 1; x < 10; x++)
			{
			for (y = 1; y < 6; y++)
				 {
				 if (Muster2D[x][y] == 71)
					 {
					 if (Muster2D[x + 1][y] == i)
						 Muster2D[x][y] = i + 1;
					else if (Muster2D[x][y + 1] == i)
						 Muster2D[x][y] = i + 1;
					else if (Muster2D[x - 1][y] == i)
						 Muster2D[x][y] = i + 1;
					else if (Muster2D[x][y - 1] == i)
						 Muster2D[x][y] = i + 1;
					}
				}
			}
		
			 }
	 k = 0;
	 //Nachbar
		 for (x = 1; x < 9; x++)
		 {
		 for (y = 1; y < 6; y++)
			 {
			 if (Muster2D[x][y] < i && Muster2D[x][y] > 0)
				 {
				 if (Muster2D[x + 1][y] == 72)
					 {
					 xs = x; ys = y; i = Muster2D[x][y];
					 hweg[k] = ’S’;
					 }
				 else if (Muster2D[x][y + 1] == 72)
					 {
					 xs = x; ys = y; i = Muster2D[x][y];
					 hweg[k] = ’O’;
					 }
				 else if (Muster2D[x - 1][y] == 72)
				 {
				 xs = x; ys = y; i = Muster2D[x][y];
				 hweg[k] = ’N’;
				 }
				 else if (Muster2D[x][y - 1] == 72)
					 {
					 xs = x; ys = y; i = Muster2D[x][y];
					 hweg[k] = ’W’;
					 }
				 }
			 }
		}
	 k++;
	 for (; i >= 0; i--) {
		 if (Muster2D[xs - 1][ys] == i - 1) {
			 xs--;
			 hweg[k] = ’S’;
			 k++;
			
		}
		 else if (Muster2D[xs + 1][ys] == i - 1) {
		 xs++;
		 hweg[k] = ’N’;
		 k++;
		
		}
		 else if (Muster2D[xs][ys - 1] == i - 1) {
			 ys--;
			
				 hweg[k] = ’O’;
			 k++;
			
		}
		else if (Muster2D[xs][ys + 1] == i - 1) {
			 ys++;
			 hweg[k] = ’W’;
			 k++;
			
		}
		
	}
	 hweg[k] = 0;
	 x = 0;
	 y = 2;
	 while (k > 0) {
		 k--;
		 if (hweg[k] == richtung[y]) {
			 rweg[x] = ’G’;
			
		}
		 else if (hweg[k] == richtung[y + 1]) {
			 rweg[x] = ’R’;
			 y++;
			if (y == 5)
				 y = 1;
			
		}
		 else if (hweg[k] == richtung[y - 1]) {
			 rweg[x] = ’L’;
		 y--;
		 if (y == 0)
		 y = 4;
			
		}
		 x++;
		
	}
	 rweg[x] = 0;
	
}

 void AksenMain(void) {
	 start();
	 if (count == 3)
		 break;
	 {
		 if (rweg[i] == 71)
			{
			 geradeaus();
			 i++;
			 }
		else if (rweg[i] == 82) {
			 turnRight();
			
				 i++;
			
		}
		 else if (rweg[i] == ’U’) {
			 umdrehen();
			 i++;
			
		}
		 else if (rweg[i] == 76) {
			 turnLeft();
			 i++;
			
		}
		 else if (rweg[i] == 76) {
			 abliefern();
			
		}
		 else if (rweg[i] == 48) {
			 break;
			
		}
		 }
	 // Die folgende Endlosschleife "erzeugt" das Programmende
		 while (true)
		
}
