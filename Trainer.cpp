#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "Trainer.h"
#include "WildPokemon.h"

using namespace std;

bool Trainer::UpdateLocation()
{
    if(fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y ) <= fabs(delta.y))
    {
        this->location = destination;
        cout << "Arrived" << endl;
        return true;
    }
    else
    {
        this->location = location + delta;
        if(location.x <= 0) location.x = 0;
        if(location.x >= 20) location.x = 20;
        if(location.y <= 0) location.y = 0;
        if(location.y >= 20) location.y = 20;
        cout << "Moved" << endl;
        this->health = health - 1;
        this->PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
        return false;
    }
}
void Trainer::SetupDestination(Point2D dest)
{
    Vector2D v1(dest.x, dest.y);
    this->destination = dest;
    if(GetDistanceBetween(dest, location) > 0)
    {
        this->delta = (this->location - v1) * (speed/GetDistanceBetween(dest, location));
    }
    else
        delta = Vector2D();
}

Trainer::Trainer() : GameObject('T')
{
    speed = 5;
    cout << "Trainer default constructed" << endl;
}
Trainer::Trainer(char in_code) : GameObject(in_code)
{
    speed = 5;
    state = TrainerStates::STOPPED;
    cout << "Trainer constructed" << endl;
}
Trainer::Trainer(Point2D in_loc, string in_name, int in_id, char in_code, unsigned int in_speed)
: GameObject(in_loc, in_id, in_code)
{
    speed = in_speed;
    name = in_name;
    state = TrainerStates::STOPPED;
    cout << "Trainer constructed" << endl;
}

Trainer::~Trainer()
{
    cout << "Trainer Destructed" << endl;
}

string Trainer::GetTrainerName()
{
    return this->name;
}

Vector2D Trainer::GetDelta()
{
    return this->delta;
}

void Trainer::StartMoving(Point2D dest)
{
    if(GetDistanceBetween(dest, location) == 0)
        cout << this->display_code << this->id_num << ":"
        << " I'm already there. See?" << endl;
    else if (this->state == 2)
        cout << this->display_code << this->id_num << ":"
        << " My Pokemon have fainted. I may move but you cannot see me" << endl;
    else
    {
        if(static_cast<int>(this->GetState()) == 3)
            current_center->RemoveOneTrainer();
        else if(static_cast<int>(this->GetState()) == 4)
            current_gym->RemoveOneTrainer();
        this->SetupDestination(dest);
        this->state = TrainerStates::MOVING;
        cout << this->display_code << this->id_num << ":"
        << " On my way" << endl;
    }
}
void Trainer::StartMovingToGym(PokemonGym* Gym)
{
    if(GetDistanceBetween(this->location,Gym->GetLocation()) == 0)
        cout << this->display_code << this->id_num << ":"
        << " I'm already at the Pokemon Gym!" << endl;
    else if (this->state == 2)
        cout << this->display_code << this->id_num << ":"
        << " My Pokemon have fainted so I can't move to the gym..." << endl;
    else
    {
        if(static_cast<int>(this->GetState()) == 3)
            current_center->RemoveOneTrainer();
        else if(static_cast<int>(this->GetState()) == 4)
            current_gym->RemoveOneTrainer();
        this->SetupDestination(Gym->GetLocation());
        this->current_gym = Gym;
        this->state = TrainerStates::MOVING_TO_GYM;
        cout << this->display_code << this->id_num << ":"
        << " On my way to the gym" << endl;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center)
{
    if(GetDistanceBetween(this->location, center->GetLocation()) == 0)
        cout << this->display_code << this->id_num << ":"
        << " I'm already at the Center!" << endl;
    else if (this->state == 2)
        cout << this->display_code << this->id_num << ":"
        << " My Pokemon have fainted so I should have gone to the center..." << endl;
    else
    {
        if(static_cast<int>(this->GetState()) == 3)
            current_center->RemoveOneTrainer();
        else if(static_cast<int>(this->GetState()) == 4)
            current_gym->RemoveOneTrainer();
        this->SetupDestination(center->GetLocation());
        this->current_center = center;
        this->state = TrainerStates::MOVING_TO_CENTER;
        cout << this->display_code << this->id_num << ":"
        << " On my way to the Center" << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles)
{
    if(state != TrainerStates::IN_GYM)
        cout << this->display_code << this->id_num << ":"
        << " I can only battle in a PokemonGym" << endl;
    else if (state == TrainerStates::FAINTED)
        cout << this->display_code << this->id_num << ":"
        << " My Pokemon have fainted so no more battles for me..." << endl;
    else if (!current_gym->IsAbletoBattle(num_battles, PokeDollars, health))
        cout << this->display_code << this->id_num << ":"
        << " Not enough money for battles, or you do not enough health." << endl;
    else if (current_gym->passed())
        cout << this->display_code << this->id_num << ":"
        << " Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    else
    {
        this->battles_to_buy = min(num_battles, current_gym->GetNumBattlesRemaining());
        this->state = TrainerStates::BATTLING_IN_GYM;
        cout << this->display_code << this->id_num << ":" <<
        " Started to battle at the Pokemon Gym" << current_gym->GetId() <<
        " with " << current_gym->GetNumBattlesRemaining() << " battles." << endl;
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
    if(this->state != TrainerStates::AT_CENTER)
        cout << this->display_code << this->id_num << ":"
        << " I can only recover health at a Pokemon Center" << endl;
    else if(!current_center->CanAffordPotion(num_potions, PokeDollars))
        cout << this->display_code << this->id_num << ":"
        << " Not enough money to recover health." << endl;
    else if(current_center->GetNumPotionRemaining() < 1)
        cout << this->display_code << this->id_num << ":"
        << " Cannot recover! No potions remaining in this Pokemon Center" << endl;
    else
    {
        this->state = TrainerStates::RECOVERING_HEALTH;
        this->potions_to_buy = min(num_potions,current_center->GetNumPotionRemaining());
        cout << this->display_code << this->id_num << ":"
        << " Started recovering " << num_potions << " potions at Pokemon Center "
        << current_center->GetId() << endl;
    }
}

void Trainer::Stop()
{
    state = TrainerStates::STOPPED;
    cout << this->display_code << this->id_num << ":Stopping..." << endl;
}

bool Trainer::HasFainted()
{
    if(this->health == 0)
        return true;
    else
        return false;
}

bool Trainer::ShouldBeVisible()
{
    if(this->state != 2)
        return true;
    else
        return false;
}

void Trainer::ShowStatus()
{
    cout << this->name << " Status: ";
    GameObject::ShowStatus();
    switch(static_cast<int>(this->GetState()))
    {
    case 0:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Stopped" << endl;
        break;
    case 1:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Moving at a speed of " << this->speed << " to destination";
        cout << this->destination;
        cout << "at each step of " << this->delta;
        cout << endl;
        break;
    case 2:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << this->name << " Is fainted and can't move. You Lose.";
        break;
    case 3:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Inside Pokemon Center " << current_center->GetId();
        cout << endl;
        break;
    case 4:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Inside PokemonGym " << current_gym->GetId();
        cout << endl;
        break;
    case 5:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Heading to Pokemon Center " << current_center->GetId() << " at a speed of "
        << this->speed << " at each step of " << this->delta;
        cout << endl;
        break;
    case 6:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Heading to PokemonGym " << current_gym->GetId() << " at a speed of "
        << this->speed << " at each step of " << this->delta;
        cout << endl;
        break;
    case 7:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Battling in PokemonGym " << current_gym->GetId() << "." << endl;
        break;
    case 8:
        cout << "Health:" << this->health << "\n" << "PokeDollars:" << this->PokeDollars
        << "\n" << "Experience:" << this->experience << endl;
        cout << "Recovering health in Pokemon Center " << current_center->GetId() << "." << endl;
        break;
    }
}

bool Trainer::Update()
{
    if(this->health < 1)
    {
        cout << this->name << " is out of health and can't move" << endl;
        state = TrainerStates::FAINTED;
        return false;
    }
    switch(static_cast<int>(this->GetState()))
    {
    case 0:
        return false;
        break;
    case 1:
        if(this->UpdateLocation() == true)
        {
            state = TrainerStates::STOPPED;
            return true;
        }
        else
            return false;
        break;
    case 2:
        return false;
        break;
    case 3:
        return false;
        break;
    case 4:
        return false;
        break;
    case 5:
        if(this->UpdateLocation() == true)
        {
            state = TrainerStates::AT_CENTER;
            current_center->AddOneTrainer();
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 6:
        if(this->UpdateLocation() == true)
        {
            state = TrainerStates::IN_GYM;
            current_gym->AddOneTrainer();
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 7:
        this->health = health - current_gym->GetHealthCost(battles_to_buy);
        this->PokeDollars = PokeDollars - current_gym->GetPokeDollarCost(battles_to_buy);
        this->experience += current_gym->TrainPokemon(battles_to_buy);
        cout << "**(" << this->name << ") completed "
        << this->battles_to_buy << "!**" << endl;
        cout << "**(" << this->name << ") gained "
        << current_gym->GetExperiencePerBattle() * battles_to_buy << " experience!**" << endl;
        this->state = TrainerStates::IN_GYM;
        return true;
        break;
    case 8:
        this->health += current_center->DistributePotion(potions_to_buy) * 5;
        this->PokeDollars = PokeDollars - current_center->GetPokeDollarCost(potions_to_buy);
        cout << "**(" << this->name << ") recovered "
        << potions_to_buy * 5 << " health!**" << endl;
        cout << "**(" << this->name << ") bought " << potions_to_buy
        << " potions(s)!**" << endl;
        this->state = TrainerStates::AT_CENTER;
        return true;
        break;
    }
}

void Trainer::CheatCodeCuzForSomeReasonGym2IsExpensiveAf()
{
    this->PokeDollars = 999999;
    this->health = 999999;
    cout << "Cheated in pokemon xDDDDD set PokeDollar to:" << this->PokeDollars << " and Health to:" << this->health << endl;
}


static double GetRandomAmountOfPokeDollars()
{
    return double(rand() % 3);
}
