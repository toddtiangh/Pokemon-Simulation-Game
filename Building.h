#ifndef Building_h
#define Building_h
#include "GameObject.h"
class Building : public GameObject
{
private:
    unsigned int trainer_count;
public:
    Building();

    Building(Point2D in_loc, int in_id, char in_code);

    void AddOneTrainer();

    void RemoveOneTrainer();

    int GetNumTrainers();

    void ShowStatus();

    bool ShouldBeVisible();
};

#endif /* Building.h */
