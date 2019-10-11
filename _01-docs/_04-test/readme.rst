++++++++++++++++++++++++++++++++
Mise au point octobre 2019
++++++++++++++++++++++++++++++++

Problème avec les capteurs à ultra son
======================================
Des détections aléatoires ! 2 pistes envisagées
 - parasites dus au moteurs
 - conflit de timer entre pulsein et PWM

Etude conflit de timer
======================================
Broches PWM des moteurs : 12 et 44
Broches pulsin des capteurs US : 28, 15 et 25

Pulsin utilise-t-elle des timer ?
Tout au plus des interruptions mais ce n'est pas clairement dit.

N'utilse même pas micros

Définition dans :
C:\\Program Files (x86)\\Arduino\\hardware\\arduino\\avr\\cores\\arduino\\wiring_pulse.c

.. code:: cpp

    unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
    {
        // cache the port and bit of the pin in order to speed up the
        // pulse width measuring loop and achieve finer resolution.  calling
        // digitalRead() instead yields much coarser resolution.
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);
        uint8_t stateMask = (state ? bit : 0);

        // convert the timeout from microseconds to a number of times through
        // the initial loop; it takes approximately 16 clock cycles per iteration
        unsigned long maxloops = microsecondsToClockCycles(timeout)/16;

        unsigned long width = countPulseASM(portInputRegister(port), bit, stateMask, maxloops);

        // prevent clockCyclesToMicroseconds to return bogus values if countPulseASM timed out
        if (width)
            return clockCyclesToMicroseconds(width * 16 + 16);
        else
            return 0;
    }

Voir aussi  `Arduino Formu`_

.. _`Arduino Formu` : https://forum.arduino.cc/index.php?topic=105289.0

    
pwm utilisent-ils des timers ?
Source : `arduino-101-timer`_

OUI :

.. code::

    On the Arduino Mega we have 6 timers and 15 PWM outputs:
    Pins 4 and 13: controlled by timer0
    Pins 11 and 12: controlled by timer1
    Pins 9 and10: controlled by timer2
    Pin 2, 3 and 5: controlled by timer 3
    Pin 6, 7 and 8: controlled by timer 4
    Pin 46, 45 and 44:: controlled by timer 5
    
Pin 12 : timer1, pin 44 : timer 5


.. _`arduino-101-timer` : https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072

Weblinks
=========

.. target-notes::


