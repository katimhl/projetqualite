#pragma once

//#include "constantes.h"
#include "Monstre.h"

class PacManTerrain {
public:
    PacManTerrain() {
        initialize();
    }

    void display() const {
        for (int i = 0; i < ROWS + 2; ++i) {//lignes du terrain
            for (int j = 0; j < COLS + 2; ++j) {//colonnes du terrain
                if (i == 0 || i == ROWS + 1 || j == 0 || j == COLS + 1) {
                    std::cout << "#";  // Utiliser des di�ses pour les contours
                } else {
                    bool isMonsterPresent = false;//si un monstre est pr�sent � la position courante du terrain
                    for (const auto& monstre : monstres) {
                        if (monstre.getX() == i - 1 && monstre.getY() == j - 1) {
                            std::cout << "M";//affiche "M" pour repr�senter le monstre
                            isMonsterPresent = true;
                            break;
                        }
                    }

                    if (!isMonsterPresent) {
                        std::cout << cellToChar(t[i - 1][j - 1]);/*Si aucun monstre n'est pr�sent � la position courante,
                                                                      cette partie affiche le caract�re correspond*/
                    }
                }
            }
            std::cout << std::endl;//passer ligne suivante
        }
    }
//Lorsque cette fonction est appel�e, cela signifie que avanturier(pac-man) a collect� l'amulette sur le terrain.
    void collectAmulet() {
        amuletCollected = true;
    }

    bool isAmuletCollected() const {//v�rifier si l'amulette a �t� collect�e
        return amuletCollected;
    }

    void movePacman(char direction) {
        int pacManRow, pacManCol;
        findPacman(pacManRow, pacManCol);

        switch (direction) {
            case 'z': // Move up
                movePacmanTo(pacManRow - 1, pacManCol);
                break;
            case 's': // Move down
                movePacmanTo(pacManRow + 1, pacManCol);
                break;
            case 'q': // Move left
                movePacmanTo(pacManRow, pacManCol - 1);
                break;
            case 'd': // Move right
                movePacmanTo(pacManRow, pacManCol + 1);
                break;
        }
    }
    /*d�place le monstre en fonction de sa logique de d�placement,
    en prenant la position actuelle du joueur (pacmanRow et pacmanCol)
    et le terrain actuel comme param�tres.*/
    void moveMonsters() {
        for (auto& monstre : monstres) {
            monstre.deplacerMonstre(pacmanRow, pacmanCol, t);
            monstre.attaquerAventurier(p1); // Appel de la fonction d'attaque du monstre
        }
    }

    auto getTerrain(){
        return t;
    }

    void initialize() {
        // Remplir le terrain avec des murs et des cases vides altern�es
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i % 2 == 0 && j % 2 == 0) {
                    t[i][j] = WALL;//mur
                } else {
                    t[i][j] = EMPTY;//vide
                }
            }
        }

        // Placer avanturier au centre
        pacmanRow = ROWS / 2;
        pacmanCol = COLS / 2;
        t[pacmanRow][pacmanCol] = PACMAN;

        // Placer l'amulette
        int amuletRow = rand() % ROWS;
        int amuletCol = rand() % COLS;
        t[amuletRow][amuletCol] = AMULET;
        amuletCollected = false;

        placerPieces();

        // Ajouter des monstres
        monstres.push_back(Monstre(5, 5, false, 2, 5, 0.8));  // Monstre aveugle (position,point vie,point de force,habilit�)
        monstres.push_back(Monstre(8, 8, true, 1, 8, 0.8));   // Monstre voyant
    }

    void placerPieces(){
        int coinsRow = rand() % ROWS;
        int coinsCol = rand() % COLS;
        t[coinsRow][coinsCol] = COINS;
    }

    void findPacman(int& row, int& col) const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (t[i][j] == PACMAN) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

    void movePacmanTo(int newRow, int newCol) {
        if (isValidMove(newRow, newCol)) {
            t[pacmanRow][pacmanCol] = EMPTY;//mise � jour de la case ou il est l'avanturier
            t[newRow][newCol] = PACMAN;//mise � jour de la case ou il va se deplac�

            // Si Pac-Man atteint l'amulette, la collecter
            if (t[newRow][newCol] == AMULET) {
                collectAmulet();
            }

            // Mettre � jour la position de Pac-Man
            pacmanRow = newRow;
            pacmanCol = newCol;
        }

        // D�placer les monstres apr�s le d�placement de Pac-Man
        moveMonsters();
    }

    bool isValidMove(int row, int col) const {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && t[row][col] != WALL;
    }

    char cellToChar(Cell cell) const {
        switch (cell) {
            case EMPTY:
                return ' ';
            case WALL:
                return '-';
            case DOT:
                return '.';
            case PACMAN:
                return 'P';
            case GHOST:
                return 'M';
            case AMULET:
                return '%';
            case MONSTER:
                return 'M';
            case COINS:
                return '€';
            default:
                return '?';
        }
    }

private:
    terrain t;
    bool amuletCollected;
    std::vector<Monstre> monstres;
    joueur p1;
    int pacmanRow, pacmanCol; // Position d'avanturier
};
