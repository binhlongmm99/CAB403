#include <stdio.h>
#include <string.h>

typedef struct Books {
	char title[60];
	char author[40];
	int pubYear;
} book;

void printBook(book myBook) {
	printf("\nBook Information\n-----------------------------------\n");
	printf("\nBook title - %s\n", myBook.title);
	printf("\nBook author - %s\n", myBook.author);
	printf("\nBook Publication Year - %d\n", myBook.pubYear);
	printf("\n--------------------------------------------------------\n");
}
	
int main(int argc, char *argv[]) {
	book myBookOne;	
	strcpy(myBookOne.title, "CAB403"); //to assign a value to a string use strcpy() function
	strcpy(myBookOne.author, "Tommy Smith");
	myBookOne.pubYear = 2023;
	book myBookTwo = {"Learning to Program", "Jason Smith", 2019};
	printBook(myBookOne);
	printBook(myBookTwo);
}


	
  