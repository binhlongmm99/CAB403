#include <stdio.h>
#include <string.h>

struct myStructure {
	int studentNumber;
	char subjectGrade;
	char subjectName[30]; 
};

void OutputData(struct myStructure *s1) ;

int main(int argc, char *argv[]) {
	struct myStructure s1;
	s1.studentNumber = 21345;
	s1.subjectGrade = 'B';
	strcpy(s1.subjectName, "CAB403");
	struct myStructure s2 = {18, 'C', "Digital Studies"}; 
	OutputData(&s1);
	OutputData(&s2);
	return 0; 
}

void OutputData(struct myStructure *s1) {
	printf("\nStudent Number - %d\n", s1->studentNumber);
	printf("\nSubject Result - %c\n", s1->subjectGrade);
	printf("\nSubject Name - %s\n", s1->subjectName);
}








