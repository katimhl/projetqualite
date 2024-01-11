#include "joueur.h"

joueur::joueur(int pVie, int pDef, int pforce):
	points_de_vie{pVie},points_de_defense{pDef}, points_de_force{pforce}
{
}

int joueur::voir_vie() const
{
	return points_de_vie;
}

int joueur::voir_defense() const
{
	return points_de_defense;
}

int joueur::voir_force() const
{
	return points_de_force;
}

void joueur::perd_vie(int pV)
{
	points_de_vie -= pV;
}

void joueur::gagne_vie(int pV)
{
	points_de_vie += pV;
}

void joueur::attaque(Monstre& e)
{
	e.recevoirAttaque(points_de_force - points_de_defense);
	epee_joueur.perd_solidite(5);
}

epee::epee(int solidite):
	point_de_solidite{solidite}
{
}

int epee::voir_solidite() const
{
	return point_de_solidite;
}

void epee::perd_solidite(int pS)
{
	point_de_solidite -= pS;
}
