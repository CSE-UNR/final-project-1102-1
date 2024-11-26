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

void scanFile(FILE* userFilePTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex);
void nounInput(char nouns[][STR_CAP], int* nounIndex);
void verbInput(char verbs[][STR_CAP], int* verbIndex);
void adjectiveInput(char adjectives[][STR_CAP], int* adjectiveIndex);

void printWords(FILE* userFilePTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex);
int stringLength(char str[]);

int main(){
	char userFile[USERFILESIZE];
	char nouns[NUM_NOUNS][STR_CAP], verbs[NUM_VERBS][STR_CAP], adjectives[NUM_ADJECTIVES][STR_CAP];
	int nounIndex = 0, verbIndex = 0, adjectiveIndex = 0;
	
	printf("Please enter desired madlibs file (madlib1.txt, madlib2.txt): ");
	fgets(userFile, USERFILESIZE, stdin);
	userFile[stringLength(userFile) - 1] = '\0';
	
	FILE* userFilePTR = fopen(userFile, "r");
	if(userFilePTR == NULL){
		printf("Could not open %s, please try again.\n", userFile);
		return 0;
	}
	
	scanFile(userFilePTR, nouns, &nounIndex, verbs, &verbIndex, adjectives, &adjectiveIndex);
	nounIndex = 0;
	verbIndex = 0;
	adjectiveIndex = 0;
	
	fclose(userFilePTR);
	fopen(userFile, "r");
	printWords(userFilePTR, nouns, &nounIndex, verbs, &verbIndex, adjectives, &adjectiveIndex);
	
	fclose(userFilePTR);
	
	
	return 0;
}

void scanFile(FILE* userFilePTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex){
	char scannedCharacter;
	while(fscanf(userFilePTR, "%c", &scannedCharacter) == 1){
		switch(scannedCharacter){
			case 'A':
				adjectiveInput(adjectives, adjectiveIndex);
				break;
			case 'N':
				nounInput(nouns, nounIndex);
				break;
			case 'V':
				verbInput(verbs, verbIndex);
				break;	
		}
	}
	
}

void nounInput(char nouns[][STR_CAP], int* nounIndex){
	printf("Please enter a noun: ");
	fgets(nouns[*nounIndex], STR_CAP, stdin);
	nouns[*nounIndex][stringLength(nouns[*nounIndex]) - 1] = '\0';
	(*nounIndex)++;

}

void verbInput(char verbs[][STR_CAP], int* verbIndex){
	printf("Please enter a verb: ");
	fgets(verbs[*verbIndex], STR_CAP, stdin);
	verbs[*verbIndex][stringLength(verbs[*verbIndex]) - 1] = '\0';
	(*verbIndex)++;

}

void adjectiveInput(char adjectives[][STR_CAP], int* adjectiveIndex){
	printf("Please enter a adjective: ");
	fgets(adjectives[*adjectiveIndex], STR_CAP, stdin);
	adjectives[*adjectiveIndex][stringLength(adjectives[*adjectiveIndex]) - 1] = '\0';
	(*adjectiveIndex)++;

}


void printWords(FILE* userFilePTR, char nouns[][STR_CAP], int* nounIndex, char verbs[NUM_VERBS][STR_CAP], int* verbIndex, char adjectives[NUM_ADJECTIVES][STR_CAP], int* adjectiveIndex){
	char scannedCharacter;
	while(fscanf(userFilePTR, "%c", &scannedCharacter) == 1){
		if(scannedCharacter != '\n'){
			if(scannedCharacter == 'A'){
				printf("%s", adjectives[*adjectiveIndex]);
				(*adjectiveIndex)++;
			} else if(scannedCharacter == 'N'){
				printf("%s" , nouns[*nounIndex]);
				(*nounIndex)++;
			} else if(scannedCharacter == 'V'){
				printf("%s", verbs[*verbIndex]);
				(*verbIndex)++;
			}
		 	else{
				printf("%c", scannedCharacter);
			}
		}
		
	}
	printf("\n");
}


int stringLength(char str[]){
	int length = 0;
	for(int i = 0; str[i] != '\0'; i++){
		length++;
	}
	
	return length;
}


