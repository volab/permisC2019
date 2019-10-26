.. PermisC_2019 documentation master file, created by
   sphinx-quickstart on Sun Sep 15 00:07:13 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.
   

Infos générales sur le projet Permis C 2019
==============================================

   :Auteur:            `VoLAB <http://www.vorobotics.com/wp/>`_
   :Projet:             Permis C 2019
   :dépôt_GitHub:       https://github.com/volab/permisC2019.git
   :documentation:      https://volab.github.io/permisC2019/
   :page_wiki:          http://www.vorobotics.com/wiki/index.php?title=Nos_Projets#Robots
   :Licence:            CC BY-NC-SA 4.0
   :Liens:              https://creativecommons.org/licenses/by-nc-sa/4.0/ 

------------------------------------------------------------------------------------------

Documentation du projet
=============================

.. contents:: Table of Contents

.. section-numbering::



Présentation
=================
Il s'agit à la fois de décrire ici un atelier d'initiation à la programmation à destination
des collégiens et lycéens ansi que la conception d'un robot 2 roues conçu par le VoLAB spécialement
à cette occasion.

.. figure:: permisC2019_robotAppercu.jpg
   :width: 500 px
   :figwidth: 100%
   :alt: alternate text
   :align: center
   
   Le robot Permis C 2019
   
Caractéristiques du robot
========================================
- Capteurs: 3 capteurs ultra son SRF-04 à l'avant (détection 2cm à 3m), 3 capteurs infrarouge à l'arrière
- Motorisation : 2 moteurs à courant continu  200R / min 1:48 
- Driver moteur : L9110S
- Calculateur : Arduino 2560 Pro
- 1 buzer
- 7 LED
- Diamètre des roues : 65mm
- Dimension: 220x130x85mm 
- Masse: 450g sans les piles
- Alimentation: 6 piles AA

Assembler son Robot
====================

Voici les grandes étapes pour fabriquer notre robot.

#. Commander les 2 cartes électronique sur le site `EasyEda.com`_  (tips commandez les cartes
nues chez le partenaire d'EasyEDA à savoir Jlpcb qui est en liens directes depuis le site de EasyEDA)

#. commander les composants

#. souder les composants sur la carte principale et sur la carte capteur infrarouge

.. _`EasyEda.com` : https://easyeda.com


Les cartes électroniques
==========================
`Carte principale`_ et `Carte capteurs infrarouge`_

.. _`Carte principale` : https://easyeda.com/VoLab-Team/eduRobot

.. _`Carte capteurs infrarouge` : https://easyeda.com/VoLab-Team/eduRobotCarte2

.. figure:: images/cartePrincipale.jpg
   :width: 400 px
   :figwidth: 100%
   :align: center
   
   Fichier Gerber carte principale
   
.. figure:: images/pcbCarteIR.jpg
   :width: 300 px
   :figwidth: 100%
   :align: center
   
   Fichier Gerber carte capteurs infrarouges   


Liste des composants
===========================

`cliquez ici <liste_matos_190921_2203.html>`_

Souder les composants sur les cartes
======================================
On commencera par les composants les moins hauts (comme les résistances) pour terminer 
avec les composants les plus hauts comme les capteurs ultrasons

Attention le buzzer à un sens de montage qui ne figure pas sur la sérigraphie de la carte (un oubli)

.. figure:: images/sensBuzerDetail.png
   :width: 200 px
   :figwidth: 100%
   :align: center
   
   Sens de montage du buzer (tourné vers l'arrière)

Idem pour les connecteurs des piles.

.. figure:: images/buzerEtConnecteurPiles.jpg
   :width: 500 px
   :figwidth: 100%
   :align: center
   
   Sens des embase XH de piles

Préparer les connecteurs des blocs de piles (qui sont livrés sans connecteur).

Attention au sens des fils comme sur la photo ci-dessous

.. figure:: images/pinceEtBlocPile.jpg
   :width: 500 px
   :figwidth: 100%
   :align: center
   
   Pince et bloc de piles
   
.. figure:: images/detailConnecteur pile.jpg
   :width: 200 px
   :figwidth: 100%
   :align: center
   
   Détail connecteur pile   
   
et souder 15cm de fil noir et rouge sur les moteurs (le fil rouge à doite)

.. figure:: images/moteur.jpg
   :width: 300 px
   :figwidth: 100%
   :align: center
   
   Fils souder sur le moteur
   
Penser à étamer l'autre extrêmité de chaque fil cela facilitera l'insertion dans les connecteur à
vis de la carte L9110.

.. figure:: images/L9110.jpg
   :width: 200 px
   :figwidth: 100%
   :align: center
   
   Détail borniers de la carte L9110

Attention cette opération est délicate et les broches métalique de ces petits moteurs bon marcher 
sont fragile. Si vous ne le sentez pas poussez la porte d'un fablab près de chez vous,
il y aura certainement une bonne âme pour vous aider.

Ajout de dernière minute. Suite à nos essais, nous avons constaté qu'il convient d'ajouter un 
condensateur de filtrage sur l'alimentation des moteurs de 470uF/16V.

.. figure:: images/capaAjoutee.jpg
   :width: 200 px
   :figwidth: 100%
   :alt: Condesateur alimentation moteur
   :align: center
   
   Condensateur 470uF/16 sur l'alimentation moteur 

Montage mécanique
===================

Liste des outils nécessaires
+++++++++++++++++++++++++++++++++
- Tournevis crussiforme PH1
- clés 6 pans de 2, 2.5 et 3 mm
- clés plate de 5.5 et 7
- clé tube de 5.5 et 7
- tournevis plat plus petit que 3.5mm (lergeur de la lame)

Les étapes du montage
+++++++++++++++++++++++

#. monter les 4 colonnettes nylon sur le châssis
#. montage des moteurs (ne pas mettre les roues tout de suite)
#. monter les 3 blocs de piles
#. monter la carte capteur infrarouge à l'arrière avec sa chargnière (opération un peu délicate)
#. monter le bal caster en dessous (la bille)
#. monter la carte électronique principale
#. connecter les 3 boîtiers de piles à la carte principale
#. relier la carte capteurs infrarouge à la carte principale
#. insérer la carte ARDUINO dans son emplacement
#. connecter les moteur à la carte L9110 puis mettre celle-ci en place sur la carte principal
#. Oui vous pouvez mettre les roues !

.. figure:: images/emplacementcolonette.jpg
   :width: 500 px
   :figwidth: 100%
   :alt: emplacement colonettes
   :align: center
   
   Emplacement des 4 colonettes - trous filetés pas besoin d'écrou


.. figure:: images/charniereArriere.jpg
   :width: 500 px
   :figwidth: 100%
   :align: center
   
   Détail charnière arrière
   
.. figure:: images/detailEquerre.jpg
   :width: 200 px
   :figwidth: 100%
   :align: center
   
   Détail de la petite équerre.  

Attention les fils rouges des moteurs doivent être connecté en partant du centre de la L9110.
Attention également à bien connecter le moteur de droite à droite !   

.. |clearer|  raw:: html

    <div class="clearer"></div>

Programmer son robot
=========================
.. image:: images/logo_mblock5.jpg
   :scale: 20 %
   :align: right
   :target: https://www.makeblock.com/

La programmation du robot se fait grâce à MBlock de chez `MakeBlock`_

.. _`MakeBlock` : https://www.makeblock.com/

Et pour vous aider, Professeur Gilles ;-) nous a rédigé de jolies `fiches pédagogiques`_

.. _`fiches pédagogiques` :  https://github.com/volab/permisC2019/tree/master/_01-docs/_01-userDoc/fiches_peda_pcb_sansvariable/doc_peda_pcb_sansvariable_pdf

.. container::

    .. image:: images/capteur_ir.JPG
       :width: 100 %
       :scale: 70 %
       :align: left
       
|clearer|

Pour aller plus loin
======================
Si vous le désirer ce robot peut également être programmer en langage C, en Python... 
mais c'est une autre histoire...

Voici donc quelques liens :

Le site officiel `ARDUINO`_

Un bon tuto sur `OpenClassRoom`_

Fabrication d'un `Labyrinthe avec des cartons et des pièces imprimées en 3D`_

`Un générateur de labyrinthe`_

`Python dans une ATMega2560`_ pour les spécialistes

`Reduicing lobe of SRF-04`_

Autre capteur à ultrason SRF-02 en I2C



.. _`ARDUINO` : https://www.arduino.cc/

.. _`OpenClassRoom` : https://openclassrooms.com/fr/courses/2778161-programmez-vos-premiers-montages-avec-arduino

.. _`Labyrinthe avec des cartons et des pièces imprimées en 3D` : https://www.google.com/search?client=firefox-b-d&channel=crow&q=labirynthe

.. _`Un générateur de labyrinthe` : http://www.mazegenerator.net/

.. _`Python dans une ATMega2560` :  https://forum.arduino.cc/index.php?topic=7558.0

.. _`Reduicing lobe of SRF-04` : https://www.robot-electronics.co.uk/htm/reducing_sidelobes_of_srf10.htm

On pourra aussi envisager d'autres options comme des moustaches, un capteur pour suiveur de ligne...

Egalement l'option batterie 16850.


Weblinks
=============

.. target-notes::


