#include "DefineInclude.h"

#include "countStudentsInFile.h"
#include "Allocation.h"
#include "readStudentsFromFile.h"
#include "printStudents.h"
#include "studentStruct.h"

int countStudentsInFile();
stud* readStudentsFromFile(stud*);
int printStudents(stud*, int);
stud* Allocation(int, stud*);

int main()
{
	stud* students = NULL;
	int count = countStudentsInFile();
	students = Allocation(count, students);
	readStudentsFromFile(students);
	printStudents(students, count);

	return EXIT_SUCCESS;
		
}