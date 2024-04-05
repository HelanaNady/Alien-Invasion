#include "Game.h"

int main()
{
	srand(time(NULL));

	Game gameObj;
	gameObj.run(INTERACTIVE, "testRandGen.txt");
	gameObj.print();

    return 0;
}