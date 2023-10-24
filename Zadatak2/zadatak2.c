/*
2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :

	A.dinamički dodaje novi element na početak liste,

	B.ispisuje listu,

	C.dinamički dodaje novi element na kraj liste,

	D.pronalazi element u listi(po prezimenu),

	E.briše određeni element iz liste */


#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME (1024)
#define ALLOCATION_ERROR (-1)
#define SUCCESS (0)
#define EMPTYLIST (-2)

#include <stdio.h>
#include <stdlib.h>
#include  <string.h>


void red() {
	printf("\033[1;31m");
}

void cyan() {
	printf("\033[0;36m");
}

void white() {
	printf("\033[0;37m");
}

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;
} person;


int create(Position);
int insertBegin(Position);
int printStudents(Position);
int insertEnd(Position);
int delete(Position);
int findLastName(Position);
Position findPrev(Position, char*);



int main()
{
	person Head;
	Head.next = NULL;
	int x = 1;
	char c;
	Position q = NULL;

	q = (Position)malloc(sizeof(person));
	if (q == NULL)
	{
		printf("Memory allocation error!\n");
		return ALLOCATION_ERROR;
	}

	while (x)
	{
		printf("\n  \n");
		red();
		printf("\t\t  **  MENU  **");
		cyan();
		printf("\n ---------------------------------------------------\n");
		white();
		printf("\n*     PRESS A: TO ADD A PERSON AT THE BEGINNING.    *");
		printf("\n*     PRESS B: TO ADD A PERSON AT THE END.          *");
		printf("\n*     PRESS C: TO FIND A PERSON IN THE LIST.        *");
		printf("\n*     PRESS D: TO DELETE A PERSON FROM THE LIST.    *");
		printf("\n*     PRESS E: TO PRINT THE LIST.                   *");
		printf("\n*     PRESS F:TO EXIT THE PROGRAM.                  *");
		cyan();
		printf("\n----------------------------------------------------\n");
		printf("\n  \n");
		red();
		printf("                                    ENTER YOUR CHOICE: ");
		cyan();

		scanf(" %c", &c);

		switch (c)
		{

		case 'a':
		case 'A':
			insertBegin(&Head);
			break;

		case 'b':
		case 'B':
			insertEnd(&Head);
			break;

		case 'c':
		case 'C':
			findLastName(Head.next);
			break;

		case 'd':
		case 'D':
			delete(&Head);
			break;

		case 'e':
		case 'E':
			printStudents(Head.next);
			break;

		case 'f':
		case 'F':
			exit(0);

		default:
			printf("Selection error!\n");
			break;
		}

	}

	return SUCCESS;
}

int create(Position q)
{
	person Head;
	Head.next = NULL;
	int x = 1;
	char c;

	printf("Write the name of the student: ");
	scanf(" %s", q->firstName);
	printf("Write the student's last name: ");
	scanf(" %s", q->lastName);
	printf("write the student's year of birth: ");
	scanf("%d", &q->birthYear);
	printf("\n----\n");

	return SUCCESS;
}

// A.dinamički dodaje novi element na početak liste

int insertBegin(Position p)
{
	Position q = NULL;

	q = (Position)malloc(sizeof(person));

	create(q);

	q->next = p->next;
	p->next = q;

	return SUCCESS;
}

// B.ispisuje listu

int printStudents(Position p)
{
	if (p == NULL) {
		printf("The list is empty!");
		return EMPTYLIST;
	}
	else {
		printf("\n  \n");
		printf("FIRST NAME\tLAST NAME\tBIRTH YEAR\n");

		while (p != 0) {
			printf("%-12s\t%-12s\t%-10d\t%-10.0l\n", p->firstName, p->lastName, p->birthYear);
			p = p->next;
		}
	}
	return SUCCESS;
}

// C.dinamički dodaje novi element na kraj liste

int insertEnd(Position p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	insertBegin(p);

	return SUCCESS;
}

// D.pronalazi element u listi(po prezimenu)

int findLastName(Position p)
{
	char last[MAX_NAME];
	printf("write the last name of the person you want to find:\n");
	scanf("%s", &last);
	while (p != NULL && strcmp(p->lastName, last))
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("\nThe element does not exist in the list!\n");
	}
	else
	{
		printf("\n%s %s %d\n", p->firstName, p->lastName, p->birthYear);
		printf("\n");
	};
	return SUCCESS;
}

// E.briše određeni element iz liste

Position findPrev(Position p, char* last) {

	Position prev = NULL;
	prev = p;
	p = p->next;

	while (p != NULL && strcmp(p->lastName, last))
	{
		prev = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf("\nThe element does not exist in the list!\n");
		return NULL;
	}
	return prev;
}

int delete(Position p) {
	Position prev = NULL;
	char last[MAX_NAME];
	printf("Write the last name of the person you want to delete:\n");
	scanf("%s", &last);
	prev = findPrev(p, last);

	if (prev != NULL)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
		printf("\n The student is deleted: %s\n", last);
	}

	return SUCCESS;
}


