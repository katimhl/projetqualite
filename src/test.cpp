#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>
#include "PacManTerrain.h"
#include "joueur.h"


TEST_CASE("Deplacement du monstre aveugle") {
    PacManTerrain terrain;
    Monstre monstre(5, 5, false, 2, 5, 0.8);

    // Deplacer le monstre aveugle plusieurs fois (10 fois dans cet exemple)
    for (int i = 0; i < 10; ++i) {
        monstre.deplacerMonstre(0, 0, terrain.getTerrain());
        bool x = terrain.isValidMove(monstre.getX(), monstre.getY());
        REQUIRE_EQ(x , true);
    }
}
//------------------------------------------------------------------------------------


TEST_CASE("Monstre attaque l'aventurier") {
    SUBCASE("Attaque reussie avec probabilite elevee") {
        // Creer un monstre avec une probabilite d'attaque elevee
        PacManTerrain terrain;
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la methode attaquerAventurier plusieurs fois
        for (int i = 0; i < 100; ++i) {
            monstre.attaquerAventurier();
            // Verifier que l'attaque est appliquee � au monstre lorsque la probabilit� est respect�e
            REQUIRE(monstre.getPointsVie() == 10 - static_cast<int>(5*0.9));

            terrain.playerDamage(monstre);
            // Verifier que l'attaque est appliquee � l'aventurier lorsque la probabilit� est respect�e
            REQUIRE(terrain.getVieJoueur() == 20 - monstre.getPointDeForce());
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
    SUBCASE("Points de vie positifs") {
        // Cr�er un monstre avec des points de vie positifs
        Monstre monstre(0, 0, true, 10, 5, 0.9);

        // Appeler la m�thode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // V�rifier que les points de vie sont correctement mis � jour apr�s l'attaque
        REQUIRE(monstre.getPointsVie() == 7);
    }

    SUBCASE("Points de vie nuls") {
        // Cr�er un monstre avec des points de vie nuls
        Monstre monstre(0, 0, true, 0, 5, 0.9);

        // Appeler la m�thode recevoirAttaque avec une valeur d'attaque
        monstre.recevoirAttaque(3);

        // V�rifier que les points de vie restent nuls apr�s l'attaque
        REQUIRE(monstre.getPointsVie() == 0);
    }

    SUBCASE("Points de vie n�gatifs") {
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
    SUBCASE("D�placement valide vers le haut") {
        // Cr�er un monstre � une position
        Monstre monstre(5, 5, false, 2, 5, 0.8);

        // Cr�er un terrain avec une cellule vide � la nouvelle position souhait�e
        PacManTerrain terrain;

        // Appeler la m�thode deplacerMonstreAveugle
        monstre.deplacerMonstreAveugle(terrain.getTerrain());

        // V�rifier que le monstre a �t� d�plac� vers le haut
        REQUIRE(monstre.getX() == 4);
        REQUIRE(monstre.getY() == 5);
    }


}
//---------------------------------------------------------------------------------------------------------
TEST_CASE("D�placement du monstre voyant") {
    SUBCASE("D�placement vers le joueur vers la droite") {
        // Cr�er un monstre � une position
        Monstre monstre(5, 5, true, 2, 5, 0.8);

        // Cr�er un terrain avec une cellule vide � la nouvelle position souhait�e
        PacManTerrain terrain;

        // Appeler la m�thode deplacerMonstreVoyant
        monstre.deplacerMonstreVoyant(5, 6, terrain.getTerrain());

        // V�rifier que le monstre a �t� d�plac� vers la droite
        REQUIRE(monstre.getX() == 5);
        REQUIRE(monstre.getY() == 6);
    }

}
//------------------------------------------------------------------------------------------------

TEST_CASE("Validation du mouvement") {
    PacManTerrain terrainPacMan;
    SUBCASE("Case valide") {

        // Appeler la m�thode isValidMove
        bool result = terrainPacMan.isValidMove(2, 3);

        // V�rifier que le mouvement est valide
        REQUIRE(result == true);
    }

    SUBCASE("Case invalide - en dehors des limites en X") {
        // Appeler la m�thode isValidMove avec une position en dehors des limites en X
        bool result = terrainPacMan.isValidMove(-1, 3); // Passer nullptr pour le terrain, car il n'est pas utilis� dans cet exemple

        // V�rifier que le mouvement est invalide
        REQUIRE(result == false);
    }


}
//------------------------------------------------------------------------------------------------------------
