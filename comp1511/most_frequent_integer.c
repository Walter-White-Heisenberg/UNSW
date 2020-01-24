#include<stdio.h>
void count_duplicates(int length, int source[length], int destination[length]){
    int p,w,i,c;
    i = 0;
    p = 0;
    while(i < length && source[i] != 0){
        w = 0;
        c = 0;       
        while(w < length){
            if(source[i] == destination[w] && i != w){
                c++;
            }
            w++;
        }if(c == 0){
            destination[p] = source[i];
            p++;
        }        
        i++;
    }
}
int main(void){
    int i,p,c;
    i = 0;
    c = 0;
    int fre[100000] = {0};
    int array[100000] = {0};
    while(scanf("%d",&array[i]) == 1){
        c = array[i] + c;
        i++;       
    }
    array[i] = 0;
    count_duplicates(100000,array,fre);
    p = 0;
    while(p < 100000 && fre[p] != 0){
        i = 0;
        while(i < 100000 && array[i] != 0){
            if(fre[p] % c == array[i]){
                fre[p] = fre[p] + c;
            }
            i++;
        }
        p++;
    }
    int max = fre[0];
    p = 0;
    while(p < 100000 && fre[p] != 0){
        if(max <= fre[p]){
            max = fre[p];
        }
        p++;
    }
    //the (max % c == 0) part is to include condition that only an integer is given
    printf("%d\n",max % c + (max % c == 0));   
}















