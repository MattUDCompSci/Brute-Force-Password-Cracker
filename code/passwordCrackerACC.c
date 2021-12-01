#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openacc.h>

static const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
static const int ALPHABET_SIZE = 62;
static const int MAX_LENGTH = 12;
int flag = 0;

int mystrcmp(char *x, char *y){
    while (*x != '\0' || *y != '\0') {
        if (*x == *y) {
            x++;
            y++;
        }
        else if ((*x == '\0' && *y != '\0')
                 || (*x != '\0' && *y == '\0')
                 || *x != *y) {
            return 1;
        }
    }
    return 0;
}

int check(char *str, char *password){
    if(!mystrcmp(str, password)){
      printf("Password was cracked: %s\n", str);
      free(str);
      return 1;
    }
    return 0;
}

int bruteForce(char *str, int index, int maxDepth, char *password){
	#pragma acc parallel loop
	for(int i = 0; i < ALPHABET_SIZE; i++){
	    str[index] = ALPHABET[i];
	    if(check(str, password)){
		flag = 1;
	    }
	    if(index != maxDepth - 1){
	        bruteForce(str, index+1, maxDepth, password);
	    }
	}
	return flag;
}

void crack(char *password){
    char *buf = malloc(MAX_LENGTH + 1);
    for(int i = 0; i < MAX_LENGTH; i++){
	memset(buf, 0, MAX_LENGTH + 1);
	if(bruteForce(buf, 0, i+1, password)){
	    exit(0);
	}
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
