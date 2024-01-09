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

typedef struct City* Tree;
struct City
{
	char CityName[MAX_SIZE];
	int Population;
	Tree Left;
	Tree Right;
}_city;

typedef struct State* Position;
struct State
{
	char CountryName[MAX_SIZE];
	char FileName[MAX_FILE_NAME];
	Position next;
	Tree root;
}_state;

int readCountryFromFile(Position, char*);
Position InsertState(char*, char*);
int PrintState(Position Head);
int NewStateInList(Position, Position);
Position FindState(Position, char*);
int SortList(Position);

int readCityFromFile();
Tree MakeTree(char*, int);
int Inorder(Tree);
int Preorder(Tree);
Tree CompletelyTree(Tree, char*, int);


int main()
{
	Position s = NULL;
	char CountryName[MAX_SIZE] = "";
	Position head = NULL;
	head = (Position)malloc(sizeof(_state));
	strcpy(head->CountryName, "");
	head->next = NULL;
	head->root = NULL;
	readCountryFromFile(head, "country.txt");
	SortList(head);
	PrintState(head);
	cyan();
	printf("\t\t\n                 CHOOSE THE COUNTRY YOU WANT:  ");
	white();
	scanf("%s", &CountryName);
	s = FindState(head, CountryName);
	if (s == NULL)
	{
		printf("The selected country does not exist in our list!");
		return COUNTRY_DOSE_NOT_EXIST;
	}

	printf("\n\t\t SELECTED COUNTRY: %s\n\n", s->CountryName);
	readCityFromFile(s, s->FileName);
	cyan();
	printf("\t\t CITIES:\n\n");
	Preorder(s->root);

	return EXIT_SUCCESS;
}


int readCountryFromFile(Position head, char* filename)
{
	char CountryName[MAX_SIZE] = "";
	char CountryFileName[MAX_SIZE] = "";
	Position NewState = NULL;

	FILE* fp = fopen("country.txt", "r+");

	if (fp == NULL)
	{
		printf("File didn't open! %s\n", strerror(errno));
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s  %s\n", CountryName, CountryFileName);
		NewState = InsertState(CountryName, CountryFileName);
		NewStateInList(head, NewState);
	}

	fclose(fp);
	return 0;
}

int SortList(Position head)
{
	Position p = NULL;
	Position q = NULL;
	Position temp = NULL;
	Position end = NULL;

	while (head->next != end) {
		q = head;
		p = head->next;
		while (p->next != end) {
			if (strcmp(p->CountryName, p->next->CountryName) > 0) {
				temp = p->next;
				q->next = temp;
				p->next = temp->next;
				temp->next = p;
				p = temp;
			}
			q = p;
			p = p->next;
		}
		end = p;
	}
	return EXIT_SUCCESS;
}


int NewStateInList(Position head, Position NewState)
{
	while (head->next != NULL) {
		head = head->next;
	}
	NewState->next = head->next;
	head->next = NewState;
	return EXIT_SUCCESS;
}

Position InsertState(char* CountryName, char* FileName)
{
	Position NewState = (Position)malloc(sizeof(_state));
	strcpy(NewState->CountryName, CountryName);
	strcpy(NewState->FileName, FileName);
	NewState->next = NULL;
	NewState->root = NULL;
	return NewState;
}


int PrintState(Position head)
{
	while (head->next)
	{
		red();
		printf("\t\t ~ %s \n", head->next->CountryName);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

Position FindState(Position head, char* CountryName)
{
	while (head->next != NULL && strcmp(CountryName, head->CountryName) != 0)
	{
		head = head->next;
	}
	return head;
}

Tree MakeTree(char* CityName, int Population)
{
	Tree c;
	c = (Tree)malloc(sizeof(_city));

	if (c == NULL)
	{
		printf("Memory allocation error!\n");
		return ALLOCATION_ERROR;
	}

	strcpy(c->CityName, CityName);
	c->Population = Population;
	c->Left = NULL;
	c->Right = NULL;

	return c;

}

Tree CompletelyTree(Tree root, Tree newCity)
{
	Tree temp = NULL;
	int result = NULL;

	if (!root)
	{
		root = newCity;
	}

	else if (newCity->Population > root->Population)
	{
		root->Right = CompletelyTree(root->Right, newCity);
	}

	else if (newCity->Population < root->Population)
	{
		root->Left = CompletelyTree(root->Left, newCity);
	}
	else
	{
		if (strcmp(root->CityName, newCity->CityName) < 0)
		{
			root->Right = CompletelyTree(root->Right, newCity);
		}

		else if (strcmp(root->CityName, newCity->CityName) > 0)
		{
			root->Left = CompletelyTree(root->Left, newCity);
		}
		else {
			free(newCity);
		}
	}

	return root;
}

int PrintCity(Tree root)
{
	if (root->Right)
	{
		PrintCity(root->Right);
		printf("%s %d", root->CityName);
	}

	if (root->Left);
	{
		PrintCity(root->Left);
		printf("%s %d", root->CityName);
	}
}
int readCityFromFile(Position country, char* CountryFileName)
{
	Position CountryName = NULL;
	char CityName[MAX_SIZE] = "";
	int Population;
	Tree newCity = NULL;

	FILE* fp = fopen(CountryFileName, "r+");

	if (fp == NULL)
	{
		printf("File didn't open!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s  %d\n", CityName, &Population);
		newCity = MakeTree(CityName, Population);
		country->root = CompletelyTree(country->root, newCity);
	}

	fclose(fp);
	return 0;
}

int Preorder(Tree root) {
	if (root == NULL)
	{
		return NULL;
	}
	Preorder(root->Right);
	purple();
	printf("\t\t-> %s\n", root->CityName);
	white();
	printf("\t\tPOPULATION: %d\n", root->Population);
	Preorder(root->Left);

	return EXIT_SUCCESS;
}