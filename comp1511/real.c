// Assignment 2 19T2 COMP1511: Castle Defense
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0 (2019-07-22): Assignment released.
// Version 1.0.1 (2019-07-22): Fix minor style issue with print_tower.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "realm.h"

////////////////////////////////////////////////////////////////////////

// `struct realm` represents a realm, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// locations, though you may want to add other fields to it.
//
// You may need to add fields to struct realm.
struct realm {
    struct location *castle;
    struct location *lair;
};

// `struct location` represents a location, which could be a land,
// a tower, or a castle. Each of those places has a different type
// of information that this struct will need to store.
//
// You will need to add fields to struct location.
struct location {
    char name[MAX_NAME_LENGTH];
    struct enemy *enemies;
    struct location *next;

};

// `struct enemy` represents an enemy, which will move through the
// realm (to each location). Towers can deal damage to it, and
// it can deal damage to the Castle.
//
// You will need to add fields to struct enemy.
struct enemy {

    struct enemy *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Function prototypes for helper functions
static Location new_location(char *name);
static void print_tower(char *name, int power, int uses, Effect effect);
static void print_land(char *name);
static void print_castle(char *name, int defense);
static void print_enemy(char *name, int cur_hp, int max_hp);

// Add prototypes for any extra functions you create here.

////////////////////////////////////////////////////////////////////////

// You need to implement the following 9 functions.
// In other words, write code to make the function work as described 
// in realm.h.

// Create a new realm, and return a pointer to it.
Realm new_realm(void) {
    struct realm *realm = malloc(sizeof(struct realm));
    realm->lair = new_location("Lair");
    realm->castle = new_location("Castle");

    if (realm->lair != NULL && realm->castle != NULL) {
        realm->lair->next = realm->castle;
    }

    return realm;
}

static Location new_location(char *name) {

    // TODO: Make this create a location and return a pointer to it.

    return NULL;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new location to the realm.
void add_location(Realm realm, char *name) {

    // Note: you should use the new_location function here.

}

// Print out the realm.
void print_realm(Realm realm) {

    // Note: you should use the provided print functions here.

}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new tower to the realm.
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses) {
    return SUCCESS;
}

// Add an enemy to the realm.
int new_enemy(Realm realm, char *location_name, char *name, int hp) {
    return SUCCESS;
}

// Advance enemies towards the castle.
int advance_enemies(Realm realm) {
    return 0;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply damage from the enemies at each tower to that tower.
int apply_damage(Realm realm) {
    return 0;
}

// Destroy the realm, and free any associated memory.
void destroy_realm(Realm realm) {

}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified buff to the relevant towers or enemies.
int apply_buff(Realm realm, char *search_term, Buff buff, int amount){
    return 0;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified effect to each tower whose name matches the
// specified search term.
int apply_effect(Realm realm, char *search_term, Effect effect) {
    return 0;
}

////////////////////////////////////////////////////////////////////////

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.




////////////////////////////////////////////////////////////////////////
//                    Provided print functions                        //
//         NOTE: YOU SHOULD NOT MODIFY THE FOLLOWING FUNCTIONS        //
////////////////////////////////////////////////////////////////////////

static void print_tower(char *name, int power, int uses, int effect) {
    printf("%32s [pow: %3d | uses: %3d]", name, power, uses);
    if (effect == EFFECT_NONE) {
        printf(" {%c}", EFFECT_NONE_CHAR);
    } else if (effect == EFFECT_ICE) {
        printf(" {%c}", EFFECT_ICE_CHAR);
    } else if (effect == EFFECT_BOUNCE) {
        printf(" {%c}", EFFECT_BOUNCE_CHAR);
    }
    printf("\n");
}

static void print_land(char *name) {
    printf("%32s [____________________]\n", name);
}

static void print_castle(char *name, int defense) {
    printf("%32s [Castle Defenses: %3d]\n", name, defense);
}

static void print_enemy(char *name, int cur_hp, int max_hp) {
    printf("%40s [hp: %d/%d]\n", name, cur_hp, max_hp);
}

////////////////////////////////////////////////////////////////////////
//              End of provided print functions                        //
////////////////////////////////////////////////////////////////////////



