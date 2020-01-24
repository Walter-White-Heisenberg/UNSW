#include<stdio.h>
#include<stdlib.h>
int isv (char character, int shift){
    if (character <= 'z' && character >= 'a'){
        return ((character- 96 + shift) % 26) + 96;
    }else if(character <= 'Z' && character >= 'A'){
        return ((character - 64 + shift) % 26) + 64;
    }else{
        return character;
    }
}
int main(int argc, char *argv[]){
    int character;
    int shift = atoi(argv[1]);
    character = getchar();
    while(character != EOF){
        printf("%c",isv(character,shift));
        character = getchar();
    }
}
