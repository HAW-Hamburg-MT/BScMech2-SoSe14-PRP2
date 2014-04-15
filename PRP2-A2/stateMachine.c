/*
 * file: stateMachine.c
 * project: BScMech2-SoSe14-PRP2
 * version: 0.1 (15.04.2014 15:20)
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
    
    switch (*currentState) {
        case START:
            /*
             Zu Beginn soll die Anlage in einem Zustand sein (Anfangszustand), der folgendermaßen cha- rakterisiert ist:
              Das Band steht.
              Die Schranke ist geschlossen.
              Die Ampelleuchten sind alle aus.
              Die Lampen Q1 und Q2 sind aus.
              Nur die Start-Taste leuchtet.
             */
            setOutput(LED_START);
            
            if (isTriggered(BTN_START)) {
                *currentState = ACTIVE;
            }else;
            
            break;
        case ACTIVE:
            /*
             Wenn die Start-Taste gedrückt wird, geht die Anlage in den Betrieb über (Zustand 2):
              Das Band steht still.
              Bei der Ampel leuchtet nur grün.
             */
            setOutput(LIGHT_GN);
            
            if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
            }else if (hasTriggered(BTN_START)){
                *currentState = START;
            }else;
    
            break;
        case TRANSP:
            /*
             Wird im Zustand 2 ein Werkstück an den Bandanfang aufgelegt, beginnt der Transport des Werkstückes.
              Das Band transportiert das aufgesetzte Werkstück nach rechts.
              Die Ampel schaltet von Grün auf Gelb.
             */
            clearBitInOutput(LIGHT_GN);
            setBitInOutput(LIGHT_YE);
            clearBitInOutput(RST_MOTOR);
            setBitInOutput(MOTOR_R);
            
            if (hasTriggered(POS_HEIGHT)) {
                *currentState = TRANSP_H;
            }
            
            break;
        case TRANSP_H:
            /*
             Wenn das Werkstück die Lichtschranke der Höhenmessung erreicht, wird folgender Zustand erreicht:
              Das Band wird gestoppt.
              Die Ampel schaltet von Gelb auf Rot.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_RD);
            
            if (hasTriggered(SNS_HEIGHT)) {
                *currentState = TRANSP_H1;
            }else {
                *currentState = TRANSP_H0;
            }
            
            break;
        case TRANSP_H1:
            /*
             Wenn die Höhe des Werkstücks erfasst wurde und die Höhe in Ordnung ist, wird folgender Zu- stand erreicht:
              Das Band läuft langsam nach rechts.
              Die Ampel schaltet auf Grün.
              Die Q1-Lampe leuchtet. Diese Lampe soll so lange leuchten, bis ein neues Werkstück auf dem Band gelegt wird.
              Geben Sie das Ergebnis der Höhenmessung zusätzlich auf der Konsole aus.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_R | MOTOR_SLOW);
            setBitInOutput(LED_Q1 | LIGHT_GN);
            printf("height OK");
            
            if (isTriggered(POS_JUNCT)) {
                *currentState = TRANSP_J;
            }
            
            break;
        case TRANSP_H0:
            /*
             Wenn die Höhe des Werkstücks erfasst wurde und die Höhe nicht in Ordnung ist, wird folgender Zustand erreicht:
              Das Band läuft langsam nach rechts.
              Die Ampel schaltet auf Rot.
              Die Q1 Lampe leuchtet nicht.
              Geben Sie das Ergebnis der Höhenmessung zusätzlich auf der Konsole aus.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(MOTOR_R | MOTOR_SLOW);
            setBitInOutput(LED_Q1 | LIGHT_RD);
            printf("height not OK");
            
            if (isTriggered(POS_JUNCT)) {
                *currentState = TRANSP_J;
            }
            
            break;
        case TRANSP_J:
            /*
             Wenn das Werkstück die Weiche erreicht hat, wird folgender Zustand erreicht:
              Das Band wird gestoppt.
              Die Ampel schaltet auf Rot.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_RD);
            
            if (hasTriggered(SNS_METAL)) {
                *currentState = TRANSP_M1;
            }else {
                *currentState = TRANSP_M0;
            }
            
            break;
        case TRANSP_M0:
            /*
             Wenn das Werkstück bei der Weiche ist und nicht metallisch ist, wird folgender Zustand er- reicht:
              Das Band läuft nach rechts.
              Die Ampel schaltet auf Gelb.
              Die Weiche wird geöffnet.
              Die Q2-Lampe leuchtet.
             */
            setBitInOutput(MOTOR_R);
            setBitInOutput(JUNCTION | LED_Q2);
            setBitInOutput(LIGHT_YE);
            
            if (hasTriggered(SNS_SLIDE)) {
                *currentState = AT_SLIDE;
            }else if (hasTriggered(POS_OUT)) {
                *currentState = AT_END;
            }else;
            
            break;
        case TRANSP_M1:
            /*
             Wenn das Werkstück bei der Weiche ist und metallisch ist, wird folgender Zustand erreicht:
              Das Band läuft nach rechts.
              Die Ampel schaltet auf Gelb und Rot.
              Die Weiche zu; Q2 aus.
             */
            setBitInOutput(MOTOR_R);
            setBitInOutput(LIGHT_YE | LIGHT_RD);
            clearBitInOutput(JUNCTION | LED_Q2);
            
            if (hasTriggered(SNS_SLIDE)) {
                *currentState = AT_SLIDE;
            }else if (hasTriggered(POS_OUT)) {
                *currentState = AT_END;
            }else;
            
            break;
        case AT_SLIDE:
            /*
             Wenn das Werkstück in der Rutsche angekommen ist, wird folgender Zustand erreicht:
              Das Band wird gestoppt.
              Die Ampel schaltet auf Rot.
             Die Anlage kann wieder ausgeschaltet werden, bzw. ein neues Werkstück eingelegt werden.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_RD);
            clearBitInOutput(JUNCTION | LED_Q2);
            
            if (hasTriggered(BTN_STOP)) {
                *currentState = START;
            }else if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
            }
            
            break;
        case AT_END:
            /*
             Wenn das Werkstück im Auslauf angekommen ist, wird folgender Zustand erreicht:
              Das Band wird gestoppt.
              Die Weiche geht zu; Q2 ausgeschaltet.
              Die Ampel schaltet auf Grün.
             Die Anlage kann wieder ausgeschaltet werden, bzw. ein neues Werkstück eingelegt werden.
             */
            clearBitInOutput(RST_MOTOR | RST_LIGHT);
            setBitInOutput(LIGHT_GN);
            clearBitInOutput(JUNCTION | LED_Q2);
            
            if (hasTriggered(BTN_STOP)) {
                *currentState = START;
            }else if (hasTriggered(POS_IN)) {
                *currentState = TRANSP;
            }
            
            break;
            
    }//END SWITCH
    
}