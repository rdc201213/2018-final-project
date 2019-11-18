/*
*对局面评分
*/
int Board_evaluate(int x,int y,int me)
{
	int value;
	value =2* Count_Stone(me);
	return value;
}
int My_Board[12][12];


/*判断是否被挑吃*/
int IF_Be_Mak(char cur_board[12][12])
{
	int Danger=0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (cur_board[i][j] == me_flag)
			{
				for (int a = 0; a < 8; a++)
				{
					if (cur_board[i + 2 * DIR[a][0]][j + 2 * DIR[a][1]] == me_flag)
					{
						for (int b = 0; b < 8; b++)
						{
							if (cur_board[i + DIR[a][0] + DIR[b][0]][j + DIR[a][1] + DIR[b][1]] == other_flag)
								Danger = Danger - 3;
						}
					}
				}
			}
		}
	}
	return Danger;
}
/*
*判断是否被夹吃
*/
int IF_Be_Yak(char cur_board[12][12])
{
	int Danger = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (cur_board[i][j] == me_flag)
			{
				for (int a = 0; a < 8; a++)
				{
					if (cur_board[i + DIR[a][0]][j + DIR[a][1]] == other_flag)
					{
						for (int b = 0; b < 8; b++)
						{
							if (cur_board[i - DIR[a][0] + DIR[b][0]][j - DIR[a][1] + DIR[b][1]] == other_flag)
								Danger = Danger - 3;
						}
					}
				}
			}
		}
	}
	return Danger;
}




/*
*计算棋子移动的防御价值
*/
int Defence_evaluate(int x, int y, int* delta)
{
	int value;
	value =IF_Danger_After(x, y, delta) + IF_Together(x, y, delta)-IF_Danger_Before(x,y)+IF_Be_Mak(x,y,delta);
	return value;
}
/* 
*判断移动前是否危险
*/
int IF_Danger_Before(int x, int y)
{
	int Safe_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[x + custodian_dir[k][0]][y + custodian_dir[k][1]] == other_flag)
		{
			Safe_value = Safe_value - 2;
		}
	}
	return Safe_value;
}
/*
*判断移动后是否危险
*/
int IF_Danger_After(int x, int y, int* delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Safe_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[new_x + custodian_dir[k][0]][new_y + custodian_dir[k][1]] == other_flag)
		{
			Safe_value = Safe_value - 5;
		}
		if (board[new_x + custodian_dir[k][0]*2][new_y + custodian_dir[k][1]*2] == other_flag)
		{
			Safe_value = Safe_value - 3;
		}
	}
	return Safe_value;
}


/*判断是否被挑吃*/
int IF_Be_Mak(int x, int y, int*delta)
{
	int Danger = 0;
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

	if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY)
	{
		for (int i = 0; i < 8; i++)
		{
			if (board[x + custodian_dir[i][0]][y + custodian_dir[i][1]] == me_flag && board[x - custodian_dir[i][0]][y - custodian_dir[i][0]] == me_flag)
			{
				for (int j = 0; j < 8; j++)
				{
					if(board[x+ custodian_dir[i][0]][y+ custodian_dir[i][1]]==other_flag)
					Danger = Danger - 10;
				}
			}
			if (board[new_x + custodian_dir[i][0] * 2][custodian_dir[i][1]] == me_flag)
			{
				Danger = Danger - 10;
			}
		}
	}
	return Danger;
}

/*
*判断周围是否有己方棋子
*/
int IF_Together(int x, int y, int*delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Individual_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[new_x + custodian_dir[k][0]][new_y + custodian_dir[k][1]] == me_flag)
		{
			Individual_value = Individual_value + 5;
		}
	}
	return Individual_value;
}



/*
*计算棋子移动的攻击价值
*/
int Attack_evaluate(int x, int y, int* delta)
{
	int value;
	value = IF_Yak(x, y, delta) + IF_Mak(x, y, delta);
	return value;
}

/*
*判断是否挑吃
*/
int IF_Mak(int x, int y, int* delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Mak_value = 0;
	if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY)
	{
		int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
		for (int i = 0; i < 4; i++) {
			int x1 = new_x + intervention_dir[i][0];
			int y1 = new_y + intervention_dir[i][1];
			int x2 = new_x - intervention_dir[i][0];
			int y2 = new_y - intervention_dir[i][1];
			if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == other_flag && board[x2][y2] == other_flag)
			{
				Mak_value = Mak_value + 5;
			}
		}
	}
	return Mak_value;
}


/*
*判断是否夹吃
*/
int IF_Yak(int x, int y, int* delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Yak_value = 0;
	if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY)
	{
		int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
		for (int i = 0; i < 8; i++) {
			int x1 = new_x + custodian_dir[i][0];
			int y1 = new_y + custodian_dir[i][1];
			int x2 = new_x + custodian_dir[i][0] * 2;
			int y2 = new_y + custodian_dir[i][1] * 2;
			if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == me_flag && board[x1][y1] == other_flag)
			{
				Yak_value = Yak_value + 5;
			}
		}
	}
	return Yak_value;
}
