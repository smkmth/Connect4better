#pragma once
#include <Windows.h>"


class CBoard
{
private:
	static const int k_iBoardWidth = 7;
	static const int k_iBoardHeight = 6;
	static const int k_iWinLineLength = 4;


	int g_aaiBoard[k_iBoardWidth][k_iBoardHeight];

	int g_aaiWinningRow[k_iWinLineLength][2];

	int g_iActivePlayer;

	HANDLE g_hwndConsole;


	const enum BoardState {
		k_iBoardSlot_Empty,
		k_iBoardSlot_Player1,
		k_iBoardSlot_Player2,
		k_iBoardSlot_Frame
	};

	const enum WinState {
		k_iState_Playing,
		k_iState_Won_Player1,
		k_iState_Won_Player2,
		k_iState_Draw,
	};

	const char k_ai8BoardElementColours[4] =
	{
		7,	// white on black
		12,	// red on black
		14,	// yellow on black
		9,	// blue on black
	};

	const char k_achBoardPieces[4] =
	{
		' ', // no piece - g_achBoardPieces[ k_iBoardSlot_Empty ]
		'@', // player 1 - g_achBoardPieces[ k_iBoardSlot_Player1 ]
		'O', // player 2 - g_achBoardPieces[ k_iBoardSlot_Player2 ]
		'!', // not used, but provided since k_iBoardSlot_Frame exists
	};

	int g_iGameState = k_iState_Playing;


public:
	CBoard();

	~CBoard();



	void InitBoard();
	void UpdateGame(int);
	void Update_CheckForWin();
	

	int GetBoardWidth();
	int GetBoardHeight();

	bool Update_CheckRowsAndCols();

};

