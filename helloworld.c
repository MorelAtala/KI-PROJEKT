//Autor: Loic - Morel

//Standard-Include-Files
#include <stdio.h>
#include <regc515c.h>
#include <stdlib.h>
#include <stdint.h>

//Diese Include-Datei macht alle Funktionen der
//AkSen-Bibliothek bekannt.
//Unbedingt einbinden!
#include <stub.h>

void folgelinie();
void rechts();
void links();
void weg();
void folgelinie();
void geradeaus();
void stop();

//Hauptprogrammroutine
unsigned char i = 0;
//unsigned char Plan[] = "RLGLRGRLGLLG.";
unsigned char Plan[] = "RLLRRRRL.";
unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
unsigned char x, y, xs = 0, ys = 0, k;
//unsigned char heuristicherweg[20];
//unsigned char richtigerweg[] = "HHHHHHHH";
unsigned char Fahrplan[] =
"xFxxxFxx.x.x.xF..x..Fxx.x.xxx..x..xx.x.x.xF..x..Fxx.x.xxx..x..xx.x.x.x";
unsigned char nachbar[] = "SWNOSW";
unsigned char Gitter[10][7];
unsigned char counter = 0;
void AksenMain(void)
{
	while (1) {

		weg();


		//	sleep(200);  motor 3 links motor 1 recht


	}

}


void weg()
{
	
for (x = 0; x <= 10; x++)
	 {
		 for (y = 0; y < 7; y++)
			 {
			 if (Fahrplan[i] == ’x’)
				 Gitter[x][y] = 70;
			else if (Fahrplan[i] == ’.’)
				 Gitter[x][y] = 71;
			 else if (Fahrplan[i] == ’F’)
				 Gitter[x][y] = 72;
			 else if (Fahrplan[i] == ’#’)
				 Gitter[x][y] = 73;
			 i++;
			 }
		}
}


 void rechts()

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 0);
	motor_pwm(1, 6);
	sleep(500);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);

	}


	folgelinie();
}


void links()

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 6);
	motor_pwm(1, 0);
	sleep(500);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);
	}

	folgelinie();

}

void geradeaus()

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 5);
	motor_pwm(1, 5);
	sleep(700);
	while (wert_mitte > 100)
	{
		wert_mitte = analog(2);
	}
	
	folgelinie();

}



void folgelinie()

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);

	if (wert_links < 100 && wert_recht < 100 && wert_mitte > 100)
	{
		motor_richtung(3, 0);
		motor_richtung(1, 0);
		motor_pwm(3, 5);
		motor_pwm(1, 5);
	}

	else if (wert_links>100 && wert_recht<100 && wert_mitte < 100)
	{
		motor_richtung(3, 0);
		motor_pwm(3, 4);
		motor_richtung(1, 0);
		motor_pwm(1, 2);

	}
	else if (wert_links<100 && wert_recht>100 && wert_mitte < 100)
	{
		motor_richtung(3, 0);
		motor_pwm(3, 2);
		motor_richtung(1, 0);
		motor_pwm(1, 4);

	}


}

void stop()
{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);

	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 0);
	motor_pwm(1, 0);

}


 void umdrehen() {
	 motor_richtung(3, 0);
	 motor_richtung(1, 0);
	 motor_pwm(3, 0);
	 motor_pwm(1, 7);
	 weg();
	 sleep(1000);
	 while (analog(2) < 100);
	 motor_pwm(1, 0);
	 count++;
	 folgelinie();
	
}


 void liefern() {
	folgelinie();
	motor_pwm(3, 0);
	motor_pwm(1, 0);
	open();
	umdrehen();
	sleep(900);
	motor_richtung(3, 1);
	motor_richtung(1, 1);
	motor_pwm(3, 7);
	motor_pwm(1, 7);
	sleep(200);
	motor_pwm(3, 0);
	motor_pwm(1, 0);
	close();
	rechts();
	
}
