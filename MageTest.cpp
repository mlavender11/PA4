#include "Mage.h"
using namespace std;

int main()
{
    Mage m1 = Mage();
    m1.ShowStatus();

    ManaSpire *s1 = new ManaSpire(1, 0.1, 1, Point2D(5, 5));
    s1->ShowStatus();

   
    
    // for (int i = 0; i < 11; i++) {
    //    // cout << " " << i << " ";
    //     if (i%2 == 0) {
    //         cout << "10" << endl;
    //         m1.StartMoving(Point2D(10,10));
    //         }
    //     else {
    //         cout << 0 << endl;
    //         m1.StartMoving(Point2D(0,0));
    //     }
    //     for (int j = 0; j < 2; j++)
    //     {
    //        // cout << j << " ";
    //         m1.Update();
    //     }
    //     cout << endl;
    // }

    m1.StartMovingToSpire(s1);
    m1.ShowStatus();
    m1.Update();
    cout << m1.GetLocation();
    m1.Update();
    cout << m1.GetLocation();
    m1.ShowStatus();

    // cout << endl << "*" << endl << endl;
    // m1.StartRecoveringMana(2);
    // m1.ShowStatus();
    // s1->ShowStatus();
    // cout << endl << "*" << endl << endl;
    // m1.Update();
    // m1.ShowStatus();
}