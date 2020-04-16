#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define X_WINDOW 500
#define Y_WINDOW 500

#define LARGEUR_TILE 24  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13

//main
int main(int argc, char *argv[]) //arguments obligatoire pour compiler en SDL
{
	char* table[] = {
	"000000000000000",
	"000000000000000",
	"000000000000000",
	"000000000000000",
	"100000000111110",
	"000000000000000",
	"000000000000000",
	"000000000000000",
	"003400022220022",
	"005600000000000",
	"005600000000000",
	"005600000000000",
	"777777777777777"};

    SDL_Window *pWindow=NULL; //Pointeur sur la fenêtre
    SDL_Renderer *pRenderer=NULL; //Pointeur sur le Rendus

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

            ///////////////////////////////////////////////////////////////////////////////////

            SDL_SetRenderTarget(pRenderer, NULL);
            SDL_Surface* pImage = IMG_Load("tileset1.png");
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

            ///////////////////////////////////////////////////////////////////////////////////

            SDL_RenderClear(pRenderer);
            
            int i,j;
			SDL_Rect Rect_dest;
			SDL_Rect Rect_source;
			Rect_source.w = LARGEUR_TILE;
			Rect_source.h = HAUTEUR_TILE;

			for(i=0; i<NOMBRE_BLOCS_LARGEUR; i++)
			{
				for(j=0; j<NOMBRE_BLOCS_HAUTEUR; j++)
				{
					Rect_dest.x = i*LARGEUR_TILE;
					Rect_dest.y = j*HAUTEUR_TILE;
					Rect_source.x = (table[j][i]-'0') * LARGEUR_TILE;
					Rect_source.y = 0;
					SDL_RenderCopy(pRenderer, Image, &Rect_source, &Rect_dest);
					SDL_RenderPresent(pRenderer);
				}
			}

            SDL_Delay(5000);

            //Création d'une texture à partir d'un PNG
            /*
            SDL_SetRenderTarget(pRenderer, NULL); //redéfinitions de la zone de travail
            SDL_Surface* pImage = IMG_Load("Char_3.png");
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

            ///////////////////////////////////////////////////////////////////////////////////

            SDL_Surface* iImage = IMG_Load("Char_3.png");
            SDL_Texture* aImage = SDL_CreateTextureFromSurface(pRenderer,iImage);

            SDL_FreeSurface(iImage);

            SDL_Rect aRect;
            aRect.x = 0;
            aRect.y = 0;

            int quit = 0;
            SDL_Event event;

            SDL_QueryTexture(aImage, NULL, NULL, &aRect.w, &aRect.h);
            aRect.w = aRect.w / 5;

            if (Image == NULL)
              printf("Erreur de chargement de l'image : %s", pImage);
          	else{
          		while(!quit)
	            {
	            	SDL_PollEvent(&event);

	            	Uint32 ticks = SDL_GetTicks();
	            	Uint32 sprite = (ticks / 100) % 5;

	            	SDL_Rect srcrect = {sprite * aRect.w, 0, aRect.w, aRect.h};
	            	SDL_Rect dstrect = {100, 100, aRect.w, aRect.h};

	            	switch(event.type)
	            	{
	            		case SDL_MOUSEBUTTONDOWN :
	            			quit = 1;
	            			break;
	            	}

	            	SDL_RenderClear(pRenderer);
	            	SDL_RenderCopy(pRenderer, aImage, &srcrect, &dstrect);
	            	SDL_RenderPresent(pRenderer);
	            }
          	}

          	SDL_DestroyTexture(aImage);*/
          	SDL_DestroyTexture(Image);
        }

        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow(pWindow); //On supprime la fenêtre
        SDL_Quit(); //On quitte SDL2
    }

    return 0;
}
