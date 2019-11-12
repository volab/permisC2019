++++++++++++++++++++++++++++++++
Advanced stuf for robot Junior
++++++++++++++++++++++++++++++++

======================================
Suiveur de ligne
======================================

3 capteur IR de chaque côté


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
Télémètrie
======================================

Choix du module RF

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

Temps d'émission mesuré avec la technique de micros : 700us entre mon poste et l'autre extrêmité
du lab.

.. _`RF24 from TMRh20` : https://github.com/nRF24/RF24

.. _`modules NRF24RL01` :  https://www.amazon.fr/Pixnor-NRF24L01-%C3%A9metteurr%C3%A9cepteur-Arduino-Compatible/dp/B016BAM80C/ref=sr_1_4?ie=UTF8&qid=1451854927&sr=8-4&keywords=nrf24l01



RPM Mesure
======================================

140 à vide pouvant descendre jusqu'à 50 en charge mais une valeur raisonnable semble être 130 rpm.
Pour un PWM à 100

260 RPM full batterie et PWM à 250

109 RMP full batterie et pour PWM 70

109 rpm avec des roues de 66mm
Soit 1 tour 66x2xpimm = 415mm x 109 / 60 soit 753mm/s ou encore 0.753mm/ms
3.77mm / cycle de 5ms


Batterie pack
======================================

16850 batterie

Chargeur de batteries

Right angle gears
======================================
https://www.ebay.com/itm/2pcs-20T-8mm-Metal-Bevel-Gear-Right-Angle-Drive-Gears-Modulus-1-Model-DIY-/222581207784

https://www.ebay.com/itm/2-x-2M-20T-Metal-Umbrella-Tooth-Bevel-Gear-Helical-Motor-Gear-20-Tooth-12mm-Bore/141855562697?_trkparms=aid%3D1110001%26algo%3DSPLICE.SIM%26ao%3D2%26asc%3D20160323102634%26meid%3D991074a4f8944beaad360ae93151d930%26pid%3D100623%26rk%3D2%26rkt%3D6%26sd%3D222581207784%26itm%3D141855562697%26pmt%3D0%26noa%3D1%26pg%3D2047675&_trksid=p2047675.c100623.m-1

https://fr.aliexpress.com/item/32893975748.html?spm=a2g0o.detail.1000014.25.1d144ab8AF9t1d&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=ee114c4f-fb10-40a3-9845-00c21843e646

https://fr.aliexpress.com/item/32890058000.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=6459793138&albag=77316928277&trgt=743612850714&crea=fr32890058000&netw=u&device=c&gclid=CjwKCAiAwZTuBRAYEiwAcr67OWbm-ZBNal13bIS6i8peFqKkGNhEntVn4o-RMG5yH6TStwxBTqlUbRoCM6oQAvD_BwE&gclsrc=aw.ds

Chercher pignon conique.
5mm :

https://fr.aliexpress.com/item/33033437185.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=7475390357&albag=84967726950&trgt=296730740870&crea=fr33033437185&netw=u&device=c&gclid=CjwKCAiAwZTuBRAYEiwAcr67OetGz9NlAWIHocH2ge2abL36oHNavBjvfWA0sG9CU37Hhvrhns5EaRoCQPQQAvD_BwE&gclsrc=aw.ds

https://fr.aliexpress.com/item/32889357017.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=6459788344&albag=76234907246&trgt=743612850874&crea=fr32889357017&netw=u&device=c&gclid=CjwKCAiAwZTuBRAYEiwAcr67ORa5HqUrbmbm7HR9KMinD4LwghugNZx6NpOdj7z_g_jY4a1msZioURoCiNwQAvD_BwE&gclsrc=aw.ds

https://fr.aliexpress.com/item/32689486596.html

Cher mais bien :
https://www.robotshop.com/ca/fr/ensemble-engrenage-conique-21-moyeux-6mm-1-4-servocity.html

Right angle motors
======================================
Banggood : `GW4058-31ZY - 12V`_ 
Moteur de boîte de vitesse d'engrenage à vis sans fin de moteur de réduction du moteur CC 12V 110rpm à double arbre

.. _`GW4058-31ZY - 12V` :  https://fr.banggood.com/GW4058-31ZY-Double-Shaft-DC-Motor-12V24V-110rpm220rpm-Reduction-Motor-Worm-Gear-Gear-Box-Motor-p-1357185.html?rmmds=search&ID=520831&cur_warehouse=CN




=========
Weblinks
=========

.. target-notes::