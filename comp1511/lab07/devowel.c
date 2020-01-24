#include<stdio.h>
int isv (char character){
    if (character == 'u' || character == 'i' || character == 'o' || character == 'e' || character == 'a'){
    return 1;
    }
    return 0;
}
int main(void){
    int character;
    character = getchar();
    while(character != EOF){
        if(isv(character) == 0){
            printf("%c",character);
        }
        character = getchar();
    }
}
