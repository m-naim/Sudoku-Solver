#include"sudoku.h"

int main(int argc, char *argv[])
{
	int i = 0;
	int choice;
	FILE* fileSudoku = NULL;
	FILE* fileslist = NULL;
	
	if (argc>1)
	{
		printf("%s", argv[1]);
		fileSudoku = fopen(argv[1], "r");
		if (fileSudoku == NULL)
		{
			printf("\nProblem while opning the file");
			printf("\n\ntape enter to exit");
			getchar();
			exit(EXIT_FAILURE);
		}
		solvegrid(fileSudoku);
	}
	else
	{	
		while (1)
		{
			intro();
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				printf("\n\t***Game mode***\t\n");
				game();
				break;
			case 2:
				stats();
				break;
			case 3:
				exit(EXIT_SUCCESS);
			}
		}
	}
	printf("\ntape enter to exit..");
	getchar();
	getchar();
	return EXIT_SUCCESS;
}

	void intro()
	{
		printf(" bienvenu a sudo game");
		printf(" \n\n\nchoose a mode please");
		printf(" \n\n\t[1]Game mode");
		printf(" \n\t[2]stats mode\n");
		printf(" \t[3]exit\n");
	}
