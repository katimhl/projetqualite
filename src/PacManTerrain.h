#ifndef PACMANTERRAIN_H
#define PACMANTERRAIN_H

//#include "constantes.h"
#include "Monstre.h"

class PacManTerrain {
public:
    PacManTerrain() {
        initialize();
    }

    void checkAttack(bool playerFirstAttack){
        for (auto& monstre : monstres) {
                if(!monstre.estVivant() && monstre.getX() == pacmanRow && monstre.getY() == pacmanCol){
                     if(playerFirstAttack) {
                                monstre.attaquerAventurier();
                                if(!monstre.estVivant()){
                                    playerDamage(monstre);
                                }
                        }else {
                                playerDamage(monstre);
                                  monstre.attaquerAventurier();
                                }

             // Appel de la fonction d'attaque du monstre}

        }
    }
    }



    void display() const {

        for (int i = 0; i < ROWS + 2; ++i) {//lignes du terrain
            for (int j = 0; j < COLS + 2; ++j) {//colonnes du terrain
                if ( amuletCollected && (i == exitRow+1 && j == exitCol+1)) {
                std::cout << "S";  // Place 'S' at the random exit position
            }
                  else
                    if (i == 0 || i == ROWS + 1 || j == 0 || j == COLS + 1) {
                    std::cout << "#";  // Utiliser des di�ses pour les contours

                } else {
                    bool isMonsterPresent = false;//si un monstre est pr�sent � la position courante du terrain
                    for (const auto& monstre : monstres) {
                        if ( !monstre.estVivant() && monstre.getX() == i - 1 && monstre.getY() == j - 1) {
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

       // if(pacmanCol == amu)
       for (auto& monstre : monstres) {
    monstre.afficherPointsDeVie();
}
afficherPointsDeVieJoueur();
    }

//Lorsque cette fonction est appel�e, cela signifie que avanturier(pac-man) a collect� l'amulette sur le terrain.
    void collectAmulet() {
        amuletCollected = true;
    }

    bool isAmuletCollected() const {//v�rifier si l'amulette a �t� collect�e
        return amuletCollected;
    }
    bool quitte() {
        if(terrain[pacmanRow][pacmanCol]== terrain[exitRow][ exitCol]){
            return true;
        }


    }
    bool isGameEnded() {
        return gameEnded;
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
                if(!monstre.estVivant()){
            monstre.deplacerMonstre(pacmanRow, pacmanCol, terrain);
            checkAttack(false);
           // monstre.attaquerAventurier(); // Appel de la fonction d'attaque du monstre}
        }
    }}

    void playerDamage(Monstre& monster) {
        pointsVieJoueur-= monster.getPointDeForce();
        if(pointsVieJoueur <= 0) {
             system("cls");
            std::cout<< "vous avez perdu";
            exit(0);
        }
    }

    Cell(*getTerrain())[COLS]  {

        return terrain;
    }

    int getVieJoueur()const{
        return pointsVieJoueur;
    }

private:
    Cell terrain[ROWS][COLS];
    bool amuletCollected;
    std::vector<Monstre> monstres;
    int pacmanRow, pacmanCol; // Position d'avanturier
    int amuletRow,amuletCol;
    bool sortieok;
    int exitRow ;
    int exitCol;
    bool gameEnded = false;
    int pointsVieJoueur;
public:
    void initialize() {
        // Remplir le terrain avec des murs et des cases vides altern�es
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Set walls and empty spaces
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i % 2 == 0 && j % 2 == 0) {
                terrain[i][j] = WALL; // mur
            } else {
                terrain[i][j] = EMPTY; // vide
            }
        }
    }

    // Place the exit in a random empty cell
    exitRow = rand() % ROWS;
    exitCol = rand() % COLS;
    while (terrain[exitRow][exitCol] == WALL)
    {
        exitRow = rand() % ROWS;
        exitCol = rand() % COLS;
    }

     //   terrain[exitRow][exitCol] = sortie;

        // Placer avanturier au centre
        pacmanRow = ROWS / 2;
        pacmanCol = COLS / 2;
        terrain[pacmanRow][pacmanCol] = PACMAN;

        // Placer l'amulette
        amuletRow = rand() % ROWS;
        amuletCol = rand() % COLS;
        terrain[amuletRow][amuletCol] = AMULET;
        amuletCollected = false;

        //placer sortie


      //  terrain[exitRow][ exitCol] = sortie;


        sortieok = false;


        // Ajouter des monstres
        monstres.push_back(Monstre(5, 5, false, 10, 5, 0.8));  // Monstre aveugle (position,point vie,point de force,habilit�)
        monstres.push_back(Monstre(8, 8, true, 10, 8, 0.8));   // Monstre voyant
        pointsVieJoueur = 20;

        }
         void afficherPointsDeVieJoueur() const {
        std::cout << "Points de vie du joueur : " << pointsVieJoueur << std::endl;
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
          /*  if (terrain[newRow][newCol] == AMULET) {
                collectAmulet();
                std::cout << "amullete collected ";
            }*/

            if (newRow == amuletRow && newCol == amuletCol) {
                collectAmulet();
                std::cout << "amullete collected "<<std::endl;

            }

            if( amuletCollected && newRow == exitRow && newCol == exitCol) {
                  system("cls");
                  std::cout<< "you won the game :)";
                  exit(0);
            }

            // Mettre � jour la position de Pac-Man
            pacmanRow = newRow;
            pacmanCol = newCol;
        }
         checkAttack(true);
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
              case SORTIE:
                return 's';
            default:
                return '?';
        }
    }
};


#endif //PACMANTERRAIN_H
