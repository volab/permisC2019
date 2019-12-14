/**
 @file config.h
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version 
 @brief Parmis C ligne follower version configuration file
*/

#ifndef _CONFIG_PERMISC_H
#define _CONFIG_PERMISC_H

#define MAQUETTE_VERSION // comment for PCB version

#define TEMPS_CYCLE 10 //ms

#define DISTANCE_ARRET 30 //cm pour capteur us

#define VITESSE_DE_BASE 115
#define VITESSE_DOUCEMENT 80
#define TEMPS_DE_MANOEUVRE  45// en nombre de cyles <=> distance parcourue 4mm/cycle quand on est
                              // lancé (VBAT7.5 C=110) mais combien de cycle met-on pour atteindre
                              // cette vitesse ? à C=80 on est plus proche de 2mm/cycle
//valeur théorique souhaité : 25 pour avancer de 100mm mais comme on part de la situation arrêté...
//Expérimentation 25 <=> 35mm parcouru
//Avec 45 <=> 80mm

#define CPT_LIG_LOST_MAX 100 //environ 30 à 40cm (environ 4mm/cycle selon VITESSE_DE_BASE et niveau
                             // de la batterie)

#define LED_AVANT_GAUCHE_PIN 27
#define LED_AVANT_DROITE_PIN 5

#define LED_ARRIERE_GAUCHE_PIN 47
#define LED_ARRIERE_DROITE_PIN 33

#define LED_SENSOR_GAUCHE_PIN 31
#define LED_SENSOR_CENTRE_PIN 25
#define LED_SENSOR_DROITE_PIN 11

#define IR_SENSOR_GAUCHE_PIN 22
#define IR_SENSOR_CENTRE_PIN 24
#define IR_SENSOR_DROITE_PIN 26

#define MOTEUR_GAUCHE_SENS_PIN 46 // S = 0 <=> marche AVANT
#define MOTEUR_DROITE_SENS_PIN 45
#define MOTEUR_GAUCHE_VITS_PIN 44 // vitesse marche avant 70 à 250 de 150 à 10 en arrière
#define MOTEUR_DROITE_VITS_PIN 12

#define BUZZER_PIN 4
    

#ifdef MAQUETTE_VERSION
    
    #define US_SENSOR_GAUCHE_TRIG_PIN 30
    #define US_SENSOR_CENTRE_TRIG_PIN 21
    #define US_SENSOR_DROITE_TRIG_PIN 13
    #define US_SENSOR_GAUCHE_ECHO_PIN 28
    #define US_SENSOR_CENTRE_ECHO_PIN 23
    #define US_SENSOR_DROITE_ECHO_PIN 15
    
    #define LINESENSOR_DROITE_EXTERNE_PIN 6
    #define LINESENSOR_DROITE_MILIEUX_PIN 8
    #define LINESENSOR_DROITE_INTERNE_PIN 10
    
    #define LINESENSOR_GAUCHE_INTERNE_PIN 14
    #define LINESENSOR_GAUCHE_MILIEUX_PIN 16
    #define LINESENSOR_GAUCHE_EXTERNE_PIN 18
    
    // #define TLMTXPIN 19
    // #define TLMRXPIN 17
    #define TIMECYCLEMESU_PIN 19
    #define TAILLE_TRAME 16
    
#else
   
    #define US_SENSOR_GAUCHE_TRIG_PIN 30
    #define US_SENSOR_CENTRE_TRIG_PIN 13
    #define US_SENSOR_DROITE_TRIG_PIN 21
    #define US_SENSOR_GAUCHE_ECHO_PIN 28
    #define US_SENSOR_CENTRE_ECHO_PIN 15
    #define US_SENSOR_DROITE_ECHO_PIN 25
   
    // #define LINESENSOR_GAUCHE_EXTERNE_PIN 53
    // #define LINESENSOR_GAUCHE_MILIEUX_PIN 51
    // #define LINESENSOR_GAUCHE_INTERNE_PIN 49
    
    // #define LINESENSOR_DROITE_EXTERNE_PIN 52
    // #define LINESENSOR_DROITE_MILIEUX_PIN 50
    // #define LINESENSOR_DROITE_INTERNE_PIN 48   

#endif

#endif