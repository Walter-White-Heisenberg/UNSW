#include<stdio.h>
#include<stdlib.h>
int isv (char character, int shift){
    if (character <= 'z' && character >= 'a'){
        return ((character- 97 + shift) % 26) + 97;
    }else if(character <= 'Z' && character >= 'A'){
        return ((character - 65 + shift) % 26) + 65;
    }else{
        return character;
    }
}
int main(int argc, char *argv[]){
    int character;
    int shift = atoi(argv[1]);
    if (shift < 0) {
        shift = shift % 26 + 26;
    }
    character = getchar();
    while(character != EOF){
        printf("%c",isv(character ,shift));
        character = getchar();
    }
    return 0;
}
