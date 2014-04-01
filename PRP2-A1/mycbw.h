/* 
 * File:   mycbw.h
 * Author: Reinhard
 *
 * Created on 14. Februar 2014, 11:42
 *
 * correctes on 01.04.2014, 17:10 by Jannik Beyerstedt
 */

#ifndef MYCBW_H
#define	MYCBW_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

//#define BNR 0
#define FIRSTPORTA 0
#define FIRSTPORTB 1
#define FIRSTPORTCL 2
#define FIRSTPORTCH 3
#define DIGITALOUT 0
#define DIGITALIN 1


    typedef unsigned short int Byte;

    void cbDConfigPort(Byte boardnummer, Byte port, Byte dir);
    void cbDOut(Byte boardnummer, Byte port, Byte value);
    void cbDIn(Byte boardnummer, Byte port, Byte *value);

    void changeSensors();


#ifdef	__cplusplus
}
#endif

#endif	/* MYCBW_H */

