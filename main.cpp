#include "Model.h"
#include "View.h"
#include "GameCommand.h"
using namespace std;

int main()
{
    Model model;
    View view;

    model.ShowStatus();
    model.Display(view);


    while (true)
    {
        getInput(model, view);
    }

    return 0;
}
