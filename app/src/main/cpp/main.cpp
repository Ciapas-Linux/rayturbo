
#include "pthread.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdatomic.h>
#include <time.h>
#include "Game.h"

int main()
{
    Game* gm = new Game();
    gm->Show();
    gm->Run();

    delete gm;

return 0;
}

