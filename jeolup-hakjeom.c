#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INSERT 1
#define DELETE 2
#define STATUS 3
#define QUIT 4
#define SIZE 99

void show_menu();
int get_command();
void insert_class(int *n, char classes[][SIZE], float credits[], float credits_of_last_class[]);
void delete_last_class(int *n, char classes[][SIZE], float credits[], float credits_of_last_class[]);
void show_status(int *n, char classes[][SIZE], float credits[]);
void select_option(char *classname, int credit);
int ask_for_credit();

int main()
{
	int cmd;			// chosen command
	int n = 0;			// number of current classes
	char classes[SIZE][SIZE];	// can store SIZE classes
	float credits[12] = {0};	// for all the credit categories below
	float credits_of_last_class[12];// for deletion of previous class

	/*
	 * [1] = total major credits
	 * [2] = english (EF, EC, ERC, EAP)
	 * [3] = professor team meeting
	 * [4] = social service or HGU character edu
	 * [5] = chapel (no credits, only # of times)
	 * [6] = basic science and math
	 * [7] = ICT convergence basics
	 * [8] = faith and worldviews
	 * [9] = etc. liberal arts classes
	 * [10] = free choice of 12 points
	 */

	for(int i = 0; i < SIZE; i++)
		strcpy(classes[i], "\0");

	do {
		cmd = get_command();
		switch (cmd) {
			case INSERT : insert_class(&n, classes, credits, credits_of_last_class);
				      break;
			case DELETE : delete_last_class(&n, classes, credits, credits_of_last_class);
				      break;
			case STATUS : show_status(&n, classes, credits);
				      break;
			case QUIT : printf("\n");
				    printf("	Have a nice day.\n");
				    break;
			default : printf("\n\n");
				  printf("	Invalid input, please try again!\n\n\n");
			}
	} while (cmd != QUIT);

	return 0;
}

int get_command()
{
	int cur_command;
	show_menu();
	scanf("%d", &cur_command);
	return cur_command;
}

void show_menu()
{
	printf("\n\n -- MENU -- \n");
	printf("1. Insert a new class\n");
	printf("2. Delete previous class\n");
	printf("3. Show status of your curriculum\n");
	printf("4. Quit\n\n");
	printf("	Select a command: ");
}

void insert_class(int *n, char classes[][SIZE], float credits[], float credits_of_last_class[])
{
	float cur_credit;
	int cur_class_type;
	char temp_class[SIZE];

	printf("\n	Now Entering new class:\n");
	printf("\n	What is the class' name? (without space) ");

	scanf("%s", temp_class);

	strcpy(classes[*n], temp_class);

	printf("\n");
	printf("		1 = major class\n");
	printf("		2 = english class (EF, EC, ERC, EAP)\n");
	printf("		3 = professor team meeting\n");
	printf("		4 = community service or HGU character education\n");
	printf("		5 = chapel\n");
	printf("		6 = basic science and math\n");
	printf("		7 = ICT convergence basics\n");
	printf("		8 = faith and worldviews\n");
	printf("		9 = etc. liberal arts classes\n");
	printf("		10 = free choice (liberal or non-liberal)\n\n");

	printf("	Please enter a number that corresponds with [%s] class: ", temp_class);
	scanf("%d", &cur_class_type);

	if(cur_class_type < 1 || cur_class_type > 9)
	{
		printf("\nWrong number... exiting\n");
		printf("\n------------------------------------------------------------");
		return;
	}

	for(int i = 1; i <= 11; i++)
		credits_of_last_class[1] = 0;

	int temp;
	switch (cur_class_type) {
		case 1 :
			temp = ask_for_credit();
			credits[1] += temp;
			credits_of_last_class[1] = temp;
			break;
		case 2 :
			credits[2] += 3;
			credits_of_last_class[2] = 3;
			break;
		case 3 : 
			credits[3] += 0.5;
			credits_of_last_class[3] = 0.5;
			break;
		case 4 :
			credits[4] += 1;
			credits_of_last_class[4] = 1;
			break;
		case 5 :
			credits[5] += 1;
			credits_of_last_class[5] = 1;
			break;
		case 6 :
			temp = ask_for_credit();
			credits[6] += temp;
			credits_of_last_class[6] = temp;
			break;
		case 7 : 
			temp = ask_for_credit();
			credits[7] += temp;
			credits_of_last_class[7] = temp;
			break;
		case 8 : 
			temp = ask_for_credit();
			credits[8] += temp;
			credits_of_last_class[8] = temp;
			break;
		case 9 : temp = ask_for_credit();
			 credits[9] += temp;
			 credits_of_last_class[9] = temp;
		case 10 :
			 temp = ask_for_credit();
			 credits[10] += temp;
			 credits_of_last_class[10] = temp;
	}

	printf("\n	New class [%s] has been added!\n", classes[*n]);
	*n += 1;
	printf("\n------------------------------------------------------------\n");
}

int ask_for_credit()
{
	float cur_class_credit;
	printf("\n	How many credits does this class have? ");
	scanf("%f", &cur_class_credit);
	return cur_class_credit;
}

void delete_last_class(int *n, char classes[][SIZE], float credits[], float credits_of_last_class[])
{
	char answer[10];

	printf("\n	Now Deleting previous class:\n\n");

	if(*n == 0) {
		printf("	There is no class! Please insert a new class!\n\n");
		printf("	Press any key to continue...	");
		getch();
		printf("\n\n-------------------------------------------------------------\n");
		return;
	}

	*n -= 1;

	printf("	Delete[%s]? (yes/no) ", classes[*n]);
	scanf("%s", answer);
	printf("\n");

	if (strcmp(answer, "yes")==0 || strcmp(answer, "YES")==0 || strcmp(answer, "y")==0 || strcmp(answer, "Y")) {
		for (int i = 1; i <= 11; i++)
		{
			credits[i] -= credits_of_last_class[i];
		}
		printf("	Deletion of [%s] class successful\n\n", classes[*n]);
		strcpy(classes[*n], "\0");
	} else if (strcmp(answer, "no")==0 || strcmp(answer, "NO")==0 || strcmp(answer, "n")==0 || strcmp(answer, "N")) {
		printf("	Aborting (Delete previous class)...\n\n");
	} else {
		printf("	Not within set options... aborting...\n\n");
	}

	printf("\n\n-------------------------------------------------------------\n");
}

void show_status(int *n, char classes[][SIZE], float credits[])
{
	float lib_arts_total = 0;
	float total_sum = 0;

	for(int i = 2; i <= 9; i++)
		lib_arts_total += credits[i];
	lib_arts_total -= credits[5];	//subtracting chapel

	total_sum = lib_arts_total + credits[1] + credits[10];

	printf("\n	Now Showing current status:\n\n");

	printf("	%d classes inserted so far:\n", *n);
	
	for (int i = 0; i < *n; i++)
		printf("		%s\n", classes[i]);

	printf("\n\n	Now showing credits:\n\n");
	printf("	%3.0f/60 MAJOR credits\n", credits[1]);
	printf("		%3.0f/3+ english (EF, EC, ERC, EAP)\n", credits[2]);
	printf("		%3.1f/3  professor team meeting (0.5 per semester)\n", credits[3]);
	printf("		%3.0f/3  community service, HGU character education\n", credits[4]);
	printf("		%3.0f/6  chapel (no credits, only to show how many)\n", credits[5]);
	printf("		%3.0f/18 basic science and math\n", credits[6]);
	printf("		%3.0f/2  ICT convergence basics\n", credits[7]);
	printf("		%3.0f/9  faith and worldviews\n", credits[8]);
	printf("		%3.0f/14 etc. liberal arts classes\n", credits[9]);
	printf("	%3.1f/58 TOTAL LIBERAL ARTS credits\n", lib_arts_total);
	printf("		%3.0f/12 free choice of 12 points\n", credits[10]);
	printf("	%3.1f/130 TOTAL SUM OF CREDITS\n\n", total_sum);

	printf("\n\n-------------------------------------------------------------\n");
}

