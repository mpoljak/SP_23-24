#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#define FILE_DIDNT_OPEN_ERROR -1
#define EXIT_SUCCESS 0
#define MAX_FILE_NAME (256)
#define ALLOCATION_ERROR -2
#define COUNTRY_DOSE_NOT_EXIST -3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void red() {
	printf("\033[1;31m");
}

void cyan() {
	printf("\033[0;36m");
}

void white() {
	printf("\033[0;37m");
}

void purple() {
	printf("\033[0;35m");
}

typedef struct City* Position;
struct City
{
	char CityName[MAX_SIZE];
	int Population;
	Position next;
}_city;


typedef struct State* Tree;
struct State
{
	char CountryName[MAX_SIZE];
	char FileName[MAX_FILE_NAME];
	Position head;
	Tree Left;
	Tree Right;
}_state;

Tree ReadCountryFromFile(Tree);
Tree MakeTree(char*, char*);
Tree CompletelyTree(Tree, Tree);
int PrintCountry(Tree);
int Preorder(Tree);
Tree FindState(Tree, char*);

Position ReadCityFromFile(Position, char*);
Position SortList(Position);
int NewTownInList(Position, Position);
Position InsertTown(char*, int);
int PrintTown(Position);


int main()
{
	Tree root = NULL;
	Tree a = NULL;
	char CountryName[MAX_SIZE] = "";
	root = ReadCountryFromFile(root, "country.txt");
	red();
	Preorder(root);
	cyan();
	printf("\t\t\n                 CHOOSE THE COUNTRY YOU WANT:  ");
	white();
	scanf("%s", &CountryName);
	a = FindState(root, CountryName);
	if (a == NULL)
	{
		printf("The selected country does not exist in our list!");
		return COUNTRY_DOSE_NOT_EXIST;
	}
	printf("\n\t\t SELECTED COUNTRY: %s\n\n", a->CountryName);
	a->head = (Position)malloc(sizeof(_city));
	strcpy(a->head->CityName, "");
	a->head->Population = 0;
	a->head->next = NULL;
	a->head = ReadCityFromFile(a->head, a->FileName);
	SortList(a->head);
	cyan();
	printf("\t\t CITIES:\n\n");
	PrintTown(a->head);
}


Tree ReadCountryFromFile(Tree root, char* filename)
{
	char CountryName[MAX_SIZE] = "";
	char FileName[MAX_SIZE] = "";
	Tree NewState = NULL;

	FILE* fp = fopen("country.txt", "r+");

	if (fp == NULL)
	{
		printf("File didn't open! %s\n", strerror(errno));
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s  %s\n", CountryName, FileName);
		NewState = MakeTree(CountryName, FileName);
		root = CompletelyTree(root, NewState);
	}

	fclose(fp);
	return root;
}
Tree MakeTree(char* CountryName, char* FileName)
{
	Tree c;
	c = (Tree)malloc(sizeof(_state));

	if (c == NULL)
	{
		printf("Memory allocation error!\n");
		return ALLOCATION_ERROR;
	}

	strcpy(c->CountryName, CountryName);
	strcpy(c->FileName, FileName);
	c->head = NULL;
	c->Left = NULL;
	c->Right = NULL;

	return c;

}

Tree CompletelyTree(Tree root, Tree newCountry)
{
	Tree temp = NULL;
	int result = NULL;

	if (!root)
	{
		root = newCountry;
	}

	else if (strcmp(root->CountryName, newCountry->CountryName) < 0)
	{
		root->Right = CompletelyTree(root->Right, newCountry);
	}
	else if (strcmp(root->CountryName, newCountry->CountryName) > 0)
	{
		root->Left = CompletelyTree(root->Left, newCountry);
	}
	else
	{
		free(newCountry);
	}

	return root;
}

int PrintCountry(Tree root)
{
	if (root->Right)
	{
		PrintCountry(root->Right);
		printf("%s %d", root->CountryName);
	}

	if (root->Left);
	{
		PrintCountry(root->Left);
		printf("%s %d", root->CountryName);
	}
}

int Preorder(Tree root)
{
	if (root == NULL)
	{
		return NULL;
	}
	Preorder(root->Left);
	printf("\t\t~ %s\n", root->CountryName);
	Preorder(root->Right);

	return EXIT_SUCCESS;

}

Tree FindState(Tree root, char* CountryName)
{
	if (!root) {
		return root;
	}
	else if (strcmp(root->CountryName, CountryName) > 0) {
		return FindState(root->Left, CountryName);
	}
	else if (strcmp(root->CountryName, CountryName) < 0) {
		return FindState(root->Right, CountryName);
	}
	else
		return root;
}

Position ReadCityFromFile(Position head, char* CountryFileName)
{
	Position CountryName = NULL;
	char CityName[MAX_SIZE] = "";
	int Population;
	Position NewTown = NULL;

	FILE* fp = fopen(CountryFileName, "r+");

	if (fp == NULL)
	{
		printf("File didn't open!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s  %d\n", CityName, &Population);
		NewTown = InsertTown(CityName, Population);
		NewTownInList(head, NewTown);
	}

	fclose(fp);
	return head;
}

Position SortList(Position head)
{
	char CityName[MAX_SIZE] = "";
	int Population = NULL;
	Position q = NULL;
	Position p = NULL;

	while (head->next != NULL)
	{
		q = head;
		p = head->next;

		if (q->Population < p->Population)
			break;
		else if (q->Population == p->Population)
		{
			if (strcmp(q->CityName, p->CityName) < 0)
				break;
			else if (strcmp(q->CityName, p->CityName) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q = p;
	p = p->next;
	return head;

}


int NewTownInList(Position head, Position NewTown)
{
	if (!head) {
		head = (Position)malloc(sizeof(_city));
		strcpy(head->CityName, "");
		head->Population = 0;
		head->next = NewTown;
	}
	else {
		while (head->next != NULL) {
			head = head->next;
		}
		NewTown->next = head->next;
		head->next = NewTown;
	}

	return 0;
}

Position InsertTown(char* CityName, int Population)
{
	Position NewTown = (Position)malloc(sizeof(_state));

	strcpy(NewTown->CityName, CityName);
	NewTown->Population = Population;
	NewTown->next = NULL;

	return NewTown;
}


int PrintTown(Position head)
{
	while (head->next)
	{
		purple();
		printf("\t\t-> %s\n", head->next->CityName);
		white();
		printf("\t\tPOPULATION: %d \n", head->next->Population);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
