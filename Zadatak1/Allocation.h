#ifndef studentStruct_h
#define studentStruct_h

#include "studentStruct.h"
#include "DefineInclude.h"

stud* Allocation(int count, stud* student)
{
	student = (stud*)malloc(sizeof(student));
	
	if (student == NULL)
	{
		printf("Memory allocation error!\n");
		
	}
	if (student->FirstName == NULL || student->LastName==NULL || student->Points == NULL)
	{
		printf("Memory allocation error! \n");
	}

	return student;
}

#endif