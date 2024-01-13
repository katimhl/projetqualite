#ifndef MONSTRE_H
#define MONSTRE_H

#include "constantes.h"
#include "joueur.h"

class Monstre {
public:
    Monstre(int X, int Y, bool estVoyant, int pointsVie, int pointsForce, double pourcentageHabilete)
        : posX(X), posY(Y), estVoyant_(estVoyant), pointsVie_(pointsVie),
          pointsForce_(pointsForce), pourcentageHabilete_(pourcentageHabilete), estMort_(false) {}

    void deplacerMonstre(const int positionJoueurLigne, const int positionJoueurColonne, const Cell terrain[ROWS][COLS]) {
        if (estVoyant_) {
            deplacerMonstreVoyant(positionJoueurLigne, positionJoueurColonne, terrain);
        } else {
            deplacerMonstreAveugle(terrain);
        }
    }

    void attaquerAventurier() {
        double probabiliteAttaque = (rand() % 100) / 100.0;
        if (probabiliteAttaque < pourcentageHabilete_) {
            int attaque = static_cast<int>(pointsForce_ * 0.9);
            // Appliquer l'attaque à l'aventurier
             recevoirAttaque(attaque);

        }
    }

    int getPointsVie() const {
        return pointsVie_;
    }

    void recevoirAttaque(int pointsForce) {
        // Absorber tous les points de force
        pointsVie_ -= pointsForce;
        if (pointsVie_ < 0) {
            pointsVie_ = 0;
            estMort_ = true; // Utiliser estMort_ pour référencer le membre de la classe
        std::cout << "Monstre a été vaincu !" << std::endl;
        }
        std::cout << "Monstre a reçu une attaque ! Points de vie restants : " << pointsVie_ << std::endl;}


    void afficherPointsDeVie() const {
    std::cout << "Points de vie du monstre : " << pointsVie_ << std::endl;
}


    int getX() const {
        return posX;
    }

    int getY() const {
        return posY;
    }

    bool estVivant() const  {
        return estMort_;
    }

private:
    int posX;
    int posY;
    bool estVoyant_;
    int pointsVie_;
    int pointsForce_;
    double pourcentageHabilete_;
    bool estMort_;
public:
 // Générer aléatoirement une direction (vers le haut, le bas, la gauche, ou la droite)
    void deplacerMonstreAveugle(const Cell terrain[ROWS][COLS]) {
        int directionX, directionY;

        do {
            directionX = rand() % 3 - 1;// -1, 0, ou 1
            directionY = rand() % 3 - 1;
        } while (!isValidMove(posX + directionX, posY + directionY, terrain));
 // Si la nouvelle position est valide, déplacer le monstre
        posX += directionX;
        posY += directionY;
    }

    void deplacerMonstreVoyant(const int positionJoueurLigne, const int positionJoueurColonne, const Cell terrain[ROWS][COLS]) {
        int directionX = 0; // Déclare deux variables pour stocker les composantes X et Y de la direction dans laquelle le monstre va se déplacer
        int directionY = 0;

        // Calculer la direction vers le joueur
        if (posX < positionJoueurLigne) {
            directionX = 1;//Si la position X du monstre est inférieure à la position X du joueur, le monstre se déplace vers la droite (directionX = 1).
        } else if (posX > positionJoueurLigne) {
            directionX = -1;
        }

        if (posY < positionJoueurColonne) {
            directionY = 1;
        } else if (posY > positionJoueurColonne) {
            directionY = -1;
        }

        // monstre se déplacer vers le joueur s'il y a une case vide en ajoutant la direction à ses coordonnées actuelles

        if (isValidMove(posX + directionX, posY + directionY, terrain)) {
            posX += directionX;
            posY += directionY;
        }
    }
//la fonction renvoie true, indiquant que le déplacement vers la position spécifiée est valide
    bool isValidMove(int row, int col, const Cell terrain[ROWS][COLS]) const {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && terrain[row][col] == EMPTY;
    }
};

#endif