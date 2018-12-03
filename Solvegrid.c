#include"sudoku.h"

void filetogrid(FILE* fileSudoku, Grid* solution)
{

	char stra[SIZE];
	char* strb;
	char* strc;

	int i = 0, j = 0;
	Grid new;

	if (fileSudoku != NULL)
	{
		while (!feof(fileSudoku))
		{
			fgets(stra, 20, fileSudoku);
			strb = strtok(stra, " ");
			strc = strb;
			if (j >= 8)
			{
				j = 0;
				i++;
			}
			new.Grid_contenet.grid[i][j] = atoi(strc);

			while (1)
			{
				strb = strtok(NULL, " ");
				if (strb == NULL)
					break;
				if (!strcmp(strb, "\n"))
					break;
				strc = strb;
				j++;
				new.Grid_contenet.grid[i][j] = atoi(strc);
			}

		}
	}
	*solution = new;
	fclose(fileSudoku);
}

void gridtofile(FILE* fileSudoku, Grid grid_solution)
{
	printf("\n\n ====Saving the solution on a file!!!========\n");
	fileSudoku = fopen("solutionfile.csv", "w");
	if (fileSudoku == NULL)
	{
		printf("Problem while opning the file");
		exit(1);
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fprintf(fileSudoku, "%d ", grid_solution.Grid_contenet.grid[i][j]);
		}
		fprintf(fileSudoku, " \n");
	}
	fclose(fileSudoku);
}

void printfgrid(Grid new)
{
	printf(" \n \t");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf(" %d ", new.Grid_contenet.grid[i][j]);
			if ((j + 1) % 3 == 0)
				printf("|");
		}
		printf(" \n \t");
		if ((i + 1) % 3 == 0)
			printf("-------------------------------");
		printf(" \n \t");
	}
	printf(" \n");
	printf(" \n");
}

void copy_grid(List_grids* gridstack) {
	Grid* new_grid = malloc(sizeof(Grid));
	Grid* head_grid = gridstack->head;
	new_grid->Grid_contenet = head_grid->Grid_contenet;
	new_grid->Grid_contenet.pos.last_number_used = 0;
	new_grid->next_grid = gridstack->head;
	gridstack->head = new_grid;
}

void printstack(List_grids* gridstack)
{
	int j = 0;
	for (Grid* i = gridstack->head; i->next_grid != NULL; i = i->next_grid)
	{
		j++;
		printf("\n GRille nbr: %d \n", j);
		printfgrid(*i);
	}
}

void distack(List_grids* gridstack)
{
	Grid* todelt = gridstack->head;
	gridstack->head = gridstack->head->next_grid;
	free(todelt);
}

int find_empty_element(coordonees* first_zero, Grid grid) {
	int i = 0, j = 0;
	while (i < 9 && grid.Grid_contenet.grid[i][j] != 0)
	{
		j++;
		if (j > 8)
		{
			i++;
			j = 0;
		}
	}
	if (grid.Grid_contenet.grid[i][j] == 0)
	{
		first_zero->x = j;
		first_zero->y = i;
		first_zero->last_number_used = 0;
		if (i < 3)
		{
			first_zero->ymax = 3;
			first_zero->ymin = 0;
		}
		else if (i < 6)
		{
			first_zero->ymax = 6;
			first_zero->ymin = 3;
		}
		else
		{
			first_zero->ymax = 9;
			first_zero->ymin = 6;
		}
		if (j < 3)
		{
			first_zero->xmax = 3;
			first_zero->xmin = 0;
		}
		else if (j < 6)
		{
			first_zero->xmax = 6;
			first_zero->xmin = 3;
		}
		else
		{
			first_zero->xmax = 9;
			first_zero->xmin = 6;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int test_number_authorisation(int n, coordonees* pos, Grid grid)
{
	Grid i = *grid.next_grid;
	int k = 0;
	if (n <= i.Grid_contenet.pos.last_number_used)
	{
		//printf("\n %d faux deja esseyé!!",n);
		return 0;
	}

	for (k = 0; k < 9; k++)
	{
		if (n == grid.Grid_contenet.grid[pos->y][k])
		{
			//printf("\n %d faux ligne !!", n);
			return 0;
		}
		else if (n == grid.Grid_contenet.grid[k][pos->x])
		{
			//printf("\n %d faux colone!!", n);
			return 0;
		}
	}
	//printf("\n ");
	for (k = pos->ymin; k < pos->ymax; k++)
	{
		for (int j = pos->xmin; j < pos->xmax; j++)
		{
			if (n == grid.Grid_contenet.grid[k][j])
			{

				return 0;
			}
		}
		//printf("\n ");
	}

	//printf("\n %d vrai!!", n);
	return 1;
}

int fill_element(coordonees* pos, Grid* grid)
{
	for (int n = 1; n < 10; n++)
	{
		if (test_number_authorisation(n, pos, *grid))
		{
			grid->Grid_contenet.grid[pos->y][pos->x] = n;
			grid->next_grid->Grid_contenet.pos.last_number_used = n;
			return 1;
		}
	}
	return 0;
}

void solvegrid(FILE* fileSudoku)
{
	Grid* solution_grid = NULL;
	List_grids solution_stack;
	coordonees empty;
	int fill_success = 1;
	int count = 0;
	solution_grid = malloc(sizeof(Grid));
	solution_grid->next_grid = NULL;
	filetogrid(fileSudoku, solution_grid);
	printf("\n\t***\tGrid to Solve\t*** \n");
	printfgrid(*solution_grid);
	solution_stack.head = solution_grid;
	printf("\n please wait...");
	while (find_empty_element(&empty, *solution_stack.head) != 0)
	{
		copy_grid(&solution_stack);
		fill_success = fill_element(&empty, solution_stack.head);
		//printfgrid(*solution_grid);
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
	gridtofile(fileSudoku, *solution_stack.head);
	printf("\n iteration number: %d\n", count);
}

int get_files_name(FILE* fileslist, files_adresse* list_of_files)
{
	int i = 0;
	char stra[SIZE];
	char *strb;
	if (fileslist != NULL)
	{
		while (!feof(fileslist))
		{
			fgets(stra, SIZE, fileslist);
			list_of_files->names[i] = malloc(SIZE * sizeof(char));
			strcpy(list_of_files->names[i], strtok(stra, "\n"));
			i++;
		}
	}
	list_of_files->count_files = i;
	return 1;
}