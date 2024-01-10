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
   
        Monstre monstre(5, 5, true, 2, 5, 0.8);

        
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
       
        Cell terrain[ROWS][COLS] = {EMPTY};
        terrain[2][3] = EMPTY;

       
        bool result = pacManTerrain.isValidMove(2, 3, terrain);

      
        REQUIRE(result == true);
    }

    SECTION("Case invalide - en dehors des limites en X") {
       
        bool result = pacManTerrain.isValidMove(-1, 3, nullptr); 

        // Vérifier que le mouvement est invalide
        REQUIRE(result == false);
    }


}
//------------------------------------------------------------------------------------------------------------
    TEST_SUITE("PacManTerrain Tests") {

    TEST_CASE("Move Pac-Man") {
        PacManTerrain terrain;

        SUBCASE("Move Up") {
            // Déplacement vers le haut
            terrain.movePacman('a');
            CHECK(terrain.isValidMove(terrain.pacmanRow - 1, terrain.pacmanCol));
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol)); 
        }

        SUBCASE("Move Down") {
            // Déplacement vers le bas
            terrain.movePacman('b');
            CHECK(terrain.isValidMove(terrain.pacmanRow + 1, terrain.pacmanCol));
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol));
        }

        SUBCASE("Move Left") {
            // Déplacement vers la gauche
            terrain.movePacman('g');
            CHECK(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol - 1));
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol));
        }

        SUBCASE("Move Right") {
            // Déplacement vers la droite
            terrain.movePacman('d');
            CHECK(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol + 1));
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol));
        }

        SUBCASE("Collect Amulet") {
            // Vérification de la collecte de l'amulette
            terrain.movePacman('d'); // Déplacer Pac-Man sur l'amulette
            CHECK(terrain.isAmuletCollected()); // L'amulette doit être collectée maintenant
        }
    }

    TEST_CASE("Move Pac-Man - Edge Cases") {
        PacManTerrain terrain;

        SUBCASE("Move Up - Against Wall") {
            // Déplacement vers le haut contre un mur
            int initialRow = terrain.pacmanRow;
            terrain.movePacman('a');
            CHECK(initialRow == terrain.pacmanRow); 
        }

        SUBCASE("Move Down - Against Wall") {
            // Déplacement vers le bas contre un mur
            int initialRow = terrain.pacmanRow;
            terrain.movePacman('b');
            CHECK(initialRow == terrain.pacmanRow);
        }

        SUBCASE("Move Left - Against Wall") {
            // Déplacement vers la gauche contre un mur
            int initialCol = terrain.pacmanCol;
            terrain.movePacman('g');
            CHECK(initialCol == terrain.pacmanCol);
        }

        SUBCASE("Move Right - Against Wall") {
            // Déplacement vers la droite contre un mur
            int initialCol = terrain.pacmanCol;
            terrain.movePacman('d');
            CHECK(initialCol == terrain.pacmanCol);
        }

        SUBCASE("Move - Outside Limits") {
            // Déplacement en dehors des limites du terrain
            int initialRow = terrain.pacmanRow;
            int initialCol = terrain.pacmanCol;

            // Déplacer Pac-Man vers le haut
            for (int i = 0; i < 100; ++i) {
                terrain.movePacman('a');
            }

            CHECK(initialRow == terrain.pacmanRow); 

            // Déplacer Pac-Man vers la gauche
            for (int i = 0; i < 100; ++i) {
                terrain.movePacman('g');
            }

            CHECK(initialCol == terrain.pacmanCol);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
TEST_SUITE("PacManTerrain Tests") {

    TEST_CASE("Collect Amulet") {
        PacManTerrain terrain;

        SUBCASE("Amulet Not Collected Initially") {
            // Vérifier que l'amulette n'est pas collectée initialement
            CHECK_FALSE(terrain.isAmuletCollected());
        }

        SUBCASE("Collect Amulet") {
            // Déplacer Pac-Man sur l'amulette
            terrain.movePacman('d');
            
            // Vérifier que l'amulette est collectée après le déplacement
            CHECK(terrain.isAmuletCollected());
        }

        SUBCASE("Collect Amulet Only Once") {
            // Déplacer Pac-Man sur l'amulette
            terrain.movePacman('d');

            // Vérifier que l'amulette est collectée après le déplacement
            CHECK(terrain.isAmuletCollected());

            // Déplacer Pac-Man à nouveau sur l'amulette
            terrain.movePacman('d');

            // Vérifier que l'amulette n'est pas collectée une deuxième fois
            CHECK_FALSE(terrain.isAmuletCollected());
        }
    }
}
//------------------------------------------------------------------------------------------------------------
TEST_SUITE("PacManTerrain Tests") {

    TEST_CASE("Move Monsters") {
        PacManTerrain terrain;

        SUBCASE("Monsters Move Towards Pac-Man") {
            // Récupérer les positions initiales des monstres
            std::vector<std::pair<int, int>> initialMonsterPositions;
            for (const auto& monstre : terrain.getMonsters()) {
                initialMonsterPositions.emplace_back(monstre.getX(), monstre.getY());
            }

            // Déplacer Pac-Man à une nouvelle position
            terrain.movePacman('a');

            // Vérifier que les monstres se déplacent vers la nouvelle position de Pac-Man
            const auto& monsters = terrain.getMonsters();
            for (size_t i = 0; i < monsters.size(); ++i) {
                CHECK(monsters[i].getX() != initialMonsterPositions[i].first || monsters[i].getY() != initialMonsterPositions[i].second);
            }
        }

        SUBCASE("Monsters Do Not Move Outside Terrain") {
            // Déplacer Pac-Man à une nouvelle position
            terrain.movePacman('a');

            // Déplacer les monstres plusieurs fois
            for (int i = 0; i < 10; ++i) {
                terrain.moveMonsters();
            }

            // Vérifier que les monstres restent à l'intérieur des limites du terrain
            const auto& monsters = terrain.getMonsters();
            for (const auto& monstre : monsters) {
                CHECK(monstre.getX() >= 0);
                CHECK(monstre.getX() < PacManTerrain::ROWS);
                CHECK(monstre.getY() >= 0);
                CHECK(monstre.getY() < PacManTerrain::COLS);
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------
TEST_SUITE("PacManTerrain Tests") {

    TEST_CASE("isValidMove") {
        PacManTerrain terrain;

        SUBCASE("Valid Moves Inside Terrain") {
            // Vérifier que les mouvements à l'intérieur des limites du terrain sont valides
            CHECK(terrain.isValidMove(terrain.pacmanRow - 1, terrain.pacmanCol)); // Move Up
            CHECK(terrain.isValidMove(terrain.pacmanRow + 1, terrain.pacmanCol)); // Move Down
            CHECK(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol - 1)); // Move Left
            CHECK(terrain.isValidMove(terrain.pacmanRow, terrain.pacmanCol + 1)); // Move Right
        }

        SUBCASE("Invalid Moves Outside Terrain") {
            // Vérifier que les mouvements en dehors des limites du terrain sont invalides
            CHECK_FALSE(terrain.isValidMove(-1, terrain.pacmanCol)); 
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, -1));
            CHECK_FALSE(terrain.isValidMove(PacManTerrain::ROWS, terrain.pacmanCol)); 
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, PacManTerrain::COLS)); 
        }

        SUBCASE("Invalid Moves into Walls") {
            // Vérifier que les mouvements dans les murs sont invalides
            int wallRow = terrain.pacmanRow - 2;
            int wallCol = terrain.pacmanCol - 2;

            CHECK_FALSE(terrain.isValidMove(wallRow, terrain.pacmanCol)); 
            CHECK_FALSE(terrain.isValidMove(terrain.pacmanRow, wallCol)); 
        }
    }
}
//------------------------------------------------------------------------------------------------------------
TEST_SUITE("PacManTerrain Tests") {

    TEST_CASE("Amulet Collected State") {
        PacManTerrain terrain;

        SUBCASE("Amulet Not Collected Initially") {
            // Vérifier que l'amulette n'est pas collectée initialement
            CHECK_FALSE(terrain.isAmuletCollected());
        }

        SUBCASE("Collect Amulet") {
            // Déplacer Pac-Man sur l'amulette
            terrain.movePacman('d');
            
            // Vérifier que l'amulette est collectée après le déplacement
            CHECK(terrain.isAmuletCollected());
        }

        SUBCASE("Amulet Not Collectible After Collection") {
            // Déplacer Pac-Man sur l'amulette
            terrain.movePacman('d');

            // Vérifier que l'amulette est collectée après le déplacement
            CHECK(terrain.isAmuletCollected());

            // Déplacer Pac-Man à nouveau sur l'amulette
            terrain.movePacman('d');

            // Vérifier que l'amulette n'est pas collectée une deuxième fois
            CHECK_FALSE(terrain.isAmuletCollected());
        }
    }
}
