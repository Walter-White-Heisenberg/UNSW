#include<stdio.h>
void isv (char character, int total[26]){
    if(character >= 'a' && character <= 'z'){
        total[character - 'a']++;
    }else if(character >= 'A' && character <= 'Z'){
        total[character - 'A']++;
    }
}
int main(void){
    int character;
    int total[26] = {0};
    int i = 0;
    int counter = 0;
    
    character = getchar();
    while(character != EOF){
        if((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
            isv(character,total);
            counter++;  
        }  
           
        character = getchar();
    }
    while(i < 26){
        double frequency = (double) total[i] / (counter);
        printf("'%c' %lf %d\n",97 + i,frequency,total[i]);
        i++;
    }
}
