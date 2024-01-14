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
    PacManTerrain pacManTerrain;
    char moveDirection;

    std::cout << "Utilisez les touches z:haut, s:bas, q:gauche, d:droite pour déplacer Pac-Man." << std::endl;


while (true) {
    // Capturer la touche du clavier sans attendre l'appui sur la touche "Entrée"

    moveDirection = _getch();
       system("cls");

    // Déplacer Pac-Man en fonction de la touche capturée
    pacManTerrain.movePacman(moveDirection);

    // Afficher le terrain après chaque déplacement
    pacManTerrain.display();
  
}

std::cout << "Félicitations ! Pac-Man a récupéré l'amulette." << std::endl;
std::this_thread::sleep_for(std::chrono::milliseconds(5000));

return 0;
}


