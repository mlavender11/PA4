#ifndef BUILDING_H
#define BUILDING_H
#include "Point2D.h"
#include "GameObject.h"
class Building : public GameObject
{
private:
    unsigned int mage_count;

public:
    Building();
    Building(char in_code, int in_Id, Point2D in_loc);

    void AddOneMage();
    void RemoveOneMage();
    void ShowStatus() const override;
    bool ShouldBeVisible() const override;

    void save(ofstream& file) const override;
    void restore(ifstream& file, Model& model) const override;
};

#endif