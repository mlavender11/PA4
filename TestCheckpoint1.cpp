#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
using namespace std;

int main()
{
    Point2D p1;
    Point2D p2(5, 4);

    cout << p1 << " " << p2 << endl;
    double dist = Point2D::GetDistanceBetweenPoints(p1, p2);
    cout << dist << endl;

    Vector2D diff = p2 - p1;
    cout << diff << endl;

    Point2D p3 = p2 + diff;
    cout << p3 << endl;

    Vector2D v1;
    Vector2D v2(3, 4);
    Vector2D v3(9, 8);

    cout << v1 << v2 << v3 << endl;
    Vector2D v1n = v1 / 2;
    Vector2D v2n = v2 * 8;
    cout << v1n << v2n << endl;

    GameObject g1('a');
    GameObject g2(p2, 2, 'b');

    cout << g1.GetLocation() << endl;
    cout << g2.GetLocation() << endl;

    cout << g1.GetId() << endl;
    cout << g2.GetId() << endl;

    cout << g1.GetState() << endl;
    cout << g2.GetState() << endl;

    g1.ShowStatus();
    g2.ShowStatus();
}