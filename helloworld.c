//Autor: Loic - Morel

//Standard-Include-Files
#include <stdio.h>
#include <regc515c.h>
#include <stdlib.h>

//Diese Include-Datei macht alle Funktionen der
//AkSen-Bibliothek bekannt.
//Unbedingt einbinden!
#include <stub.h>

//Hauptprogrammroutine
void AksenMain(void)
{
	
	unsigned char wert = 0, wert_links=0, wert_recht=0;
	lcd_cls();
	
while(1) {
		wert_links = analog(0); 
		wert_recht = analog(7);

		if (wert_links<100 && wert_recht<100)
		{
			motor_richtung(3, 0);
			motor_richtung(1, 0);
			motor_pwm(3, 10);
			motor_pwm(1, 10);
		}
		else if (wert_links>100 && wert_recht>100)
		{
			motor_richtung(3, 0);
			motor_richtung(1, 0);
			motor_pwm(3, 10);
			motor_pwm(1, 10);
		}
		else if (wert_links>100 && wert_recht<100)
		{
			motor_richtung(3, 0);
			motor_pwm(3, 2);
			motor_richtung(1, 0);
			motor_pwm(1, 7);
		}
		else if (wert_links<100 && wert_recht>100)
		{
			motor_richtung(3, 0);
			motor_pwm(3, 7);
			motor_richtung(1, 0);
			motor_pwm(1, 2);
		}
	
	} 



//	sleep(200);  motor 3 links motor 1 recht



	while (1);
}
