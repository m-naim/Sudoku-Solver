#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 25

typedef struct _coordonees {
	int x;
	int y;
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	int last_number_used;
}coordonees;

typedef struct _contenet
{
	int grid[9][9];
	coordonees pos;
}contenet;

typedef struct _Grid
{
	contenet Grid_contenet;
	struct _Grid* next_grid;
}Grid;
//definir le nom de la structure, début, fin et le contenu (grille)
typedef struct _List_grids{  

	Grid* head;
}List_grids;

typedef struct _FILES_ADRESSE {
	char** names;
	int count_files;
}files_adresse;


void filetogrid(FILE* fileSudoku,Grid* gridstack); //convertir le fichier en une grille et la mettre au debut de la pile 
void print_grid(Grid* gridtodisplay);  //afficher la grille dans la console

void copy_grid(List_grids* gridstack); //faire une copie de la derniere grille dans la pile 

//fonctions nécéssaire pour remplir la grille
int find_empty_element(coordonees* first_zero, Grid grid); //chercher la première case vide puis la remplir 
int test_number_authorisation(int n,coordonees* pos, Grid grid);  //test si le nombre vérifie les conditions
int fill_element(coordonees* pos, Grid* grid);


void distack(List_grids* gridstack); // on dépile
void gridtofile(FILE* fileSudoku,Grid grid_solution); //sauvegarder la grille résolu dans un fichier 

void printfgrid(Grid new);
void printstack(List_grids* gridstack);

void solvegrid(FILE* fileSudoku);
int get_files_name(FILE* fileslist, files_adresse* list_of_files);

void intro();
void game();
Grid* playscreen(Grid* game_grid, int *score, coordonees* pos,contenet original);
void getscore(int *score, Grid* game_grid, Grid* solution_grid, coordonees* pos);
Grid* solvegridforThegame( Grid* solution_grid);
int solvegridforstats(FILE* fileSudoku);

int stats(void);
