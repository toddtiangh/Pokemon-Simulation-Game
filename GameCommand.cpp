#include "GameCommand.h"
#include <iostream>
#include <cmath>

using namespace std;

void DoMoveCommand(Model &model, int trainer_id, Point2D p1)
{
    Trainer* ptr = model.GetTrainerPtr(trainer_id);
    cout << "Moving " << ptr->GetTrainerName() << " to ";
    cout << p1;
    cout << endl;
    ptr->StartMoving(p1);
}

void DoMoveToCenterCommand(Model &model, int trainer_id, int center_id)
{
    Trainer *ptr = model.GetTrainerPtr(trainer_id);
    PokemonCenter *center_ptr = model.GetPokemonCenterPtr(center_id);
    cout << "Moving " << ptr->GetTrainerName() << " to Pokemon Center "
    << center_id << endl;
    ptr->StartMovingToCenter(center_ptr);
}

void DoMoveToGymCommand(Model &model, int trainer_id, int gym_id)
{
    Trainer* ptr = model.GetTrainerPtr(trainer_id);
    PokemonGym* gym_ptr = model.GetPokemonGymPtr(gym_id);
    cout << "Moving " << ptr->GetTrainerName() << " to Pokemon Gym "
    << gym_id << endl;
    ptr->StartMovingToGym(gym_ptr);
}

void DoStopCommand(Model &model, int trainer_id)
{
    Trainer* ptr = model.GetTrainerPtr(trainer_id);
    cout << "Stopping " << ptr->GetTrainerName() << endl;
    ptr->Stop();
}

void DoBattleCommand(Model &model, int trainer_id, unsigned int battles)
{
    Trainer* ptr = model.GetTrainerPtr(trainer_id);
    cout << ptr->GetTrainerName() << " is battling" << endl;
    ptr->StartBattling(battles);
}

void DoRecoverInCenterCommand(Model &model, int trainer_id, unsigned int potions_needed)
{
    Trainer* ptr = model.GetTrainerPtr(trainer_id);
    cout << "Recovering " << ptr->GetTrainerName() << "'s Pokemon's health" << endl;
    ptr->StartRecoveringHealth(potions_needed);
}

void DoAdvanceCommand(Model &model, View& view)
{
    model.ShowStatus();
    int x, y, state;
    for(int i = 1; i <= model.GetNumTrainers(); i++)
    {
        Trainer *ptr = model.GetTrainerPtr(i);
        x = ptr->GetLocation().x;
        y = ptr->GetLocation().y;
        view.Plot(x,y);
        ptr->Update();
        state = static_cast<int>(ptr->GetState());
        for(int j = 1; j < model.GetNumWildPokemon(); j++)
        {
            WildPokemon* wp_ptr = model.GetWildPokemonPtr(j);
            if (fabs(ptr->GetLocation().x - wp_ptr->GetLocation().x) <= fabs(ptr->GetDelta().x) &&
            fabs(ptr->GetLocation().y - wp_ptr->GetLocation().y ) <= fabs(ptr->GetDelta().y) &&
                static_cast<int>(wp_ptr->GetState()) != 2)
            {
                wp_ptr->follow(ptr);
            }
            if(state == 2)
            {
                if(wp_ptr->GetCurrentTrainer() == ptr)
                {
                    model.Update(wp_ptr, ptr);
                }
            }
            view.Plot(wp_ptr->GetLocation().x, wp_ptr->GetLocation().y);
            wp_ptr->Update();
            view.Plot(wp_ptr);
        }
        if((state >= 3 && state < 5) || state >= 7)
        {
            for(int j = 1; j < model.GetNumWildPokemon(); j++)
            {
                WildPokemon* wp_ptr = model.GetWildPokemonPtr(j);
                if(static_cast<int>(wp_ptr->GetState()) == 2)
                    view.Plot(wp_ptr->GetLocation().x, wp_ptr->GetLocation().y);
            }
            view.Plot(ptr->GetLocation().x, ptr->GetLocation().y, state);
        }
        else
        {
            view.Plot(ptr);
        }
        for(int i = 1; i <= model.GetNumCenters(); i++)
        {
            PokemonCenter* ptr = model.GetPokemonCenterPtr(i);
            if(ptr == NULL) continue;
            if(ptr->GetNumTrainers() == 0)
                view.Plot(ptr);
        }
        for(int i = 1; i <= model.GetNumGyms(); i++)
        {
            PokemonGym* ptr = model.GetPokemonGymPtr(i);
            if(ptr == NULL) continue;
            if(ptr->GetNumTrainers() == 0)
                view.Plot(ptr);
        }

        if(state == 2)
        {
            int x = ptr->GetLocation().x;
            int y = ptr->GetLocation().y;
            if(y == 20)
                view.Plot(x,y - 1);
            else view.Plot(x,y);
        }
    }
    model.ShowStatus();
    view.Draw();
}

void DoRunCommand(Model &model, View &view)
{
    model.ShowStatus();
    int time = model.GetTime();
    int x, y, state;
    for(int i = 1; i <= model.GetNumTrainers(); i++)
    {
        Trainer *ptr = model.GetTrainerPtr(i);
        x = ptr->GetLocation().x;
        y = ptr->GetLocation().y;
        view.Plot(x,y);
    }

    while(!model.Update() && model.GetTime() < time + 50)
        model.ShowStatus();

    for(int i = 1; i <= model.GetNumTrainers(); i++)
    {
        Trainer *ptr = model.GetTrainerPtr(i);
        state = static_cast<int>(ptr->GetState());
        x = ptr->GetLocation().x;
        y = ptr->GetLocation().y;
        for(int j = 1; j < model.GetNumWildPokemon(); j++)
        {
            WildPokemon* wp_ptr = model.GetWildPokemonPtr(j);
            if (fabs(ptr->GetLocation().x - wp_ptr->GetLocation().x) <= fabs(ptr->GetDelta().x) &&
            fabs(ptr->GetLocation().y - wp_ptr->GetLocation().y ) <= fabs(ptr->GetDelta().y) &&
                static_cast<int>(wp_ptr->GetState()) != 2)
            {
                wp_ptr->follow(ptr);
            }
            if(state == 2)
            {
                if(wp_ptr->GetCurrentTrainer() == ptr)
                {
                    model.Update(wp_ptr, ptr);
                }
            }
            view.Plot(wp_ptr->GetLocation().x, wp_ptr->GetLocation().y);
            wp_ptr->Update();
            view.Plot(wp_ptr);
        }
        if((state >= 3 && state < 5) || state >= 7)
        {
            for(int i = 1; i <= model.GetNumCenters(); i++)
            {
                PokemonCenter* ptr = model.GetPokemonCenterPtr(i);
                if(ptr->GetNumTrainers() == 0)
                    view.Plot(ptr);
            }
            for(int i = 1; i <= model.GetNumGyms(); i++)
            {
                PokemonGym* ptr = model.GetPokemonGymPtr(i);
                if(ptr->GetNumTrainers() == 0)
                    view.Plot(ptr);
            }
            view.Plot(ptr->GetLocation().x,ptr->GetLocation().y , state);
            ptr->ShowStatus();
        }
        else
        {
            view.Plot(ptr);
        }
        for(int i = 1; i <= model.GetNumCenters(); i++)
        {
            PokemonCenter* ptr = model.GetPokemonCenterPtr(i);
            if(ptr->GetNumTrainers() == 0)
                view.Plot(ptr);
        }
        for(int i = 1; i <= model.GetNumGyms(); i++)
        {
            PokemonGym* ptr = model.GetPokemonGymPtr(i);
            if(ptr->GetNumTrainers() == 0)
                view.Plot(ptr);
        }
        if(state == 2)
        {
            int x = ptr->GetLocation().x;
            int y = ptr->GetLocation().y;
            if(y == 20)
                view.Plot(x,y - 1);
            else view.Plot(x,y);
        }
    }
    model.ShowStatus();
    view.Draw();
}
