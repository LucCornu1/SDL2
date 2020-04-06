#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define X_WINDOW 1000
#define Y_WINDOW 700

//main
int main(int argc, char *argv[]) //arguments obligatoire pour compiler en SDL
{
    SDL_Window *pWindow=NULL; //Pointeur sur la fen�tre
    SDL_Renderer *pRenderer=NULL; //Pointeur sur le Rendus
    SDL_Texture *pTexture=NULL; //Pointeur sur la texture

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0) //initialisation de la vid�o, des contr�les, de l'audio, etc.
    {
        //Cr�ation de la fen�tre : on associe la cr�ation de la fen�tre � une variable pour pouvoir la manipuler
        pWindow = SDL_CreateWindow("SDL_Partie1",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_WINDOW, Y_WINDOW, SDL_WINDOW_SHOWN);
        //SDL_WINDOWPOS_CENTERED permet de centrer la fen�tre dans l'�cran de l'utilisateur
        //X_WINDOW et Y_WINDOW sont des constantes d�terminant la taille de la fen�tre SDL2
        //SDL_WINDOW_SHOWN pr�cise que la fen�tre doit �tre affich�e

        //Cr�ation du renderer et de la texture, seulement si l'�tape pr�c�dente n'a pas �chou�e
        if(pWindow!=NULL)
        {
            pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
            SDL_RenderClear(pRenderer);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(5000);
              //----------------------------------------------------------------------------//
            //Cr�ation d'une texture � partir d'un PNG
            SDL_SetRenderTarget(pRenderer, NULL); //red�finitions de la zone de travail
            SDL_Surface* pImage = IMG_Load("meth.png");
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,pImage);

            SDL_FreeSurface(pImage);

            if (Image == NULL)
              printf("Erreur de chargement de l'image : %s", pImage);

            SDL_Rect myRect;
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);//R�cup�re le format de l'image

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);

            SDL_Delay(5000);
            //----------------------------------------------------------------------------//
        }

        SDL_DestroyWindow(pWindow); //On supprime la fen�tre
        SDL_Quit(); //On quitte SDL2
    }

    return 0;
}
