#include <stdio.h>

enum Elements {Fire, Water, Air, Earth};

typedef struct Pokemon {
    double attack;
    double defence;
    char *name;
    double effectiveness;
    enum Elements type;
} Pokemon;

double pokemon_calc_strength(Pokemon p1, Pokemon p2);
void pokemon_battle(Pokemon p1, Pokemon p2);

int main() {
    Pokemon charmander, squirtle;

    charmander.name = "Charmander";
    charmander.type = Fire;
    squirtle.name = "Squirtle";
    squirtle.type = Water;

    charmander.attack = squirtle.attack = 10;
    charmander.defence = squirtle.defence = 20;
    //charmander.attack = 50;

    pokemon_battle(charmander, squirtle);
}

// Calculates p1's strength in a battle against p2
double pokemon_calc_strength(Pokemon p1, Pokemon p2) {
    return (p1.attack / p2.defence) * p1.effectiveness * 50;
}

// Evaluate the winner of a pokemon battle between p1 and p2
void pokemon_battle(Pokemon p1, Pokemon p2) {
    // I know this is quite ugly and I could've used case-switch but I like this a bit better
    if (p1.type == Fire) {
        if (p2.type == Water) {
            p1.effectiveness = 0.5;
            p2.effectiveness = 2;
        } else if (p2.type == Fire) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Air) {
            p1.effectiveness = 2;
            p2.effectiveness = 0.5;
        } else if (p2.type == Earth) {
            p1.effectiveness = p2.effectiveness = 1;
        }
    } else if (p1.type == Water) {
        if (p2.type == Water) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Fire) {
            p1.effectiveness = 2;
            p2.effectiveness = 0.5;
        } else if (p2.type == Air) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Earth) {
            p1.effectiveness = 0.5;
            p2.effectiveness = 2;
        }
    } else if (p1.type == Air) {
        if (p2.type == Water) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Fire) {
            p1.effectiveness = 0.5;
            p2.effectiveness = 2;
        } else if (p2.type == Air) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Earth) {
            p1.effectiveness = 2;
            p2.effectiveness = 0.5;
        }
    } else if (p1.type == Earth) {
        if (p2.type == Water) {
            p1.effectiveness = 2;
            p2.effectiveness = 0.5;
        } else if (p2.type == Fire) {
            p1.effectiveness = p2.effectiveness = 1;
        } else if (p2.type == Air) {
            p1.effectiveness = 0.5;
            p2.effectiveness = 2;
        } else if (p2.type == Earth) {
            p1.effectiveness = p2.effectiveness = 1;
        }
    }

    if (pokemon_calc_strength(p1, p2) > pokemon_calc_strength(p2, p1)) {
        printf("%s Is the winner!\nReward: 10 Ultra balls!\n", p1.name);
    } else if (pokemon_calc_strength(p2, p1) > pokemon_calc_strength(p1, p2)) {
        printf("%s Is the winner!\nReward: 10 Ultra balls!\n", p2.name);
    } else {
        printf("The battle results in a draw!\n");
    }
}