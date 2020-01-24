// Helper function to create GGG for testing purposes.
static Pokemon create_GGG(void) {
    Pokemon pokemon = new_pokemon(
            GGG_ID, GGG_NAME,
            GGG_HEIGHT, GGG_WEIGHT,
            GGG_FIRST_TYPE,
            GGG_SECOND_TYPE
    );
    return pokemon;
}
