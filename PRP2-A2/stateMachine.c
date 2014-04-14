/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.1 (14.04.2014 10:00)
 *
 *
 * Created by Jannik Beyerstedt
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 2
 * festo conveyor belt system - excercise 2
 */

#include <stdio.h>
#include "stateMachine.h"
#include "systemFunctions.h"

void theMachine(States *currentState) {
    /*
     Zu Beginn soll die Anlage in einem Zustand sein (Anfangszustand), der folgendermaßen cha- rakterisiert ist:
      Das Band steht.
      Die Schranke ist geschlossen.
      Die Ampelleuchten sind alle aus.
      Die Lampen Q1 und Q2 sind aus.
      Nur die Start-Taste leuchtet.
     */
    
    /*
     Wenn die Start-Taste gedrückt wird, geht die Anlage in den Betrieb über (Zustand 2):
      Das Band steht still.
      Bei der Ampel leuchtet nur grün.
     */
    
    /*
     Wird im Zustand 2 ein Werkstück an den Bandanfang aufgelegt, beginnt der Transport des Werkstückes. Dazu schaltet die Steuerung die Anlage in folgenden Zustand:
      Das Band transportiert das aufgesetzte Werkstück nach rechts.
      Die Ampel schaltet von Grün auf Gelb.
     */
    
    /*
     Wenn das Werkstück die Lichtschranke der Höhenmessung erreicht, wird folgender Zustand erreicht:
      Das Band wird gestoppt.
      Die Ampel schaltet von Gelb auf Rot.
     */
    
    /*
     Wenn die Höhe des Werkstücks erfasst wurde und die Höhe in Ordnung ist, wird folgender Zu- stand erreicht:
      Das Band läuft langsam nach rechts.
      Die Ampel schaltet auf Grün.
      Die Q1-Lampe leuchtet. Diese Lampe soll so lange leuchten, bis ein neues Werkstück auf dem Band gelegt wird.
      Geben Sie das Ergebnis der Höhenmessung zusätzlich auf der Konsole aus.
     */
    
    /*
     Wenn die Höhe des Werkstücks erfasst wurde und die Höhe nicht in Ordnung ist, wird folgender Zustand erreicht:
      Das Band läuft langsam nach rechts.
      Die Ampel schaltet auf Rot.
      Die Q1 Lampe leuchtet nicht.
      Geben Sie das Ergebnis der Höhenmessung zusätzlich auf der Konsole aus.
     */
    
    /*
     Wenn das Werkstück die Weiche erreicht hat, wird folgender Zustand erreicht:
      Das Band wird gestoppt.
      Die Ampel schaltet auf Rot.
     */
    
    /*
     Wenn das Werkstück bei der Weiche ist und nicht metallisch ist, wird folgender Zustand er- reicht:
      Das Band läuft nach rechts.
      Die Ampel schaltet auf Gelb.
      Die Weiche wird geöffnet.
      Die Q2-Lampe leuchtet.
     */
    
    /*
     Wenn das Werkstück bei der Weiche ist und metallisch ist, wird folgender Zustand erreicht:
      Das Band läuft nach rechts.
      Die Ampel schaltet auf Gelb und Rot.
      Die Weiche bleibt zu; Q2 aus.
     */
    
    /*
     Wenn das Werkstück in der Rutsche angekommen ist, wird folgender Zustand erreicht:
      Das Band wird gestoppt.
      Die Ampel schaltet auf Rot.
     Die Anlage kann wieder ausgeschaltet werden, bzw. ein neues Werkstück eingelegt werden.
     */
    
    /*
     Wenn das Werkstück im Auslauf angekommen ist, wird folgender Zustand erreicht:
      Das Band wird gestoppt.
      Die Weiche geht zu; Q2 ausgeschaltet.
      Die Ampel schaltet auf Grün.
     Die Anlage kann wieder ausgeschaltet werden, bzw. ein neues Werkstück eingelegt werden.
     */
    
    
    
    printf("haha");
    
    
}