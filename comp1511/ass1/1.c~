#include<stdio.h>
int prime_identifier(int input){
    int identifier = 1;//I design the function such that if input is a composite, then identifier-1 
    int i = 2;
    
    while(i < 14){//the reason why I use 14 but not 24 is 13 is the maxmum prime factor we need to count for, for example, 17 and 34 are not in the realtion of cocomposite, and 51 is above limit, so it's enough to know 2 is a factor of 34 same as 38,46,knowing the prime factor above 13 is useless when you are playing.
        if(input % i == 0 ){
            identifier--;
            i = i + 12;//I only need to know if input is a prime, then I need identifier be either 0 or 1, so if there is a prime factor, the loop will stop due to i is bigger than 14
        }
    i++;
    }
    return identifier;
}
void knowing_cards_in_others_hand(int size_inhand,int card_in_hand[size_inhand],int played_this_round[40],int played[4],int unplayed[40]){//to do this, we need to know all the card quelified as "from 10-49 but played before, also not in my hand".

    int a,b,c,i;//these four variable are for the general purpose of my while loop, because I need to compare a lot of array, therefore I will use a lot of counter
    int card = 10;
    int unplayed_card_counter=0;
    while(card < 49){
        i = 0;
        a = 0;
        while(a < size_inhand){
        
            if(card == card_in_hand[a]){
                i++;
            }
            
            a++;
        }
        
        b = 0;
        while(b < 4 && played_this_round[b] != 0){
        
            if(card == played_this_round[b]){
                i++;
            }
            
            b++;            
        }
        
        c = 0;
        while(c < 40 && played[c] != 0){
        
            if(card == played[c]){
            i++;
            }
            
            c++;
        }
        
        if(i == 0){//if a card is belong to any array above, then i won't be 0
            unplayed[unplayed_card_counter]=card;
            unplayed_card_counter++;            
        }    
        card++;
    }

}

int main(void){
    int i;
    int card_in_hand[4];
    int played_this_round[4]={0};
    int played[40]={0};
    int unplayed[40]={0};
    i=0;
    while(i < 10){
        scanf("%d",&played[i]);
        i++;
    }
    i=0;
    while(i < 3){
        scanf("%d",&played_this_round[i]);
        i++;
    }
    i=0;
    while(i < 4){
        scanf("%d",&card_in_hand[i]);
        i++;
    }
    i=0;
    knowing_cards_in_others_hand(4,card_in_hand,played_this_round,played,unplayed);
    while(i < 40){
        printf("%d ",unplayed[i]);
i++;
}
printf("\n\n\n\n\n");
}
