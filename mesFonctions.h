/*====================================
AUTEUR : Prof. Techniques de l'informatique
PROJET : General - inclut dans Jeu de Battleship
NOM DU FICHIER : mesFonctions.h
DATE : 2026-03-11
BASEE SUR : TP1 Programmation Oriente Objet
DESCRIPTION : fonctions pour consoles multi-plateformes
====================================*/
#pragma once

#include <iostream>
#include "point.h" // Ajoutez vos fichiers "point.h" et "point.cpp" développés dans un laboratoire précédent

/********************************/
/* NE MODIFIEZ PAS CE FICHIER ! */
/* IL EST DÉJÀ COMPLET !        */
/********************************/
void sleepMs(int ms);
Point getMouseClick();
void ignoreMouseClicks();
void clearScreen(std::ostream& output);

void debugMessage(std::string str, bool terminale, int exitcode);

void criticMessage(std::string str, int exitcode);

void conPause(bool bDisplaymessage, int timeout);
