#ifndef PokemonCenter_h
#define PokemonCenter_h
#include "Building.h"

enum PokemonCenterStates
    {
        POTIONS_AVAILABLE = 0,
        NO_POTIONS_AVAILABLE = 1
    };
class PokemonCenter : public Building
{
private:
    unsigned int potion_capacity;
    unsigned int num_potions_remaining = potion_capacity;
    double pokedollar_cost_per_potion;
public:
    PokemonCenter();

    PokemonCenter(Point2D in_loc, int in_id, double potion_cost, unsigned int potion_cap);

    ~PokemonCenter();

    bool HasPotions();

    unsigned int GetNumPotionRemaining();

    bool CanAffordPotion(unsigned int potion, double budget);

    double GetPokeDollarCost(unsigned int potion);

    unsigned int DistributePotion(unsigned int potion_needed);

    bool Update();

    void ShowStatus();
};

#endif /* PokemonCenter_h */

