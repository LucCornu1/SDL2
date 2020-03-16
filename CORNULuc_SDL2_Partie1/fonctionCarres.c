#include "fonctionCarres.h"

//Dessin d'un carre vide
int carreVide(SDL_Renderer *pRenderer, SDL_Rect* rect)
//Fonction qui prend en param�tres le renderer, et les coordonn�es du rectangle � afficher
//Elle retourne le renderer apr�s avoir affich� le retangle vide
{
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On s�lectionne la couleur blanche
        SDL_RenderDrawRect(pRenderer, rect); //On dessine le carr� � l'aide de la fonction SDL_RenderDrawRect
        //SDL_RenderDrawRect prend en param�tres le renderer et le rectangle � dessiner

        SDL_RenderPresent(pRenderer); //On affiche le carr�

        return(pRenderer); //On retourne le renderer
}

//Dessin d'un carre plein
int carrePlein(SDL_Renderer *pRenderer, SDL_Rect* rect)
//Fonction qui prend en param�tres le renderer, et les coordonn�es du rectangle � afficher
//Elle retourne le renderer apr�s avoir affich� le retangle plein
{
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255); //On s�lectionne la couleur blanche
        SDL_RenderDrawRect(pRenderer, rect); //On dessine le carr� � l'aide de la fonction SDL_RenderDrawRect
        //SDL_RenderDrawRect prend en param�tres le renderer et le rectangle � dessiner

        SDL_RenderFillRect(pRenderer, rect); //On rempli le carr� � l'aide de la fonction SDL_RenderFillRect
        //SDL_RenderDrawRect prend en param�tres le renderer et le rectangle � remplir

        SDL_RenderPresent(pRenderer); //On affiche le carr�

        return(pRenderer); //On retourne le renderer
}
