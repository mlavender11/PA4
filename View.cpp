#include "View.h"
using namespace std;

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
    out_x = (int)((location.x - origin.x) / scale);
    out_y = (int)((location.y - origin.y) / scale);

    if (out_x < 0 || out_x >= size || out_y < 0 || out_y >= size)
    {
        cout << "An object is outside the display" << endl;
        return false;
    }

    return true;
}

View::View()
    : size(11), scale(2)
{
}

void View::Clear()
{
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            grid[y][x][0] = '.';
            grid[y][x][1] = ' ';
        }
    }
}

void View::Plot(GameObject *ptr)
{
    int x, y;
    
    if(!GetSubscripts(x, y, ptr->GetLocation())) return;

    if (grid[y][x][0] != '.')
    {
        grid[y][x][0] = '*';
        grid[y][x][1] = ' ';
    }
    else
    {
        ptr->DrawSelf(grid[y][x]);
    }
}

void View::Draw() {
    cout << "size: " << size << " scale: " << scale << " origin: " << origin << endl;
    for (int y = size - 1; y >= 0; y--) {
        if (y % 2 == 0)
            cout << setw(2) << (int)(origin.y + y * scale);
        else
            cout << "  ";
        for (int x = 0; x < size; x++)
            cout << grid[y][x][0] << grid[y][x][1];
        cout << endl;
    }
    cout << "  ";
    for (int x = 0; x < size; x += 2)
        cout << setw(2) << (int)(origin.x + x * scale) << "  "; // skip odd columns
    cout << endl;
}

int View::GetMaxSize() const
{
    return view_maxsize;
}