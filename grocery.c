
/* Grocery Inventory
 *
 * Author: deadend, 12/18/18 
 *
 * 1 for Fridge
 * 2 for Freezer
 * 3 for dry goods
 *
 * save to text file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define MAX 256

void refrigerator_func(void);
void freezer_func(void);
void dry_func(void);
void write_func(void);
void menu(void);
void add_entry(void);
void remove_entry(void);

int main(void)
{
	menu();
}

void menu(void)
{

	int number = 0;

	/*
	 * number = 1 // Refrierator
	 * number = 2 // Freezer
	 * number = 3; // Dry storage
	 */

	while(1)
	{
		int reply;

		puts("\n1. for Fridge\n2. for Freezer\n3. for dry shelve\n4. Add/Remove Entry\n5. Exit Program\n");
		scanf("%d", &reply);

		switch (reply)
		{
			case 1:
				{
					number = 1;
					refrigerator_func();
					break;
				}

			case 2:
				{
					number = 2;
					freezer_func();
					break;
				}

			case 3:
				{
					number = 3;
					dry_func();
					break;
				}
	
			case 4:
				{
					write_func();
					break;
				}
		
			case 5:
				{
					exit(0);
				}


			default:
				{
					puts("Error!\n");
					exit(1);
				}
		}
	}
}

void refrigerator_func(void)
{
	FILE *refrig;
	char str[MAXCHAR];

	refrig = fopen("REFRIGERATOR.TXT", "r+");

	if (refrig == NULL)
	{
		printf("Could not open file REFRIGERATOR.TXT\n");
		exit(0);

	}

	puts("\n");

	while(fgets(str, MAXCHAR, refrig) != NULL)
		printf("%s", str);

	fclose(refrig);
}

void freezer_func(void)
{
	FILE *freezer;
	char str[MAXCHAR];

	freezer = fopen("FREEZER.TXT", "r+");

	if (freezer == NULL)
	{
		printf("Could not open file FREEZER.TXT\n");
		exit(0);
	}

	puts("\n");

	while(fgets(str, MAXCHAR, freezer) != NULL)
		printf("%s", str);
	fclose(freezer);
}

void dry_func(void)
{
	FILE *dry;
	char str[MAXCHAR];

	dry = fopen("DRY_STOCK.TXT", "r+");

	if (dry == NULL)
	{
		printf("Could not open file DRY.TXT\n");
		exit(0);
	}

	puts("\n");

	while(fgets(str, MAXCHAR, dry) != NULL)
		printf("%s", str);

	fclose(dry);
}

void write_func(void)
{
	for (;;)
	{
		puts("\n");
		printf("a. Add Entry\n");
		printf("b. Remove Entry\n");

		char choice;

		scanf(" %c", &choice);

		if (choice == 'a')
			add_entry();
		else if (choice == 'b')
			remove_entry();
		else
			printf("Invalid choice.\n");
	}
}

void add_entry(void)
{
	FILE *fp;
	FILE *fp2;
	FILE *fp3;

	fp = fopen("REFRIGERATOR.TXT", "a+");
	fp2 = fopen("FREEZER.TXT", "a+");
	fp3 = fopen("DRY_STOCK.TXT", "a+");

	int number;
	char fridge_string[20];
	char freezer_string[20];
	char dry_string[20];

	puts("\n1. for Fridge\n2. for Freezer\n3. for dry shelve\n");
	scanf("%d",  &number);

	if (number == 1)
	{
		printf("Enter item to add (%d): ", number);
		scanf("%s", fridge_string);

		fprintf(fp, "%s\n", fridge_string);

		fclose(fp);
		printf("\nADDED: %s\n", fridge_string);

		menu();
	}

	else if (number == 2)
	{
		printf("Enter item to add (%d): ", number);
		scanf("%s", freezer_string);

		fprintf(fp2, "%s\n", freezer_string);

		fclose(fp2);

		printf("\nADDED: %s\n", freezer_string);

		menu();
	}

	else if (number == 3)
	{
		printf("Enter item to add (%d): ", number);
		scanf("%s", dry_string);

		fprintf(fp3, "%s\n", dry_string);

		fclose(fp3);

		printf("\nADDED: %s\n", dry_string);

		menu();
	}

	else
	{
		printf("Incorrect Entry\n");
		add_entry();
	}
}

void remove_entry(void)
{
	FILE *fp;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;
	
	char str[MAXCHAR];
	char str2[MAX];
	char ch;

	fp = fopen("REFRIGERATOR.TXT", "a+");
	fp2 = fopen("FREEZER.TXT", "a+");
	fp3 = fopen("DRY_STOCK.TXT", "a+");
	fp4 = fopen("temp.txt", "a+");		// open temporary file in write mode

	int ln, number, ctr;
	ctr = 0;

	if (!fp4)
	{
		printf("Unable to open a temporary file to write!\n");
		exit(0);
	}

	puts("\n1. for Fridge\n2. for Freezer\n3. for dry shelve\n");
	scanf("%d", &number);
	

	if(number == 1)
	{
		// Print REFRIGERATOR.TXT to screen

		while(fgets(str, MAXCHAR, fp) != NULL)
		{
			printf("%s", str);
		}
		
		puts("\n");

		printf("Input the line you want to remove: ");
		scanf("%d", &ln);

		while(fgets(str2, MAX, fp) != NULL)
		{
			printf("%s", str2);
		}

		rewind(fp);
		while(fgets(str2, MAX, fp) != NULL)
		{
			ctr++;
			if (ctr != ln)
			{
				fprintf(fp4, "%s", str2);
			}
		}


		fclose(fp);
		fclose(fp4);

		// remove REFRIGERATOR.TXT
		remove("REFRIGERATOR.TXT");
		
		// copy fp4 ("temp.txt") to REFRIGERATOR.TXT
		rename("temp.txt", "REFRIGERATOR.TXT");

		// now output buffer fp4 to screen

		fp=fopen("REFRIGERATOR.TXT", "r");
		ch = fgetc(fp);

		printf("Now the contents of the file REFIRGERATOR.TXT is: \n\n");
		while(ch != EOF)
		{
			printf("%c", ch);
			ch = fgetc(fp);
		}

		fclose(fp);

		menu();
	}

	else if (number == 2)
	{
		// Freezer (2) option (FREEZER.TXT)

		while(fgets(str, MAXCHAR, fp) != NULL)
		{
			printf("%s", str);
		}

		puts("\n");
		
		printf("Input the line you want to remove: ");
		scanf("%d", &ln);

		while(fgets(str2, MAX, fp2) != NULL)
		{
			printf("%s", str2);
		}

		rewind(fp2);
		while(fgets(str2, MAX, fp2) != NULL)
		{
			ctr++;
			if (ctr != ln)
			{
				fprintf(fp4, "%s", str2);
			}
		}
		
		fclose(fp2);
		fclose(fp4);

		remove("FREEZER.TXT");

		rename("temp.txt", "FREEZER.TXT");

		fp = fopen("FREEZER.TXT", "r");
		ch = fgetc(fp2);

		printf("Now the contents of the file FREEZER.TXT is: \n\n");
		while(ch != EOF)
		{
			printf("%c", ch);
			ch = fgetc(fp2);
		}
		
		fclose(fp2);

		menu();
	}

	else if (number == 3)
	{
		// print DRY_STOCK.TXT to screen

		while(fgets(str, MAXCHAR, fp3) != NULL)
		{
			printf("%s", str);
		}

		puts("\n");
		
		printf("Input the line you want to remove: ");
		scanf("%d", &ln);

		while(fgets(str2, MAX, fp3) !=NULL)
		{
			printf("%s", str2);
		}

		rewind(fp3);
		while(fgets(str2, MAX, fp3) != NULL)
		{
			ctr++;
			if (ctr != ln)
			{
				fprintf(fp4, "%s", str2);
			}
		}

		fclose(fp3);
		fclose(fp4);

		// remove DRY_STOCK.TXT
		remove("DRY_STOCK.TXT");

		rename("temp.txt", "DRY_STOCK.TXT");

		// now outbut buffer fp3 to screen

		fp = fopen("DRY_STOCK.TXT", "r");
		ch = fgetc(fp3);

		printf("Now the contents of the file DRY_STOCK.TXT is: \n\n");
		while (ch != EOF)
		{
			printf("%c", ch);
			ch = fgetc(fp3);
		}

		fclose(fp3);

		menu();
	}
}
