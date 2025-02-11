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
#include "timerSynchrone.h"

#ifndef _CROBOTJUNIOR_H
#define _CROBOTJUNIOR_H

#define NBR_TAG 5
/**
* @class CRobotJunior robot.h
* @brief Classe qui prend en charge tout les comportement du robot Junior du VoLAB
*/
class CRobotJunior{
    public:
        void init( unsigned long tempsCycle );
        void update();
        
        enum { FOLLOWLIGNE, LIGNELOST, PAUSE, END, RETRIVELIGN, RECULE, REALIGN
                , REAL_ST21, REAL_ATTTIMER, REAL_ST22
                , REAL_ATTALIG, REAL_ST0, REAL_ST1};
        
    private:

        Flasher _ledAvantGauche, _ledAvantDroite;
        Flasher _ledCapteurGauche, _ledCapteurCentre, _ledCapteurDroite;
        Flasher _ledArriereGauche, _ledArriereDroite;

        CUsSensor _usGauche, _usCentre, _usDroite;

        CIrSensor _irGauche, _irCentre, _irDroite;

        CRjLiner _liner;

        CBuzzer _buz;

        CDCMotor _motG, _motD;

        
        //Methodes privées
        void _initLeds();
        void _initSensors();
        void _initBuzzer();
        void _initMotors();
        void _updateLeds();
        void _updatesSensors();
        void _allumLedGauche();
        void _allumeLedDroite();
        void _allumeDroiteGauche();
        void _eteindLed();
        void _tourneGauche( int force );
        void _tourneGauche();
        void _tourneDroite( int force );
        void _tourneDroite();
        void _avanceDoucement();
        
        void _stop();
        void _followTheLigne();
        bool _retriveLigne();
        bool _realigne();
        
        char _trame[ TAILLE_TRAME + 1 ];/**< @brief trame NRF24 */
        
        
    
        
        //Attributs privés
        unsigned int _vitesseDeBase = VITESSE_DE_BASE ;
        unsigned int _vitesseDoucement = VITESSE_DOUCEMENT ;
        unsigned long _tempsCycle;          
        unsigned long _prevMillis;
        byte _cpt = 0; /**< @brief Usage ? */
        
        byte _capteurLigneDroite;
        byte _capteurLigneGauche;
        
        float _bat;
        byte _batEnt, _batDec;
        bool _inRun;
        // void _buzTutTut();
        bool _lignePerdue;
        unsigned int _cptPerteLigne; /**< @brief utilisé dans la détection de perte de la ligne */
        // unsigned int _etat;
        
        unsigned int _detectTagOn;
        int _etatRobot;
        unsigned long _cptPause; /**< @brief permet de faire une pause dans la machine d'état */
        TimerSynchrone _ts1;
        
        
        unsigned int _cptRecul; /**< @brief permet de régler la distance de recule */
        byte _cptRetrieveLigne;
        
        unsigned int _cptTour;
        unsigned int _vitesGaucheRetrive;
        
        bool _s2_1, _s2_2;
        bool _manoeuvreEnCours;/**< @brief uniquement utilisé dans la manoeuvre de la 
        stratégie 2 de _realigne() */
        bool _tourneAGauche; /**< @brief uniquement utilisé dans la manoeuvre de la 
        stratégie 2 de _realigne() */
	
};

#endif