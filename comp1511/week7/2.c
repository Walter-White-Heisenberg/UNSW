#include<stdio.h>
#include<stlib.h>
int roll_die(int nside);
int main(int argc, int *argv[]){
    
    if(argc != 3){
    printf("usage:%s < number_of_dice><sides_of_dice>\n is")
    }
    int ndice = atoi(argc [1]);
    int nside = strtol(argv[2],NULL, 10);
    int d = 0;
    while (d < ndice){
    printf("%d ", roll_die(n_side));
    d++;
    }
    printf("\n");
    return 0;
}

int roll_die (int nside){
    return (rand()% nside)+1;

}
