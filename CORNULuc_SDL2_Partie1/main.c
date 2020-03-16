#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonctionCercles.h"
#include "fonctionCarres.h"

#define X_WINDOW 1000
#define Y_WINDOW 700

int main(int argc, char *argv[]) //arguments obligatoire pour compiler en SDL
{
    SDL_Window *pWindow=NULL; //Pointeur sur la fenêtre
    SDL_Renderer *pRenderer=NULL; //Pointeur sur le Rendus
    SDL_Texture *pTexture=NULL; //Pointeur sur la texture

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0) //initialisation de la vidéo, des contrôles, de l'audio, etc.
    {
        //Création de la fenêtre : on associe la création de la fenêtre à une variable pour pouvoir la manipuler
        pWindow = SDL_CreateWindow("SDL_Partie1",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_WINDOW, Y_WINDOW, SDL_WINDOW_BORDERLESS);
        //SDL_WINDOWPOS_CENTERED permet de centrer la fenêtre dans l'écran de l'utilisateur
        //X_WINDOW et Y_WINDOW sont des constantes déterminant la taille de la fenêtre SDL2
        //SDL_WINDOW_SHOWN précise que la fenêtre doit être affichée

        //Création du renderer et de la texture, seulement si l'étape précédente n'a pas échouée
        if(pWindow!=NULL)
        {
            pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
            //Création d'un renderer : On lui donne la fenêtre sur laquelle il va être affiché

            //Affichage du point et de la ligne en SDL2
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
            //SDL_SetRenderDrawColor prend en paramètre le renderer et les valeurs RGBA, allant de 0 à 255
            //Cette fonction permet de changer la couleur des prochains éléments affichés
            SDL_RenderDrawPoint(pRenderer, 200, 200);
            //La fonction SDL_RenderDrawPoint prend en paramètre le Renderer, et les coordonnées du point à afficher
            SDL_RenderPresent(pRenderer); //On affiche le rendu
            SDL_RenderDrawLine(pRenderer, 250, 200, 450, 200);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(9000); //SDL_Delay prend en paramètre un int, et le programme va attendre le nombre spécifié en milisecondes

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //Affichage du fond de la fenêtre en rouge
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE); //SDL_ALPHA_OPAQUE équivaut à 255 pour la transparence
            SDL_RenderClear(pRenderer);
            //SDL_RenderClear prend en paramètre le renderer, et le "nettoie". Dans le cas présent, il retire le point du renderer
            SDL_RenderPresent(pRenderer); //Comme le renderer est vide, la couleur va s'appliquer au fond de la fenêtre

            SDL_Delay(9000);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //Affichage des carrés vides et pleins
            //On enregistre les coordonnées et les dimensions du carré vide dans un SDL_Rect
            SDL_Rect rectEmpty;
            rectEmpty.x = 10;
            rectEmpty.y = 10;
            rectEmpty.w = 100;
            rectEmpty.h = 100;

            //Idem pour le carré plein
            SDL_Rect rectFull;
            rectFull.x = 110;
            rectFull.y = 110;
            rectFull.w = 100;
            rectFull.h = 100;

            //On appelle les fonctions permettant de dessiner ces carrés (voir fonctionCarres.c)
            carreVide(pRenderer, &rectEmpty);
            carrePlein(pRenderer, &rectFull);

            SDL_Delay(9000);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //Pour y voir plus clair, on remet le fond en rouge
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);
            SDL_RenderPresent(pRenderer);

            //On appelle les fonctions permettant de dessiner les cercles (voir fonctionCercles.c)
            cercleVide(pRenderer, 100, 100, 100, 1000);
            cerclePlein(pRenderer, 300, 300, 100, 1000);

            SDL_Delay(9000);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //Pour y voir plus clair, on remet le fond en rouge
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);
            SDL_RenderPresent(pRenderer);

            //Création d'une texture à partir d'un BMP
            SDL_SetRenderTarget(pRenderer, NULL); //redéfinitions de la zone de travail
            SDL_Surface* pBmp = SDL_LoadBMP("Starmetal.bmp");
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,pBmp);

            SDL_FreeSurface(pBmp);

            if (Image == NULL)
              printf("erreur");

            SDL_Rect rectImg;
            rectImg.x = 100;
            rectImg.y = 100;
            rectImg.w = 100;
            rectImg.h = 100;
            SDL_QueryTexture(Image, NULL, NULL, &rectImg.w, &rectImg.h);//Récupère le format de l'image

            SDL_RenderCopy(pRenderer, Image, NULL, &rectImg);
            SDL_RenderPresent(pRenderer);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            SDL_Delay(5000);

            SDL_DestroyRenderer(pRenderer); //On supprime le renderer
        }

        SDL_DestroyWindow(pWindow); //On supprime la fenêtre
        SDL_Quit(); //On quitte SDL2
    }

    return 0;
}
