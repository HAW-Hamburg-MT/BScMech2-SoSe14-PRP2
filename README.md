BScMech2-SoSe14-PRP2
====================

Programmieren Labor Mechatroniker HAW Hamburg

## this semester is closed, every project works correctly

## PRP2-A4:
C++ inheritance demonstration for correcting sensor values with a linear, as well as lookup table correction.


## PRP2-A3:

### TODO:

1. update outputList for using a function pointer

### Requirements

####R001 - Erfassen von Kenndaten 
Von jedem Werkstück, das die Anlage nach dem Drücken von Start durchläuft, sollen Kenn- daten erfasst werden.
Die Kenndaten beinhalten:

* den Zeitpunkt, an dem das Werkstück auf das Band gelegt wurde
* ob das Werkstück die korrekte Höhe hat oder nicht
* ob das Werkstück metallisch ist oder nicht.
* den Zeitpunkt, an dem das Werkstück am Ende / in der Rutsche ist

####R002 - Interne Verwaltung der Kenndaten

Die Kenndaten von jedem Werkstück werden in einer dynamischen Liste gespeichert. Die Liste enthält alle Kenndaten der Werkstücke, die nach dem letzten Drücken von Start erfolgreich sor- tiert wurden.

####R003 - Ausgabe der Kenndaten

Wird die Taste Start zum Abschalten der Anlage betätigt, so wird die Liste der Kenndaten auf dem Bildschirm ausgegeben. Parallel wird die Liste der Kenndaten als CSV-Datei gespeichert. Trennzeichen ist das Semikolon.
Hinweis: Wird wieder die Taste Start gedrückt, so wird die Liste gelöscht und nimmt wieder die Daten der nächsten Werkstücke auf.

####R004 - Erhalt alter Kenndaten

Bereits vorhandene Dateien mit Kenndaten von Werkstücken werden nicht überschrieben.



## TODO PRP2-A2 dev: ++closed++
**do not develop in this branch any more!!!**

#####AT_END: 
* **current behaviour is not good**
* switch to ACTIVE **only** if item is removed!
* this prevents going to transport if there is an item at the end which will fall down then

#####AT_SLIDE:
* new item at POS_IN will TRANSP
* BTN_START will ACTIVE
* BTN_STOP will START
