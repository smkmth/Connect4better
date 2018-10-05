#include "pch.h"
#include "CBoard.h"
#include "CBoard.h"
#include <iostream>
#include <Windows.h>"


using namespace std;



CBoard::CBoard()
{
	void InitBoard();
	HANDLE g_hwndConsole = NULL;
	g_hwndConsole = GetStdHandle(STD_OUTPUT_HANDLE);

}


CBoard::~CBoard()
{

}


//getters
int CBoard::GetBoardHeight() { return k_iBoardHeight; }
int CBoard::GetBoardWidth() { return k_iBoardWidth; }



void CBoard::InitBoard()
{

	system("cls");

	const char	k_chSeparatorVertical = '|';
	const char	k_chSeparatorHorizontal = '-';
	const char	k_chSeparatorJoin = '+';



	for (int iColumnNumber = 0; iColumnNumber < k_iBoardWidth; ++iColumnNumber)
	{
		cout << " " << (iColumnNumber + 1);
	}
	cout << endl;


	for (int iRow = 0; iRow < k_iBoardHeight; ++iRow)
	{

		SetConsoleTextAttribute(g_hwndConsole, k_ai8BoardElementColours[k_iBoardSlot_Frame]);

		cout << k_chSeparatorJoin;

		// we print 2 chars per column
		for (int iSeparator = 0; iSeparator < k_iBoardWidth; ++iSeparator)
		{
			cout << k_chSeparatorHorizontal << k_chSeparatorJoin;
		}
		cout << endl;


		cout << k_chSeparatorVertical;

		// again, 2 chars per column
		for (int iColumn = 0; iColumn < k_iBoardWidth; ++iColumn)
		{
			// cache board element index
			char i8BoardElementIndex = g_aaiBoard[iColumn][iRow];

			// render board element in appropriate colour
			SetConsoleTextAttribute(g_hwndConsole, k_ai8BoardElementColours[i8BoardElementIndex]);
			cout << k_achBoardPieces[i8BoardElementIndex];

			// render frame in frame colour
			SetConsoleTextAttribute(g_hwndConsole, k_ai8BoardElementColours[k_iBoardSlot_Frame]);
			cout << k_chSeparatorVertical;
		}
		cout << endl;
	}

	// final row at bottom of board
	SetConsoleTextAttribute(g_hwndConsole, k_ai8BoardElementColours[k_iBoardSlot_Frame]);
	cout << k_chSeparatorJoin;
	// we print 2 chars per column
	for (int iSeparator = 0; iSeparator < k_iBoardWidth; ++iSeparator)
	{
		cout << k_chSeparatorHorizontal << k_chSeparatorJoin;
	}
	cout << endl;

	// render column numbers again
	SetConsoleTextAttribute(g_hwndConsole, k_ai8BoardElementColours[k_iBoardSlot_Empty]);
	for (int iColumnNumber = 0; iColumnNumber < k_iBoardWidth; ++iColumnNumber)
	{
		cout << " " << (iColumnNumber + 1);
	}
	cout << endl;


}


void CBoard::UpdateGame(int iArgColumn)
{
	// find the 'lowest' available position in iArgColumn
	// N.B. 0,0 is top left of board, so 'lowest' row is highest index
	int iLowestEmptyRow = 0;
	for (int iRowToCheck = 0; iRowToCheck < k_iBoardHeight; ++iRowToCheck)
	{
		if (k_iBoardSlot_Empty == g_aaiBoard[iArgColumn][iRowToCheck])
		{
			iLowestEmptyRow = iRowToCheck;
		}
		else
		{
			break;
		}
	}

	// insert current player's piece there
	// N.B. g_iActivePlayer is always either k_iBoardSlot_Player1 or k_iBoardSlot_Player2
	g_aaiBoard[iArgColumn][iLowestEmptyRow] = g_iActivePlayer;

	// if this finds a winning row it sets g_iGameState and g_aaiWinningRow
	Update_CheckForWin();
}


void CBoard::Update_CheckForWin()
{

	if (Update_CheckRowsAndCols())
	{
		g_iGameState = g_iActivePlayer;
	}
}


bool CBoard::Update_CheckRowsAndCols()
{

	{
		
		int iMaxRowToCheck = (k_iBoardHeight - (k_iWinLineLength - 1));

		for (int iColumn = 0; iColumn < k_iBoardWidth; ++iColumn)
		{
			for (int iRow = 0; iRow < iMaxRowToCheck; ++iRow)
			{
				
				if (g_aaiBoard[iColumn][iRow] == g_iActivePlayer)
				{
					g_aaiWinningRow[0][0] = iColumn;
					g_aaiWinningRow[0][1] = iRow;

					int iLinePosIndex = (k_iWinLineLength - 1);

					for (; iLinePosIndex > 0; --iLinePosIndex)
					{
						int iCheckRow = iRow + iLinePosIndex;

						if (g_aaiBoard[iColumn][iCheckRow] == g_iActivePlayer)
						{
							g_aaiWinningRow[iLinePosIndex][0] = iColumn;
							g_aaiWinningRow[iLinePosIndex][1] = iCheckRow;
						}
						else
						{
							break;
						}
					}

					if (0 == iLinePosIndex)
					{
						return true;
					}
				}
			}
		}

		return false;
	}

}




