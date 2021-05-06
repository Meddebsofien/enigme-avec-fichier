#ifndef ENIGME_H_
#define ENIGME_H_
/** 
* @struct rep
* @brief struct for reponse 
*/

typedef struct {

char rep1[10];
SDL_Surface *r1;             // surface reponse1
SDL_Rect position_rep1;              // Rectangle pour la reponse 1 
char rep2[10];
SDL_Surface *r2;               // surface reponse2 
SDL_Rect position_rep2;          // Rectangle pour la reponse 2
char rep3[10];            
SDL_Surface *r3;        // surface reponse3
SDL_Rect position_rep3;    // Rectangle pour la reponse 3
char rep_vrai[10];
}rep; 
/** 
* @struct Enigme 
* @brief struct for Enigme
*/

typedef struct { 
char question[300];
rep reponse; 
SDL_Surface *ques;                // surface question 
SDL_Rect position_question;        // Rectangle pour question 
SDL_Surface *fonds;
SDL_Surface *afficherTemps;
SDL_Rect positionfonds;
SDL_Rect positionTemps;
int gameover;

int tempsActuel , tempsPrecedent , compteur ,f;
char temps[20];
TTF_Font *police3 ;
}Enigme;

int aleatoire ();
void genererEnigme (char* fichier,Enigme *E);
Enigme afficherEnigme (Enigme E, SDL_Surface * surface_enigme);
int resolutionEnigme (Enigme E, SDL_Surface *surface_enigme,int a,int b);
#endif