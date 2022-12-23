#include <iostream>
#include "Building.h"
#include "GameObject.h"

using namespace std;

Building::Building() : GameObject('B')
{
    trainer_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(Point2D in_loc, int in_id, char in_code) : GameObject(in_loc, in_id, in_code)
{
    trainer_count = 0;
    cout << "Building constructed" << endl;
}

void Building::AddOneTrainer()
{
    ++trainer_count;
}

void Building::RemoveOneTrainer()
{
    if(trainer_count == 0)
        trainer_count = 0;
    else
        --trainer_count;
}

int Building::GetNumTrainers()
{
    return this->trainer_count;
}

void Building::ShowStatus()
{
    cout << "Display Code:" << this->display_code
    << "  ID:" << this->id_num << "  Located At:" << this->GetLocation();
    cout << endl;
    if(this->trainer_count > 1)
        cout << this->trainer_count << " Trainers are in this building" << endl;
    else
        cout << this->trainer_count << " Trainers is in this building" << endl;
}

bool Building::ShouldBeVisible()
{
    return true;
}


