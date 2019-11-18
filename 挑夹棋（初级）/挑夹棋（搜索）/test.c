struct Command findValidPos(char board[BOARD_SIZE][BOARD_SIZE], int cur_flag) 
{
	for (int k = 0; k < 8; k++) {
		const int* delta = DIR[k];
		for (int x = 0; x < BOARD_SIZE; x++) 
		{
			for (int y = 0; y < BOARD_SIZE; y++) 
			{
				if (board[x][y] != cur_flag) 
				{
					continue;
				}
				int new_x = x + delta[0];
				int new_y = y + delta[1];
				if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY) 
				{
					board[x][y] = EMPTY;
					board[new_x][new_y] = cur_flag;
				}
			}
		}
	}
}


/*
*Ìô¼ÐÎ»ÅÐ¶Ï
*/


/*
*¼ÐÎ»
*/

for (int i = 0; i < 12; i++)
{
	for (int j = 0; j < 12; j++)
	{
		if (board[i][j] == me_flag)
		{
			for (int k = 0; k < 8; k++)
			{
				if (board[i + DIR[k][0]][j + DIR[k][1]] == other_flag)
				{
					for (int a = 0; a < 8; a++)
					{
						if (board[i + 2 * DIR[k][0] + DIR[a][0]][j + 2 * DIR[k][1] + DIR[a][1]] == Me_flag)
							value = value + 5;
					}
					if (board[i - 1][j - 1] == other_flag && board[i - 1][j + 1] == other_flag)
						value = value + 5;
					if (board[i - 1][j - 1] == other_flag && board[i + 1][j - 1] == other_flag)
						value = value + 5;
					if (board[i + 1][j - 1] == other_flag && board[i + 1][j + 1] == other_flag)
						value = value + 5;
					if (board[i - 1][j + 1] == other_flag && board[i + 1][j + 1] == other_flag)
						value = value + 5;
				}
			}
		}
	}
}


/*
*ÌôÎ»
*/
for (int i = 0; i < 12; i++)
{
	for (int j = 0; j < 12; j++)
	{
		if (board[i][j] == me_flag)
		{
			if (board[i - 1][j - 1] == other_flag && board[i - 1][j + 1] == other_flag && board[i - 1][j] == EMPTY)
				value = value + 3;
			if (board[i - 1][j - 1] == other_flag && board[i + 1][j - 1] == other_flag && board[i][j - 1] == EMPTY)
				value = value + 3;
			if (board[i + 1][j - 1] == other_flag && board[i + 1][j + 1] == other_flag && board[i + 1][j] == EMPTY)
				value = value + 3;
			if (board[i - 1][j + 1] == other_flag && board[i + 1][j + 1] == other_flag && board[i][j + 1] == EMPTY)
				value = value + 3;
		}
	}
}





/*
*Ìø³öÑ­»·
*/

