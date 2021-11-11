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

//Hauptprogrammroutine
void AksenMain(void)
{
	while (1) {

		weg();


		//	sleep(200);  motor 3 links motor 1 recht


	}

}


void weg()
{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	lcd_cls();

	{
		wert_recht = analog(0);
		wert_links = analog(7);
		wert_mitte = analog(2);

		if (wert_links > 100 && wert_recht > 100 && wert_mitte > 100)

		{
			geradeaus();
		}

		else
		{
			folgelinie();
		}

	}


}


void rechts()

{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 0);
	motor_pwm(1, 8);
	sleep(1000);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);
	}



}


void links()

{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 8);
	motor_pwm(1, 0);
	sleep(1000);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);
	}



}

void geradeaus()

{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 8);
	motor_pwm(1, 8);
	sleep(500);
	while (wert_mitte > 100)
	{
		wert_mitte = analog(2);
	}

}



void folgelinie()

{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);

	if (wert_links < 100 && wert_recht < 100 && wert_mitte > 100)
	{
		motor_richtung(3, 0);
		motor_richtung(1, 0);
		motor_pwm(3, 9);
		motor_pwm(1, 9);
	}

	if (wert_links>100 && wert_recht<100 && wert_mitte < 100)
	{
		motor_richtung(3, 0);
		motor_pwm(3, 5);
		motor_richtung(1, 0);
		motor_pwm(1, 2);

	}
	else if (wert_links<100 && wert_recht>100 && wert_mitte < 100)
	{
		motor_richtung(3, 0);
		motor_pwm(3, 2);
		motor_richtung(1, 0);
		motor_pwm(1, 5);

	}


}

