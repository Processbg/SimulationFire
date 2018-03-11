#include "graphics.h"

#define L 40
#define C 60
#define DUREE_FEU 720
#define DUREE_CENDRE 220

struct parcelle 
{
	COULEUR couleur;
	int type;
	int duree;

};
typedef struct parcelle PARCELLE;

PARCELLE T1 [L][C];
PARCELLE T2 [L][C];
int duree_feu = 3;
int duree_centre = 4;

COULEUR couleur_terrain_aleatoire()
{
	COULEUR c=rouge;
	int i = alea_int(6);
		
	if (i == 0)
	{
		c = rouge;
	}
	if (i == 1)
	{
		c = bleu;
	}
	if (i == 2)
	{
		c = vert;
	}
	if (i == 3)
	{
		c = noir;
	}
	if (i == 4)
	{
		c = gris;
	}
	if (i == 5)
	{
		c = marron;
	}
	return c;
}

PARCELLE init_parcelle_sans_feu()
{
	PARCELLE P;
	
	P.couleur=couleur_terrain_aleatoire();
	
	if (P.couleur == marron)
		P.type = 0;
		
	if (P.couleur == vert)
		P.type = 1;
		
	if (P.couleur == bleu)
		P.type = 2;
		
	return P;
}

PARCELLE init_parcelle_avec_feu()
{
	PARCELLE P;
	
	P.couleur=couleur_terrain_aleatoire();
	
	if (P.couleur == marron)
		P.type = 0;
		
	if (P.couleur == vert)
		P.type = 1;
		
	if (P.couleur == bleu)
		P.type = 2;
	
	if (((P.couleur == marron) || (P.couleur == vert) || (P.couleur == bleu)) 
		&& 
		((P.type = 0) || (P.type = 1) || (P.type = 2)))
		{
			P.couleur = rouge;
			P.type = 3;
		}
	
	return P;
}

void terraine_aleatoire_sans_feu()
{
	int i,j;;
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
		{
			T1[i][j] = init_parcelle_sans_feu();
		}	
}

void terraine_aleatoire_avec_feu()
{
	int i,j;;
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
		{
			T1[i][j] = init_parcelle_avec_feu();
		}	
}

void affiche_parcelle(POINT bg, COULEUR c)
{
	POINT hd;
	hd.x = bg.x + 10;
	hd.y = bg.y + 10;
	
	draw_fill_rectangle(bg,hd,c);
}

void affiche_terrain_sans_feu()
{
	int i,j;
	POINT bg;
	bg.x = 0; bg.y = 0;
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
			{
					bg.x = i*10;
					bg.y = j*10;
					affiche_parcelle(bg,T1[i][j].couleur);
			}	
}

void affiche_terrain_avec_feu(POINT p)
{
	int i,j;
	POINT bg;
	bg.x = 0; bg.y = 0; 
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
			{
					bg.x = i*10;
					bg.y = j*10;
					affiche_parcelle(bg,T1[i][j].couleur);
			}			
}

void affiche_t2()
{
	int i,j;
	POINT bg;
	bg.x = 0; bg.y = 0;
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
			{
					bg.x = i*10;
					bg.y = j*10; 
					affiche_parcelle(bg,T2[i][j].couleur);
			}	
}

void copie_t2_t1()
{
	int i,j;
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
			{
				T1[i][j]=T2[i][j];
			}	
}

void modifier_parcelle(int i, int j)
{
	if(T1[i][j].couleur == rouge)
	{
		duree_feu--;
		if(duree_feu == 0)
		{
			duree_feu = 3;
			T2[i][j].couleur = gris;	
		}
		else
		{
			T2[i][j].couleur = rouge;
		}
	}
	else
	{
	
		if(T1[i][j].couleur == gris)
		{
			duree_centre--;
			if(duree_centre == 0)
			{
				duree_centre = 4;
				T2[i][j].couleur = noir;	
			}
			else
			{
				T2[i][j].couleur = gris;
			}	
		}
		else
		{
			if(T1[i][j].couleur == vert)
			{
				if((T1[i-1][j-1].couleur==rouge)
					||
				(T1[i-1][j].couleur==rouge)
					||
				(T1[i-1][j+1].couleur==rouge)
					||
				(T1[i][j-1].couleur==rouge)
					||
				(T1[i][j+1].couleur==rouge)
					||
				(T1[i+1][j-1].couleur==rouge)
					||
				(T1[i+1][j].couleur==rouge)
					||
				(T1[i+1][j+1].couleur==rouge))
				{
					T2[i][j].couleur=rouge;
				}
			}
			else
			{
				T2[i][j].couleur = T1[i][j].couleur;
			}	
		}
	}	
}

void modifier_T2()
{
	int i,j;
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
			{
				modifier_parcelle(i,j);
			}			
}

void modif_terraine(int i, int j)
{
	if(T1[i][j].couleur == rouge)
	{
		duree_feu--;
		if(duree_feu == 0)
		{
			duree_feu = 3;
			T2[i][j].couleur = gris;	
		}
		else
		{
			T2[i][j].couleur = rouge;
		}
	}
	else
	{
	
		if(T1[i][j].couleur == gris)
		{
			duree_centre--;
			if(duree_centre == 0)
			{
				duree_centre = 4;
				T2[i][j].couleur = noir;	
			}
			else
			{
				T2[i][j].couleur = gris;
			}	
		}
		else
		{
			if(T1[i][j].couleur == vert)
			{
				if((T1[i-1][j-1].couleur==rouge)
					||
				(T1[i-1][j].couleur==rouge)
					||
				(T1[i-1][j+1].couleur==rouge)
					||
				(T1[i][j-1].couleur==rouge)
					||
				(T1[i][j+1].couleur==rouge)
					||
				(T1[i+1][j-1].couleur==rouge)
					||
				(T1[i+1][j].couleur==rouge)
					||
				(T1[i+1][j+1].couleur==rouge))
				{
					T2[i][j].couleur=rouge;
				}
			}
			else
			{
				T2[i][j].couleur = T1[i][j].couleur;
			}	
		}
	}
}

void recopie_terraine(int i, int j)
{
	PARCELLE E [L][C];
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
		{
			E[i][j] = T2[i][j];
			T1[i][j] = E[i][j];
		}
}

int compare_T1_T2(int i, int j)
{
	int a = 0, b = 1;
	 
	
	if(*(T1) == *(T2))
		{
			for(i=0; i<L; i++)
				for(j=0; j<C; j++)
				{
					T1[i][j] = T2[i][j];
				}	
			return a;	
		}
	else
		return b;
}

COULEUR modif_parcielle(int i, int j)
{
	if(T1[i][j].couleur == rouge)
	{
		duree_feu--;
		if(duree_feu == 0)
		{
			duree_feu = 3;
			T2[i][j].couleur = gris;	
		}
		else
		{
			T2[i][j].couleur = rouge;
		}
	}
	else
	{
	
		if(T1[i][j].couleur == gris)
		{
			duree_centre--;
			if(duree_centre == 0)
			{
				duree_centre = 4;
				T2[i][j].couleur = noir;	
			}
			else
			{
				T2[i][j].couleur = gris;
			}	
		}
		else
		{
			if(T1[i][j].couleur == vert)
			{
				if((T1[i-1][j-1].couleur==rouge)
					||
				(T1[i-1][j].couleur==rouge)
					||
				(T1[i-1][j+1].couleur==rouge)
					||
				(T1[i][j-1].couleur==rouge)
					||
				(T1[i][j+1].couleur==rouge)
					||
				(T1[i+1][j-1].couleur==rouge)
					||
				(T1[i+1][j].couleur==rouge)
					||
				(T1[i+1][j+1].couleur==rouge))
				{
					T2[i][j].couleur=rouge;
				}
			}
			else
			{
				T2[i][j].couleur = T1[i][j].couleur;
			}	
		}
	}
	
	return T2[i][j].couleur;
}

int continuer(int i, int j)
{
	int c = 1, f = 0; 
	
	if (modif_parcielle(i,j) == gris)	 
		return c;
		
	else if (modif_parcielle(i,j) == noir)	 
		return f;
		
	else if (modif_parcielle(i,j) == rouge)	 
		return c;
	
	return 1;
}

void init_feu(POINT p)
{
	int i,j;
	POINT hd;
	
	hd.x = 10*L;
	hd.y = 10*C;
	
	for(i=0; i<L; i++)
		for(j=0; j<C; j++)
		{
			p = wait_clic();
			if (p.x <= hd.x && p.y <= hd.y)
				affiche_terrain_avec_feu(p);
			else
				exit(0);	
		}	
}

void modifie(int i, int j)
{
	while(compare_T1_T2(i,j) != 1)
	{
		modifier_T2();
		affiche_t2();
		copie_t2_t1();
		modifier_parcelle(i,j);
		modifier_T2();
		modif_terraine(i,j);
		recopie_terraine(i,j);
		continuer(i,j);
	}
}

int main()
{
	int Largeur = C*10, Hauteur = L*10, i = 0, j = 0;
	POINT p;
	
	init_graphics(Largeur,Hauteur);
	
	terraine_aleatoire_sans_feu();
	affiche_terrain_sans_feu();
	terraine_aleatoire_avec_feu();
	init_feu(p);
	affiche_terrain_avec_feu(p);
	modifie(i,j);

	wait_escape();
	exit(0);
}
