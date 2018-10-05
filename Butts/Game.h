#pragma once
#include "CBoard.h"
class Game
{
public:

	Game();
	~Game();

	CBoard* GetCurrentBoard();
	bool ConfirmQuitGame();

private:

	CBoard PlayBoard;
	CBoard* CurrentBoard;



};







