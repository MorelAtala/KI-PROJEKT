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

//Prototypen
void folgelinie();
void rechts();
void links();
void weg();
void folgelinie();
void geradeaus();
void abliefern();
void turn();
void turnx();
void stop();
void umdrehen();
void umdrehen1();

//Hauptprogrammroutine
unsigned char i = 0;// counter
unsigned char j = 0;// counter
unsigned char Plan[] = "GLGTGGGRLGLGRGRLGGGTGGGRLGLRGRLLGLRGRLGGGT."; // weg für die Zulieferung der Pizzen einer Karte
//unsigned char Plan[] = "RLGGGGGLRGRLLGGGGGLRGRT.";
unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0; // werte der Sensoren


void AksenMain(void)
{

/* Vor der Abfahrt muss das Licht eingeschaltet werden dann wenn ok, wird die funktion weg abgerufen*/
	lcd_cls();
	lcd_puts("Wert: ");
	lcd_ubyte(analog(8));
	while (analog(8) > 100){
								
	}

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

	/*

	Bei der einer Kreuzung , kontrolliert man Plan[i] . Um zu wissen was zu tun ist. 
	und am Ende i++ und so weiter so wird für G R L den Weg verfolgt. 
	Und für T dreht der Roboter um.
	Nach der Lieferung der Pizza oder für die nächste Lieferung am Startpunkt.

	*/


	while (i < 45)
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
			else if (Plan[i] == 'T') /* wenn der Roboter angekommen ist.
			erstmals umdrehen 90rad und dann noch mal umdrehen um 180 grad 
			schaffen zu können um die nächste Lieferung vorbereiten zu können.
			
			*/ {
				turn();
				sleep(700);
				turnx();
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

		/*
		wenn der Taster gedrückt wird j++ . Bei manchen Karten gibts Lieferorte
		wo unsere Roboter sich nicht sehr gut 
		umdrehen kann um die nächste richtige Kreuzung zu erkennen 
		und die Linie weiter richtig  verfolgen un den Plan schaffen zu können.

		Bei diesen Lieferorte : wird eine speziale Funktion umdrehen1() abgerufen. 
		*/
			while (digital_in(0) == 0)
			{
				j++;
				if (j == 2){
					umdrehen1();
				}
				else{
					//sleep(1000);
					umdrehen();
				}

			}
			folgelinie(); // immer wenn nichts linie folgen
		}



	}


	/*	else
	{
	folgelinie();
	}
	*/

	//stop();

}


void rechts() // rechts abbiegen

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 0);
	motor_pwm(1, 9);
	sleep(1000);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);

	}


	folgelinie();
}


void links() // links abbiegen

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 9);
	motor_pwm(1, 0);
	sleep(500);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);
	}

	folgelinie();

}

void geradeaus() // geradeaus fahren

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 5);
	motor_pwm(1, 5);
	sleep(1000);
	while (wert_mitte > 100)
	{
		wert_mitte = analog(2);
	}

	folgelinie();

}



void folgelinie() // Linie verfolgen

{
	//unsigned char wert_links = 0, wert_recht = 0, wert_mitte = 0;
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);

	if (wert_links < 100 && wert_recht < 100 && wert_mitte > 100)
	{
		motor_richtung(3, 0);
		motor_richtung(1, 0);
		motor_pwm(3, 7);
		motor_pwm(1, 7);
	}

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

void stop() // am Ende Stop
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


void turn() // für die Funktion umdrehen() nach dem der Taster gedrückt wird
{
	wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);


	motor_richtung(3, 0);
	motor_richtung(1, 1);
	motor_pwm(3, 10);
	motor_pwm(1, 10);
	sleep(1000);
	while (wert_mitte < 100)
	{
		wert_mitte = analog(2);

	}
	motor_richtung(3, 0);
	motor_richtung(1, 1);
	motor_pwm(3, 10);
	motor_pwm(1, 10);

	folgelinie();

}
void turnx() // 270° fürs Umdrehen am Startpunkt nachdem die letzte Pizza geliefert wurde und wenn die nächste geladen muss.
{
	motor_richtung(3, 1);
	motor_richtung(1, 1);
	motor_pwm(3, 5);
	motor_pwm(1, 5);
	sleep(1000);
	motor_richtung(3, 0);
	motor_richtung(1, 0);
	motor_pwm(3, 0);
	motor_pwm(1, 0);
	sleep(2000);
	folgelinie;

}

void abliefern()// nutzlos

{
	/*wert_recht = analog(0);
	wert_links = analog(7);
	wert_mitte = analog(2);*/

	//folgelinie();

	motor_richtung(1, 0);
	motor_richtung(3, 0);
	motor_pwm(1, 8);
	motor_pwm(3, 8);
	if (digital_in(0) == 0)
	{
		motor_richtung(2, 0);
		motor_pwm(2, 10);
		motor_pwm(2, 0);
		//sleep(1000);
		turn();

	}


}


//Links oder Recht 90°
void umdrehen() // nachdem der Taster gedrückt wird und die Pizza abgelegt wird.

{
	motor_richtung(2, 0);
	motor_pwm(2, 3);
	sleep(1000);
	motor_pwm(2, 0);
	motor_richtung(1, 1);
	motor_richtung(3, 1);
	motor_pwm(1, 5);
	motor_pwm(3, 5);
	sleep(500);
	motor_richtung(2, 1);
	motor_pwm(2, 6);
	sleep(500);
	motor_pwm(2, 0);
	turn();


}

//gerade 180°
void umdrehen1()// bei machen Karte um die richtige Kreuzung nach dem umdrehen zu erkennen

{
	motor_richtung(2, 0);
	motor_pwm(2, 3);
	sleep(1000);
	motor_pwm(2, 0);
	motor_richtung(1, 1);
	motor_richtung(3, 1);
	motor_pwm(1, 5);
	motor_pwm(3, 5);
	sleep(1000);
	motor_richtung(2, 1);
	motor_pwm(2, 6);
	sleep(500);
	motor_pwm(2, 0);
	turn();


}
