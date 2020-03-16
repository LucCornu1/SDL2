#include "fonctionCercles.h"

//Dessin d'un cercle vide
int cercleVide(SDL_Renderer *pRenderer, int XCercle, int YCercle, int radiusCercle, int nbPoints)
//Fonction qui prend en paramètres le renderer, les coordonnées du centre du cercle à afficher, le rayon du cercle et le nombre de points
//Elle retourne le renderer après avoir affiché le cercle vide
{
	int xPoint, yPoint, xPointCercle, yPointCercle;
	int i;
	double angleA;

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On sélectionne la couleur blanche

	for(i=0; i < nbPoints; i++) //Calcule des points du cercle à partir de son centre et de son rayon
	{
        angleA = (double)i / (double)nbPoints * 2 * M_PI;

        xPointCercle = (int)(radiusCercle * cos(angleA));
		yPointCercle = (int)(radiusCercle * sin(angleA));

		xPoint = XCercle + xPointCercle;
		yPoint = YCercle + yPointCercle;

        SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);
        //Une fois le point calculé, on l'affiche, et on répète l'opération jusqu'à avoir un cercle de nPoints
	}

	SDL_RenderPresent(pRenderer); //On affiche le cercle sur la fenêtre

	return(pRenderer); //On retourne le renderer
}

//Dessin d'un cercle plein
int cerclePlein(SDL_Renderer *pRenderer, int XCercle, int YCercle, int radiusCercle, int nbPoints)
//Fonction qui prend en paramètres le renderer, les coordonnées du centre du cercle à afficher, le rayon du cercle et le nombre de points
//Elle retourne le renderer après avoir affiché le cercle plein
{
	int xPoint, yPoint, xPointCercle, yPointCercle;
	int i;
	int xTab, yTab;
	double angleA;

	int tailleTableau = radiusCercle*2;

	int TPoints[tailleTableau][tailleTableau];

	for(xTab=0; xTab<tailleTableau; xTab++)
	{
        for(yTab=0; yTab<tailleTableau; yTab++)
        {
            TPoints[xTab][yTab] = 0;
        }
	}

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On sélectionne la couleur blanche

	for(i=0; i < nbPoints; i++) //Calcule des points du cercle à partir de son centre et de son rayon
	{
        angleA = (double)i / (double)nbPoints * 2 * M_PI;

		xPointCercle = (int)(radiusCercle * cos(angleA));
		yPointCercle = (int)(radiusCercle * sin(angleA));

		xPoint = XCercle + xPointCercle;
		yPoint = YCercle + yPointCercle;

        SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);
        //Une fois le point calculé, on l'affiche

        if(angleA < (M_PI / 2))
        {
            for(xTab=radiusCercle; xTab <= radiusCercle+xPointCercle; xTab++)
            {
                for(yTab=radiusCercle; yTab <= radiusCercle+yPointCercle; yTab++)
                {
                    TPoints[xTab][yTab] = 1;
                    TPoints[radiusCercle*2-xTab][yTab] = 1;
                    TPoints[xTab][radiusCercle*2-yTab] = 1;
                    TPoints[radiusCercle*2-xTab][radiusCercle*2-yTab] = 1;
                }
            }
        }
        //On répète l'opération jusqu'à avoir un cercle de nPoints
	}

	for(xTab=0; xTab<tailleTableau; xTab++)
	{
        for(yTab=0; yTab<tailleTableau; yTab++)
        {
            if(TPoints[xTab][yTab] == 1)
            {
                xPoint = XCercle + xTab - radiusCercle;
                yPoint = YCercle + yTab - radiusCercle;
                SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);
            }
        }
	}

	SDL_RenderPresent(pRenderer); //On affiche le cercle sur la fenêtre

	return(pRenderer); //On retourne le renderer
}
