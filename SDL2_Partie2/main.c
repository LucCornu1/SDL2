#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define LARGEUR_TILE 24  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13

const int FPS=1;

void Afficher(SDL_Renderer*, SDL_Texture*, char**, int, int, int, int);

int main(int argc, char *argv[])
{
    SDL_Window *pWindow=NULL;           //Pointeur sur la fenêtre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsulé dans window

    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0) //INIT_EVERYTHING = initialise l'audio, la vidéo, les contrôles,... cf; SDL wiki/API by name/SDL_Init
    {
        pWindow = SDL_CreateWindow("TILESET_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, SDL_WINDOW_SHOWN);

        //si succès, créer window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

            //------------------------------------------------------------------------------------------------//
            //Tilemapping

            char* table[] = {
            	"000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000022222221111111122222220000",
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000000000000000000022220000",
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000000221220000000022220000",
                "000000000000000000000000000000",
                "003400000000000000000000000000",
                "005600000000000003400000000000",
                "005600000000000005600000000000",
                "005600000000000005600000000000",
                "777777777777777777777777777777"
            };

            unsigned long int nTempsActuel=0;
            unsigned long int nTempsPrecedent=0;
            int nDeltaTime = div(1000,FPS).quot;
            int xBase = 0;
            int yBase = 0;

            SDL_Surface *tileset = NULL;
            SDL_Texture *textuTil = NULL;
            SDL_Event event;
            int continuer = 1, tempsPrecedent = 0, tempsActuel = 0;

            tileset = IMG_Load("tileset1.png");
            if (tileset == NULL)
            {
                fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
                goto quit;
            }

            textuTil = SDL_CreateTextureFromSurface(pRenderer, tileset);
            if (textuTil == NULL)
            {
                fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
                goto quit;
            }
            SDL_FreeSurface(tileset);

            Afficher(pRenderer, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR,0,0);
            while(continuer)
            {
                SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                continuer = 0;
                                break;

                            //Gestion des touches
                            case SDLK_d:
                            	if(xBase < NOMBRE_BLOCS_LARGEUR) //Si l'utilisateur appuie sur la touche d ET qu'il n'arrive pas en bout de tableau
                            		xBase = xBase + 1; //Alors il avance d'un block vers la droite
                            	break;

                            case SDLK_q:
                            	if(xBase > 0) //Si l'utilisateur appuie sur la touche q ET qu'il n'arrive pas en bout de tableau
                            		xBase = xBase - 1; //Alors il avance d'un block vers la gauche
                            	break;

                            case SDLK_s:
                            	if(yBase < 4) //Si l'utilisateur appuie sur la touche s ET qu'il n'arrive pas en bout de tableau
                            		yBase = yBase + 1; //Alors il avance d'un block vers le bas
                            	break;

                            case SDLK_z:
                            	if(yBase > 0) //Si l'utilisateur appuie sur la touche z ET qu'il n'arrive pas en bout de tableau
                            		yBase = yBase - 1; //Alors il avance d'un block vers le haut
                            	break;
                        }
                        break;
                }

                nTempsActuel = SDL_GetTicks();
                if (nTempsActuel > nTempsPrecedent + nDeltaTime) //On effectue l'affichage à chaque frame.
                {
                    Afficher(pRenderer, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR, xBase, yBase);
                    nTempsPrecedent = nTempsActuel;
                }

                SDL_RenderPresent(pRenderer);
            }

            //------------------------------------------------------------------------------------------------//

            quit: //On supprime tout ce qui à été créé
            SDL_DestroyTexture(textuTil);
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
        }
    }

    return 0;
}

void Afficher(SDL_Renderer* pRenderer, SDL_Texture* textuTil, char** table, int nombre_blocs_largeur, int nombre_blocs_hauteur,int iBase, int jBase)
//But : Afficher la tilemap
//Entree : le Renderer, une texture, la tilemap, la largeur, la hauteur et le minimum i à afficher
//Sortie : rien (mais "colle" la tilemap)
{
    int i, j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = LARGEUR_TILE;
    Rect_dest.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.h = HAUTEUR_TILE;
    for(i = iBase ; i < NOMBRE_BLOCS_LARGEUR + iBase; i++) //On commence à i = x pour arriver à NOMBRE_BLOCS_LARGEUR + x
    {
        for(j = jBase ; j < NOMBRE_BLOCS_HAUTEUR + jBase; j++)
        {
            Rect_dest.x = (i - iBase) * LARGEUR_TILE;
            Rect_dest.y = (j - jBase) * HAUTEUR_TILE;
            Rect_source.x = (table[j][i] - '0') * LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_RenderCopy(pRenderer, textuTil, &Rect_source, &Rect_dest);
        }
    }
}
