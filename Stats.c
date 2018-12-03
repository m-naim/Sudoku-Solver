#include"sudoku.h"
int stats()
{
	char **list = NULL;
	char *str;
	files_adresse list_of_files;
	FILE* fileSudoku = NULL;
	FILE* fileStats = NULL;
	FILE* fileslist = NULL;
	int i, tmp;
	printf("\n\t***stats mode***\t\n");
	list_of_files.names = malloc(SIZE * sizeof(char*));
	fileslist = fopen("filesliste.csv", "r");
	fileStats = fopen("fileStats.csv", "w");
	if (fileslist == NULL)
	{
		printf("\nProblem while opning the file");
		printf("\n\ntape enter to exit");
		getchar();
		exit(EXIT_FAILURE);
	}
	get_files_name(fileslist, &list_of_files);
	for (i = 0; i < list_of_files.count_files;i++)
	{
		printf("\n %s\t", list_of_files.names[i]);
		if (list_of_files.names[i][6] == 'f')
			printf("facile \t");
		else if (list_of_files.names[i][6] == 'd')
			printf("difficile \t");
		else
			printf("moyen \t");
		fileSudoku = fopen(list_of_files.names[i], "r");
		if (fileSudoku == NULL)
		{
			printf("\nProblem while opning the file");
			printf("\n\ntape enter to exit");
			getchar();
			exit(EXIT_FAILURE);
		}
		tmp = solvegridforstats(fileSudoku);

		printf(" %d \n", tmp);
		//fprintf(fileStats, "%s;%d;\n", str,tmp);
	}
	return 0;
}

int solvegridforstats(FILE* fileSudoku)
{
	Grid* solution_grid = NULL;
	List_grids solution_stack;
	coordonees empty;
	int fill_success = 1;
	int count = 0;
	solution_grid = malloc(sizeof(Grid));
	solution_grid->next_grid = NULL;
	filetogrid(fileSudoku, solution_grid);
	solution_stack.head = solution_grid;
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
	return count;
}