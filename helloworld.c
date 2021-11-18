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

void AksenMain(void)
{
	while (1) {

		weg();


		//	sleep(200);  motor 3 links motor 1 recht


	}

}


void weg()
{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	lcd_cls();

	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);




	while (i < 9)
	{

		if (wert_links > 100 && wert_recht > 100 && wert_mitte > 100)
		{

			if (Plan[i] == 'R')
			{
				rechts();
				i++;
			}
			else if (Plan[i] == 'L')
			{
				links();
				i++;
			}
			else if (Plan[i] == 'G')
			{
				geradeaus();
				i++;
			}
			else
			{
				stop();
				i++;
			}


		}
		else

		{
			folgelinie();
		}

		
		
	}
	

	/*	else
		{
		folgelinie();
		}
		*/

	stop();

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

