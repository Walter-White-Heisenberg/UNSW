#include<stdio.h>
int prime_identifier(int input){
    int identifier = 1;
    //I design the function such that if input is a composite, then identifier-1 
    int i = 2;
    
    while (i < 14){
    //the reason why I use 14 but not 24 is 13 is the maxmum prime factor we need to count for, for example, 17 and 34 are not in the realtion of cocomposite, and 51 is above limit, so it's enough to know 2 is a factor of 34 same as 38,46,knowing the prime factor above 13 is useless when you are playing.
        if (input % i == 0 ){
            identifier--;
            i = i + 12;
            //I only need to know if input is a prime, then I need identifier be either 0 or 1, so if there is a prime factor, the loop will stop due to i is bigger than 14
        }
        i++;
    }
    return identifier;
}
int main(void){    
    int card[10];
    int initial_prime[10]={0};
    //I need to know how many prime is in my hand
    int initail_composite[10]={0};
    //I know this looks very confusing and unnecessary. Long story, my discard strategy is to give biggest composite number when I don't have prime bigger than 17. If you use the initial array which contains both prime and comp, the program will go wrong when 42 is the biggest or the second biggest composite in your hand. I find that when 42 is in my hand, the best way to write a program that give the "non-42"biggest composite I have is to design an array only contain "non-douglas" composite card.
    int douglas_or_not=0;
    // I need to know if 42 is in my hand
    int prime_counter=0;
    //this one will be used during the definition of prime card array
    int comp_counter=0;
    //this one will be used during the definition of composite card array
    int i = 0;
    //i is for the general purpose of all loops
    

    while (i < 10){   
        scanf("%d", &card[i]);        
        if (card[i] == 42){
            douglas_or_not++;
        }else if (prime_identifier(card[i]) == 1){
            initial_prime[prime_counter]=card[i];
            prime_counter++;
        }else{
            initail_composite[comp_counter]=card[i];
            comp_counter++;
        }               
        i++;       
    }
    
    int prime=prime_card_counter(card, 10);
    //after knowing the exact size of prime, it's easier for me to print out biggest prime
    int composite=10 - prime - douglas_or_not;
    //after knowing the exact size of prime, it's easier for me to print out biggest composite
    
    if (douglas_or_not == 1){    
        printf("42 ");
   //in my strategy, giving out 42 is in the highest priority, the second high priority is prime bigger than 17, the last his big composite.
   //why 17? because you never win a prime round with the prime lower than 17 most of time            
        if (prime >= 1 && initial_prime[prime-1] > 17){        
            printf("%d ",initial_prime[prime-1]);            
            if (prime >= 2 && initial_prime[prime-2] > 17){        
                printf("%d",initial_prime[prime-2]);        
            }else{            
                printf("%d",initail_composite[composite-1]);        
            }           
        }else{
            printf("%d %d",initail_composite[composite-1],initail_composite[composite-2]);
        }
    }else{            
        if (prime >= 1 && initial_prime[prime-1] > 17){        
            printf("%d ",initial_prime[prime-1]);            
            if (prime >= 2 && initial_prime[prime-2] > 17){        
                printf("%d ",initial_prime[prime-2]);                
                if (prime >= 3 && initial_prime[prime-3] > 17){       
                    printf("%d",initial_prime[prime-3]);        
                }else{        
                    printf("%d",initail_composite[composite-1]);        
                }        
            }else{        
                printf("%d %d",initail_composite[composite-1],initail_composite[composite-2]);        
            }            
        }else{            
            printf("%d %d %d",initail_composite[composite-1],initail_composite[composite-2],initail_composite[composite-3]);        
        }    
    }
    printf("\n");   
}
