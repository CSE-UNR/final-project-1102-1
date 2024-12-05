//Justin Gu
//Hussien Almelhem
//Vance Quarry
//CS 135 Final Project

#include <stdio.h>
#define USERFILESIZE 13
#define STR_CAP 100
#define NUM_NOUNS 10
#define NUM_VERBS 10
#define NUM_ADJECTIVES 10
#define LINE_CAP 100

//Reading files and printing result functions
void scanFile(FILE* userFilePTR, char scannedFile[][STR_CAP], int* numLinesPTR);
void printWords(FILE* userFilePTR, char scannedFile[][STR_CAP], int numLines, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex);
void scanPlaceholders(FILE* userFilePTR, char scannedFile[][STR_CAP], int* numLinesPTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex);

//Placeholder reader functions
void nounInput(char nouns[][STR_CAP], int* nounIndex);
void verbInput(char verbs[][STR_CAP], int* verbIndex);
void adjectiveInput(char adjectives[][STR_CAP], int* adjectiveIndex);

//String functions
int stringLength(char str[]);
void stringCopy(char[], char[]);

int main(){
	char userFile[USERFILESIZE];
	char nouns[NUM_NOUNS][STR_CAP], verbs[NUM_VERBS][STR_CAP], adjectives[NUM_ADJECTIVES][STR_CAP];
	int nounIndex = 0, verbIndex = 0, adjectiveIndex = 0, numLines = 0;
	char scannedFile[LINE_CAP][STR_CAP];
	
	//Prompt user for madlibs file
	printf("Please enter desired madlibs file (madlib1.txt, madlib2.txt): ");
	fgets(userFile, USERFILESIZE, stdin);
	userFile[stringLength(userFile) - 1] = '\0';
	
	//Opening and checking if process was successful
	FILE* userFilePTR = fopen(userFile, "r");
	if(userFilePTR == NULL){
		printf("Could not open %s, please try again.\n", userFile);
		return 0;
	}
	
	//Scanning file for placeholders
	scanFile(userFilePTR, scannedFile, &numLines);
	scanPlaceholders(userFilePTR, scannedFile, &numLines, nouns, &nounIndex, verbs, &verbIndex, adjectives, &adjectiveIndex);
	
	//Reset indexs for placeholders
	nounIndex = 0;
	verbIndex = 0;
	adjectiveIndex = 0;
	
	//Print final results
	printWords(userFilePTR, scannedFile, numLines, nouns, &nounIndex, verbs, &verbIndex, adjectives, &adjectiveIndex);
	fclose(userFilePTR);
	
	return 0;
}

void scanFile(FILE* userFilePTR, char scannedFile[][STR_CAP], int* numLinesPTR){
	char scannedLine[STR_CAP];
	while(fgets(scannedLine, STR_CAP, userFilePTR) != NULL){
		//Copy current string into an array of strings for the file
		stringCopy(scannedLine, scannedFile[*numLinesPTR]);
		(*numLinesPTR)++;
	}
}

void scanPlaceholders(FILE* userFilePTR, char scannedFile[][STR_CAP], int* numLinesPTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex){
	char tempLine[STR_CAP];
	for(int i = 0; i < *numLinesPTR; i++){
		stringCopy(scannedFile[i], tempLine); //Copy current line of string into a 1D array
		if(stringLength(tempLine) == 2){ //Check if the array length size is 2, i.e. "A\n"
			if(tempLine[0] == 'A'){ //Check for first index of array for placeholder and run corresponding function
				adjectiveInput(adjectives, adjectiveIndex);
			} else if(tempLine[0] == 'N'){
				nounInput(nouns, nounIndex);
			} else if(tempLine[0] == 'V'){
				verbInput(verbs, verbIndex);
			}
			
		} 	
	}
}


void nounInput(char nouns[][STR_CAP], int* nounIndex){
	printf("Please enter a noun: ");
	fgets(nouns[*nounIndex], STR_CAP, stdin);
	nouns[*nounIndex][stringLength(nouns[*nounIndex]) - 1] = '\0'; //Setting endline for noun string
	(*nounIndex)++;
}

void verbInput(char verbs[][STR_CAP], int* verbIndex){
	printf("Please enter a verb: ");
	fgets(verbs[*verbIndex], STR_CAP, stdin);
	verbs[*verbIndex][stringLength(verbs[*verbIndex]) - 1] = '\0'; //Setting endline for verb string
	(*verbIndex)++;
}

void adjectiveInput(char adjectives[][STR_CAP], int* adjectiveIndex){
	printf("Please enter a adjective: ");
	fgets(adjectives[*adjectiveIndex], STR_CAP, stdin);
	adjectives[*adjectiveIndex][stringLength(adjectives[*adjectiveIndex]) - 1] = '\0'; //Setting endline for adjective string
	(*adjectiveIndex)++;
}


void printWords(FILE* userFilePTR, char scannedFile[][STR_CAP], int numLines, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex){
	char scannedLine[STR_CAP];
	int size = 0;
	for(int i = 0; i < numLines; i++){
		stringCopy(scannedFile[i], scannedLine); //Copy current index string from array of strings to a 1D array
		if(stringLength(scannedLine) == 2 && scannedLine[0] != '!'){ //Check if the string length is 2 and if the first character of string is not a punctuation 
			if(scannedLine[0] == 'A'){
				if(scannedFile[i + 1][0] == '.' || scannedFile[i + 1][0] == '!' || scannedFile[i + 1][0] == ','){  //Check the next line, if it begins with a punctuation print corresponding spacing.
					printf(" %s", adjectives[*adjectiveIndex]);
					(*adjectiveIndex)++;	
				} else {
					printf(" %s ", adjectives[*adjectiveIndex]);
					(*adjectiveIndex)++;	
				}
			} else if(scannedLine[0] == 'N'){
				if(scannedFile[i + 1][0] == '.' || scannedFile[i + 1][0] == '!' || scannedFile[i + 1][0] == ','){ //Check the next line, if it begins with a punctuation print corresponding spacing.
					printf(" %s" , nouns[*nounIndex]);
					(*nounIndex)++;
				} else {
					printf(" %s " , nouns[*nounIndex]);
					(*nounIndex)++;
				}
			} else if(scannedLine[0] == 'V'){
				if(scannedFile[i + 1][0] == '.' || scannedFile[i + 1][0] == '!' || scannedFile[i + 1][0] == ','){ //Check the next line, if it begins with a punctuation print corresponding spacing.
					printf(" %s", verbs[*verbIndex]);
					(*verbIndex)++;
				} else {
					printf(" %s ", verbs[*verbIndex]);
					(*verbIndex)++;
				}
			}
		}
		else{
			//If conditions above are not met, find the size of the current selected string, set an endline character, and print.
		 	size = stringLength(scannedLine); 
		 	scannedLine[size - 1] = '\0';
		 	printf("%s", scannedLine);
		}
	}
	printf("\n");
}

//STRING LIBRARY
int stringLength(char str[]){
	int length = 0;
	for(int i = 0; str[i] != '\0'; i++){
		length++;
	}
	
	return length;
}

void stringCopy(char source[], char dest[]){
	int i;
	for(i = 0; source[i] != '\0'; i++){
		dest[i] = source[i];
	}
	dest[i] = '\0';
}
