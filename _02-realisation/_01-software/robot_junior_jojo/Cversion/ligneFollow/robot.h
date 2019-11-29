/**
 @file robot.h
 @author J.SORANZO
 @date 02/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'entête de la classe CRobotJunior
*/

#include <Arduino.h>
#include "config.h"
#include "flasher.h"
#include "usSensor.h"
#include "irSensor.h"
#include "liner.h"
#include "buzer.h"
#include "motor.h"
#include "RF24.h"

#ifndef _CROBOTJUNIOR_H
#define _CROBOTJUNIOR_H


/**
* @class CRobotJunior robot.h
* @brief Classe qui prend en charge tout les comportement du robot Junior du VoLAB
*/
class CRobotJunior{
    public:
        void init( unsigned long tempsCycle );
        void update();
        
    private:
        Flasher _ledAvantGauche, _ledAvantDroite;
        Flasher _ledCapteurGauche, _ledCapteurCentre, _ledCapteurDroite;
        Flasher _ledArriereGauche, _ledArriereDroite;

        CUsSensor _usGauche, _usCentre, _usDroite;

        CIrSensor _irGauche, _irCentre, _irDroite;

        CRjLiner _liner;

        CBuzzer _buz;

        CDCMotor _motG, _motD;
        unsigned int _vitesseDeBase = VITESSE_DE_BASE ;
        unsigned long _tempsCycle;
        void _initLeds();
        void _initSensors();
        void _initBuzzer();
        void _initMotors();
        void _updateLeds();
        void _updatesSensors();
        void _allumLedGauche();
        void _allumeLedDroite();
        void _eteindLed();
        void _tourneGauche( int force );
        void _tourneDroite( int force );
        unsigned long _prevMillis;
        void _stop();
        char _trame[ TAILLE_TRAME + 1 ];
        byte _cpt = 0;
        float _bat;
        byte _batEnt, _batDec;
        bool _inRun;
        void _buzTutTut();
        bool _lignePerdue;
        unsigned long _cptPerteLigne;
        
	
};

#endif