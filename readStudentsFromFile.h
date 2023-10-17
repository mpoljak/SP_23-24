
#ifndef readStudentsFromFile_h
#define readStudentsFromFile_h

#include "studentStruct.h"
#include "DefineInclude.h"

stud* readStudentsFromFile(stud* students)
{
	int i = 0;
	FILE* fp;
	fp = fopen("listofstudents.txt", "r");

	if (fp == NULL) {
		printf("File didn't open!\n");
		
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", students[i].FirstName, students[i].LastName, &students[i].Points);
		i++;
	}

	fclose(fp);
	return students;
}
#endif 