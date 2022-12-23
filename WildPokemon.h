#ifndef WildPokemon_h
#define WildPokemon_h

#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "Point2D.h"
#include "PokemonGym.h"
#include "Vector2D.h"
#include "Trainer.h"

using namespace std;

enum WildPokemonStates
    {
        IN_ENVIORMENT = 0,
        DEAD = 1,
        IN_TRAINER = 2
    };

class WildPokemon : public GameObject
{
protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    string name;
    Trainer* current_trainer = NULL;

public:
    WildPokemon(Point2D in_loc, int in_id, string in_name, bool in_variant, double in_attack, double in_health);

    ~WildPokemon();

    void follow(Trainer* t);

    bool get_variant();

    double get_attack();

    double get_health();

    bool get_in_combat();

    Trainer* GetCurrentTrainer();

    bool Update();

    void ShowStatus();

    bool ShouldBeVisible();
};

#endif /* WildPokemon_h */
