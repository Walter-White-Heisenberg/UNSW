
// Assignment 1 19T1 COMP1511 Coco
//
// This program was written by Yun Li (z5231701)
// on 31/03/2019
//
//designed to played a card called coco as good as human
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


void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);

int prime_card_counter(int *card, int size);
int big_composite_counter(int *card, int size);
int prime_identifier(int input);

//for this function, if you input your card as an array and the size of
//it, plus the card played in all the previous rounds and the card
//played in this round as other two arrays, then the last array you
//input will be turn into an array containing what's left in all other
//player's hand
void knowing_cards_left (
    int size_inhand, int card_in_hand[size_inhand],
    int played_this_round[N_PLAYERS], int played[N_CARDS],
    int unplayed[N_CARDS]);
int cocomposite_or_not(int target, int input, int input2);
//it will play the biggest card cocomposite with
//and lower than target card, or return "0" when there is no 
//same type card playable
int just_lower(int input, int array[N_CARDS_INITIAL_HAND]);
//the function which gives the max_right_type card played this round
int max_right_card(int card_a, int card_b, int card_c);
//a higher level of "just_lower",also return 0 when illegal
int card_to_play(int card_one, int right_max_card,
                 int array[N_CARDS_INITIAL_HAND]);
//biggest cocomposite to play when first card is a comp, also return 0
int biggest_possible(int input, int array[N_CARDS_INITIAL_HAND]);
//after the deduction about what's left in other people's hand, we can
//know know what's the best composite card to play without risk of 
//getting penalty point, also return 0
int smartass(int first, int unplayed[N_CARDS], 
int in_hand[N_CARDS_INITIAL_HAND]);

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

    printf("uncle Wang next door");

}

// give biggest three when no 42 in hand, or give biggest two and 42
void choose_discards() {
    int card[N_CARDS_INITIAL_HAND];
    int initial_prime[N_CARDS_INITIAL_HAND]={0};
    int initail_composite[N_CARDS_INITIAL_HAND]={0};
    int douglas_or_not = 0;
    // I need to know if 42 is in my hand
    int prime_counter = 0;
    //this one will be used during the definition of prime card array
    int comp_counter = 0;
    //this one will be used during the definition of composite array
    int i = 0;
    //i is for the general purpose of all loops
    
    while (i < N_CARDS_INITIAL_HAND) {   
        scanf("%d", &card[i]);        
        if (card[i] == 42) {
            douglas_or_not++;
        }             
        i++;       
    }
    if (douglas_or_not == 1){
        if (card[9] == 42) {
            printf("%d %d 42", card[8],card[7]);
        }else if (card[8] == 42){
            printf("%d %d 42", card[9],card[7]);
        }else{
            printf("%d %d 42", card[9],card[8]);
        }        
    }else{
        printf("%d %d %d",card[7] ,card[8], card[9]);
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
    int prime_hand[10] = {0};
    int big_composite_hand[10] = {0};
    int small_composite_hand[10] = {0};    
    int composite_hand[10] = {0};
    int possible_card = 10;
    //possible_card start from 10 and end in 50 in the while loop
    int prime_hand_counter = 0;
    // int prime_counter = 0
    int big_comp_counter = 0;
    int small_comp_counter = 0;
    int comp_counter = 0;
   
    
    while (possible_card < 50) {
        i = 0;    
        while (i < number_in_hand) {        
            if (prime_identifier(possible_card) == 1 && 
                card_in_random[i] == possible_card) {                      
                
                prime_hand[prime_hand_counter]=possible_card;
                prime_hand_counter++;               
            } else if (prime_identifier(possible_card) == 0 && 
                        card_in_random[i]==possible_card && 
                        42 < possible_card) {
                //which means when big_comp_counter=0, 
                //I don't have any big composite                     
                big_composite_hand[big_comp_counter] = possible_card;
                // big_composite_hand[big_comp_counter] = possible card;
                big_comp_counter++;
                composite_hand[comp_counter] = possible_card;
                // composite_hand[comp_counter] = possible card;
                comp_counter++;                 
            } else if (card_in_random[i] == 42 && possible_card ==42) {                   
                douglas_in_hand_identifier++;
                //0 or 1 tells us we have douglas or not        
            } else if (prime_identifier(possible_card) == 0 &&
                         card_in_random[i]==possible_card &&
                          42 > possible_card) {            
                //same as the comment for "big_comp_counter"
                small_composite_hand[small_comp_counter] = possible_card;
                small_comp_counter++;
                composite_hand[comp_counter] = possible_card;
                comp_counter++;                
            }
            i++; 
        }
        possible_card++;
    }
     
    //prime_hand[prime_hand_counter] represent the biggest prime 
    //-1 from four counter to cancel a pointless "+1" in the while loop 
    small_comp_counter--;
    big_comp_counter--;
    prime_hand_counter--;
    comp_counter--;
     
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
        else if (prime_identifier(card_current_out[i]) == 1) {
            is_prime_out++;
        }else if (((card_current_out[i] == 44) ||
        (card_current_out[i] == 45) || (card_current_out[i] == 46) ||
        (card_current_out[i] == 48) || (card_current_out[i] == 49)) 
            && cocomposite_or_not(card_current_out[i], 
            card_current_out[0], card_current_out[0]) > 0) {  
            //designed this for the eliminaiton of douglas, 
            //when somebody play cocomposite bigger than 42. 
            //This is to sure the big composite he played
            //is cocomposite with the first card    
            big_composite_identifier++;                
        }
        i++;
    }
    //I only need "is_prime_out" be 0 or 1
    if (is_prime_out > 1) {
        is_prime_out = 1;
    }
    int max_card = max_right_card(card_current_out[0], 
    card_current_out[1], card_current_out[2]);
    
    int card_played_before[N_CARDS] = {0};
    
    if (number_in_hand != N_CARDS_INITIAL_HAND) {
        i = 0;
        while (i < 4 * (N_CARDS_INITIAL_HAND - number_in_hand)) {
            scanf("%d", &card_played_before[i]);
            i++;
        }
    }    

    i = 0;
    int is_prime_previous[1] = {0};
    int is_douglas_previous[1] = {0};
    while(i < N_CARDS) {
        if (prime_identifier(card_played_before[i]) == 1 && 
        card_played_before[i] != 0) {
            is_prime_previous[0] = 1;
        }else if (card_played_before[i] == 42 && 
        card_played_before[i] != 0) {
            is_douglas_previous[0] = 1;
        }
        i++;        
    }

    int card_unplayed[N_CARDS] = {0}; 
    //generate an array that shows 
    //what's the possible card opponents gonna play next.
    //by using all the card has been played, 
    //including my card, cards in previous rounds and current round,
    knowing_cards_left (number_in_hand, card_in_random, 
    card_current_out, card_played_before , card_unplayed);

    //mainly, there are four general situations decided by
    //if you have 42 and if the round is before or after 5?
    //why before or after 5? because the function "smartass"
    //only applied after round 5 (thought to be best time to set
    //after experiment)
    
    //following is before round 5 and with 42 in hand
    //player with 42 perfer to play in the end then there is more chance 
    //to let other take 7 point
    if (number_in_hand > 5 && douglas_in_hand_identifier == 1){
        //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if (small_composite_hand[0] != 0) {
                //small_composite_hand[0] means first small_composite
                //because all the number in array is in order
                //so first one also means smallest
                // "!= 0" means there is small composite in hand 
                    printf("%d",
                    small_composite_hand[small_comp_counter/2]);
                    //divided by two because both biggest or smallest is
                    //not wanted
                }else{
                    if (prime_hand[0] != 0) {
                        printf("%d",prime_hand[0]);
                        //if you play prime first, 
                        //then choose the smallest to play
                    }else{  
                        if (big_composite_hand[0] != 0) {
                            printf("%d",big_composite_hand[0]);
                        }else{
                            printf("42");
                        }
                    }
                }            
            }else{
                if (small_composite_hand[0] != 0) {
                    printf("%d",
                    small_composite_hand[small_comp_counter/2]);
                }else{
                    if (big_composite_hand[0] != 0) {
                        printf("%d",big_composite_hand[0]);
                    }else{  
                        printf("42");
                    }
                }    
            }                            
        }else {
        //not first player
            if (prime_identifier(card_current_out[0]) == 0) {
                if (big_composite_identifier == 1 && 
                cocomposite_or_not(card_current_out[0],42,42) != 0) {
                    //all the composite over 42 share factor with 42
                    printf("42");
                }else{
                    if (just_lower(card_current_out[0],
                    big_composite_hand) != 0) {
                        printf("%d",just_lower(card_current_out[0],
                                    big_composite_hand));
                    }else{
                        if(card_to_play(card_current_out[0], max_card, 
                           small_composite_hand) != 0) {
                            printf("%d",card_to_play(card_current_out[0], 
                                    max_card, small_composite_hand));
                        }else{
                            if(cocomposite_or_not(card_current_out[0],
                            42,42) != 0) {
                                printf("42");
                            //never play 42 as first card
                            }else{
                                printf("%d",
                                composite_hand[comp_counter]);
                            }
                        }
                    }
                }
            }else{
                if(just_lower(card_current_out[0],prime_hand) != 0) {
                    printf("%d",
                    just_lower(card_current_out[0],prime_hand));
                }else{
                    printf("42");
                }
            }
        }
    }
    if (number_in_hand > 5 && douglas_in_hand_identifier == 0){
    //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if (prime_hand[0] != 0 && prime_hand[0] < 19) {
                    printf("%d",prime_hand[0]);              
                }else {
                    if(is_douglas_out == 0) {
                        if (small_composite_hand[0] != 0) {
                            printf("%d",
                            small_composite_hand[small_comp_counter]);
                        }else {  
                            printf("%d",big_composite_hand[0]);                       
                        }
                    }else{
                        if(composite_hand[0] != 0){
                            printf("%d",composite_hand[comp_counter]);
                        }else{
                            printf("%d",prime_hand[0]);
                        }    
                    }   
                }
            }else {
                if(is_douglas_previous[0] == 1) {
                    if (composite_hand[0] != 0) {
                        if(composite_hand[comp_counter] == 49 && 
                        big_comp_counter > 1) { 
                        //if 49 is played first, it's likely that
                        //somebody don't have 14 21 28 35 42
                        //then you may get primes 
                            printf("%d",composite_hand[comp_counter-1]);
                        }else{
                            printf("%d",composite_hand[comp_counter]);
                        }    
                    }else{
                        printf("%d",prime_hand[prime_hand_counter]);                                                                        
                    }  
                }else {
                    if (small_composite_hand[0] != 0) {
                        printf("%d",
                        small_composite_hand[small_comp_counter]);
                    }else {  
                        if(big_composite_hand[0] != 0){
                            printf("%d",big_composite_hand[0]);                      
                        }else {
                            printf("%d",prime_hand[0]);                                                      
                        }
                    }
                }
            }                                       
        }else if(played_this_round > 0 && played_this_round < 3){
            //the key point is to take advantage of existing big card
            //that's why using card_to_play
            //sometime, just_lower is used for safety
            if (prime_identifier(card_current_out[0]) == 0) {
                if (card_to_play(card_current_out[0], 
                    max_card, composite_hand) != 0){ 
                    printf("%d",card_to_play(card_current_out[0], 
                    max_card, composite_hand));
                }else {  
                    if(prime_hand[0] != 0){                    
                        printf("%d",prime_hand[prime_hand_counter]);
                    }else{
                        printf("%d",composite_hand[comp_counter]);
                    }
                }
            }else {
                if (prime_hand[0] != 0){ 
                    printf("%d",just_lower(max_card, prime_hand));
                }else {
                    printf("%d",composite_hand[comp_counter]);
                }
            }
        }else{
        //when it's last to play, good thing is you can play the biggest
        //composite (by using function biggest possible) when 
        //there are no prime or 42 played before
        //or even decides play the prime or not
            if (prime_identifier(card_current_out[0]) == 0) {
                if(is_prime_out + is_douglas_out == 0) {
                    if (biggest_possible(card_current_out[0], 
                        composite_hand) != 0) { 
                        printf("%d",biggest_possible(card_current_out[0],
                        composite_hand));
                    }else {                       
                        if(prime_hand[0] != 0){                    
                            printf("%d",prime_hand[prime_hand_counter]);
                        }else{
                            printf("%d",
                            composite_hand[comp_counter]);
                        }
                    }
                }else{
                    if (card_to_play(card_current_out[0], max_card, composite_hand) != 0) { 
                        printf("%d",card_to_play(card_current_out[0], max_card, composite_hand));
                    }else {                       
                        if(prime_hand[0] != 0){
                            printf("%d",prime_hand[prime_hand_counter]);
                        }else{
                            printf("%d",composite_hand[comp_counter]);
                        }
                    }
                }
            }else {
                if(prime_hand[0] != 0) {
                    printf("%d",just_lower(max_card, prime_hand));
                }else {
                    printf("%d",composite_hand[comp_counter]);
                }
            }
        }
    }
    
    if (number_in_hand < 6 && douglas_in_hand_identifier == 1){
    //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if(smartass(0, card_unplayed, 
                composite_hand) != 0){
                    printf("%d",smartass(0, card_unplayed, 
                composite_hand));
                }else{
                    if (small_composite_hand[0] != 0) {
                        printf("%d",small_composite_hand[small_comp_counter/2]);
                    }else{
                        if (prime_hand[0] != 0) {
                            // explain
                            printf("%d",prime_hand[0]);
                        }else{  
                            if (big_composite_hand[0] != 0) {
                                printf("%d",big_composite_hand[0]);
                            }else{
                                printf("42");
                            }
                        }
                    }
                }                            
            }else{
                if(smartass(0, card_unplayed, 
                composite_hand) != 0) {
                    printf("%d",smartass(0, card_unplayed, 
                composite_hand));
                }else{
                    if (small_composite_hand[0] != 0) {
                        printf("%d",small_composite_hand[small_comp_counter/2]);
                    }else{
                        if (big_composite_hand[0] != 0) {
                            printf("%d",big_composite_hand[0]);
                        }else{  
                            printf("42");
                        }
                    }
                }    
            }                            
        }else {
        //not first player
            if (prime_identifier(card_current_out[0]) == 0) {
                if (big_composite_identifier == 1) {
                    printf("42");
                }else{
                    if(smartass(card_current_out[0], card_unplayed, 
                    composite_hand) != 0) {
                        printf("%d",smartass(card_current_out[0], card_unplayed, 
                    composite_hand));
                    }else{
                        if (just_lower(card_current_out[0],big_composite_hand) != 0){
                            printf("%d",just_lower(card_current_out[0],
                                        big_composite_hand));
                        }else{
                            if(card_to_play(card_current_out[0], max_card, 
                               small_composite_hand) != 0){
                                printf("%d",card_to_play(card_current_out[0], 
                                        max_card, small_composite_hand));
                            }else{
                                if(cocomposite_or_not(card_current_out[0],
                                42,42) != 0){
                                    printf("42");
                                }else{
                                    printf("%d",composite_hand[comp_counter]);
                                }
                            }                        
                        }
                    }
                }
            }else{
                if(smartass(card_current_out[0], card_unplayed, 
                composite_hand) != 0) {
                    printf("%d",smartass(card_current_out[0], card_unplayed, 
                composite_hand));
                }else{
                    if(just_lower(card_current_out[0],prime_hand) != 0) {
                        printf("%d",just_lower(card_current_out[0],prime_hand));
                    }else{
                        printf("42");
                    }
                }
            }
        }
    }
    //the strategy before round 5 and after round 5 are very similar
    //except the using of smartass which can generally play a composite
    //that never win a round
    if (number_in_hand < 6 && douglas_in_hand_identifier == 0){
    //strategy when first to play
        if (played_this_round == 0) {
            if (is_prime_previous[0] == 1) {
                if (prime_hand[0] != 0 && prime_hand[0] < 19) {
                    printf("%d",prime_hand[0]);              
                }else {
                    if(smartass(0, card_unplayed, 
                composite_hand) != 0) {
                        printf("%d",smartass(0, card_unplayed, 
                composite_hand));
                    }else{
                        if(is_douglas_out == 0) {
                            if (small_composite_hand[0] != 0) {
                                printf("%d",
                                small_composite_hand[small_comp_counter]);
                            }else {  
                                if(big_composite_hand[0] != 0){
                                    printf("%d",big_composite_hand[0]);                       }else{
                                    printf("%d",prime_hand[0]);
                                } 
                            }
                        }else{
                            if(composite_hand[0] != 0){
                                printf("%d",composite_hand[comp_counter]);
                            }else{
                                printf("%d",prime_hand[0]);
                            }
                        }       
                    }
                }
            }else {
                if(is_douglas_previous[0] == 1) {
                    if(smartass(0, card_unplayed, 
                composite_hand) != 0){
                        printf("%d",smartass(0, card_unplayed, 
                composite_hand));
                    }else{                    
                        if (composite_hand[0] != 0) {                        
                            if (composite_hand[comp_counter] == 49 && 
                            big_comp_counter > 1) {  
                                printf("%d",
                                composite_hand[comp_counter-1]);
                            }else{
                                printf("%d",
                                composite_hand[comp_counter]);
                            }    
                        }else{
                            printf("%d",
                             prime_hand[prime_hand_counter]); 
                        }
                    }      
                }else {
                    if (smartass(0, card_unplayed, 
                composite_hand) != 0){
                        printf("%d",smartass(0, card_unplayed, 
                composite_hand));
                    }else{
                        if (small_composite_hand[0] != 0) {
                            printf("%d",small_composite_hand[small_comp_counter]);
                        }else {  
                            if (big_composite_hand[0] != 0){
                                printf("%d",big_composite_hand[0]);                      
                            }else {
                                printf("%d",prime_hand[0]);                                                      
                            }
                        }
                    }
                }
            }                                       
        }else if (played_this_round > 0 && played_this_round < 3){
            if (prime_identifier(card_current_out[0]) == 0) {
                if (smartass(card_current_out[0], card_unplayed, 
                composite_hand) != 0){
                    printf("%d",smartass(card_current_out[0], 
                    card_unplayed, composite_hand));
                }else{
                    if (card_to_play(card_current_out[0], 
                        max_card, composite_hand) != 0){ 
                        printf("%d",card_to_play(card_current_out[0], 
                        max_card, composite_hand));
                    }else {  
                        if(prime_hand[0] != 0){                    
                            printf("%d",prime_hand[prime_hand_counter]);
                        }else{
                            printf("%d",composite_hand[comp_counter]);
                        }
                    }
                }
            }else {
                if (prime_hand[0] != 0){ 
                    printf("%d",just_lower(max_card, prime_hand));
                }else {
                    printf("%d",composite_hand[comp_counter]);
                }
            }
        }else{
        //last to play, hte strategy is very similar to 
        //"play_this_round >= 1 || play_this_round <= 3" situation
            if (prime_identifier(card_current_out[0]) == 0) {
                if (is_prime_out + is_douglas_out == 0) {
                    if (biggest_possible(card_current_out[0], 
                        composite_hand) != 0) { 
                        printf("%d",biggest_possible(card_current_out[0],
                        composite_hand));
                    }else {                       
                        if(prime_hand[0] != 0){                    
                            printf("%d",prime_hand[prime_hand_counter]);
                        }else{
                            printf("%d",
                            composite_hand[comp_counter]);
                        }
                    }
                }else{
                    if (card_to_play(card_current_out[0], 
                    max_card, composite_hand) != 0) { 
                        printf("%d",card_to_play(card_current_out[0], 
                        max_card, composite_hand));
                    }else {                       
                        if (prime_hand[0] != 0){
                            printf("%d",prime_hand[prime_hand_counter]);
                        }else{
                            printf("%d",composite_hand[comp_counter]);
                        }
                    }
                }
            }else {
                if (prime_hand[0] != 0) {
                    printf("%d",just_lower(max_card, prime_hand));
                }else {
                    printf("%d",composite_hand[comp_counter]);
                }
            }
        }
    }  
    printf("\n");    
}

//count how many prime card is in an array
int prime_card_counter(int *card, int size) {
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



void knowing_cards_left(int size_inhand,
int card_in_hand[size_inhand],int played_this_round[N_PLAYERS],
int played[N_CARDS],int unplayed[N_CARDS]) {
    //we need to know all the card quelified as "from 10-49 but played before, also not in my hand".
    int a,b,c,i;
    //these four variable are for the general purpose of my while loop, because I need to compare a lot of array, therefore I will use a lot of counter
    int card = 10;
    int unplayed_card_counter = 0;
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


//to see if three composite cards in co_composite relationship
//if you want to compare two cards, then just use two same number for
//"input" and "input2"
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

//input a target composite and a composite array, 
//then you get a co-composite number in this array 
//which is closest but lower than target one
//also work for prime if you use prime array
//return 0 when there are no card in array share same type
int just_lower(int input, int array[N_CARDS_INITIAL_HAND]) {
    int i , a , b;
    i = 0;
    int card_just_lower;
    if (prime_identifier(input) == 1) {
        //there is no smaller prime
        if (array[0] > input){
            card_just_lower = array[0];
        }
        else{
            a = 0;
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
        a = -1;
        b = -1;
        int counter = 0;
        int bigger_comp[N_CARDS_INITIAL_HAND] = {0};
        while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
            if (array[i] < input && cocomposite_or_not(input , 
            array[i], array[i]) > 0){
                a = i;               
            }else if (array[i] > input && 
            cocomposite_or_not(input , array[i], array[i]) > 0){
                b = i; 
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
    i = 0;
    int biggest;

    //a is for the loop purpose just like i;
    a = -1;
    while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
        if (cocomposite_or_not(input , array[i], array[i]) > 0){
            a = i;               
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
    //function represents right type card as themselves 
    //and wrong type card as "0"  
    p_b = prime_identifier(card_b) * card_b;
    p_c = prime_identifier(card_c) * card_c;
    
    int cocomp_identifier_b = 0;
    int cocomp_identifier_c = 0;
    //same as above, but this time I also need to 
    //identify sharing same factor or not
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
        + p_b * (p_b > p_c) * (p_b > card_a) + 
        p_c * (p_c > card_a) * (p_c > p_b);
    }else{
        max_card = card_a * (card_a >= comp_b) * (card_a >= comp_c) + 
        comp_b * (comp_b > comp_c) * (comp_b > card_a) + comp_c * 
        (comp_c > card_a)*(comp_c > comp_b);
    }
    return max_card;
}

//"just_lower" can play the best card against only first card,
//for just counting more situation in the program,
//"card_to_play" can play according to both first card and biggest card

int card_to_play(int card_one, int right_max_card, int array[N_CARDS_INITIAL_HAND]) {
    int right_card_to_play;
    int must_right = just_lower(card_one, array);
        //a is for the loop purpose just like i;
    int a=-1;
    int i=0;
    while (i < N_CARDS_INITIAL_HAND && array[i] != 0) {
        if (array[i] < right_max_card && 
        cocomposite_or_not(card_one , array[i], array[i]) > 0){
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
int smartass(int first, int unplayed[N_CARDS], 
            int in_hand[N_CARDS_INITIAL_HAND]) {
    int bigger,smaller;
    int best_card = 0;
    int i = N_CARDS_INITIAL_HAND - 1;
    int a = 0;

    int possible_counter[20];
    if (first == 0){
        bigger = 0;
        smaller = 0;
        while(-1 < i){
            while(a < N_CARDS && unplayed[a] != 0){
                if (cocomposite_or_not(in_hand[i],
                unplayed[a],unplayed[a]) == 1) {
                    if(unplayed[a] > in_hand[i]){
                        bigger++;
                    }else{
                        smaller++;
                    }
                }
                a++; 
            }
            if(smaller < 3 && bigger != 0){
                best_card = in_hand[i];
                i = i - 9;
            }else {
                best_card = 0;
            }
            i--;
        }       
    }else{
        bigger = 0;
        smaller = 0;
        while(-1 < i){
            while(a < N_CARDS && unplayed[a] != 0) {
                if (cocomposite_or_not(first,
                in_hand[i],unplayed[a]) == 1) {
                    if(unplayed[a] > in_hand[i]) {
                        bigger++;
                    }else{
                        smaller++;
                    }
                }
                a++; 
            }
            if(smaller ==0 && bigger != 0){
                best_card = in_hand[i];
                i = i - 9;
            }else {
                best_card = 0;
            }
            i--;
        }
    }
    return best_card;    
}






