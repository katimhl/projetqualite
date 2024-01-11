#include <iostream>
#include <conio.h> // Pour _getch()
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "constantes.h"
#include "Monstre.h"
#include "PacManTerrain.h"

int main() {
    PacManTerrain terrain;
    char moveDirection;

    std::cout << "Utilisez les touches z, q, s, d pour deplacer Pac-Man." << std::endl;

    while (!terrain.isAmuletCollected()) {
        // Capturer la touche du clavier sans attendre l'appui sur la touche "Entr�e"
        moveDirection = _getch();
        // D�placer Pac-Man en fonction de la touche captur�e
        terrain.movePacman(moveDirection);

        // Afficher le terrain apr�s chaque d�placement
        terrain.display();

        // Pause de 300 millisecondes entre chaque d�placement
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    std::cout << "F�licitations ! Pac-Man a r�cup�r� l'amulette." << std::endl;

    return 0;
}
