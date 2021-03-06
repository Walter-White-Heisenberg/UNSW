#include<stdio.h>
int prime_identifier(int input) {
    int identifier = 1;
    //I design the function such that if input is a composite, then identifier-1 
    int i = 2;
    
    while (i < input) {
        //the reason why I use 14 but not 24 is 13 is the maxmum prime 
        //factor we need to count for, for example, 
        //17 and 34 are not in the realtion of cocomposite, and 51 is above limit, 
        //so it's enough to know 2 is a factor of 34 same as 38,46,
        //knowing the prime factor above 13 is useless when you are playing.
        if (input % i == 0 ) {
            identifier--;
            i = i + 48;
            //I only need to know if input is a prime, 
            //then I need identifier be either 0 or 1, 
            //so if there is a prime factor, 
            //the loop will stop due to i is bigger than 48
        }
        i++;
    }
    return identifier;
}


int cocomposite_or_not (int target, int input ,int input2){
    int n_of_factor , i;
    i = 0;
    n_of_factor = 0;
    int factor_array[6] = {2 , 3 , 5 , 7 , 11 , 13};
    while (i < 6) {
        if (target % factor_array[i] == 0) {
            if (input % factor_array[i] == 0) {
                if(input2 % factor_array[i] == 0) {
                    n_of_factor++;
                }    
            }
        }
        i++;
    }
    return n_of_factor;
}

//if you input a target composite and a composite array, 
//then you get a co-composite number in this array 
//which is closest but lower than target composite
//if you input a target prime and a prime array,
//then you get a prime number in this array 
//which is closest to but lower than target prime
int just_lower(int input, int array[10]) {
    int i , a , b;
    i=0;
    if (prime_identifier(input) == 1) {
    //there is no smaller prime
        if (array[0] > input){
            return array[0];
        }
        else{
            a=0;
            while(i < 10 && array[i] != 0 ) {
                if (array[i] < input){
                    a=i;
                }
                i++;
            }
            return array[a]; 
        }   
    }else{
        //a is for the loop purpose just like i;
        a=-1;
        b=-1;
        int counter = 0;
        int bigger_comp[10] = {0};
        while (i < 10 && array[i] != 0) {
            if (array[i] < input &&
                cocomposite_or_not(input , array[i],array[i]) > 0){
                a=i;               
            }else if (array[i] > input && 
                     cocomposite_or_not(input , array[i],array[i]) > 0){
                b=i; 
                bigger_comp[counter] = array[i];
                counter++;            
            }            
            i++;
        }if (a > -1) {
        //there is smaller cocoomposite
            return array[a];
        }if (a == -1 && b > -1) {
        //there is no smaller cocomposite 
            return bigger_comp[0]; 
        }if(a == -1 && b == -1) {
        //there is no cocomposite in this array
            return 0;
        } 
    }    
}
int max_right_card(int card_a, int card_b, int card_c) {
    int p_b, p_c;
    //card_a is special, because it is the first card
    //because prime_identifier will only out put 0 or 1,
    //then I can use it to only represent right type of card as themselves
    p_b = prime_identifier(card_b) * card_b;
    p_c = prime_identifier(card_c) * card_c;
    
    int cocomp_identifier_b = 0;
    int cocomp_identifier_c = 0;
    //same as above, but this time I also need to 
    //identify they share same factor or not
    if (cocomposite_or_not(card_a, card_b, card_b) > 0) {
        cocomp_identifier_b = 1;
    }if (cocomposite_or_not(card_a, card_c, card_c) > 0) {
        cocomp_identifier_c = 1;
    }    
    int comp_b = cocomp_identifier_b * card_b;
    int comp_c = cocomp_identifier_c * card_c; 
    int max_card;       
    if(prime_identifier(card_a) == 1){
    //I use the model in my week3 lab question "order3_challenge2" question to 
    //find out the max prime between three card when it's a prime round
        max_card = card_a * (card_a >= p_b) * (card_a >= p_c) 
        + p_b * (p_b > p_c) * (p_b > card_a) + p_c * (p_c > card_a) * (p_c > p_b);
    }else{
        max_card = card_a * (card_a >= comp_b) * (card_a >= comp_c) + 
        comp_b * (comp_b > comp_c) * (comp_b > card_a) + comp_c * (comp_c > card_a)*(comp_c > comp_b);
    }
    return max_card;
}
//this function is the higher level of "just_lower" function, 
//"just_lower" can play the best card against only first card,
//but"card_to_play" can play best card against both first card and biggest card
//What I did is just counting more situation in the program

int card_to_play(int card_one, int right_max_card, int array[10]) {
    int right_card_to_play;
    int must_right = just_lower(card_one, array);
        //a is for the loop purpose just like i;
    int a=-1;
    int i=0;
    while (i < 10 && array[i] != 0) {
        if (array[i] < right_max_card && cocomposite_or_not(card_one , array[i], array[i]) > 0){
            a=i;                         
        }            
        i++;
    }if (a > -1) {
    //there is smaller cocoomposite
        right_card_to_play = array[a];
    }else{
        if(must_right != 0){
            right_card_to_play = must_right;
        }else{
            right_card_to_play = 0;
        }
    }    
    return right_card_to_play;           
}

int biggest_possible(int input, int array[10]) {
    int i , a , b;
    i=0;
    int biggest;

    //a is for the loop purpose just like i;
    a=-1;
    while (i < 10 && array[i] != 0) {
        if (cocomposite_or_not(input , array[i], array[i]) > 0){
            a=i;               
        }          
        i++;
    }if (a > -1) {
    //there is available cocoomposite
        biggest = array[a];
    }else{
        biggest = 0;
    } 
    return biggest;    
}

int main(void){
    int i;
    i=0;
    int card_in_random[10]={0};
    while(i < 10){
    scanf("%d",&card_in_random[i]);
    i++;
    }
    int prime_in_hand[10] = {0};
    int big_composite_in_hand[10] = {0};
    int small_composite_in_hand[10] = {0};    
    int composite_in_hand[10] = {0};
    int possible_card = 10;
    //possible_card start from 10 and end in 50 in the while loop
    int counter_for_prime_array = 0;
    int counter_for_big_comp_array = 0;
    int counter_for_small_comp_array = 0;
    int counter_for_comp_array = 0;
   
    
    while (possible_card < 50) {
        i = 0;    
        while (i < 10) {        
            if (prime_identifier(possible_card) == 1 && card_in_random[i] == possible_card) {                      
                prime_in_hand[counter_for_prime_array]=possible_card;
                counter_for_prime_array++;               
            }else if (prime_identifier(possible_card) == 0 && 
            card_in_random[i]==possible_card && 42 < possible_card) {
                //which means when counter_for_big_comp_array=0, 
                //I don't have any big composite                     
                big_composite_in_hand[counter_for_big_comp_array] = possible_card;
                counter_for_big_comp_array++;
                composite_in_hand[counter_for_comp_array] = possible_card;
                counter_for_comp_array++;                 
            }else if(prime_identifier(possible_card) == 0 && card_in_random[i]==possible_card && 42 > possible_card) {            
                //same as the comment for "counter_for_big_comp_array"
                small_composite_in_hand[counter_for_small_comp_array] = possible_card;
                counter_for_small_comp_array++;
                composite_in_hand[counter_for_comp_array] = possible_card;
                counter_for_comp_array++;                
            }
            i++; 
        }
        possible_card++;
    }
    counter_for_small_comp_array--;
    counter_for_big_comp_array--;
    counter_for_prime_array--;
    counter_for_comp_array=counter_for_comp_array - 1;
    printf("%d \n\n\n\n",card_to_play(34, max_right_card(34,16,18), composite_in_hand)); 


    printf("%d",max_right_card(34,16,18));
    printf("\n");
    return 0;
}


