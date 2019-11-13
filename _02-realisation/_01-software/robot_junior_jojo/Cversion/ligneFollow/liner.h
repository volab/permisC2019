/**
 @file _fileName_cpp_or_h
 @author J.SORANZO
 @date 27/10/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'entête de la classe  CRjLiner

Utilise la classe CIrSensor
*/

#include "irSensor.h"
#include <Arduino.h>

#ifndef _CRJLINER_H
#define _CRJLINER_H

/**
* @class CRjLiner liner.h
* @brief Class du capteur suiveur de ligne composé de 6 détecteurs (3 de chaque côté)
*/
class CRjLiner{
    public:
        void begin( 
              int pinGaucheExt
            , int pinGaucheMid
            , int pinGaucheCentre
            , int pinDrouteCentre
            , int pinDroiteMid
            , int pinDroiteExt);
        byte getValue( ){ return _value; }
        byte getValueDroite( ){ return _valueD; } /**< @brief return 0, 1, 2, or 4 */
        byte getValueGauche( ){ return _valueG; } /**< @brief return 0, 1, 2, or 4 */
        void update();
        void forceUpdate(); /**< @brief pour ne pas attendre samplePeriod - lecture directe */
        
    private:
        byte _value;
        byte _valueD;
        byte _valueG;
        CIrSensor _irSensor[6];
        unsigned long _previousMillis;
        unsigned int _samplePeriod = 2;
};

#endif