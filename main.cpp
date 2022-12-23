#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include "Model.h"
#include "GameCommand.h"
#include "WildPokemon.h"
#include "Input_Handling.h"

using namespace std;
//unsigned int GetInt()
//
//char GetChar()
//
//double GetDouble()
int main()
{
    char ch, type;
    double x, y;
    unsigned int battle_amount, potion_amount;
    int id1, id2;
    Model* m1 = new Model;
    View* view = new View;
    m1->ShowStatus();

    Trainer* t1 = m1->GetTrainerPtr(1);
    Trainer * t2 = m1->GetTrainerPtr(2);
    PokemonCenter* c1 = m1->GetPokemonCenterPtr(1);
    PokemonCenter* c2 = m1->GetPokemonCenterPtr(2);
    PokemonGym* g1 = m1->GetPokemonGymPtr(1);
    PokemonGym* g2 = m1->GetPokemonGymPtr(2);
    WildPokemon* wp1 = m1->GetWildPokemonPtr(1);
    WildPokemon* wp2 = m1->GetWildPokemonPtr(2);
    view->Clear();
    view->Plot(t1);
    view->Plot(t2);
    view->Plot(c1);
    view->Plot(c2);
    view->Plot(g1);
    view->Plot(g2);
    view->Plot(wp1);
    view->Plot(wp2);
    view->Draw();

    while(!m1->CheckCompletion() && !m1->CheckLoss())
    {
        cout << "Input Commands" << endl;
        cin >> ch;
        try{
            switch(ch)
            {
            case 'm':
                if(cin >> id1 >> x >> y) DoMoveCommand(*m1,id1,Point2D(x,y));
                else throw Invalid_Input("Invalid Input");
                break;
            case 'c':
                if(cin >> id1 >> id2) DoMoveToCenterCommand(*m1, id1, id2);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'g':
                if(cin >> id1 >> id2) DoMoveToGymCommand(*m1, id1, id2);
                else throw Invalid_Input("Invalid Input");
                break;
            case 's':
                if(cin >> id1) DoStopCommand(*m1, id1);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'b':
                if(cin >> id1 >> battle_amount) DoBattleCommand(*m1, id1, battle_amount);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'p':
                if(cin >> id1 >> potion_amount) DoRecoverInCenterCommand(*m1, id1, potion_amount);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'a':
                if(ch == 'a') DoAdvanceCommand(*m1, *view);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'r':
                if(ch == 'r');
                else throw Invalid_Input("Invalid Input");
                DoRunCommand(*m1, *view);
                break;
            case 'q':
                if(ch == 'q') exit(0);
                else throw Invalid_Input("Invalid Input");
                break;
            case 'n':
                if(cin >> type >> id1 >> x >> y);
                else throw Invalid_Input("Invalid Input");
                if(type == 'c') m1->CreateCenter(Point2D(x,y), id1, *view);
                else if (type == 'g') m1->CreateGym(Point2D(x,y), id1, *view);
                else if (type == 't') m1->CreateTrainer(Point2D(x,y), id1, *view);
                else if (type == 'w') m1->CreatePokemon(Point2D(x,y), id1, *view);
                break;
            default:
                throw Invalid_Input("Invalid Input");
            }
        }   catch (Invalid_Input& except)
            {
                cout << "Invalid Input - " << except.msg_ptr << endl;
                break;
            }
    }
    return 0;
}

