#include<stdio.h>
int isv (char character){
    if (character <= 'z' && character >= 'a'){
        return character - ('a' -'A');
    }else if(character <= 'Z' && character >= 'A'){
        return character + ('a' -'A');
    }else{
        return character;
    }
}
int main(void){
    int character;
    character = getchar();
    while(character != EOF){
        printf("%c",isv(character));
        character = getchar();
    }
}
