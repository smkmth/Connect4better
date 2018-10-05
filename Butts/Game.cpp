#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game()
{
	CBoard PlayBoard;
	PlayBoard.InitBoard();
	CBoard* CurrentBoard;
	CurrentBoard = &PlayBoard;

}


Game::~Game()
{
}

CBoard * Game::GetCurrentBoard()
{

	if (CurrentBoard != nullptr)
	{
		return CurrentBoard;
	}
}

bool Game::ConfirmQuitGame() {

	system("cls");
	std::cout << "######################################\n"
		<< "### are you sure you want to quit? ###\n"
		<< "######################################\n"
		<< "'y' followed by return to confirm, any other input will cancel.\n";

	// get 1st input char and flush the input buffer to prevent unwanted immediate returns from cin.get() later
	std::cin.clear();
	char chInput = std::cin.get();
	std::cin.sync();

	return (('y' == chInput) || ('Y' == chInput)) ? true : false;
}

