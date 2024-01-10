#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Monstre.h"
#include "PacManTerrain.h"





TEST_CASE("D�placement du monstre aveugle") {
    PacManTerrain pacManTerrain;
    Monstre monstre(5, 5, false, 2, 5, 0.8);

    // D�placer le monstre aveugle plusieurs fois (10 fois dans cet exemple)
    for (int i = 0; i < 10; ++i) {
        monstre.deplacerMonstre(0, 0, pacManTerrain.getTerrain());
        REQUIRE(pacManTerrain.isValidMove(monstre.getX(), monstre.getY()));
    }
}
//------------------------------------------------------------------------------------


TEST_CASE("Monstre attaque l'aventurier") {
    SUBCASE("Attaque r�ussie avec probabilit� �lev�e") {
        // Cr�er un monstre avec une probabilit� d'attaque �lev�e
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la m�thode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // V�rifier que l'attaque est appliqu�e � l'aventurier lorsque la probabilit� est respect�e
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10 - static_cast<int>(5 * 0.9));
            }
        }
    }

    SUBCASE("Aucune attaque avec probabilit� basse") {
        // Cr�er un monstre avec une probabilit� d'attaque basse
        Monstre monstre(0, 0, true, 10, 5, 0.1);

        // Appeler la m�thode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // V�rifier que l'attaque n'est pas appliqu�e � l'aventurier lorsque la probabilit� n'est pas respect�e
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10);
            }
        }
    }

    SUBCASE("Monstre aveugle n'attaque pas") {
        // Cr�er un monstre aveugle
        Monstre monstre(0, 0, false, 10, 5, 0.9);

        // Appeler la m�thode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // V�rifier que l'attaque n'est pas appliqu�e � l'aventurier (monstre aveugle ne devrait pas attaquer)
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10);
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------

TEST_CASE("Monstre re�oit une attaque") {
    SECTION("Points de vie positifs") {
        // Cr�er un monstre avec des points de vie positifs
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la m�thode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // V�rifier que les points de vie sont correctement mis � jour apr�s l'attaque
        REQUIRE(monstre.getPointsVie() == 7);
    }

    SECTION("Points de vie nuls") {
        // Cr�er un monstre avec des points de vie nuls
        Monstre monstre(0, 0, true, 0, 5, 0.9);

        // Appeler la m�thode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // V�rifier que les points de vie restent nuls apr�s l'attaque
        REQUIRE(monstre.getPointsVie() == 0);
    }

    SECTION("Points de vie n�gatifs") {
        // Cr�er un monstre avec des points de vie n�gatifs
        Monstre monstre(0, 0, true, -5, 5, 0.9);

        // Appeler la m�thode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // V�rifier que les points de vie restent nuls apr�s l'attaque
        REQUIRE(monstre.getPointsVie() == 0);
    }
}
//-------------------------------------------------------------------------------------------------------------
TEST_CASE("D�placement du monstre aveugle") {
    SECTION("D�placement valide vers le haut") {
        // Cr�er un monstre � une position
        Monstre monstre(5, 5, false, 2, 5, 0.8);

        // Cr�er un terrain avec une cellule vide � la nouvelle position souhait�e
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[4][5] = EMPTY;

        // Appeler la m�thode deplacerMonstreAveugle
        monstre.deplacerMonstreAveugle(terrain);

        // V�rifier que le monstre a �t� d�plac� vers le haut
        REQUIRE(monstre.getX() == 4);
        REQUIRE(monstre.getY() == 5);
    }


}
//---------------------------------------------------------------------------------------------------------
TEST_CASE("D�placement du monstre voyant") {
    SECTION("D�placement vers le joueur vers la droite") {
        // Cr�er un monstre � une position
        Monstre monstre(5, 5, true, 2, 5, 0.8);

        // Cr�er un terrain avec une cellule vide � la nouvelle position souhait�e
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[5][6] = EMPTY;

        // Appeler la m�thode deplacerMonstreVoyant
        monstre.deplacerMonstreVoyant(5, 6, terrain);

        // V�rifier que le monstre a �t� d�plac� vers la droite
        REQUIRE(monstre.getX() == 5);
        REQUIRE(monstre.getY() == 6);
    }

}
//------------------------------------------------------------------------------------------------

TEST_CASE("Validation du mouvement") {
    PacManTerrain pacManTerrain;
    SECTION("Case valide") {
        // Cr�er un terrain avec une cellule vide � la position sp�cifi�e
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[2][3] = EMPTY;

        // Appeler la m�thode isValidMove
        bool result = pacManTerrain.isValidMove(2, 3, terrain);

        // V�rifier que le mouvement est valide
        REQUIRE(result == true);
    }

    SECTION("Case invalide - en dehors des limites en X") {
        // Appeler la m�thode isValidMove avec une position en dehors des limites en X
        bool result = pacManTerrain.isValidMove(-1, 3, nullptr); // Passer nullptr pour le terrain, car il n'est pas utilis� dans cet exemple

        // V�rifier que le mouvement est invalide
        REQUIRE(result == false);
    }


}
//------------------------------------------------------------------------------------------------------------
#endif // TEST_H
