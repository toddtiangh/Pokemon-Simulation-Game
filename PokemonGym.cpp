#include "GameObject.h"
#include "PokemonGym.h"
#include <iostream>

using namespace std;

PokemonGym::PokemonGym()
{
    display_code = 'G';
    state = PokemonGymStates::NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}
PokemonGym::PokemonGym(Point2D in_loc, int in_id, unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle)
{
    display_code = 'G';
    id_num = in_id;
    location = in_loc;
    max_number_of_battles = max_battle;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    PokeDollar_cost_per_battle = PokeDollar_cost;
    state = PokemonGymStates::NOT_DEFEATED;
    cout << "PokemonGym constructed" << endl;
}

PokemonGym::~PokemonGym()
{
    cout << "PokemonGym Destructed" << endl;
}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty)
{
    return double(battle_qty * this->PokeDollar_cost_per_battle);
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty)
{
    return (health_cost_per_battle * battle_qty);
}

unsigned int PokemonGym::GetNumBattlesRemaining()
{
    return this->num_battle_remaining;
}

bool PokemonGym::IsAbletoBattle(unsigned int battle_qty, double budget, unsigned int health)
{
    if(budget > this->GetPokeDollarCost(battle_qty) && health > this->GetHealthCost(battle_qty))
        return true;
    else
        return false;
}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units)
{
    if(this->num_battle_remaining - battle_units >= 0)
    {
        this->num_battle_remaining = num_battle_remaining - battle_units;
        return (battle_units * this->experience_per_battle);
    }
    else
    {
        int temp = num_battle_remaining;
        num_battle_remaining = 0;
        return (temp * this->experience_per_battle);
    }
}

unsigned int PokemonGym::GetExperiencePerBattle()
{
    return this->experience_per_battle;
}

bool PokemonGym::Update()
{
    if(passed() && static_cast<int>(this->state) == 0)
    {
        state = PokemonGymStates::DEFEATED;
        display_code = 'g';
        cout << this->display_code << this->id_num << " has been beaten" << endl;
        return true;
    }
    else
        return false;
}

bool PokemonGym::passed()
{
    if(static_cast<int>(this->state) == 1)
        return true;
    else
        return false;
}

void PokemonGym::ShowStatus()
{
    cout << "PokemonGymStatus: ";
    this->Building::ShowStatus();
    cout << "Max Number of Battles:" << this->max_number_of_battles << endl;
    cout << "Health cost per battle:" << this->health_cost_per_battle << endl;
    cout << "PokeDollar per battle:" << this->PokeDollar_cost_per_battle << endl;
    cout << "Experience per battle:" << this->experience_per_battle << " " << endl;
    cout << this->num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
}

