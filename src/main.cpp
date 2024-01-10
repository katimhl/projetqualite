#include <iostream>
#include <conio.h> // Pour _getch()
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
//#include "constantes.h"
#include "Monstre.h"
#include "PacManTerrain.h"

int main() {
    PacManTerrain pacManTerrain;
    char moveDirection;

    std::cout << "Utilisez les touches z, q, s, d pour deplacer Pac-Man." << std::endl;

    while (!pacManTerrain.isAmuletCollected()) {
        //nettoye la console avant de réécrir
        system("cls");

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
