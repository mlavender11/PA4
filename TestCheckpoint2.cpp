#include "DemonHideout.h"
#include "ManaSpire.h"
using namespace std;

int main() {
    Point2D loc = Point2D(0, 10);

    // Building b1;
    // Building b2 = Building('f', 20, loc);
    // b1.ShowStatus();
    // cout << endl;
    // b2.ShowStatus();
    // b2.AddOneMage();
    // b2.ShowStatus();
    // b2.AddOneMage();
    // b2.ShowStatus();
    // b2.RemoveOneMage();
    // b2.ShowStatus();
    // b2.RemoveOneMage();
    // b2.ShowStatus();
    // b2.RemoveOneMage();
    // b2.ShowStatus();
    // cout << b1.ShouldBeVisible() << endl;
    
    // ManaSpire m1;
    // ManaSpire m2(30, 10000, 540, loc);
    // m1.ShowStatus();
    // m2.ShowStatus();
    // cout << m2.HasCrystals() << endl;
    // cout << m2.GetNumCrystalsRemaining() << endl;
    // cout << m1.CanAffordCrystal(2, 30) << endl;
    // cout << m1.GetCrystalCost(3) << endl;

    // ManaSpire m1(1, 100, 10, loc);
    // m1.ShowStatus();

    // // cout << m1.GetCrystalCost(10) << endl;
    // // cout << m1.CanAffordCrystal(10, 1001) << endl;
    // m1.AddOneMage();
    // cout << m1.DistributeCrystals(10) << endl;
    // m1.ShowStatus();
    // m1.Update();
    // m1.ShowStatus();


    DemonHideout d1;
    DemonHideout d2(15, 4, 2, 10, 3, loc);
    // cout << endl;
    // d1.ShowStatus();
    cout << endl;
    d2.ShowStatus();

    cout << endl;
    // cout << d1.GetGoldCost(2) << " " << d2.GetGoldCost(2) << endl;
    // cout << d1.GetManaCost(2) << " " << d2.GetManaCost(2) << endl;
    // cout << d1.GetNumBattlesRemaining() << " " << d2.GetNumBattlesRemaining() << endl;
    // cout << d1.GetExperiencePerBattle() << " " << d2.GetExperiencePerBattle() << endl;

    // cout << d2.IsAbleToBattle(3, 7, 11) << endl;
    cout << d2.DemonBattle(3) << endl;
    cout << d2.passed() << endl;
    d2.ShowStatus();
    cout << d2.Update() << endl;
    d2.ShowStatus();
    cout << d2.Update() << endl;
}