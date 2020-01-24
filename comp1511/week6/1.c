#include<stdio.h>
void print_char_array(char array[] , int size);
void print_string(char string[]);
int string_length(char string[]);
void read_string(char *string, int size);

int main(void)
{
char string[100];
printf("string is s %p\n",string);
read_string(string,100);


printf("The user wrote '%s'\n",string);
/*print_char_array(nums,string_length(nums));
print_string(nums);
printf("string_length('%s')=%d\n",nums,string_length(nums));
printf("string_length('%s')=%d\n",nums,strlen(nums));*/


return 0;
}

void print_char_array(char array[] , int size){
    int i=0;
    while(i<size){
        putchar(array[i]);
        i++;
    }
    putchar('\n');
}
    void print_string(char string[]){
    int i=0;
    while(string[i]!='\0'){
        putchar(string[i]);
        i++;
    }
    putchar('\n');
    }
    
    int string_length(char string[]){
        int length = 0;
        while(string[length]!='\0')
        {
            length++;
        }
    return length;
    }
void read_string(char *read_string, int size){
    
    i=0;
    int c = getchar();
    while(c!= EOF && i<size-1){
    string[i] = c;
    putchar(c);
    c=getchar();
    i++;
}
}
