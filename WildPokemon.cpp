#include <iostream>
#include <cmath>
#include "WildPokemon.h"

using namespace std;

WildPokemon::WildPokemon(Point2D in_loc, int in_id, string in_name, bool in_variant, double in_attack, double in_health) : GameObject(in_loc, in_id, 'W')
{
    name = in_name;
    attack = in_attack;
    health = in_health;
    variant = in_variant;
    in_combat = false;
    state = WildPokemonStates::IN_ENVIORMENT;
    current_trainer = NULL;
}

WildPokemon::~WildPokemon()
{
    cout << "WildPokemon destructed";
}
void WildPokemon::follow(Trainer* t)
{
    if(static_cast<int>(this->GetState()) != 2)
    {
    current_trainer = t;
    this->state = WildPokemonStates::IN_TRAINER;
    this->location = Point2D(t->GetLocation().x, t->GetLocation().y - 1);
    }
}
bool WildPokemon::get_variant()
{
    return this->variant;
}
double WildPokemon::get_attack()
{
    return this->attack;
}
double WildPokemon::get_health()
{
    return this->health;
}
bool WildPokemon::get_in_combat()
{
    return this->in_combat;
}
Trainer* WildPokemon::GetCurrentTrainer()
{
    return this->current_trainer;
}
bool WildPokemon::Update()
{
    if(this->state == WildPokemonStates::IN_ENVIORMENT) return false;
    else if (this->health < 1)
    {
        cout << this->name << " is dead ";
        this->state = WildPokemonStates::DEAD;
        return true;
    }
    else if (static_cast<int>(this->state) == 2)
    {
        this->location = Point2D(current_trainer->GetLocation().x, current_trainer->GetLocation().y - 2);
    }
}

void WildPokemon::ShowStatus()
{
    cout << this->name << " Status: ";
    GameObject::ShowStatus();
    switch(static_cast<int>(this->GetState()))
    {
    case 0:
        cout << this->name << " has " << this->health << " health " <<
        "and " << this->attack << " attack " << "and is currently in the wild" << endl;
        break;
    case 1:
        cout << this->name << " is dead." << endl;
        break;

    case 2:
        cout << this->name << " is currently following a trainer" << endl;
        break;
    }
}
bool WildPokemon::ShouldBeVisible()
{
    if(static_cast<int>(this->state) != 1)
        return true;
    else return false;
}


