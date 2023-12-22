#include <iostream>
#include <conio.h> // Pour _getch()
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
//la taille de notre terrain
const int ROWS = 10;
const int COLS = 20;
//Cette �num�ration repr�sente les diff�rents types de cellules sur le terrain du jeu
enum Cell {
    EMPTY,//Cellule vide
    WALL,//mur
    DOT,//Point
    PACMAN,//aventurier
    GHOST,//monstre aveugle
    AMULET,//amulette
    MONSTER//monstre voyant
};

class Monstre {
public:
    Monstre(int X, int Y, bool estVoyant, int pointsVie, int pointsForce, double pourcentageHabilete)
        : posX(X), posY(Y), estVoyant_(estVoyant), pointsVie_(pointsVie),
          pointsForce_(pointsForce), pourcentageHabilete_(pourcentageHabilete) {}

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
            // Appliquer l'attaque � l'aventurier

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
        }
    }

    int getX() const {
        return posX;
    }

    int getY() const {
        return posY;
    }

private:
    int posX;
    int posY;
    bool estVoyant_;
    int pointsVie_;
    int pointsForce_;
    double pourcentageHabilete_;
 // G�n�rer al�atoirement une direction (vers le haut, le bas, la gauche, ou la droite)
    void deplacerMonstreAveugle(const Cell terrain[ROWS][COLS]) {
        int directionX, directionY;

        do {
            directionX = rand() % 3 - 1;// -1, 0, ou 1
            directionY = rand() % 3 - 1;
        } while (!isValidMove(posX + directionX, posY + directionY, terrain));
 // Si la nouvelle position est valide, d�placer le monstre
        posX += directionX;
        posY += directionY;
    }

    void deplacerMonstreVoyant(const int positionJoueurLigne, const int positionJoueurColonne, const Cell terrain[ROWS][COLS]) {
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

        if (isValidMove(posX + directionX, posY + directionY, terrain)) {
            posX += directionX;
            posY += directionY;
        }
    }
//la fonction renvoie true, indiquant que le d�placement vers la position sp�cifi�e est valide
    bool isValidMove(int row, int col, const Cell terrain[ROWS][COLS]) const {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && terrain[row][col] == EMPTY;
    }
};

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
                        std::cout << cellToChar(terrain[i - 1][j - 1]);/*Si aucun monstre n'est pr�sent � la position courante,
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
            case 'a': // Move up
                movePacmanTo(pacManRow - 1, pacManCol);
                break;
            case 'b': // Move down
                movePacmanTo(pacManRow + 1, pacManCol);
                break;
            case 'g': // Move left
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
            monstre.deplacerMonstre(pacmanRow, pacmanCol, terrain);
            monstre.attaquerAventurier(); // Appel de la fonction d'attaque du monstre
        }
    }

private:
    Cell terrain[ROWS][COLS];
    bool amuletCollected;
    std::vector<Monstre> monstres;
    int pacmanRow, pacmanCol; // Position d'avanturier

    void initialize() {
        // Remplir le terrain avec des murs et des cases vides altern�es
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i % 2 == 0 && j % 2 == 0) {
                    terrain[i][j] = WALL;//mur
                } else {
                    terrain[i][j] = EMPTY;//vide
                }
            }
        }

        // Placer avanturier au centre
        pacmanRow = ROWS / 2;
        pacmanCol = COLS / 2;
        terrain[pacmanRow][pacmanCol] = PACMAN;

        // Placer l'amulette
        int amuletRow = rand() % ROWS;
        int amuletCol = rand() % COLS;
        terrain[amuletRow][amuletCol] = AMULET;
        amuletCollected = false;

        // Ajouter des monstres
        monstres.push_back(Monstre(5, 5, false, 2, 5, 0.8));  // Monstre aveugle (position,point vie,point de force,habilit�)
        monstres.push_back(Monstre(8, 8, true, 1, 8, 0.8));   // Monstre voyant
    }

    void findPacman(int& row, int& col) const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (terrain[i][j] == PACMAN) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

    void movePacmanTo(int newRow, int newCol) {
        if (isValidMove(newRow, newCol)) {
            terrain[pacmanRow][pacmanCol] = EMPTY;//mise � jour de la case ou il est l'avanturier
            terrain[newRow][newCol] = PACMAN;//mise � jour de la case ou il va se deplac�

            // Si Pac-Man atteint l'amulette, la collecter
            if (terrain[newRow][newCol] == AMULET) {
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
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && terrain[row][col] != WALL;
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
            default:
                return '?';
        }
    }
};

int main() {
    PacManTerrain pacManTerrain;
    char moveDirection;

    std::cout << "Utilisez les touches a, b, g, d pour d�placer Pac-Man." << std::endl;

    while (!pacManTerrain.isAmuletCollected()) {
        // Capturer la touche du clavier sans attendre l'appui sur la touche "Entr�e"
        moveDirection = _getch();

        // D�placer Pac-Man en fonction de la touche captur�e
        pacManTerrain.movePacman(moveDirection);

        // Afficher le terrain apr�s chaque d�placement
        pacManTerrain.display();

        // Pause de 500 millisecondes entre chaque d�placement
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "F�licitations ! Pac-Man a r�cup�r� l'amulette." << std::endl;

    return 0;
}
