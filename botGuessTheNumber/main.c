#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int rangeA = 1;
int rangeB = 1000;
int guessNumber = 0;
int numberToGuess;
int counter;
int LOW = 0;
int HIGH = 1;
int OK = 2;
int games=0;
int gamesNumber;
FILE *fptr;

int botGuess(FILE *fptr) {
	guessNumber = (rangeA+rangeB)/2;
	if (guessNumber == rangeA) {
		guessNumber = rangeB;
	}
	printf("Bot: Creo que es el %i.\n", guessNumber);
	fprintf(fptr, "Bot: Creo que es el %i.\n", guessNumber); 
}

void botUpdateInfo(int response, FILE *fptr){
	if (response == LOW) {
		printf("Bot: Dejame pensar...\n");
		fprintf(fptr, "Bot: Dejame pensar...\n"); 
		rangeA = guessNumber;
	} else if (response == HIGH) {
		printf("Bot: Dejame pensar...\n");
		fprintf(fptr, "Bot: Dejame pensar...\n"); 
		rangeB = guessNumber;
	} else {
		printf("Bot: Soy un genio.\n");
		fprintf(fptr, "Bot: Soy un genio.\n"); 
	}
}

void resetGame(FILE *fptr) {
	games++;
	counter = 0;
    numberToGuess = rand() % 1000 + 1;
    //FILE *serie;
    //serie = fopen("serie4.txt", "a");
    //fprintf(serie,"Numero %i.\n", numberToGuess);
    rangeA = 1;
	rangeB = 1000;
	if (games <= gamesNumber) {
	    printf("\n\nMaster: Vamos a jugar a \"Adivina el numero\". Es tu partida numero %i.\n", games); 
		printf("Master: Tienes que adivinar un numero del 1 al 1000.\n");
		fprintf(fptr,"\n\nMaster: Vamos a jugar a \"Adivina el numero\". Es tu partida numero %i.\n", games);
		fprintf(fptr,"Master: Tienes que adivinar un numero del 1 al 1000.\n");
	}
}

int main(void) {
	fptr = fopen("guessTheNumberContest.txt", "a");
	printf("Master: Hola amo humano, dime el numero de veces que quieres que tus bots esclavos jueguen.\n");
	fprintf(fptr,"Master: Hola amo humano, dime el numero de veces que quieres que tus bots esclavos jueguen.\n");  
	scanf("%i", &gamesNumber);
	printf("Master: Jugaremos %i veces como su todopoderosa mente desea.\n", gamesNumber);
	fprintf(fptr, "Master: Jugaremos %i veces como su todopoderosa mente desea.\n", gamesNumber);
    bool end = false;
    srand(time(NULL));
	resetGame(fptr);
    do {
		botGuess(fptr);
        if (guessNumber == numberToGuess) {
            printf("Master: Lo has adiviniado en %i intentos, enhorabuena \n", counter);
            fprintf(fptr,"Master: Lo has adiviniado en %i intentos, enhorabuena! \n", counter);
            botUpdateInfo(OK, fptr);
            resetGame(fptr);
        } else if (guessNumber < numberToGuess) {
            printf("Master: El numero es bajo. Prueba otra vez.\n");
            fprintf(fptr, "Master: El numero es bajo. Prueba otra vez.\n");
            botUpdateInfo(LOW, fptr);
        }else if (guessNumber > numberToGuess) { 
            printf("Master: El numero es alto. Intentalo de nuevo.\n");
            fprintf(fptr, "Master: El numero es alto. Intentalo de nuevo.\n");
            botUpdateInfo(HIGH, fptr);
        }
        counter++;
        // si quisieramos ralentizar la ejecución.
        //usleep(200 * 1000);
    } while (games <= gamesNumber);

	fclose(fptr);
    return 0;
}
