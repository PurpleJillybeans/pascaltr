/*
 * Pascal's Triangle generator
 * @PurpleJillybeans@kind.social - 19124-03-21 - CC-0 license
 * This is a terrible idea and it's going to cause a lot of trouble
 * but I'm doing it anyway.
 *
 * Technically this is all basic, standard C89 so should work on any OS,
 * but I'm doing all the dev work on DOS because retrocomputing is fun!
 */

//includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//preprocessor directives
#define MAXCOLS 80 //80 column display
#define MAXELEMENT 10 //strlen(pow(256,sizeof(unsigned long int)))
#define MAXLINES 12 //factorial function breaks beyond here

//function definitions
void doTriangle(int count);
void getPascalTriangleLine(int n, char *pascalLine);
unsigned long int factorial(int n);
void strCenter(char *input,int targetLength);

//functions
int main(int argc, char *argv[]) {
	//char *envp[] is compiler-specific
	//getenv(varname) is a more universal standard
	
	//apparently \n works on DOS, thought it needed \n\l
	printf("Pascal's Triangle doodad by PurpleJillybeans\n\n");

	//process args
	if(argc == 2) { //exactly one arg
		int count = 0;

		//just (int)'ing a char* does NOT work
		errno = 0; //strtol() puts error info here if encountered
		count = strtol(argv[1],NULL,10); //or atoi(argv[1])

		if(count > 0 && count <= 12 && errno == 0) { //arg was valid
			doTriangle(count);
			exit(EXIT_SUCCESS);
		}
		else if(count > 12) {
			fprintf(stderr,"Maximum lines is %d\n",MAXLINES);
			exit(EXIT_FAILURE);
		}
		else { //arg was zero, negative, or NaN, or strtol() error'd
			fprintf(stderr,"Parameter must be a positive int\n");
			exit(EXIT_FAILURE);
		}
	}

	//if we got here, we didn't get exactly one arg
	printf("Usage: %s number_of_lines\n",argv[0]);
	exit(EXIT_SUCCESS); //void main() causes odd things
}

void doTriangle(int count) {
	//printf() a Pascal Triangle with $count lines
	int n;
	char pascalLine[MAXCOLS] = ""; //malloc() behind the scenes!
	int targetLineLength; //can't declare using a function result

	//sizeof() isn't really meant for strings
	getPascalTriangleLine(count-1,pascalLine);
	targetLineLength = strlen(pascalLine);

	for(n=0;n<count;n++) {
		strcpy(pascalLine,""); //varname = "" doesn't work
		getPascalTriangleLine(n,pascalLine);
		strCenter(pascalLine,targetLineLength);
		printf("%s\n",pascalLine);
	}
}

void getPascalTriangleLine(int n, char *pascalLine) {
	//puts line n of Pascal's Triangle as a string into caller-declared ptr
	//C(n,k) = binomial(n,k) = n!/(k!*(n-k)!), 0 <= k <= n
	//Math circlejerk: http://oeis.org/A007318
	int k;
	char pascalElement[MAXELEMENT] = "";

	for(k=0;k<=n;k++) {
		if(k > 0) { strcat(pascalLine," "); }
		//get our element as a string
		//might also be able to use itoa() (nonstandard)
		sprintf(
				pascalElement,
				"%d",
				factorial(n)/(factorial(k)*factorial(n-k))
		);
		strCenter(pascalElement,3); //fixed element width for pretties
		strcat(pascalLine,pascalElement);
	}
}

unsigned long int factorial(int n) {
	//product of all natural ints from 1 to n
	//n! = 1*2*3*...*n
	//would use a lib for this normally, but this is a learning exercise
	//TODO: make it work with n > 12 (use floats?)
	
	if(n == 0) { return(1); } //0! == 1, not 0 (empty product)
	return(n * factorial(n - 1));

	//could do it with a for loop, but recursion is more efficient
	//directly translatable to big-pi notation
	//int out = 1; for (i=1;i<=n;i++) { out = out * i; }; return(out);
}

void strCenter(char *input,int targetLength) {
	//pads line with spaces to center-align it for given line length
	//another one that I'd probably use a lib for normally
	int spacesLeft = 0;
	int spacesRight = 0;
	char buffer[MAXCOLS] = "";
	int i;

	if(strlen(input) >= targetLength) { return; }

	spacesLeft = (targetLength - strlen(input))/2;
	for(i=0;i<spacesLeft;i++) {
		strcat(buffer," ");
	}
	strcat(buffer,input);
	spacesRight = targetLength - strlen(buffer);
	for(i=0;i<spacesRight;i++) {
		strcat(buffer," ");
	}

	strcpy(input,buffer);
}
