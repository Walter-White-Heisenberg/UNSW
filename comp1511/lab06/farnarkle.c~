

// COMP1511 Farnarkling lab exercises
//
// This program by Frank Li (z5231701) on 31/03/2019

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define N_TILES 4
#define MAX_TILE 8
#define MAX_TURNS 100

// ADD YOUR #defines (if any) here

// You have to write these functions
int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]);
int count_arkles(int tiles1[N_TILES], int tiles2[N_TILES]);
void play_farnarkle(int hidden_tiles[]);
void farnarkle_ai(int turn, int previous_guesses[MAX_TURNS][N_TILES],
                  int farnarkles[MAX_TURNS], int arkles[MAX_TURNS],
                  int guess[N_TILES]);

// Don't change these functions
int test_farnarkle_ai(int hidden_tiles[]);
void print_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]);
void read_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]);
int read_tiles(int tiles[N_TILES]);
void print_tiles(int tiles[N_TILES]);
void set_tiles_to_pseudo_random_values(int tiles[N_TILES]);

// ADD PROTOTYPES FOR ANY FUNCTIONS YOU CREATE HERE

// DO NOT CHANGE THIS FUNCTION
// This main function won't be marked as part of the lab
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the lab.

int main(void) {
    int call_which_function = 0;

    printf("Enter 0 to call count_farnarkles()\n");
    printf("Enter 1 to call count_arkles()\n");
    printf("Enter 2 to call play_farnarkle()\n");
    printf("Enter 3 to call test_ai_farnarkle_player()\n");
    printf("Call which function: ");
    scanf("%d", &call_which_function);

    if (call_which_function == 0) {
        int tiles1[N_TILES], tiles2[N_TILES];
        read_two_tile_sequences(tiles1, tiles2);
        int farnarkles = count_farnarkles(tiles1, tiles2);
        printf("count_farnarkles returned %d for\n", farnarkles);
        print_two_tile_sequences(tiles1, tiles2);
    } else if (call_which_function == 1) {
        int tiles1[N_TILES], tiles2[N_TILES];
        read_two_tile_sequences(tiles1, tiles2);
        int arkles = count_arkles(tiles1, tiles2);
        printf("count_arkles returned %d for\n", arkles);
        print_two_tile_sequences(tiles1, tiles2);
    } else if (call_which_function == 2) {
        int hidden_tiles[N_TILES];
        set_tiles_to_pseudo_random_values(hidden_tiles);
        play_farnarkle(hidden_tiles);
    } else if (call_which_function == 3) {
        int hidden_tiles[N_TILES];
        printf("Enter hidden tiles: ");
        assert(read_tiles(hidden_tiles) == N_TILES);
        test_farnarkle_ai(hidden_tiles);
    }

    return 0;
}

// return number of farnarkles
int count_farnarkles(int tiles1[N_TILES], int tiles2[N_TILES]) {
    int x,i;
    x=0;
    i=0;
    while(x<N_TILES){
        if(tiles1[x]==tiles2[x]){
            i++;
        }
    x++;
    }

    // PUT YOUR CODE HERE
    // NOTE DO NOT CHANGE tiles1 or tiles2

    return i;
}

// return number of arkles
int count_arkles(int tiles1[N_TILES], int tiles2[N_TILES]) {
    int x,y,i,arkle;
    x=0;
    y=0;
    arkle=0;
    i=0;
    int array1[N_TILES],array2[N_TILES];    
    while(x<N_TILES){
    if(tiles1[x]==tiles2[x]){
        i++;
        }
    array2[x]=tiles2[x];
    array1[x]=tiles1[x];
    x++;
    }
    x=0;
    while(x<N_TILES){
     y=0;   
        while(y<N_TILES){                   
            if(array1[x] == array2[y]){   
                arkle++;
                array1[x]=array1[x]+20;
                array2[y]=array2[y]+array1[x]+40;
            }
            y++;
        }
     x++;   
    } 
   arkle=arkle-i;
   return arkle;
}

// play_farnarkle is given a sequence of hidden tiles.
// It reads guesses from a human player,
// printing the number of farnarkles and arkles for each guess,
// until the human player guesses the sequence.

void play_farnarkle(int hidden_tiles[N_TILES]) {

int tiles[N_TILES];
int x=0;
int identifier=0;
int FA,A,y;
    while(identifier==0){
        x++;
        y=0;
        printf("Enter guess for turn %d: ",x);
        while(y<N_TILES){
        scanf("%d",&tiles[y]);
        y++;
        }
        FA=count_farnarkles(tiles, hidden_tiles);
        A=count_arkles(tiles, hidden_tiles);
        printf("%d farnarkles, %d arkles\n",FA,A);
        if(FA==4){
            printf("You win\n");
            identifier++;
        }

    }    // PUT YOUR CODE HERE
}

// farnarkle_ai is given
//
// turn: the turn number
// previous_guesses: an array of turn - 1 previous guesses
// farnarkles: an array of turn - 1 farnarkle counts for previous guesses
// arkles: an array of turn - 1 arkle counts for previous guesses
//
// it should choose a suitable guess and store it in the array guess

void farnarkle_ai(int turn, int previous_guesses[MAX_TURNS][N_TILES],
                  int farnarkles[MAX_TURNS], int arkles[MAX_TURNS],
                  int guess[N_TILES]) {
    int i,a,RN;
    int identify=0;
    if(turn=1){
        i = 0;
        while(i < N_TILES){
        guess[i]=1+i;
        i++;
    }
    else{
        if(farnarkles[turn-1]+arkles[turn-1] == 0 && identify == 0){
            i=0;
            while(i < N_TILES){
            guess[i]=previous_guesses[turn-1][i]+N_TILES
            i++;
            identify++;            
            }
        }
        else{
        counter=
        i=0;
        a=1;
        while(i < N_TILES){
                guess[i]=a;
                i++;  
                }      
        if(){
                             
            }
        }
   i = 0;
    while(i < N_TILES){
    previous_guess[turn-1][i]=guess[i];
    i++;
    }
    }
    }
// DO NOT CHANGE THE FUNCTIONS BELOW HERE

// DO NOT CHANGE THIS FUNCTION
void print_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]) {
    printf("Sequence 1: ");
    print_tiles(tiles1);
    printf("\n");
    printf("Sequence 2: ");
    print_tiles(tiles2);
    printf("\n");
}

// DO NOT CHANGE THIS FUNCTION
void read_two_tile_sequences(int tiles1[N_TILES], int tiles2[N_TILES]) {
    printf("Enter tile sequence 1: ");
    assert(read_tiles(tiles1) == N_TILES);
    printf("Enter tile sequence 2: ");
    assert(read_tiles(tiles2) == N_TILES);
}

// DO NOT CHANGE THIS FUNCTION
// read N_TILES tiles into array tiles
// returns number of tiles successfully read
int read_tiles(int tiles[N_TILES]) {
    int i = 0;
    while (i < N_TILES) {
        if (scanf("%d", &tiles[i]) != 1) {
            return i;
        }
        if (tiles[i] < 1 || tiles[i] > MAX_TILE) {
            return i;
        }
        i = i + 1;
    }
    return i;
}

// DO NOT CHANGE THIS FUNCTION
// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
    int i = 0;
    while (i < N_TILES) {
        printf("%d", tiles[i]);
        if (i < N_TILES - 1) {
            printf(" ");
        }
        i = i + 1;
    }
}

// DO NOT CHANGE THIS FUNCTION
void set_tiles_to_pseudo_random_values(int tiles[N_TILES]) {
    // seed (initialize) pseudo-random number generate with current time in seconds
    srand(time(NULL));

    int i = 0;
    while (i < N_TILES) {
        // rand() returns a pseudo-random integer in ranger 0 to RAND_MAX inclusive
        // convert to an integer in the range 1..MAX_TILE_template
        tiles[i] = rand() % MAX_TILE + 1;
        i = i + 1;
    }
}

// DO NOT CHANGE THIS FUNCTION

// test_farnarkle_ai is given a sequence of hidden tiles
// It calls the function farnarkle_ai to make a guess
// printing the number of farnarkles and arkles for each guess,
// until farnarkle_ai guesses the sequence.
// number of turns taken is returned

int test_farnarkle_ai(int hidden_tiles[N_TILES]) {
    int guesses[MAX_TURNS][N_TILES] = {{0}};
    int farnarkles[MAX_TURNS] = {0};
    int arkles[MAX_TURNS] = {0};
    int turn_limit = MAX_TILE * N_TILES;

    int turn = 0;
    while (turn <= turn_limit) {

        int i = 0;
        while (i < N_TILES) {
            guesses[turn][i] = -1;
            i = i + 1;
        }

        printf("Turn %d: farnarkle AI guess is: ", turn + 1);
        fflush(stdout); // help debugging

        farnarkle_ai(turn + 1, guesses, farnarkles, arkles, guesses[turn]);

        print_tiles(guesses[turn]);
        printf(" = ");

        int j = 0;
        while (j < N_TILES) {
            if (guesses[turn][j] < 1 || guesses[turn][j] > MAX_TILE) {
                printf("Invalid guess\nGame ended\n");
                return 0;
            }
            j = j + 1;
        }

        farnarkles[turn] = count_farnarkles(hidden_tiles, guesses[turn]);
        arkles[turn] = count_arkles(hidden_tiles, guesses[turn]);

        printf("%d farnarkles, %d arkles\n", farnarkles[turn], arkles[turn]);

        if (farnarkles[turn] == N_TILES) {
            printf("Farnarkle AI took %d turns to guess the tiles\n", turn + 1);
            return turn + 1;
        }
        turn = turn + 1;
    }
    printf("Turn limit of %d turns exceeded\nGame ended\n", turn_limit);
    return turn + 1;
}


