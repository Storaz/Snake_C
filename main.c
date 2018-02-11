#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define MAX 20

/*
Snake qui plante au démarrage et qui ne prend pas en compte le corps du serpent
*/

typedef struct Position_joueur
{
    int joueur_x;
    int joueur_y;
}Position_joueur;

typedef struct Position_Queue
{
    int queue_x;
    int queue_y;
}Position_Queue;

//prototypes
void menu_jeu();
void creation_plateau(char[MAX][MAX]);
void gotoxy(int,int);
int wherex();
int wherey();
void creation_joueur(Position_joueur*,char[MAX][MAX]);
void creation_nourriture(char[MAX][MAX]);
void deplacement(char[MAX][MAX],Position_joueur*);




int main()
{
    char Terrain[MAX][MAX];
    Position_joueur Jouer;
    menu_jeu();
    creation_plateau(Terrain);
    creation_joueur(&Jouer,Terrain);
    creation_nourriture(Terrain);
    deplacement(Terrain,&Jouer);
    return 0;
}

void menu_jeu(){
//BUT:Afficher le menu du jeu
//ENTREE:Aucune
//SORTIE:Aucune
    printf("Vous allez jouer au jeu du snake\n");
    system("pause");
    system("cls");
}

void creation_plateau(char Terrain[MAX][MAX]){
//BUT:Afficher le plateau du jeu
//ENTREE:Le tableau
//SORTIE:Tableau remplit
    int plateau_x;
    int plateau_y;

    for(plateau_x=0;plateau_x<MAX;plateau_x++)
        {
            for(plateau_y=0;plateau_y<MAX;plateau_y++)
            {
                if(plateau_x==0 || plateau_x==(MAX-1) || plateau_y==0 || plateau_y==(MAX-1)) //Affichage du plateau
                   printf('X');
                else
                    printf(' ');
            }

            printf("\n");
             }
             system("pause");
}


//Procédures et fonctions permetttant d'utiliser le gotoxy
void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }

int wherex()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD  result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.X;
  }

int wherey()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD  result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.Y;
  }

void creation_joueur(Position_joueur* pos_joueur,char Terrain[MAX][MAX]){
//BUT:initialiser le joueur à des coordonnées définies
//ENTREE:Le terrain
//SORTIE:Le joueur
    pos_joueur->joueur_x=10;
    pos_joueur->joueur_y=10;
    gotoxy(pos_joueur->joueur_x,pos_joueur->joueur_y); //On affecte des coordonnées au joueur
    Terrain[pos_joueur->joueur_x][pos_joueur->joueur_y]='Y'; //Affichage
  }

void creation_nourriture(char Terrain[MAX][MAX]){
//BUT:Créer les aliments à ramasser
//ENTREE:Le terrain
//SORTIE:Coordonnées des aliments
    int alea_x;
    int alea_y;
    srand(time(NULL));
    if(Terrain[MAX][MAX]!='X' && Terrain[MAX][MAX]!='X'){ //On affecte une valeur aléatoire aux aliments
        alea_x = rand()%(MAX-1);
        alea_y = rand()%(MAX-1);
        Terrain[alea_x][alea_y]='!'; //Affichage de l'aliment
    }
}

void deplacement (char Terrain[MAX][MAX],Position_joueur* pos_joueur){
//BUT:Gérer le déplacement ainsi que la condition de fin
//ENTREE:Le terrain, la position du joueur ainsi que la position des aliments
//SORTIE:Aucune
    int gameover=1,plateau_x,plateau_y;
    do{
        Sleep(300);
        for(plateau_y=0;plateau_y<MAX;plateau_y++)
            {
                if(pos_joueur->joueur_x==0 || pos_joueur->joueur_x==(MAX-1) || pos_joueur->joueur_y==0 || pos_joueur->joueur_y==(MAX-1)){ //On compare si le joueur se situe sur les bordures
                    gameover=0; //Si le joueur est sur les bordures
                }
            }
        Terrain[pos_joueur->joueur_x][pos_joueur->joueur_y]=' '; //On vide l'affichage du joueur actuel pour le remplacer dès qu'il appuye sur une touche
        if(GetAsyncKeyState(VK_UP)){ //Dès que le joueur appuye sur la flèche du haut
            pos_joueur->joueur_y--; //On actualise les coordonnées du joueur
        }

        if(GetAsyncKeyState(VK_DOWN)){ //Dès que le joueur appuye sur la flèche du bas
            pos_joueur->joueur_y++; //On actualise les coordonnées du joueur
        }

        if(GetAsyncKeyState(VK_LEFT)){ //Dès que le joueur appuye sur la flèche de gauche
            pos_joueur->joueur_x--; //On actualise les coordonnées du joueur
        }

        if(GetAsyncKeyState(VK_RIGHT)){ //Dès que le joueur appuye sur la flèche de droite
            pos_joueur->joueur_x++; //On actualise les coordonnées du joueur
        }
        gotoxy(pos_joueur->joueur_x,pos_joueur->joueur_y);
        printf('Y'); //Affichage
    }while(gameover==1); //Tant que le joueur n'ets pas sur les bords, alors le jeu continue
}
