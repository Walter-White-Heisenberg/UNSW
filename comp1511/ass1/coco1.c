
// Assignment 1 19T1 COMP1511 Coco
//
// This program was written by Yun Li (z5231701)
// on 31/03/2019
//

#include <stdio.h>
#include <assert.h>


#define ACTION_PLAYER_NAME    0
#define ACTION_DISCARD        1
#define ACTION_PLAY_CARD      2

#define N_CARDS              40
#define N_CARDS_INITIAL_HAND 10
#define N_PLAYERS             4
#define N_CARDS_DISCARDED     3

#define CARD_MIN             10
#define CARD_MAX             49


// IF YOU NEED MORE #defines ADD THEM HERE


void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int prime_card_counter(int *card, int size);
int big_composite_counter(int *card, int size);
int prime_identifier(int input);

// for this function, if you input your card as an arrayand the size of
// it, plus the card played in all the previous rounds and the card
// played in this round as other two arrays, then the last array you
// input will be turn into an array containing what's left in all other
// player's hand
void knowing_cards_in_others_hand (
    int size_inhand, int card_in_hand[size_inhand],
    int played_this_round[N_PLAYERS], int played[N_CARDS],
    int unplayed[N_CARDS]);
int cocomposite_or_not(int target, int input, int input2);
//it will play the biggest possible card share same type with
//and lower than target card, or return "0" when there is no 
//same type card playable
int just_lower(int input, int array[N_CARDS_INITIAL_HAND]);
//the function which gives the max_right_type card played this round
int max_right_card(int card_a, int card_b, int card_c);
//a higher level of "just_lower"
int card_to_play(int card_one, int right_max_card,
                 int array[N_CARDS_INITIAL_HAND]);
//biggest cocomposite I can play when first card is a composite
int biggest_possible(int input, int array[N_CARDS_INITIAL_HAND]);
// You should not need to change this main function

int main(void) {

    int which_action = 0;
    scanf("%d", &which_action);
    if (which_action == ACTION_PLAYER_NAME) {
        print_player_name();
    } else if (which_action == ACTION_DISCARD) {
        choose_discards();
    } else if (which_action == ACTION_PLAY_CARD) {
        choose_card_to_play();
    }

    return 0;
}

void print_player_name(void) {

    printf("player");

}

// The discard strategy is to give biggest composite number when I don't
// have prime bigger than 17.  If you use the initial array which
// contains both prime and comp, the program will go wrong when 42
// is the biggest or the second biggest composite in your hand.  I
// find that when 42 is in my hand, the best way to write a program
// that give the "non-42"biggest composite I have is to design an
// array only contain "non-douglas" composite card.
void choose_discards() {
    int card[N_CARDS_INITIAL_HAND];
    int initial_prime[N_CARDS_INITIAL_HAND]={0};
    int initail_composite[N_CARDS_INITIAL_HAND]={0};
    int douglas_or_not = 0;
    // I need to know if 42 is in my hand
    int prime_counter = 0;
    //this one will be used during the definition of prime card array
    int comp_counter = 0;
    //this one will be used during the definition of composite card array
    int i = 0;
    //i is for the general purpose of all loops
    

    while (i < N_CARDS_INITIAL_HAND) {   
        scanf("%d", &card[i]);        
        if (card[i] == 42) {
            douglas_or_not++;
        }else if (prime_identifier(card[i]) == 1) {
            initial_prime[prime_counter] = card[i];
            prime_counter++;
        }else{
            initail_composite[comp_counter] = card[i];
            comp_counter++;
        }               
        i++;       
    }
    
    int prime = prime_card_counter(card, N_CARDS_INITIAL_HAND);
    //after knowing the exact size of prime, 
    //it's easier for me to print out biggest prime
    int composite = N_CARDS_INITIAL_HAND - prime - douglas_or_not;
    //after knowing the exact size of prime, 
    //it's easier for me to print out biggest composite
    
    if (douglas_or_not == 1) {    
        printf("42 ");
        //in my strategy, giving out 42 is in the highest priority, 
        //the second high priority is prime bigger than 17,
        //the last his big composite.
        //why 17? because you never win a prime round 
        //with the prime lower than 17 most of time
        if (prime >= 1 && initial_prime[prime-1] > 17) {        
            printf("%d ", initial_prime[prime-1]);            
            if (prime >= 2 && initial_prime[prime-2] > 17) {        
                printf("%d", initial_prime[prime-2]);        
            } else {            
                printf("%d",initail_composite[composite-1]);        
            }           
        }else{
            printf("%d %d", initail_composite[composite-1],
                   initail_composite[composite-2]);
        }
    }else{            
        if (prime >= 1 && initial_prime[prime-1] > 17) {        
            printf("%d ",initial_prime[prime-1]);            
            if (prime >= 2 && initial_prime[prime-2] > 17) {        
                printf("%d ",initial_prime[prime-2]);                
                if (prime >= 3 && initial_prime[prime-3] > 17) {       
                    printf("%d",initial_prime[prime-3]);        
                }else{        
                    printf("%d",initail_composite[composite-1]);        
                }        
            }else{        
                printf("%d %d",initail_composite[composite-1],
                              initail_composite[composite-2]);        
            }            
        }else{            
            printf("%d %d %d",initail_composite[composite-1] , 
                              initail_composite[composite-2] , 
                              initail_composite[composite-3]);        
        }    
    }
    printf("\n");   
}


void choose_card_to_play(void) {
    int i;
    //i is for the general purpose of all loops
    int number_in_hand, played_this_round, position;
    //if you have 42 in your hand greatly influence the strategy,
    //so we had better to identify the existence of it    
    int douglas_in_hand_identifier = 0;
    // NUMBER OF CARDS IN YOUR HAND,  NUMBER OF CARDS PLAYED THIS ROUND, 
    //TABLE POSITION    
    scanf("%d %d %d", &number_in_hand, &played_this_round, &position);    
    // ADD CODE TO READ THE CARDS OF YOUR HAND INTO AN ARRAY   
    int card_in_random[number_in_hand];
    i = 0;
    while (i < number_in_hand) {    
        scanf("%d", &card_in_random[i]);        
        i++;
    }    
    // I want to divided card in my hand into differet parts: prime,
    // composite bigger than 42, composite smaller than 42, and 42.  
    int prime_in_hand[10] = {0};
    int big_composite_in_hand[10] = {0};
    int small_composite_in_hand[10] = {0};    
    int composite_in_hand[10] = {0};
    int possible_card = 10;
    //possible_card start from 10 and end in 50 in the while loop
    int counter_for_prime_array = 0;
    // int prime_counter = 0
    int big_comp_counter = 0;
    int small_comp_counter = 0;
    int counter_for_comp_array = 0;
   
    
    while (possible_card < 50) {
        i = 0;    
        while (i < number_in_hand) {        
            if (prime_identifier(possible_card) == 1 && 
                card_in_random[i] == possible_card) {                      
                
                prime_in_hand[counter_for_prime_array]=possible_card;
                counter_for_prime_array++;               
            } else if (prime_identifier(possible_card) == 0 && 
                        card_in_random[i]==possible_card && 
                        42 < possible_card) {
                //which means when big_comp_counter=0, 
                //I don't have any big composite                     
                big_composite_in_hand[big_comp_counter] = possible_card;
                // big_composite_hand[big_comp_counter] = possible card;
                big_comp_counter++;
                composite_in_hand[counter_for_comp_array] = possible_card;
                // composite_hand[comp_counter] = possible card;
                counter_for_comp_array++;                 
            } else if (card_in_random[i] == 42 && possible_card ==42) {                   
                douglas_in_hand_identifier++;
                //0 or 1 tells us we have douglas or not        
            } else if (prime_identifier(possible_card) == 0 &&
                         card_in_random[i]==possible_card &&
                          42 > possible_card) {            
                //same as the comment for "big_comp_counter"
                small_composite_in_hand[small_comp_counter] = possible_card;
                small_comp_counter++;
                composite_in_hand[counter_for_comp_array] = possible_card;
                counter_for_comp_array++;                
            }
            i++; 
        }
        possible_card++;
    } 
    //prime_in_hand[counter_for_prime_array] can represent the biggest prime, 
    //-1 from four counter to cancel a point less "+1" in the while loop 
    small_comp_counter--;
    big_comp_counter--;
    counter_for_prime_array--;
    counter_for_comp_array--;
     
    // ADD CODE TO READ THE CARDS PREVIOUSLY PLAYED THIS ROUND INTO AN ARRAY
    int card_current_out[N_PLAYERS] = {0};
    int is_douglas_out = 0;
    int is_prime_out = 0;
    int big_composite_identifier = 0;
    //these two variables are for current round   
    i = 0;
    while (i < played_this_round) {
        scanf("%d", &card_current_out[i]);
        if (card_current_out[i] == 42) {
            is_douglas_out++;
        }
        else if(prime_identifier(card_current_out[i]) == 1){
            is_prime_out++;
        }else if (((card_current_out[i] == 44) ||
        (card_current_out[i] == 45) || (card_current_out[i] == 46) ||
        (card_current_out[i] == 48) || (card_current_out[i] == 49)) 
            && cocomposite_or_not(card_current_out[i], 
            card_current_out[0], card_current_out[0]) > 0) {  
            //I design this for the eliminaiton of douglas, when somebody play 
            //cocomposite bigger than 42. so I also need to sure the big 
            //composite he played is cocomposite with the first card    
            big_composite_identifier++;                
        }
        i++;
    }
    //I only need "is_prime_out" be 0 or 1
    if (is_prime_out > 1){
        is_prime_out = 1;
    }
    int max_card = max_right_card(card_current_out[0], 
    card_current_out[1], card_current_out[2]);
    
    // ADD CODE TO READ THE CARDS PLAYED IN THE HISTORY OF THE GAME INTO AN ARRAY
    int card_played_before[N_CARDS];

    //so I read 4 card everytime but the position in array is higher and higher 
    //like 1234,5678,9101112

    if(number_in_hand == 10){
        i = 0;
        while (i < 40) {
            card_played_before[i] = 0;
            i++;
        }
    }else{
        /int played_pre_round[(N_CARDS_INITIAL_HAND - number_in_hand) * 4];
        i = 0;
        while (i < (N_CARDS_INITIAL_HAND - number_in_hand) * 4) {
            scanf("%d", &played_pre_round[i]);
            i++;
        }
        int b = (N_CARDS_INITIAL_HAND - 1 - number_in_hand) * 4;
        i = 0;
        while(b < N_CARDS) {            
            if (i < (N_CARDS_INITIAL_HAND - number_in_hand) * 4) {
                card_played_before[b] = played_pre_round[i];
                i++;
            }else{
                card_played_before[b] = played_pre_round[0];
            }
            b++;            
        }
    }    
    i = 0;
    while (i < 40) {
        printf("%d ", card_played_before[i]);
        i++;
    }
    i=0;
    int is_prime_previous[1]={0};
    int is_douglas_previous[1]={0};
    while(i < N_CARDS) {
        if (card_played_before[i] != 0 && prime_identifier(card_played_before[i]) == 1) {
            is_prime_previous[0] = 1;
        }else if (card_played_before[i] == 42 && 
        card_played_before[i] != 0) {
            is_douglas_previous[0] = 1;
        }
        i++;        
    }
    // YOU WILL NEED TO USE A WHILE LOOP AND SCANF
    int card_unplayed[N_CARDS]={0};

    //if my program can remember all the card has been played, 
    //including my card, cards played in previous rounds and current round, 
    //Then I can generate an array that shows 
    //what's the possible card opponents gonna play next.
    //Then I wrote a void function to do this
    knowing_cards_in_others_hand (number_in_hand,card_in_random , 
    card_current_out,card_played_before , card_unplayed);
    //then we run the funcion which create the array of unplayed card   
    
    if (number_in_hand > 0 && douglas_in_hand_identifier == 1){
    //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if (small_composite_in_hand[0] != 0) {
                    // explain
                    printf("%d",small_composite_in_hand[small_comp_counter/2]);
                }else{
                    if (prime_in_hand[0] != 0) {
                        // explain
                        printf("%d",prime_in_hand[0]);
                    }else{  
                        if (big_composite_in_hand[0] != 0) {
                            printf("%d",big_composite_in_hand[0]);
                        }else{
                            printf("42");
                        }
                    }
                }            
            }else{
                if (small_composite_in_hand[0] != 0) {
                    printf("%d",small_composite_in_hand[small_comp_counter/2]);
                }else{
                    if (big_composite_in_hand[0] != 0) {
                        printf("%d",big_composite_in_hand[0]);
                    }else{  
                        printf("42");
                    }
                }    
            }                            
        }else {
        //not first player
            if (prime_identifier(card_current_out[0]) == 0) {
                if (big_composite_identifier == 1) {
                    printf("42");
                }else{
                    if (just_lower(card_current_out[0],big_composite_in_hand) != 0){
                        printf("%d",just_lower(card_current_out[0],
                                    big_composite_in_hand));
                    }else{
                        if(card_to_play(card_current_out[0], max_card, 
                           small_composite_in_hand) != 0){
                            printf("%d",card_to_play(card_current_out[0], 
                                    max_card, small_composite_in_hand));
                        }else{
                            if(cocomposite_or_not(card_current_out[0],
                            42,42) != 0){
                            printf("42");
                            }else{
                                printf("%d",composite_in_hand[counter_for_comp_array]);
                            }
                        }
                    }
                }
            }else{
                if(just_lower(card_current_out[0],prime_in_hand) != 0) {
                    printf("%d",just_lower(card_current_out[0],prime_in_hand));
                }else{
                    printf("42");
                }
            }
        }
    }
    if (number_in_hand > 0 && douglas_in_hand_identifier == 0){
    //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if (prime_in_hand[0] != 0) {
                    printf("%d",prime_in_hand[0]);              
                }else {
                    if(is_douglas_out == 0) {
                        if (small_composite_in_hand[0] != 0) {
                            printf("%d",small_composite_in_hand[small_comp_counter]);
                        }else {  
                            printf("%d",big_composite_in_hand[0]);                       
                        }
                    }else{
                        printf("%d",composite_in_hand[counter_for_comp_array]);
                    }   
                }
            }else {
                if(is_douglas_previous[0] == 1) {
                    if (composite_in_hand[0] != 0) {
                        if(composite_in_hand[counter_for_comp_array] == 49 && big_comp_counter > 1) {  
                            printf("%d",composite_in_hand[counter_for_comp_array-1]);
                        }else{
                            printf("%d",composite_in_hand[counter_for_comp_array]);
                        }    
                    }else{
                        printf("%d",prime_in_hand[counter_for_prime_array]);                                                                        
                    }  
                }else {
                    if (small_composite_in_hand[0] != 0) {
                        printf("%d",small_composite_in_hand[small_comp_counter]);
                    }else {  
                        if(big_composite_in_hand[0] != 0){
                            printf("%d",big_composite_in_hand[0]);                      
                        }else {
                            printf("%d",prime_in_hand[0]);                                                      
                        }
                    }
                }
            }                                       
        }else if(played_this_round > 0 && played_this_round < 3){
            if (prime_identifier(card_current_out[0]) == 0) {
                if (card_to_play(card_current_out[0], 
                    max_card, composite_in_hand) != 0){ 
                    printf("%d",card_to_play(card_current_out[0], max_card, composite_in_hand));
                }else {  
                    if(prime_in_hand[0] != 0){                    
                        printf("%d",prime_in_hand[counter_for_prime_array]);
                    }else{
                        printf("%d",composite_in_hand[counter_for_comp_array]);
                    }
                }
            }else {
                if (prime_in_hand[0] != 0){ 
                    printf("%d",just_lower(max_card, prime_in_hand));
                }else {
                    printf("%d",composite_in_hand[counter_for_comp_array]);
                }
            }
        }else{
        //last to play, hte strategy is very similar to 
        //"play_this_round >= 1 || play_this_round <= 3" situation
            if (prime_identifier(card_current_out[0]) == 0) {
                if(is_prime_out + is_douglas_out == 0) {
                    if (biggest_possible(card_current_out[0], 
                        composite_in_hand) != 0) { 
                        printf("%d",biggest_possible(card_current_out[0],
                        composite_in_hand));
                    }else {                       
                        if(prime_in_hand[0] != 0){                    
                            printf("%d",prime_in_hand[counter_for_prime_array]);
                        }else{
                            printf("%d",
                            composite_in_hand[counter_for_comp_array]);
                        }
                    }
                }else{
                    if (card_to_play(card_current_out[0], max_card, composite_in_hand) != 0) { 
                        printf("%d",card_to_play(card_current_out[0], max_card, composite_in_hand));
                    }else {                       
                        if(prime_in_hand[0] != 0){
                            printf("%d",prime_in_hand[counter_for_prime_array]);
                        }else{
                            printf("%d",composite_in_hand[counter_for_comp_array]);
                        }
                    }
                }
            }else {
                if(prime_in_hand[0] != 0) {
                    printf("%d",just_lower(max_card, prime_in_hand));
                }else {
                    printf("%d",composite_in_hand[counter_for_comp_array]);
                }
            }
        }
    }  
    // THEN REPLACE THIS PRINTF WITH CODE TO CHOOSE AND PRINT THE CARD YOU WISH TO PLAY 
    printf("\n");    
}
    // ADD YOUR FUNCTIONS HERE


//count how many prime card is in an array
int prime_card_counter(int *card, int size) {
// count_primes()
    int i = 0;
    int prime_counter = 0;
    while (i < size) {   
        if ((card[i] == 11) || (card[i] == 13) || (card[i] == 17) ||
            (card[i] == 19) || (card[i] == 23) || (card[i] == 29) ||
            (card[i] == 31) || (card[i] == 37) || (card[i] == 41) ||
            (card[i] == 43) || (card[i] == 47)) {       
            prime_counter++;                
        }
        i++;
    }
    return prime_counter;
}

//count how many composite card bigger than 42 is in an array
int big_composite_counter(int *card, int size) {
    int i = 0;
    int big_composite_counter = 0;
    while (i < size) {    
        if ((card[i] == 44) || (card[i] == 45) || (card[i] == 46) ||
            (card[i] == 48) || (card[i] == 49)) {       
            big_composite_counter++;                
        }
        i++;
    }
    return big_composite_counter;
}

int prime_identifier(int input) {
    int identifier = 1;
    //I design the function such that if input is a composite, then identifier-1 
    int i = 2;
    
    while (i < input) {
        if (input % i == 0 ) {
            return 0;
        }
        i++;
    }
    //identifier designed to be either 0 or 1
    return identifier;
}


// get_other_hands()???
void knowing_cards_in_others_hand(int size_inhand,int card_in_hand[size_inhand],int played_this_round[N_PLAYERS],int played[N_CARDS],int unplayed[N_CARDS]) {
    //we need to know all the card quelified as "from 10-49 but played before, also not in my hand".
    int a,b,c,i;
    //these four variable are for the general purpose of my while loop, because I need to compare a lot of array, therefore I will use a lot of counter
    int card = 10;
    int unplayed_card_counter=0;
    //this one will be used during the definition of unplayed card array
    while (card < 50) {
        i = 0;
        a = 0;
        while (a < size_inhand) {        
            if (card == card_in_hand[a]) {
                i++;
            }            
            a++;
        }       
        b = 0;
        while (b < N_PLAYERS && played_this_round[b] != 0) {        
            if (card == played_this_round[b]) {
                i++;
            }            
            b++;            
        }        
        c = 0;
        while (c < N_CARDS && played[c] != 0) {        
            if (card == played[c]) {
                i++;
            }            
            c++;
        }        
        if (i == 0) {
        //if a card is belong to any array above, then i won't be 0
            unplayed[unplayed_card_counter]=card;
            unplayed_card_counter++;            
        }    
        card++;
    }
}

/*
if (cocomposite(first, high)) {
    if 
*/
//to see if two or three composite cards in co_composite relationship
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
//it's very handy hahahaha
int just_lower(int input, int array[N_CARDS_INITIAL_HAND]) {
    int i , a , b;
    i=0;
    int card_just_lower;
    if (prime_identifier(input) == 1) {
        //there is no smaller prime
        if (array[0] > input){
            card_just_lower = array[0];
        }
        else{
            a=0;
            while(i < N_CARDS_INITIAL_HAND && array[i] != 0 ) {
                if (array[i] < input){
                    a=i;
                }
                i++;
            }
            card_just_lower = array[a]; 
        }   
    }else{
        //a is for the loop purpose just like i;
        a=-1;
        b=-1;
        int counter = 0;
        int bigger_comp[N_CARDS_INITIAL_HAND] = {0};
        while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
            if (array[i] < input && cocomposite_or_not(input , array[i], array[i]) > 0){
                a=i;               
            }else if (array[i] > input && cocomposite_or_not(input , array[i], array[i]) > 0){
                b=i; 
                bigger_comp[counter] = array[i];
                counter++;            
            }            
            i++;
        }if (a > -1) {
        //there is smaller cocoomposite
            card_just_lower = array[a];
        }else if (a == -1 && b > -1) {
        //there is no smaller cocomposite 
            card_just_lower = bigger_comp[0]; 
        }else if(a == -1 && b == -1) {
        //there is no cocomposite in this array
            card_just_lower = 0;
        }else{
            card_just_lower = 0;
        } 
    }
    return card_just_lower;    
}

int biggest_possible(int input, int array[N_CARDS_INITIAL_HAND]) {
    int i , a , b;
    i=0;
    int biggest;

    //a is for the loop purpose just like i;
    a=-1;
    while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
        if (cocomposite_or_not(input , array[i], array[i]) > 0){
            a=i;               
        }          
        i++;
    }if (a > -1) {
    //there is available big cocoomposite
        biggest = array[a];
    }else{
        biggest = 0;
    } 

    return biggest;    
}

//the function which gives the max_right_type card played this round
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

int card_to_play(int card_one, int right_max_card, int array[N_CARDS_INITIAL_HAND]) {
    int right_card_to_play;
    int must_right = just_lower(card_one, array);
        //a is for the loop purpose just like i;
    int a=-1;
    int i=0;
    while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
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







