int Count_Stone(char board[12][12])
{
	int value = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (board[i][j] == me_flag)
			{
				for (int k = 0; k < 8; k++)
				{
					if(board[i+dir[k][0]][j+dir[k][1]]==me_flag)
				}
			}
		}
	}
	return value;
}


int dir[8][2]={ {1,-3}, {3, -1}, {3, 1}, {1, 3}, {-1, 3}, {-3,1}, {-3, -1}, {-1, -3} }