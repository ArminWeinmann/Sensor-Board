# PIC Board Advanced 7 Board Support Package
## Download des PBA7 BSP
Der Sourcecode des PBA7-BSP kann <a href="firmware.zip"> hier </a> heruntergeladen werden.

## Inhalt BSP
Der entpackte Ordner enth�lt nun folgende Unterordner und Dateien:

Ordner / Datei  	| Inhalt
--------------------| ---------------------------------------------------------------------------------------------------------------------
inc                 | Include-Files des BSP
mcc_generated_files	| Vom Microchip Code Configurator generierte Files zur Hardwareansteuerung
nbproject			| Porjektdateien des Beispielprojektes
src             	| Source-Files des BSP
%LICENSE.md      	| Lizenz --> Bitte durchlesen
main.c 				| Hauptprogramm des Beispielprojekts
Makefile			| Makefile des Beispielprojektes
MCC_Config.mc3		| Konfigurationsdatei des Code Configurators
%README.md       	| Anleitung

## BSP-Module
Modul           	| Zweck
-------------------	| ---------------------------------------------------------------------------------------------------------------------
\ref BTN            | Auslesen der Taster auf dem PBA7. Zustands- oder Flankenabfrage.
\ref CONFIG              | Allgemeine Funktionen und Makros f�r das PBA7.
\ref OLED             	| Ansteuerung des OLEDM204. Mit kleinen Anpassungen auch f�r andere Controller und Displays verwendbar.
\ref RTC            		| Ansteuerung des RTC DS3231. Kann auch als Temperatursensor eingesetzt werden.
\ref STATEMACHINE      	| Funktionen f�r den Umgang mit Zustandsmaschinen.
\ref SYSTICK            	| Library f�r die Verwendung von Softtimern.


## Neues PBA7 Projekt erstellen
1. Den Ordner firmware an einen gew�nschten Ort kopieren.
2. In MPLAB "Open Project.." anw�hlen.
3. An die richtige Stelle navigieren und "firmware" �ffnen.
4. Rechtsklick auf das Projekt PBA7 -> "Rename.." und das Projekt mit dem Projektnamen benennen. Das H�ckchen "Also Rename Project Folder" anw�hlen.
5. Der Inhalt von main.c (Hardwaretest) kann gel�scht werden.
 
## Interrupts
Der Mikrocontroller verf�gt nur �ber einen Interrupt-Vektor. Die Interrupts wurden mit dem Microchip Code Cofigurator
konfiguriert. Zus�tzliche Interrupts sollten ebenfalls �ber den MCC registriert werden.

## Hardware initialisieren
Zum Initialisieren der Hardware muss die Funktion ```PBA_Init();``` aufgerufen werden.

```C
#include "inc/PBA_config.h"
void main(void)
{
    PBA_Init();     /* Initialisieren der Hardware */
    while(1)
    {
                    /*My Code*/
    }
}
  ```
  
## Verwendung von Loopdelays
Systick stellt Funktionen im Umgang mit Softtimern zur Verf�gung. Diese Timer k�nnen gesetzt werden und werden 
im Hintergrund im 1ms Takt heruntergez�hlt. Diese Softtimer k�nnen auch f�r ein Loopdelay verwendet werden.

```C
#include "inc/PBA_config.h"

enum{ LOOP_TIMER };

void main(void)
{
    PBA_Init();             /*Initialisieren der Hardware*/
    SYSTICK_TimerLoadAndRun(LOOP_TIMER,10);     /*Zyklustimer Init, loop-time=10ms*/
    while(1)
    {
        while(!SYSTICK_Timeout(LOOP_TIMER));    //Warten bis Zykluszeit abgelaufen ist.
        SYSTICK_TimerLoadAndRun(LOOP_TIMER,10); //Zyklustimer neu laden und starten
        ...
    }
}
  ```
 
## Verwendung von Zustandmaschinen
F�r die Verwendung von Zustandsmaschinen steht die Library Statemaschine zur Verf�gung. Diese erm�glicht es den Eintritt
sowie den Austritt aus einem State zu ermitteln. Dazu muss eine Update Funktion aufgerufen und mittel Init Funktion
ein Pointer auf den Zustand registriert werden. Die Update Funktion muss unterhalb des switch sein, ansonsten wird 
beim ersten Durchlauf die StateEntry Funktion false zur�ck geben. 

```C
typedef enum{
    STATE1, STATE2
}state_t;
  
enum{
    LOOP_TIMER
};
  
void main(void)
{
    PBA_Init();     
    
    state_t myState = STATE1;   //Zustand als Enum
    STATEMACHINE_Init(&myState);    //Pointer auf Zustand �bergeben
    
    SYSTICK_TimerLoadAndRun(LOOP_TIMER,10);     //Looptimer starten
    while (1)
    {
        while(!SYSTICK_Timeout(LOOP_TIMER));        //Loopdelay
        SYSTICK_TimerLoadAndRun(LOOP_TIMER,10);
  
        switch(myState){
            case STATE1:
                if(STATEMACHINE_StateEntry()){ .. }     //Es wurde in den Zustand gewechselt
                
                if(someEvent){
                    myState = STATE2;       //Wechsel in den n�chsten Zustand
                }
                //do
                //..

                if(STATEMACHINE_StateExit()){ .. }      //Der Zustand wurde verlassen
                break;

            case STATE2:
                //..
                break;
        }
        STATEMACHINE_Update();      //Aktualisieren der Zust�nde
    }
}
```

## Verwendung des BTN Moduls
Mit dem BTN Modul k�nnen Taster abgefragt werden. Das Modul beinhaltet Methoden um Flanken und Zust�nde abzufragen.
Es wird jeweils die Bitnummer des Tasters auf dem Port angegeben um eine Abfrage zu machen (z.B. 3 f�r Taster3).
Das Modul ist auf ein externes Delay zur Entprellung angewiesen. Zustandabfragen sind auch ohne Delay m�glich. 

```C
enum{
    LOOP_TIMER
};
  
void main(void)
{
    PBA_Init();     
    
    SYSTICK_TimerLoadAndRun(LOOP_TIMER,10);     //Looptimer starten
    while (1)
    {
        while(!SYSTICK_Timeout(LOOP_TIMER));        //Loopdelay (wird zur Entprellung ben�tigt)
        SYSTICK_TimerLoadAndRun(LOOP_TIMER,10);

        if(BTN_GetNegEdge(3)){ 
            //do..
        }

    }
}
```

## LEDs ansteuern
Das PBA7 verf�gt �ber 10 LEDs an zwei Ports. Diese k�nnen per Makros (LED0 bis LED9) einzeln oder mit der Funktion
```PBA_SetLEDs(0x03FF);``` alle gleichzeitig angesteuert werden. 

## Ausgaben ans Display und �ber UART
Ausgaben ans Display oder ans Terminal k�nnen mit ```printf("some Text");``` gemacht werden. Das Config Modul bietet
die M�glichkeit zu konfigurieren ob Ausgaben per printf ans Display, ans Termin, an beides oder an nichts gesendet 
werden. Dies geschieht mit der Funktion ```PBA_ConfigPrintf(true,false);```, wobei der erste Boolean die Ausgabe ans 
OLED und der zweite die Ausgabe ans Terminal konfigueriert. 

## COM-Port Treiber
Je nach Betriebssystem und Konfiguration wird der Treiber f�r den USB-Seriell-Wandler FT230X nicht automatisch installiert.
Die Virtual Com Port (VCP) Treiber k�nnen im <a href="http://www.ftdichip.com/Drivers/VCP.htm" target="_blank">Downloadbereich</a> von FTDI Chip heruntergeladen werden. <br>
F�r unge�bte Benutzer stellt der Hersteller <a href="http://www.ftdichip.com/Support/Documents/InstallGuides.htm" target="_blank">Installationsanleitungen</a> f�r alle g�ngigen Betriebssysteme zur Verf�gung.
