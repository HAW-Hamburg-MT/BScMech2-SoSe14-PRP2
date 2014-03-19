/*
 * File:   mycbw.c
 * Author: Reinhard
 *
 * Created on 14. Februar 2014, 12:00
 */

#include "mycbw.h"

Byte porta = 0;
Byte portb = 0;
Byte portc = 0;
Byte portcl = 0;
Byte portch = 0;

typedef char String3[3];

String3 cv[4] = {" A", " B", "CL", "CH"};
char io[2] = {'O', 'I'};

void cbDConfigPort(Byte boardnummer, Byte port, Byte dir) {


    if (port > FIRSTPORTCH) printf("Komischer Port! port = %u\n", port);
    else {
        printf("cbDConfigPort %s %c\n", cv[port], io[dir]);
        if ((((port == FIRSTPORTA) || (port == FIRSTPORTCL)) && (dir != DIGITALOUT)) ||
                (((port == FIRSTPORTB) || (port == FIRSTPORTCH)) && (dir != DIGITALIN)))
            printf("Falsche Richtung/Port\n");

        else if (port == FIRSTPORTB) portb = 0xFF;
        else if (port == FIRSTPORTCL) portcl = 0;
        else if (port == FIRSTPORTA) porta = 0;
        else if (port == FIRSTPORTCH) portch = 0xA;
    }

}

void cbDOut(Byte boardnummer, Byte port, Byte value) {
    printf("cbDOut %s %x\n", cv[port], value);

    if (port == FIRSTPORTA) porta = value;
    else if (port == FIRSTPORTCL) portcl = value;
    else printf("Falsche Portnummer fuer Ausgabe\n");
}

void cbDIn(Byte boardnummer, Byte port, Byte *value) {

    if (port == FIRSTPORTB) *value = portb;
    else if (port == FIRSTPORTCH) *value = portch;
    else printf("Falsche Portnummer fuer Eingabe\n");
    printf("cbDIn port = %s value = %x\n", cv[port], *value);
}

void changeSensors() {
    printf("\nchangeSensors\n");
    printf("Define new port B : ");
    scanf("%x", &portb);
    printf("Define new port CH: ");
    scanf("%x", &portch);
}



