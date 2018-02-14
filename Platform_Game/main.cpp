#include "Game.h"
#include <memory>

int main()
{
	Game game;
	while (!game.GetWindow()->IsExit())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}
	system("pause");
	return 0;
}
