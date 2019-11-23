++++++++++++++++++++++++++++++++
Advanced stuf for robot Junior
++++++++++++++++++++++++++++++++

======================================
Suiveur de ligne
======================================

3 capteurs IR de chaque côté


Ajout d'un connecteur 8 points.

+-------+------------+-------------+
| Pin   | Signal     | Arduino pin |
+=======+============+=============+
| 1     | GND        |   -         |
+-------+------------+-------------+
| 2     | D EXT      |   6         |
+-------+------------+-------------+
| 3     | D MID      |   8         |
+-------+------------+-------------+
| 4     | D INT      |   10        |
+-------+------------+-------------+
| 5     | G INT      |   14        |
+-------+------------+-------------+
| 6     | G MID      |   16        |
+-------+------------+-------------+
| 7     | G EXT      |   18        |
+-------+------------+-------------+
| 8     | P5V        |   -         |
+-------+------------+-------------+

======================================
Télémètrie / RF transmissions
======================================

Besoin  débit 
======================================
Exemple:

On part sur 32 octets soit 320bits en moins de 1ms à transmettre

1 bits (1/320)ms = 3.215 10-6 environ 312kbits/s

Trame: (séparateur ,)

Sensor gauche (1c),Sensor droit (1c),Vbat(3c),reserve (3c) soit 11 octets

Exemple:

4,0,3.2,0.0

11 octets trasmis en 1ms (max)

10-3/110 = 9us/bits soit 110kbits/s


Choix du module RF 
======================================

Très bonne vidéo youtube:  `Electronoobs`_

.. _`Electronoobs` : https://www.youtube.com/watch?v=vxF1N9asjts

433MHz low cost modules
======================================
Utilisation de module 433MHz solution rapidement abandonnée porté insufisante au travers des murs.

.. figure:: images/moduleRF.jpg
   :width: 200 px
   :figwidth: 100%
   :alt: Modules RF 433MHz
   :align: left
   
   Modules RF 433MHz

Deux fils de 173mm de long pour les antennes des modules radio.

Communiquer sans fil en 433MHz avec la bibliothèque VirtualWire et une carte Arduino / Genuino sur
`les carnets du maker`_

Très bon article sur `DroneBot Workshop`_

`Radiohead library`_

 

.. _`les carnets du maker` : https://www.carnetdumaker.net/articles/communiquer-sans-fil-en-433mhz-avec-la-bibliotheque-virtualwire-et-une-carte-arduino-genuino/

.. _`Radiohead library` : https://www.airspayce.com/mikem/arduino/RadioHead/

.. _`DroneBot Workshop` : https://dronebotworkshop.com/433mhz-rf-modules-arduino/

ACP220 modules 
======================================
On a pas réussi à les faire fonctionner

Nous avons réussi à les faire communiquer avec le logiciel prévu pour les paramètrer: RF-Magic

A condition de lancer le logiciel en mode admi (sous W7) et de changer le nom du port COM 
pour un nom ne comportant qu'un seul digit de COM37 vers COM2 par exemple.

Essais à 433MHz, 470, 434 avec les même id node et des id différents. sans aucun succès.

Module récupérer il y a quelques année impossible de dire s'ils était fonctionnels.

NF24 
======================================
Utilisation de la librairie : `RF24 from TMRh20`_ disponible sur github mais aussi directement 
dans le gestionnaire de librairie ARDUINO. Librairie très bien renseignée avec une documentation
très complète sous Doxygen.

Les `modules NRF24RL01`_ utilsés proviennent de chez Amazon.

.. figure:: images/NRF24modules_.jpg
   :width: 300 px
   :figwidth: 100%
   :alt: NRF24L01 modules
   :align: left
   
   NRF24L01 modules

.. figure:: images/NRF24pinout.png
   :width: 300 px
   :figwidth: 100%
   :alt: NRF24L01 modules
   :align: left
   
   NRD24L01 pinout


Réussite. Transfert de 4 puis 8 octets à 2Mbps.

Le temps total d'aller et retour est d'environ 1.4ms. Utilisation du sketch exemple GettingStarted.ino
Léèrement modifié.

.. code:: cpp

    
    /*
    * Getting Started example sketch for nRF24L01+ radios
    * This is a very basic example of how to send data from one node to another
    * Updated: Dec 2014 by TMRh20
    */
    
    #include <SPI.h>
    #include "RF24.h"
    
    /****************** User Config ***************************/
    /***      Set this radio as radio number 0 or 1         ***/
    bool radioNumber = 1;
    
    /* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
    RF24 radio(7,8);
    /**********************************************************/
    
    byte addresses[][6] = {"Node1","Node2"};
    
    // Used to control whether this node is sending or receiving
    bool role = 0;
    unsigned long cpt = 0;
    void setup() {
      Serial.begin(115200);
      Serial.println(F("RF24/examples/GettingStarted"));
      Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
      
      radio.begin();
    
      // Set the PA Level low to prevent power supply related issues since this is a
     // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
      radio.setPALevel(RF24_PA_MAX);
      if( radio.setDataRate( RF24_2MBPS ) ) Serial.println("speed is now 2Mbps");
    
      
      // Open a writing and reading pipe on each radio, with opposite addresses
      if(radioNumber){
        radio.openWritingPipe(addresses[1]);
        radio.openReadingPipe(1,addresses[0]);
        Serial.print("Je suis le node : ");Serial.println( (char *)addresses[1] );
      }else{
        radio.openWritingPipe(addresses[0]);
        radio.openReadingPipe(1,addresses[1]);
        Serial.print("Je suis le node : ");Serial.println( (char *)addresses[0] );
      }
      if ( !radio.isChipConnected() ){
          Serial.println(" Pb connection ! Aborted.");
          for(;;);
      } else {
          Serial.println( "appreil bien connecte.");
          // for(;;);
      }  
      Serial.print("pa level : "); Serial.println( radio.getPALevel() );
      Serial.print("Payloadsize : ");Serial.println( radio.getPayloadSize() );
      
      // Start the radio listening for data
      radio.startListening();
    }
    
    void loop() {
      
      
    /****************** Ping Out Role ***************************/  
    if (role == 1)  {
        Serial.println("TX role");
        radio.stopListening();                                    // First, stop listening so we can talk.
        
        
        Serial.println(F("Now sending"));
    
        // unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
        unsigned long start_time[2];
        start_time[0]= micros();                             // Take the time, and send it.  This will block until complete
        start_time[1]= millis();
         if (!radio.write( start_time, 2*sizeof(unsigned long) )){
           Serial.println(F("failed"));
         }
            
        radio.startListening();                                    // Now, continue listening
        
        unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
        boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
        
        while ( ! radio.available() ){                             // While nothing is received
          if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
              timeout = true;
              break;
          }      
        }
            
        if ( timeout ){                                             // Describe the results
            Serial.println(F("Failed, response timed out."));
        }else{
            unsigned long got_time[2];                                 // Grab the response, compare, and send to debugging spew
            radio.read( got_time, 2*sizeof(unsigned long) );
            unsigned long end_time = micros();
            
            // Spew it
            Serial.print(F("Sent "));
            Serial.print(start_time[0]);
            Serial.print(start_time[1]);
            Serial.print(F(", Got response "));
            Serial.print(got_time[0]);
            Serial.print(got_time[1]);
            Serial.print(F(", Round-trip delay "));
            Serial.print(end_time-start_time[0]);
            Serial.println(F(" microseconds"));
        }
    
        // Try again 1s later
        delay(1000);
      }
    
    
    
    /****************** Pong Back Role ***************************/
    
    if ( role == 0 ){
        // unsigned long got_time;
        unsigned long got_time[2];
        // Serial.print("Role peroquet.");
        // Serial.println( cpt++);
        if( radio.available()){
            // Variable for the received timestamp
            while (radio.available()) {                                   // While there is data ready
                radio.read( got_time, 2*sizeof(unsigned long) );             // Get the payload
            }
            
            radio.stopListening();                                        // First, stop listening so we can talk   
            radio.write( got_time, 2*sizeof(unsigned long) );              // Send the final one back.      
            radio.startListening();                                       // Now, resume listening so we catch the next packets.     
            // Serial.print(F("Sent response "));
            // Serial.println(got_time);  
        }
    }
    
    
    
    
    /****************** Change Roles via Serial Commands ***************************/
    
      if ( Serial.available() )
      {
        char c = toupper(Serial.read());
        if ( c == 'T' && role == 0 ){      
          Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
          role = 1;                  // Become the primary transmitter (ping out)
        
       }else
        if ( c == 'R' && role == 1 ){
          Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
           role = 0;                // Become the primary receiver (pong back)
           radio.startListening();
           
        }
      }
    
    
    } // Loop


La doc de la méthode write, nous apprend que c'est une méthode bloquante et que la pyload est fixe.

La méthode getPayloadSize() renvoi 32. donc que nous transmettion 8 ou 32 octets le temps sera 
identique !

On atteind facilement les extrémité du lab en conservant 1.5ms.

.. WARNING::
    Les broche 7 et 8 étaient inversée.
    
.. code:: cpp

    /**
   * Arduino Constructor
   *
   * Creates a new instance of this driver.  Before using, you create an instance
   * and send in the unique pins that this chip is connected to.
   *
   * @param _cepin The pin attached to Chip Enable on the RF module
   * @param _cspin The pin attached to Chip Select
   */
    RF24(uint16_t _cepin, uint16_t _cspin);

Temps d'émission mesuré avec la technique de micros : 700us entre mon poste et l'autre extrêmité
du lab.

.. _`RF24 from TMRh20` : https://github.com/nRF24/RF24

.. _`modules NRF24RL01` :  https://www.amazon.fr/Pixnor-NRF24L01-%C3%A9metteurr%C3%A9cepteur-Arduino-Compatible/dp/B016BAM80C/ref=sr_1_4?ie=UTF8&qid=1451854927&sr=8-4&keywords=nrf24l01


Autres solutions à explorer
======================================
XBEE : product line sur protocole ZigBee

Diffcile à approvisionner sur le marcher chinois et relativement honéreux.

Dispo `XBEE chez MOUSER`_ à 18€ sans antenne sachant qu'il en faut au moins 2

Préférer les modules en 2.4GHz à mon avis (pifométrique)

LORA

BLE4.0

Modules `BLE sur AMAZON`_ à 9.99€ pièce

Modules `BLE sur aliExpress`_ à 2.33€ basé sur un CC2541 de TI

`Exemple ARDUINO`_

`BLE5.0 sur AMAZON`_ 9.99€ basé sur un CC2640R2F de TI

`DSD Tech`_ official website


.. _`XBEE chez MOUSER` : https://www.mouser.fr/ProductDetail/Digi-International/XB3-24Z8PT-J?qs=sGAEpiMZZMve4%2FbfQkoj%252BHnv3ft0YYh1ZelV1uOq7SE%3D

.. _`BLE sur AMAZON` : https://www.amazon.com/DSD-TECH-Bluetooth-iBeacon-Arduino/dp/B06WGZB2N4/ref=sr_1_10?keywords=BLE&qid=1573809341&s=electronics&sr=1-10

.. _`BLE sur aliExpress` : https://fr.aliexpress.com/item/32672670920.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=6459793138&albag=77316928277&trgt=743612850714&crea=fr32672670920&netw=u&device=c&gclid=Cj0KCQiAtrnuBRDXARIsABiN-7C4xnJh8vQRrAfhBURZXjxJaNliTPFUQSnPELZ7C6L5TvKNkYxi3nsaAoWlEALw_wcB&gclsrc=aw.ds

.. _`Exemple ARDUINO` : https://www.electroschematics.com/getting-started-with-ble-and-arduino/


.. _`BLE5.0 sur AMAZON` : https://www.amazon.com/DSD-TECH-Bluetooth-CC2640R2F-Arduino/dp/B07MBLVHH8/ref=sr_1_17?keywords=BLE&qid=1573809341&s=electronics&sr=1-17 

.. _`DSD Tech` : http://www.dsdtech-global.com/2019/01/dsdtech-sh-11-ble.html 

======================================
RPM Mesure
======================================

140 à vide pouvant descendre jusqu'à 50 en charge mais une valeur raisonnable semble être 130 rpm.
Pour un PWM à 100

260 RPM full batterie et PWM à 250

109 RMP full batterie et pour PWM 70

109 rpm avec des roues de 66mm
Soit 1 tour 66x2xpimm = 415mm x 109 / 60 soit 753mm/s ou encore 0.753mm/ms
3.77mm / cycle de 5ms


================================
Mesure de temps de cycle
================================
Mesure du temps nécessaire pour exécuter la mise à jour des pwm moteur 

méthode : void CRobotJunior::update()

Branche devJojo_sans_OptiVersionAvecTlmNRF24, commit : 53488c

Temps mesuré à l'oscilloscope 69us (y compris les 2 digitalWrite qui prennet chacun environ 9us)

Plus grâve est le temps de répétition qui vaut une vingtaine de ms très instable. Cause identifiée :
les capteurs ultrason et leur timeout à 30ms utilisant la fonction pulse bloquante.

une solution élégante serait de fixer le timeout à 2900us soit 50cm.

En désactivant tout, le temps de cyle est à 5ms/+1.4ms : ce jitter de 1.4ms est inexplicable et persiste
même en aillant désactivé tous les update de la méthode robot.update(). Un début d'explication serait
dans l'implémentation de la foinction millis elle-même voir sur le `forum ARDUINO`_

.. _`forum ARDUINO` :  : https://forum.arduino.cc/index.php?topic=46351.0


======================================
Batterie pack
======================================

16850 batterie

Chargeur de batteries

======================================
Right angle gears
======================================
`2 pignons 20 dents axe 8mm sur ebay`_ 3.95USD

`2 pignons 20 dents axe 12mm sur ebay`_ 16.49USD

`1 pignon + 1 roue pas hélicoïdal`_ axe 6mm et 12mm sur ebay 2,9€ 

`2 pignon axe à choisir de 6 à 15mm 16 ou 20 dents`_ 8.8€ en 16 dents sur ebay

 

.. _`2 pignons 20 dents axe 8mm sur ebay` : https://www.ebay.com/itm/2pcs-20T-8mm-Metal-Bevel-Gear-Right-Angle-Drive-Gears-Modulus-1-Model-DIY-/222581207784

.. _`2 pignons 20 dents axe 12mm sur ebay` : https://www.ebay.com/itm/2-x-2M-20T-Metal-Umbrella-Tooth-Bevel-Gear-Helical-Motor-Gear-20-Tooth-12mm-Bore/141855562697?_trkparms=aid%3D1110001%26algo%3DSPLICE.SIM%26ao%3D2%26asc%3D20160323102634%26meid%3D991074a4f8944beaad360ae93151d930%26pid%3D100623%26rk%3D2%26rkt%3D6%26sd%3D222581207784%26itm%3D141855562697%26pmt%3D0%26noa%3D1%26pg%3D2047675&_trksid=p2047675.c100623.m-1

.. _`1 pignon + 1 roue pas hélicoïdal` :  https://fr.aliexpress.com/item/32893975748.html?spm=a2g0o.detail.1000014.25.1d144ab8AF9t1d&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=ee114c4f-fb10-40a3-9845-00c21843e646

.. _`2 pignon axe à choisir de 6 à 15mm 16 ou 20 dents` : https://fr.aliexpress.com/item/32890058000.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=6459793138&albag=77316928277&trgt=743612850714&crea=fr32890058000&netw=u&device=c&gclid=CjwKCAiAwZTuBRAYEiwAcr67OWbm-ZBNal13bIS6i8peFqKkGNhEntVn4o-RMG5yH6TStwxBTqlUbRoCM6oQAvD_BwE&gclsrc=aw.ds

Chercher dans Google pignon conique 5mm :

Sur Aliexpress:

`2 pcs, 20T 5, 6 ou 8mm`_ 3.13€ ! + 4.06€ de FdP

`2 pcs 0.5M 30T engrenage conique alésage 5mm en laiton`_ 10.87€ + 6.62fdp

.. _`2 pcs, 20T 5, 6 ou 8mm` :  https://fr.aliexpress.com/item/33033437185.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=7475390357&albag=84967726950&trgt=296730740870&crea=fr33033437185&netw=u&device=c&gclid=CjwKCAiAwZTuBRAYEiwAcr67OetGz9NlAWIHocH2ge2abL36oHNavBjvfWA0sG9CU37Hhvrhns5EaRoCQPQQAvD_BwE&gclsrc=aw.ds

.. _`2 pcs 0.5M 30T engrenage conique alésage 5mm en laiton` : https://fr.aliexpress.com/item/32689486596.html

Cher mais bien :

`Ensemble d'Engrenage Conique 2:1 (Moyeux de 6mm et 1/4")`_ 26.30€ + FdP ????

.. figure:: images/engrenage90inverse.jpg
   :width: 300 px
   :figwidth: 100%
   :alt: Engrenage Roboshop
   :align: center
   
   Engrenage Roboshop

.. _`Ensemble d'Engrenage Conique 2:1 (Moyeux de 6mm et 1/4")` :  https://www.robotshop.com/ca/fr/ensemble-engrenage-conique-21-moyeux-6mm-1-4-servocity.html

======================================
Right angle motors
======================================
Banggood : `GW4058-31ZY - 12V`_ 
Moteur de boîte de vitesse d'engrenage à vis sans fin de moteur de réduction du moteur CC 12V 110rpm
à double arbre.
 
 .. figure:: images/moteur90Banggood.jpg
   :width: 300 px
   :figwidth: 100%
   :alt: Moteur 90° 110rpm Banggood
   :align: center
   
   Moteur 90° 110rpm Banggood

.. _`GW4058-31ZY - 12V` :  https://fr.banggood.com/GW4058-31ZY-Double-Shaft-DC-Motor-12V24V-110rpm220rpm-Reduction-Motor-Worm-Gear-Gear-Box-Motor-p-1357185.html?rmmds=search&ID=520831&cur_warehouse=CN




=========
Weblinks
=========

.. target-notes::