#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define X_WINDOW 1000
#define Y_WINDOW 700

//main
int main(int argc, char *argv[]) //arguments obligatoire pour compiler en SDL
{
    SDL_Window *pWindow=NULL; //Pointeur sur la fenêtre
    SDL_Renderer *pRenderer=NULL; //Pointeur sur le Rendus
    SDL_Texture *pTexture=NULL; //Pointeur sur la texture

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0) //initialisation de la vidéo, des contrôles, de l'audio, etc.
    {
        //Création de la fenêtre : on associe la création de la fenêtre à une variable pour pouvoir la manipuler
        pWindow = SDL_CreateWindow("SDL_Partie1",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_WINDOW, Y_WINDOW, SDL_WINDOW_SHOWN);
        //SDL_WINDOWPOS_CENTERED permet de centrer la fenêtre dans l'écran de l'utilisateur
        //X_WINDOW et Y_WINDOW sont des constantes déterminant la taille de la fenêtre SDL2
        //SDL_WINDOW_SHOWN précise que la fenêtre doit être affichée

        //Création du renderer et de la texture, seulement si l'étape précédente n'a pas échouée
        if(pWindow!=NULL)
        {
            pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
            SDL_RenderClear(pRenderer);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(5000);
              //----------------------------------------------------------------------------//
            //Création d'une texture à partir d'un PNG
            SDL_SetRenderTarget(pRenderer, NULL); //redéfinitions de la zone de travail
            SDL_Surface* pImage = IMG_Load("meth.png");
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,pImage);

            SDL_FreeSurface(pImage);

            if (Image == NULL)
              printf("Erreur de chargement de l'image : %s", pImage);

            SDL_Rect myRect;
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);//Récupère le format de l'image

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(5000);
            //----------------------------------------------------------------------------//
        }

        SDL_DestroyWindow(pWindow); //On supprime la fenêtre
        SDL_Quit(); //On quitte SDL2
    }

    return 0;
}
