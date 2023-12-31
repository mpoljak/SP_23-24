#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHR (256)
#define ALLOCATION_ERROR (-1)
#define EMPTYLIST (-2)
#define SUCCESS (0)
#define FAILED (1)

#include <stdio.h>
#include <stdlib.h>

void cyan() {
	printf("\033[0;36m");
}

void white() {
	printf("\033[0;37m");
}

void purple() {
	printf("\033[0;35m");
}

typedef struct polynomaial* Position;

struct polynomaial {
	int coeff;
	int power;
	Position next;
};

int main()
{
	char choice;
	int x = 1;

	struct polynomaial Head1;
	struct polynomaial Head2;
	struct polynomaial HeadA;
	struct polynomaial HeadM;

	Head1.next = NULL;
	Head2.next = NULL;
	HeadA.next = NULL;
	HeadM.next = NULL;

	while (x)
	{
		printf("\n  \n");
		cyan();
		printf("\t\t  **  MENU  **");
		cyan();
		printf("\n ---------------------------------------------------\n");
		white();
		printf("\n*     PRESS 1: TO PRINT POLYNOMIALS.                *");
		printf("\n*     PRESS 2: TO ADD  ADD POLYNOMIALS.             *");
		printf("\n*     PRESS 3: MULTIPLY POLYNOMIALS.                *");
		printf("\n*     PRESS 4:TO EXIT THE PROGRAM.                  *");
		cyan();
		printf("\n----------------------------------------------------\n");
		printf("\n  \n");
		printf("                                    ENTER YOUR CHOICE: ");

		scanf(" %c", &choice);

		switch (choice)
		{

		case '1':
			inputFirst(&Head1);
			inputSecond(&Head2);
			purple();
			printf("Polynomaial 1: \n\n");
			print(Head1.next);
			printf("\n\n");
			printf("Polynomaial 2: \n\n");
			print(Head2.next);
			break;
		case '2':
			polynomaialAdd(Head1.next, Head2.next, &HeadA);
			purple();
			printf("Add Two Polynomials: \n\n");
			print(HeadA.next);
			break;
		case '3':
			polynomialMultiply(Head1.next, Head2.next, &HeadM);
			purple();
			printf("Multiply Two Polynomials:\n\n ");
			print(HeadM.next);
			break;
		case '4':
			exit(0);

		default:
			printf("Selection error!\n");
			break;
		}

	}

	return SUCCESS;
}

int inputFirst(Position p)
{
	FILE* fp = NULL;
	fp = fopen("Polynomial1.txt", "r");
	if (fp == NULL)
	{
		printf("Failed to open file!\n");
		return FAILED;
	}
	while (!feof(fp))
	{
		Position q = NULL;
		q = (Position)malloc(sizeof(struct polynomaial));
		if (q == NULL)
		{
			printf("Memory allocation error!\n");
			return ALLOCATION_ERROR;
		}
		Position prev, temp;
		temp = p->next;
		prev = p;
		fscanf(fp, "%d %d", &q->coeff, &q->power);
		while (temp != NULL && (temp->power < q->power))
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL)
			q->next = temp;
		else
			q->next = NULL;
	}
	return SUCCESS;
}
int inputSecond(Position p)
{
	FILE* fp = NULL;
	fp = fopen("Polynomial2.txt", "r");
	if (fp == NULL)
	{
		printf("Failed to open file!\n");
		return FAILED;
	}
	while (!feof(fp))
	{
		Position q = NULL;
		q = (Position)malloc(sizeof(struct polynomaial));
		if (q == NULL)
		{
			printf("Memory allocation error!\n");
			return ALLOCATION_ERROR;
		}
		Position prev, temp;
		temp = p->next;
		prev = p;
		fscanf(fp, "%d %d", &q->coeff, &q->power);
		while (temp != NULL && temp->power < q->power)
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL)
			q->next = temp;
		else
			q->next = NULL;
	}
	return SUCCESS;
}

int polynomaialAdd(Position p1, Position p2, Position r) {
	while (p1->next != NULL && p2->next != NULL)
	{
		Position s = NULL;
		s = (Position)malloc(sizeof(struct polynomaial));
		if (s == NULL)
		{
			printf("Memory allocation error!\n");
			return ALLOCATION_ERROR;
		}
		s->next = NULL;

		if (p1->next->power < p2->next->power)
		{
			s->power = p1->next->power;
			s->coeff = p1->next->coeff;
			p1 = p1->next;
		}
		else if (p1->next->power > p2->next->power)
		{
			s->power = p2->next->power;
			s->coeff = p2->next->coeff;
			p2 = p2->next;
		}
		else
		{
			s->power = p1->next->power;
			s->coeff = (p1->next->coeff + p2->next->coeff);
			p1 = p1->next;
			p2 = p2->next;
		}
		r->next = s;
		r = s;
	}
	Position temp;
	if (p1->next == NULL)
		temp = p2->next;
	else
		temp = p1->next;
	while (temp != NULL)
	{
		Position s = NULL;
		s = (Position)malloc(sizeof(struct polynomaial));
		if (s == NULL)
		{
			printf("Memory allocation error!\n");
			return ALLOCATION_ERROR;
		}
		s->next = NULL;
		s->power = temp->power;
		s->coeff = temp->coeff;
		r->next = s;
		r = s;
		temp = temp->next;
	}
	return SUCCESS;
}

int polynomialMultiply(Position p1, Position p2, Position r)
{
	Position first = p1->next;
	Position second = p2->next;
	struct polynomaial P;
	Position s = NULL;
	s = (Position)malloc(sizeof(struct polynomaial));
	if (s == NULL)
	{
		printf("Memory allocation error!\n");
		return ALLOCATION_ERROR;
	}
	s->next = NULL;
	P.next = s;
	while (first != NULL)
	{
		second = p2->next;
		while (second != NULL)
		{

			s->coeff = first->coeff * second->coeff;
			s->power = first->power + second->power;
			polynomaialAdd(&P, r, r);

			second = second->next;
		}
		first = first->next;
	}

	return SUCCESS;
}

int print(Position p)
{
	if (p == NULL)
	{
		printf("The list is empty!\n");
		return EMPTYLIST;
	}

	while (p != NULL)
	{
		printf("The coefficient is: %d The exponent is: %d\n", p->coeff, p->power);
		p = p->next;
	}
	return SUCCESS;
}