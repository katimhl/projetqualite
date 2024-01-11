#pragma once

#include "constantes.h"
#include "joueur.h"

class Monstre {
public:
    Monstre(int X, int Y, bool estVoyant, int pointsVie, int pointsForce, double pourcentageHabilete)
        : posX(X), posY(Y), estVoyant_(estVoyant), pointsVie_(pointsVie),
          pointsForce_(pointsForce), pourcentageHabilete_(pourcentageHabilete) {}

    void deplacerMonstre(const int positionJoueurLigne, const int positionJoueurColonne, terrain t) {
        if (estVoyant_) {
            deplacerMonstreVoyant(positionJoueurLigne, positionJoueurColonne, t);
        } else {
            deplacerMonstreAveugle(t);
        }
    }

    void attaquerAventurier(joueur& j) {
        double probabiliteAttaque = (rand() % 100) / 100.0;
        if (probabiliteAttaque < pourcentageHabilete_) {
            int attaque = static_cast<int>(pointsForce_ * 0.9);
            // Appliquer l'attaque � l'aventurier
            j.perd_vie(attaque);
        }
    }

    int getPointsVie() const {
        return pointsVie_;
    }

    int setPointsVie(int pV) {
        pointsVie_ = pV;
    }

    void recevoirAttaque(int pointsForce) {
        // Absorber tous les points de force
        pointsVie_ -= pointsForce;
        if (pointsVie_ < 0) {
            pointsVie_ = 0;
        }
    }

    int getX() const {
        return posX;
    }

    int getY() const {
        return posY;
    }

    // G�n�rer al�atoirement une direction (vers le haut, le bas, la gauche, ou la droite)
    void deplacerMonstreAveugle(terrain t) {
        int directionX, directionY;

        do {
            directionX = rand() % 3 - 1;// -1, 0, ou 1
            directionY = rand() % 3 - 1;
        } while (!isValidMove(posX + directionX, posY + directionY, t));
 // Si la nouvelle position est valide, d�placer le monstre
        posX += directionX;
        posY += directionY;
    }

    void deplacerMonstreVoyant(const int positionJoueurLigne, const int positionJoueurColonne, terrain t) {
        int directionX = 0; // D�clare deux variables pour stocker les composantes X et Y de la direction dans laquelle le monstre va se d�placer
        int directionY = 0;

        // Calculer la direction vers le joueur
        if (posX < positionJoueurLigne) {
            directionX = 1;//Si la position X du monstre est inf�rieure � la position X du joueur, le monstre se d�place vers la droite (directionX = 1).
        } else if (posX > positionJoueurLigne) {
            directionX = -1;
        }

        if (posY < positionJoueurColonne) {
            directionY = 1;
        } else if (posY > positionJoueurColonne) {
            directionY = -1;
        }

        // monstre se d�placer vers le joueur s'il y a une case vide en ajoutant la direction � ses coordonn�es actuelles

        if (isValidMove(posX + directionX, posY + directionY, t)) {
            posX += directionX;
            posY += directionY;
        }
    }
//la fonction renvoie true, indiquant que le d�placement vers la position sp�cifi�e est valide
    bool isValidMove(int row, int col, terrain t) const {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && t[row][col] == EMPTY;
    }

private:
    int posX;
    int posY;
    bool estVoyant_;
    int pointsVie_;
    int pointsForce_;
    double pourcentageHabilete_;
 
};
