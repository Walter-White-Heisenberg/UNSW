// a program that will store five students' marks in an array
// it will output all the marks for verification
//it will also calculate and report the average mark
#include<stdio.h>
int main(void)  {
    int x;
    int marks[5]={0};
    // commented out manual entre to keep it as a reference
    double total=0;
    //manually input marks
    x=0;
    printf("Please enter five separate marks.\n");
    while(x<5){
    scanf("%d",&marks[x]);
    x++;
    }
    /*marks[0]=55;
    marks[1]=84;
    marks[2]=72;
    marks[3]=43;
    marks[4]=60;*/
    //loop through array and printf out values
    x=0;
    while(x<5){printf("%d\n",marks[x]);

        total+=marks[x];//total=total+marks[x]
        x++;
    }
printf("average: %lf\n",total/5.0);

    return 0;
}
