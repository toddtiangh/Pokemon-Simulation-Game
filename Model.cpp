#include "Model.h"
#include "WildPokemon.h"
#include "Trainer.h"


Model::Model()
{
    time = 0;
    Trainer* ash_ptr = new Trainer(Point2D(5,1), "Ash", 1, 'T', 1);
    GameObject* obj_ptr1 = ash_ptr;
    Trainer* misty_ptr = new Trainer(Point2D(10,1), "Misty,", 2, 'T', 2);
    GameObject* obj_ptr2 = misty_ptr;

    PokemonCenter* C1_ptr = new PokemonCenter(Point2D(1,20), 1, 1, 100);
    GameObject* obj_ptr3 = C1_ptr;
    PokemonCenter* C2_ptr = new PokemonCenter(Point2D(10,20), 2, 2, 200);
    GameObject* obj_ptr4 = C2_ptr;

    PokemonGym* G1_ptr = new PokemonGym(Point2D(0,0), 1, 10, 1, 2, 3);
    GameObject* obj_ptr5 = G1_ptr;
    PokemonGym* G2_ptr = new PokemonGym(Point2D(5,5), 2, 20, 5, 7.5, 4);
    GameObject* obj_ptr6 = G2_ptr;

    WildPokemon* WP1_ptr = new WildPokemon(Point2D(10,12), 1, "Charmander", false, 5, 2);
    GameObject* obj_ptr7 = WP1_ptr;
    WildPokemon* WP2_ptr = new WildPokemon(Point2D(15,15), 2, "Squirtle", false, 5, 2);
    GameObject* obj_ptr8 = WP2_ptr;

    trainer_ptrs.push_back(ash_ptr);
    object_ptrs.push_back(obj_ptr1);
    trainer_ptrs.push_back(misty_ptr);
    object_ptrs.push_back(obj_ptr2);

    center_ptrs.push_back(C1_ptr);
    object_ptrs.push_back(obj_ptr3);
    center_ptrs.push_back(C2_ptr);
    object_ptrs.push_back(obj_ptr4);

    gym_ptrs.push_back(G1_ptr);
    object_ptrs.push_back(obj_ptr5);
    gym_ptrs.push_back(G2_ptr);
    object_ptrs.push_back(obj_ptr6);

    wildpokemon_ptrs.push_back(WP1_ptr);
    object_ptrs.push_back(obj_ptr7);
    wildpokemon_ptrs.push_back(WP2_ptr);
    object_ptrs.push_back(obj_ptr8);

    for(int i = 0; i < object_ptrs.size(); i++)
        active_ptrs.push_back(object_ptrs[i]);

    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    for(int i = 0; i < object_ptrs.size(); i++)
    {
        delete object_ptrs[i];
    }
    cout << "Model destructed" << endl;
}

bool Model::CheckCompletion()
{
    int j = 0;
    for(int i = 0; i < gym_ptrs.size(); i++)
    {
        if(gym_ptrs[i]->GetNumBattlesRemaining() == 0)
            j++;
        else
            continue;
    }
    if(j == gym_ptrs.size())
    {
        cout << "GAMECOMPLETED" << endl;
        return true;
    }
    else
        return false;
}

bool Model::CheckLoss()
{
    int j = 0;
    for(int i = 0; i < trainer_ptrs.size(); i++)
    {
        if(static_cast<int>(trainer_ptrs[i]->GetState()) == 2)
            j++;
        else
            continue;
    }
    if(j == trainer_ptrs.size())
    {
        cout << "GAMELOST" << endl;
        return true;
    }
    else
        return false;
}
Trainer* Model::GetTrainerPtr(int id)
{
    for(int i = 0; i < object_ptrs.size(); i++)
    {
        if(trainer_ptrs[i]->GetId() == id)
        {
            return trainer_ptrs[i];
        }
    }
    return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
    for(int i = 0; i < center_ptrs.size(); i++)
    {
        if(center_ptrs[i]->GetId() == id)
        {
            return center_ptrs[i];
        }
    }
    return NULL;
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
    for(int i = 0; i < gym_ptrs.size(); i++)
    {
        if(gym_ptrs[i]->GetId() == id)
        {
            return gym_ptrs[i];
        }
    }
    return NULL;
}

WildPokemon* Model::GetWildPokemonPtr(int id)
{
    for(int i = 0; i < wildpokemon_ptrs.size(); i++)
    {
        if(wildpokemon_ptrs[i]->GetId() == id)
        {
            return wildpokemon_ptrs[i];
        }
    }
    return NULL;
}

bool Model::Update()
{
    time++;
    for(int i = 0; i < object_ptrs.size(); i++)
    {
        GameObject* curr_ptr = object_ptrs[i];
        if(curr_ptr->Update())
        {
            return true;
            break;
        }
    }
    return false;
}

void Model::Update(WildPokemon* wp_ptr, Trainer* ptr)
{
    for(int i = 0; i < this->GetNumWildPokemon(); i++)
    {
        if(object_ptrs[i] == wp_ptr) delete this->object_ptrs[i];
        if(object_ptrs[i] == ptr) delete this->object_ptrs[i];
    }
}
void Model::ShowStatus()
{
    for(int i = 0; i < object_ptrs.size(); i++)
    {
        GameObject* curr_ptr = object_ptrs[i];
        curr_ptr->ShowStatus();
    }
}

int Model::GetNumTrainers()
{
    return trainer_ptrs.size();
}

int Model::GetNumWildPokemon()
{
    return wildpokemon_ptrs.size();
}

int Model::GetNumGyms()
{
    return gym_ptrs.size();
}

int Model::GetNumCenters()
{
    return center_ptrs.size();
}

void Model::incrementTime()
{
    this->time++;
}

int Model::GetTime()
{
    return this->time;
}

void Model::CreateGym(Point2D in_loc, int in_id, View& view)
{
    bool Invalid_ID = false;
    for(int i = 0; i < gym_ptrs.size(); i++)
    {
        PokemonGym* temp = gym_ptrs[i];
        if(temp->GetId() == in_id) Invalid_ID = true;
    }
    if(in_id > 9) cout << "Choose ID # that is less than 10" << endl;
    else if(!Invalid_ID)
    {
        unsigned int max_battle, health_loss, exp_per_battle;
        double PokeDollar_cost;
        cout << "Please enter desired amount of battles, health loss, cost of battles, and exp per battle: ";
        cin >> max_battle >> health_loss >> PokeDollar_cost >> exp_per_battle;
        PokemonGym* g_ptr = new PokemonGym(in_loc, in_id, max_battle, health_loss, PokeDollar_cost, exp_per_battle);
        gym_ptrs.push_back(g_ptr);
        view.Plot(g_ptr);
        view.Draw();
    }
    else cout << "ID already exists" << endl;
}

void Model::CreateCenter(Point2D in_loc, int in_id, View& view)
{
    bool Invalid_ID = false;
    for(int i = 0; i < center_ptrs.size(); i++)
    {
        PokemonCenter* temp = center_ptrs[i];
        if(temp->GetId() == in_id) Invalid_ID = true;
    }
    if(in_id > 9) cout << "Choose ID # that is less than 10" << endl;
    else if(!Invalid_ID)
    {
        double potion_cost;
        unsigned int potion_cap;
        cout << "Please enter potion cost, and potion cap: ";
        cin >> potion_cost >> potion_cap;
        PokemonCenter* c_ptr = new PokemonCenter(in_loc, in_id, potion_cost, potion_cap);
        center_ptrs.push_back(c_ptr);
        view.Plot(c_ptr);
        view.Draw();
    }
    else cout << "ID already exists" << endl;
}

void Model::CreateTrainer(Point2D in_loc, int in_id, View& view)
{
    bool Invalid_ID = false;
    for(int i = 0; i < trainer_ptrs.size(); i++)
    {
        Trainer* temp = trainer_ptrs[i];
        if(temp->GetId() == in_id) Invalid_ID = true;
    }
    if(in_id > 9) cout << "Choose ID # that is less than 10" << endl;
    else if(!Invalid_ID)
    {
        string in_name;
        int in_id;
        char in_code;
        unsigned int in_speed;
        cout << "Please enter the name, and speed of your trainer";
        cin >> in_name >> in_speed;
        Trainer* t_ptr = new Trainer(in_loc, in_name, in_id, 'T', in_speed);
        trainer_ptrs.push_back(t_ptr);
        view.Plot(t_ptr);
        view.Draw();
    }
    else cout << "ID already exists" << endl;
}

void Model::CreatePokemon(Point2D in_loc, int in_id, View& view)
{
    bool Invalid_ID = false;
    for(int i = 0; i < wildpokemon_ptrs.size(); i++)
    {
        WildPokemon* temp = wildpokemon_ptrs[i];
        if(temp->GetId() == in_id) Invalid_ID = true;
    }
    if(in_id > 9) cout << "Choose ID # that is less than 10" << endl;
    else if(!Invalid_ID)
    {
        string in_name;
        double in_attack, in_health;
        cout << "Please enter the name, attack, and health of your pokemon";
        cin >> in_name >> in_attack >> in_health;
        WildPokemon* w_ptr = new WildPokemon(in_loc, in_id, in_name, false, in_attack, in_health);
        wildpokemon_ptrs.push_back(w_ptr);
        view.Plot(w_ptr);
        view.Draw();
    }
    else cout << "ID already exists" << endl;
}
