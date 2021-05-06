/** 
* @file Enigme.c 
* @brief Testing Program. 
* @author sofien 
* @version 0.1 
* @date Apr 04, 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Enigme.h"
/** 
* @brief To choisir un entier au hasard . 
* @param Nothing
* @return le numero de la  ligne de question afficheé
*/ 

int aleatoire ()
{
	int i,j,x,k,n=10;
	int tab[n];
	for(j=0;j<n;j++)
		tab[j]=j;

	srand(time(NULL));
	i=rand()%n;
    x=tab[i];
    for(k=i;k<n;k++)
    	tab[k]=tab[k+1];
    n--;
	return x;
}
/** 
* @brief To genere l'enigme. 
* @param the enigme
* @param un fichier ou l'enigme se trouve 
* @return Nothing 
*/ 

void genererEnigme (char* fichier,Enigme *E)
{
FILE *f=NULL;
int numero,i,j=0;
TTF_Font *police = NULL;
TTF_Font *police1 = NULL;
SDL_Color couleurJaune = {200,200,20};
 police = TTF_OpenFont("aaaa.ttf",45);
 police1 = TTF_OpenFont("1.ttf",45);

 E->fonds=NULL;
 E->afficherTemps=NULL;
 E->positionfonds;
 E->positionTemps.x=840;
 E->positionTemps.y=0;

 E->tempsActuel=0;
 E->tempsPrecedent=0;
 E->compteur=20;
 E->f=0;
 E->police3 =NULL;

 //E->temps[20] ="o";
 E->fonds=IMG_Load("back2.png");
     E->positionfonds.x=0;
     E->positionfonds.y=0;
E->police3 = TTF_OpenFont("Sketch.ttf", 65);
E->gameover=0;

char caractereActuel;
char chaine[256]="";
numero=aleatoire();
f=fopen(fichier,"r");
if(f!=NULL)
{while(fgets(chaine,256,f)!=NULL)
{
	j++;

   if(j==numero)
{
i=0;
                do
               {
                caractereActuel = fgetc(f);                      // Recuperer la question 
                E->question[i]=caractereActuel;   
                  i++;                                               
                }while(caractereActuel!='.');

i=0;
                do
               {
                caractereActuel = fgetc(f);                          // Recuperer la proposition 1
                E->reponse.rep1[i]=caractereActuel;
                i++;
               }while(caractereActuel!='.');


i=0;
               do
               {
               caractereActuel = fgetc(f);                                // Recuperer la proposition 2
               E->reponse.rep2[i]=caractereActuel;
               i++;
               }while(caractereActuel!='.');
i=0;

               do
               {
               caractereActuel = fgetc(f);
               E->reponse.rep3[i]=caractereActuel;                       // Recuperer la proposition 3
               i++;

               }while(caractereActuel!='.');
i=0;

               do
               {caractereActuel=fgetc(f);                                   // Recuperer la reponse vrai
                E->reponse.rep_vrai[i]=caractereActuel;
                i++;
               }while(caractereActuel!='.');

}

}
fclose(f);


}

                       // Écriture du texte dans la SDL_Surface question
     E->ques =TTF_RenderText_Blended(police,E->question,couleurJaune);
     E->position_question.x = 100;
     E->position_question.y =50;

                       // Écriture du texte dans la SDL_Surface reponse1

    E->reponse.r1=TTF_RenderText_Blended(police1,E->reponse.rep1,couleurJaune);
    E->reponse.position_rep1.x = 200;
    E->reponse.position_rep1.y =200 ;
 E->reponse.position_rep1.w=E->reponse.r1->w;
                     // Écriture du texte dans la SDL_Surface reponse2

    E->reponse.r2=TTF_RenderText_Blended(police1,E->reponse.rep2,couleurJaune);
    E->reponse.position_rep2.x = 200;
    E->reponse.position_rep2.y =300 ;
E->reponse.position_rep2.w=E->reponse.r2->w;
                       // Écriture du texte dans la SDL_Surface reponse3

    E->reponse.r3=TTF_RenderText_Blended(police1,E->reponse.rep3,couleurJaune);
    E->reponse.position_rep3.x = 200;
    E->reponse.position_rep3.y =400 ;
    E->reponse.position_rep3.w=E->reponse.r3->w;
/*TTF_CloseFont(police);
TTF_CloseFont(police1);
TTF_Quit();*/
}
/** 
* @brief pour afficher l'enigme. 
* @param enigme
* @param la screen  
* @return Enigme
*/ 

Enigme afficherEnigme (Enigme E, SDL_Surface * surface_enigme)
{

SDL_Color couleurBlanche = {255, 255, 255};

sprintf(E.temps, "Temps : %d", E.compteur);
E.afficherTemps = TTF_RenderText_Solid(E.police3, E.temps,couleurBlanche);

            E.tempsActuel = SDL_GetTicks();
            if (E.tempsActuel - E.tempsPrecedent >= 1000) /* Si 100ms au moins se sont écoulées */
            {
                E.compteur -= 1;
                if(E.compteur==0)
                {
                  SDL_Delay(1000);
                  E.gameover=1;
                }
                E.tempsPrecedent = E.tempsActuel; /* On met à jour le tempsPrecedent */
             }
SDL_BlitSurface(E.fonds, NULL,surface_enigme,&E.positionfonds); 

SDL_BlitSurface(E.ques,&E.positionfonds,surface_enigme,&E.position_question);


SDL_BlitSurface(E.reponse.r1,&E.positionfonds,surface_enigme,&E.reponse.position_rep1);


SDL_BlitSurface(E.reponse.r2,&E.positionfonds,surface_enigme,&E.reponse.position_rep2);


SDL_BlitSurface(E.reponse.r3,&E.positionfonds,surface_enigme,&E.reponse.position_rep3);
SDL_BlitSurface(E.afficherTemps,&E.positionfonds,surface_enigme, &E.positionTemps);

    SDL_Flip(surface_enigme);
             
          /*  SDL_FillRect(surface_enigme, NULL, SDL_MapRGB(surface_enigme->format, 255, 255, 255));
            positionTemps.x = 840;
            positionTemps.y = 0;*/

          
          
       
           

 
    /*TTF_CloseFont(police);
    TTF_Quit();*/
    return E;
}
/** 
* @brief To initialize the background b . 
* @param Enigme
* @param surface de l'Enigme 
* @param  l'abscisse de curseur
* @param  l'ordonne de curseur
* @return 0 si la reponse est fausse 1 si la reponse est vrai
*/ 

int resolutionEnigme (Enigme E, SDL_Surface *surface_enigme,int a,int b)
{

   //
  int Reso=-1;

int w,v;



v=E.reponse.rep_vrai[0];


if (a > E.reponse.position_rep1.x && a< E.reponse.position_rep1.x + E.reponse.position_rep1.w && b >E.reponse.position_rep1.y && b < E.reponse.position_rep1.y+45)
    {
    	w=E.reponse.rep1[0];

    if(w==v)
     {
      Reso=1;
      }
    else
     {Reso=0;
     
    }


     }
else if (a > E.reponse.position_rep2.x && a< E.reponse.position_rep2.x+E.reponse.position_rep2.w && b >E.reponse.position_rep2.y && b < E.reponse.position_rep2.y+45)
    {
w=E.reponse.rep2[0];

if(w==v)
      {Reso=1;

}
    else
     {Reso=0;
     }


     }
else if (a > E.reponse.position_rep3.x && a< E.reponse.position_rep3.x+E.reponse.position_rep3.w && b >E.reponse.position_rep3.y && b < E.reponse.position_rep3.y+45)
    {w=E.reponse.rep3[0];

if(w==v)
     { Reso=1;

}
    else
     {Reso=0;

}

     }



return Reso;

}

