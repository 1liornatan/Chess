#include "All.h"

void main()
{
	int menu_choice, path_state;
	char* file_name = NULL;
	chessPos position;
	pathTree tree;
	chessPosList* knight_lst = NULL;
	BOOL section1 = OFF, section2 = OFF, section3 = OFF;
	menu_choice = menu();
	while (menu_choice != EXIT)
	{
		if (menu_choice == 1)
		{
			section1 = ON;
			getKnightStartingPosition(position);
			printf("\n");
		}
		else if (menu_choice == 2)
		{
			if (section1 == OFF)
				printf(RED "You need to choose section 1 first.\n\n" RESET);
			else
			{
				section2 = ON;
				tree = findAllPossibleKnightPaths(&position);
				system("cls");
				printf(GREEN "Tree created successfully.\n\n" RESET);
				/*printPossiblePositions(tree.root);*/
			}
		}
		else if (menu_choice == 3)
		{
			if (section1 == OFF)
				printf(RED "You need to choose section 1 first.\n\n" RESET);
			else
			{
				if (section2 == OFF)
					printf("You should have chosen section 2.\nCreating a tree by default...\n\n");
				section2 = ON;
				section3 = ON;
				knight_lst = findKnightPathCoveringAllBoard(&tree);
				if (knight_lst == NULL)
					printf("There is no path that covers all board.\n\n");
				else
				{
					printf(GREEN "A list with a path covering all board created.\n\n" RESET);
					/*printFullPath(knight_lst);*/
				}
			}
		}
		else if (menu_choice == 4)
		{
			if (section1 == OFF)
				printf(RED "You need to choose section 1 first.\n\n" RESET);
			else
			{
				if (section3 == OFF)
				{
					printf("You should have chosen section 3.\nCreating a cover list by default...\n\n");
					if (section2 == OFF)
						tree = findAllPossibleKnightPaths(&position);
					section2 = ON;
					section3 = ON;
					knight_lst = findKnightPathCoveringAllBoard(&tree);
					if (knight_lst == NULL)
						printf("There is no path that covers all board.\n\n");
					else
					{
						printf(GREEN "A list with a path covering all board created.\n\n" RESET);
						/*printFullPath(knight_lst);*/
					}
					file_name = getFileName();
					saveListToBinFile(file_name, knight_lst);
					system("cls");
					printf(GREEN "File created.\n\n" RESET);
				}
				else
				{
					file_name = getFileName();
					saveListToBinFile(file_name, knight_lst);
					system("cls");
					printf(GREEN "File created.\n\n" RESET);
				}
					freePathTree(tree);
					freeList(knight_lst);
			}
		}
		else if (menu_choice == 5)
		{
			file_name = getFileName();
			system("cls");
			path_state = checkAndDisplayPathFromFile(file_name);
			printPathState(path_state);
		}
		menu_choice = menu();
	}
	system("cls");
	endPrint();
	if (file_name != NULL)
		free(file_name);
}