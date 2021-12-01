#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openacc.h>

static const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
static const int ALPHABET_SIZE = 62;
static const int MAX_LENGTH = 12;

void check(char *str, char *password){
    if(!strcmp(str, password)){
      printf("Password was cracked: %s\n", str);
      free(str);
      exit(0);
    }
}

void bruteForce(char *str, int index, int maxDepth, char *password){
	for(int i = 0; i < ALPHABET_SIZE; i++){
	    str[index] = ALPHABET[i];
	    check(str, password);
	    if(index != maxDepth - 1){
	        bruteForce(str, index+1, maxDepth, password);
	    }
	}
}

void crack(char *password){
    char *buf = malloc(MAX_LENGTH + 1);
    for(int i = 0; i < MAX_LENGTH; i++){
	memset(buf, 0, MAX_LENGTH + 1);
	bruteForce(buf, 0, i+1, password);
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Invalid Arguments");
        return 1;
    }
    else{
        crack(argv[1]);
    }
}
