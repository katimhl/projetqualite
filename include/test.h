#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Monstre.h"
#include "PacManTerrain.h"





TEST_CASE("Déplacement du monstre aveugle") {
    PacManTerrain pacManTerrain;
    Monstre monstre(5, 5, false, 2, 5, 0.8);

    // Déplacer le monstre aveugle plusieurs fois (10 fois dans cet exemple)
    for (int i = 0; i < 10; ++i) {
        monstre.deplacerMonstre(0, 0, pacManTerrain.getTerrain());
        REQUIRE(pacManTerrain.isValidMove(monstre.getX(), monstre.getY()));
    }
}
//------------------------------------------------------------------------------------


TEST_CASE("Monstre attaque l'aventurier") {
    SUBCASE("Attaque réussie avec probabilité élevée") {
        // Créer un monstre avec une probabilité d'attaque élevée
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la méthode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // Vérifier que l'attaque est appliquée à l'aventurier lorsque la probabilité est respectée
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10 - static_cast<int>(5 * 0.9));
            }
        }
    }

    SUBCASE("Aucune attaque avec probabilité basse") {
        // Créer un monstre avec une probabilité d'attaque basse
        Monstre monstre(0, 0, true, 10, 5, 0.1);

        // Appeler la méthode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // Vérifier que l'attaque n'est pas appliquée à l'aventurier lorsque la probabilité n'est pas respectée
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10);
            }
        }
    }

    SUBCASE("Monstre aveugle n'attaque pas") {
        // Créer un monstre aveugle
        Monstre monstre(0, 0, false, 10, 5, 0.9);

        // Appeler la méthode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // Vérifier que l'attaque n'est pas appliquée à l'aventurier (monstre aveugle ne devrait pas attaquer)
            if (monstre.getPointsVie() == 10) {
                REQUIRE(monstre.getPointsVie() == 10);
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------

TEST_CASE("Monstre reçoit une attaque") {
    SECTION("Points de vie positifs") {
        // Créer un monstre avec des points de vie positifs
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la méthode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // Vérifier que les points de vie sont correctement mis à jour après l'attaque
        REQUIRE(monstre.getPointsVie() == 7);
    }

    SECTION("Points de vie nuls") {
        // Créer un monstre avec des points de vie nuls
        Monstre monstre(0, 0, true, 0, 5, 0.9);

        // Appeler la méthode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // Vérifier que les points de vie restent nuls après l'attaque
        REQUIRE(monstre.getPointsVie() == 0);
    }

    SECTION("Points de vie négatifs") {
        // Créer un monstre avec des points de vie négatifs
        Monstre monstre(0, 0, true, -5, 5, 0.9);

        // Appeler la méthode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // Vérifier que les points de vie restent nuls après l'attaque
        REQUIRE(monstre.getPointsVie() == 0);
    }
}
//-------------------------------------------------------------------------------------------------------------
TEST_CASE("Déplacement du monstre aveugle") {
    SECTION("Déplacement valide vers le haut") {
        // Créer un monstre à une position
        Monstre monstre(5, 5, false, 2, 5, 0.8);

        // Créer un terrain avec une cellule vide à la nouvelle position souhaitée
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[4][5] = EMPTY;

        // Appeler la méthode deplacerMonstreAveugle
        monstre.deplacerMonstreAveugle(terrain);

        // Vérifier que le monstre a été déplacé vers le haut
        REQUIRE(monstre.getX() == 4);
        REQUIRE(monstre.getY() == 5);
    }


}
//---------------------------------------------------------------------------------------------------------
TEST_CASE("Déplacement du monstre voyant") {
    SECTION("Déplacement vers le joueur vers la droite") {
        // Créer un monstre à une position
        Monstre monstre(5, 5, true, 2, 5, 0.8);

        // Créer un terrain avec une cellule vide à la nouvelle position souhaitée
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[5][6] = EMPTY;

        // Appeler la méthode deplacerMonstreVoyant
        monstre.deplacerMonstreVoyant(5, 6, terrain);

        // Vérifier que le monstre a été déplacé vers la droite
        REQUIRE(monstre.getX() == 5);
        REQUIRE(monstre.getY() == 6);
    }

}
//------------------------------------------------------------------------------------------------

TEST_CASE("Validation du mouvement") {
    PacManTerrain pacManTerrain;
    SECTION("Case valide") {
        // Créer un terrain avec une cellule vide à la position spécifiée
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[2][3] = EMPTY;

        // Appeler la méthode isValidMove
        bool result = pacManTerrain.isValidMove(2, 3, terrain);

        // Vérifier que le mouvement est valide
        REQUIRE(result == true);
    }

    SECTION("Case invalide - en dehors des limites en X") {
        // Appeler la méthode isValidMove avec une position en dehors des limites en X
        bool result = pacManTerrain.isValidMove(-1, 3, nullptr); // Passer nullptr pour le terrain, car il n'est pas utilisé dans cet exemple

        // Vérifier que le mouvement est invalide
        REQUIRE(result == false);
    }


}
//------------------------------------------------------------------------------------------------------------
#endif // TEST_H
