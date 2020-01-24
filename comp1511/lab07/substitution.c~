#include<stdio.h>
int main(int argc, char *argv[]){
    int character,i,complex[26];
    char word[27] = "abcdefghijklmnopqrstuvwxyz";
    i = 0;    
    while(i < 26){
        complex[i] = (2019 - word[i]) * argv[1][i];
        i++;
    }character = getchar();
    while(character != EOF){     
        if((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
            i = 0;
            while(i < 26){
                if(character == word[i]){
                    printf("%c",complex[i] / (2019 - word[i]));
                }else if(character == word[i] - 'a' + 'A'){
                    printf("%c",complex[i] / (2019 - word[i]) - 'a' + 'A');
                }
                i++;                 
            }
        }else{
            printf("%c",character);
        }    
        character = getchar();  
    }
}
