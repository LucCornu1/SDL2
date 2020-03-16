#include "fonctionCarres.h"

//Dessin d'un carre vide
int carreVide(SDL_Renderer *pRenderer, SDL_Rect* rect)
//Fonction qui prend en paramètres le renderer, et les coordonnées du rectangle à afficher
//Elle retourne le renderer après avoir affiché le retangle vide
{
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On sélectionne la couleur blanche
        SDL_RenderDrawRect(pRenderer, rect); //On dessine le carré à l'aide de la fonction SDL_RenderDrawRect
        //SDL_RenderDrawRect prend en paramètres le renderer et le rectangle à dessiner

        SDL_RenderPresent(pRenderer); //On affiche le carré

        return(pRenderer); //On retourne le renderer
}

//Dessin d'un carre plein
int carrePlein(SDL_Renderer *pRenderer, SDL_Rect* rect)
//Fonction qui prend en paramètres le renderer, et les coordonnées du rectangle à afficher
//Elle retourne le renderer après avoir affiché le retangle plein
{
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On sélectionne la couleur blanche
        SDL_RenderDrawRect(pRenderer, rect); //On dessine le carré à l'aide de la fonction SDL_RenderDrawRect
        //SDL_RenderDrawRect prend en paramètres le renderer et le rectangle à dessiner

        SDL_RenderFillRect(pRenderer, rect); //On rempli le carré à l'aide de la fonction SDL_RenderFillRect
        //SDL_RenderDrawRect prend en paramètres le renderer et le rectangle à remplir

        SDL_RenderPresent(pRenderer); //On affiche le carré

        return(pRenderer); //On retourne le renderer
}
