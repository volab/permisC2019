++++++++++++++++++++++++++++++++++++++++++++
Documentation du projet PermisC 2019
++++++++++++++++++++++++++++++++++++++++++++

.. image:: logoVoLAB_200x200.jpg

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
- Capteurs: 3 capteurs ultra son SRF-04 à l'avant, 3 capteur infrarouge à l'arrière
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

#. Commander les 2 cartes électronique sur le site easyEda.com

#. commander les composants

#. souder les composants sur la carte principale et sur la carte capteur infrarouge


Les cartes électroniques
==========================
`Carte principale`_ et `Carte capteurs infrarouge`_

.. _`Carte principale` : https://easyeda.com/VoLab-Team/eduRobot

.. _`Carte capteurs infrarouge` : https://easyeda.com/VoLab-Team/eduRobotCarte2

Liste des composants
===========================

`cliquez ici <liste_mato_190914_1930.html>`_

Souder les composants sur les cartes
======================================
On commencera par les composants les moins hauts (comme les résistances) pour terminer 
avec les composants les plus comme les capteurs ultrasons

Attention le buzzer à un sens de montage qui ne figure pas sur la sérigraphie de la carte (un oubli)




Montage mécanique
===================

Programmer son robot
=========================
La programmation du robot se fait grâce à MBlock de chez `MakeBlock`_ link_desc

.. _`MakeBlock` : https://www.makeblock.com/

Pour aller plus loin
======================
Si vous le désirer ce robot peut également être programmer en langage C, en Python... 
mais c'est une autre hostoire 

Quelques liens :

Le site officiel `ARDUINO`_

`Python dans une ATMega2560`_ pour les spécialiste

.. _`Python dans une ATMega2560` :  https://forum.arduino.cc/index.php?topic=7558.0

.. _`ARDUINO` : https://www.arduino.cc/

Weblinks
=============

.. target-notes::