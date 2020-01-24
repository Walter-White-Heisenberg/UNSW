#include<stdio.h>

int is_included(char *small, char *big){ 
    int b = 0, counter = 0, smleng = 0, bigleng = 0;
    int a,i;
    while(big[bigleng] != '\0'){
        bigleng++;
    }while(small[smleng] != '\0'){
        smleng++;
        if(smleng > bigleng){
            return 0;
        }
    }    
    while(b <= bigleng){
        a = 0;
        i = 0;
        while(i == 0 && a <= smleng && b+1 <= bigleng){
            while(big[b] == big[b+1]){
                b++;
            }
            if(small[a] == big[b] || (small[a] - big[b]) == 'A' - 'a' ||
            small[a] - big[b] == 'a' - 'A'){
                printf("@@@ %c %c %d\n",small[a],big[b],counter);
                a++;
                b++;
                counter++;
                printf("www %c %c %d %d\n",small[a],big[b],counter,small[a] - big[b]);
                if(smleng == counter){
                    return 1;
                }
            }else{
                i = 1;
            }
        }
        printf("%c %c %d\n",small[a],big[b],counter);
        counter = 0;
        b++;
    }
    return 0;
}
int main(int argc, char **argv){
    printf("\n%d\n",is_included(argv[1],argv[2]));
}
