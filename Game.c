#include"sudoku.h"

void game()
{
	int choice;
	int endGame = 0;
	int score = 0;
	Grid* solution_grid = NULL;
	Grid* game_grid = NULL;
	contenet original;
	List_grids solution_stack;
	int fill_success = 1;
	int count = 0;

	FILE* fileSudoku = NULL;
	printf("choose level plz\n");
	printf(" \n\n\t[1]easy");
	printf(" \n\t[2]midim");
	printf(" \n\t[3]hard\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		fileSudoku = fopen("easy.csv", "r");
		break;
	case 2:
		fileSudoku = fopen("Grids/fileSudoku.csv", "r");
		break;
	case 3:
		fileSudoku = fopen("Grids/fileSudoku.csv", "r");
		break;
	default:
		printf("Wrong number !");
		break;
	}
	solution_grid = malloc(sizeof(Grid));
	solution_grid->next_grid = NULL;
	game_grid = malloc(sizeof(Grid));
	game_grid->next_grid = NULL;
	filetogrid(fileSudoku, game_grid);
	solution_grid = solvegridforThegame(game_grid);
	original = game_grid->Grid_contenet;
	coordonees userpos;
	while (endGame == 0) {
		game_grid = playscreen(game_grid, &score, &userpos,original);
		getscore(&score, game_grid, solution_grid, &userpos, &endGame);
	}
}

Grid* playscreen(Grid* game_grid, int *score, coordonees* pos,contenet original)
{
	printf(" \n\tYour scror:%d\n", *score);
	printfgrid(*game_grid);
	printf(" \n\tgive a position and a value please:\n");
	printf(" \n\t\t x=");
	scanf("%d", &pos->x);
	printf(" \n\t\t y=");
	scanf("%d", &pos->y);
	printf(" \n\t\t value=");
	scanf("%d", &pos->last_number_used);
	if (pos->last_number_used > 9 || pos->x > 8 || pos->y > 8)
	{
		printf(" \n\t\t erreur!");
		printf(" \n\t\t please respecte this:");
		printf(" \n\t\t val<10  x<9  y<9");
	}
	else if(original.grid[pos->x][pos->y]!=0)
		printf(" \n\t\t erreur!  you can't change the value in this position");
	else
		game_grid->Grid_contenet.grid[pos->x][pos->y] = pos->last_number_used;
	return game_grid;
}
void getscore(int *score, Grid* game_grid, Grid* solution_grid, coordonees* pos, int* end)
{
	//printfgrid(*solution_grid);
	if (solution_grid->Grid_contenet.grid[pos->x][pos->y] == pos->last_number_used)
		*score = *score + 5;
	else
	{
		*score--;
	}
}
Grid* solvegridforThegame(Grid* solution_grid)
{
	List_grids solution_stack;
	int fill_success = 1;
	int count = 0;
	solution_stack.head = solution_grid;
	coordonees empty;
	while (find_empty_element(&empty, *solution_stack.head) != 0)
	{
		copy_grid(&solution_stack);
		fill_success = fill_element(&empty, solution_stack.head);
		if (fill_success == 0)
		{
			distack(&solution_stack);
			distack(&solution_stack);
		}
		count++;
		if (empty.x == 8 && empty.y == 8)
		{
			break;
		}
	}
	solution_grid = solution_stack.head;
	return solution_grid;
}