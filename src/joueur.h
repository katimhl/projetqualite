#ifndef JOUEUR_H
#define JOUEUR_H

class Monstre;

class epee
{
public:
	epee(int solidite = 50);
	virtual ~epee() = default;
	int voir_solidite() const;
	void perd_solidite(int pS);
private:
	int point_de_solidite;
};


class joueur
{
public:
	joueur(int pVie = 100, int pDef = 100, int pforce = 15);
	int voir_vie()const;
	int voir_defense()const;
	int voir_force()const;
	void perd_vie(int pV);
	void gagne_vie(int pV);
	void attaque(Monstre& e);
	void deplace(int x,int y){
		d_x=x;
		d_y=y;
	}
	int X()const{return d_x;}
	int Y()const{return d_y;}
private:
	int points_de_vie;
	int points_de_defense;
	int points_de_force;
	epee epee_joueur;
	int d_x,d_y;
};

#endif