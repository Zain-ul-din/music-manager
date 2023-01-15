#include "App.h"

#pragma comment(lib, "Winmm.lib")

// driver code
int main()
{
    App* app = new App();
    app->start_app();
    delete app;
	return 0;
}


