#ifndef Model_h
#define Model_h
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "WildPokemon.h"
#include <vector>
#include <typeinfo>
#include "View.h"

class Model
{
private:
    int time = 0;
    vector<GameObject*> object_ptrs;
    vector<Trainer*> trainer_ptrs;
    vector<PokemonCenter*> center_ptrs;
    vector<PokemonGym*> gym_ptrs;
    vector<WildPokemon*> wildpokemon_ptrs;
    vector<GameObject*> active_ptrs;
public:
    Model();

    ~Model();

    bool CheckCompletion();

    bool CheckLoss();

    Trainer* GetTrainerPtr(int id);

    PokemonCenter* GetPokemonCenterPtr(int id);

    PokemonGym* GetPokemonGymPtr(int id);

    WildPokemon* GetWildPokemonPtr(int id);

    bool Update();

    void ShowStatus();

    int GetNumTrainers();

    int GetNumWildPokemon();

    int GetNumCenters();

    int GetNumGyms();

    void Update(WildPokemon* wp_ptr, Trainer* ptr);

    void incrementTime();

    int GetTime();

    void CreateCenter(Point2D in_loc, int in_id, View& view);

    void CreateGym(Point2D in_loc, int in_id, View& view);

    void CreatePokemon(Point2D in_loc, int in_id, View& view);

    void CreateTrainer(Point2D in_loc, int in_id, View& view);

};

#endif /* Model_h */
