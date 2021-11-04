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

//Hauptprogrammroutine
void AksenMain(void)
{

	folgelinie();
	

	//	sleep(200);  motor 3 links motor 1 recht



	
}


void folgelinie()
{
	unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	lcd_cls();

	while (1) {
		wert_recht = analog(0);
		wert_links = analog(7);
		wert_mitte = analog(2);

		if (wert_links > 100 && wert_recht > 100 && wert_mitte > 100)

		{
			rechts();
		}

		if (wert_links<100 && wert_recht<100 && wert_mitte > 100)
		{
			motor_richtung(3, 0);
			motor_richtung(1, 0);
			motor_pwm(3, 8);
			motor_pwm(1, 8);
		}
		/*else if (wert_links>100 && wert_recht>100)
		{
			motor_richtung(3, 0);
			motor_richtung(1, 0);
			motor_pwm(3, 10);
			motor_pwm(1, 10);
		} */
		else if (wert_links>100 && wert_recht<100 && wert_mitte < 100)
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
