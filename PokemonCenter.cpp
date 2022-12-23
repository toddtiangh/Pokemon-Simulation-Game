#include "Building.h"
#include "PokemonCenter.h"
#include <iostream>

using namespace std;

PokemonCenter::PokemonCenter()
{
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = PokemonCenterStates::POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter::PokemonCenter(Point2D in_loc, int in_id, double potion_cost, unsigned int potion_cap)
{
    location = in_loc;
    display_code = 'C';
    id_num = in_id;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = potion_cost;
    state = PokemonCenterStates::POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed" << endl;
}

PokemonCenter::~PokemonCenter()
{
    cout << "PokemonCenter Destructed" << endl;
}

bool PokemonCenter::HasPotions()
{
    if(this->num_potions_remaining > 0)
        return true;
    else
        return false;
}

unsigned int PokemonCenter::GetNumPotionRemaining()
{
    return this->num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
    if(budget >= this->GetPokeDollarCost(potion))
        return true;
    else
        return false;
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
    return (potion * this->pokedollar_cost_per_potion);
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
    if(this->num_potions_remaining >= potion_needed)
    {
        this->num_potions_remaining -= potion_needed;
        return potion_needed;
    }
    else
    {
        int temp = this->num_potions_remaining;
        this->num_potions_remaining = 0;
        return temp;
    }
}

bool PokemonCenter::Update()
{
    if(this->num_potions_remaining == 0 && static_cast<int>(this->GetState()) == 0)
    {
        this->display_code = 'c';
        state = PokemonCenterStates::NO_POTIONS_AVAILABLE;
        cout << "PokemonCenter: " << this->id_num << " has run out of potions" << endl;
        return true;
    }
    else
        return false;
}

void PokemonCenter::ShowStatus()
{
    cout << "PokemonCenter Status: ";
    this->Building::ShowStatus();
    cout << "PokeDollars per potion: " <<
    this->pokedollar_cost_per_potion << endl;
    cout << "Has " << this->num_potions_remaining
    << " potion(s) remaining" << endl;
}


