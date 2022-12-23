#include <iostream>
#include "Point2D.h"
#include "GameObject.h"

using namespace std;

GameObject::GameObject(char in_code)
{
    display_code = in_code;
    id_num = 1;
    state = '0';
    cout << "GameObject constructed" << endl;
}
GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    state = '0';
    cout << "GameObject constructed" << endl;
}

GameObject::~GameObject()
{

}
Point2D GameObject::GetLocation()
{
    return this->location;
}

int GameObject::GetId()
{
    return this->id_num;
}

char GameObject::GetState()
{
    return this->state;
}

void GameObject::ShowStatus()
{
    cout << "Display_code:" << this->display_code << " Id_num:" << this->GetId() << " at:" << this->GetLocation();
    cout << endl;
}

void GameObject::DrawSelf(char** ptr)
{
    *ptr = &this->display_code;
}




