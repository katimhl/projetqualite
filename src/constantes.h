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

using terrain = Cell[ROWS][COLS];