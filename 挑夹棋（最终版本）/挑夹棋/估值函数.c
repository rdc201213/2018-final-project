int Attack_evaluate(int x, int y, int* delta)
{
	int value;
	value= IF_Yak(x, y,*delta) + IF_Mak(x, y,*delta) ;
	return value;
}
/*
*≈–∂œ «∑Òº–≥‘
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
				Yak_value = Yak_value + 3;
			}
		}
	}
	return Yak_value;
}

/*
*≈–∂œ «∑ÒŒ£œ’
*/
int IF_Danger(int x, int y,int* delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Safe_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[new_x + custodian_dir[k][0]][new_y + custodian_dir[k][1]] == other_flag)
		{
			Safe_value = Safe_value - 2;
		}
	}
	return Safe_value;
}

/*
*≈–∂œ÷‹Œß «∑Ò”–º∫∑Ω∆Â◊”
*/
int IF_Together(int x, int y, int*delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Individual_value = -16;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[new_x + custodian_dir[k][0]][new_y + custodian_dir[k][1]] ==me_flag)
		{
			Individual_value = Individual_value +2;
		}
	}
	return Individual_value;
}


int k, i, j, Temp_value,Value=0;


for (i = 0; i < 12; i++)
{
	for (j = 0; j < 12; j++)
	{
		if (borad[i][j] == me_flag)
		{
			for ( k = 0; k < 8; k++)
			{
				const int* delta = DIR[k];
				Temp_value= Attack_evaluate(x, y,*delta)//+Defence_evaluate(x,y,*delta)//;
				if (Temp_value > Value)
				{
					Value = Temp_value;
					Command.x = x;
					Command.y = y;
					Command.option = k;
				}
			}
		}
	}
}





/*
*≈–∂œ «∑ÒÃÙ≥‘
*/
int IF_Mak(int x, int y,int* delta)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Mak_value=0;
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


int Defence_evaluate(int x, int y, int* delta)
{
	int value=0;
	return IF_Danger(x, y, delta) + IF_Stable(x, y, delta);
}




int i = 0;

for (int k = 0; k < 8; k++)
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (board[x][y] == me && isInBound(x + DIR[k][0], y + DIR[k][1]) && board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
			{
				Copy_Board(board, My_Board);
				My_place(x, y, k, cur_flag, My_Board);
				preferPos.value[i] =First_evaluate(My_Board);
				preferPos[i].x = x;
				preferPos[i].y = y;
				preferPos.option[i] = k;
			}
		}
	}
}

//≈≈¡–




for (i = 0; i < 20; i++)
{
	My_place(preferPos[i].x, preferPos[i].y, preferPos[i].option, cur_flag, Temp_board);
	value=Min()
}





for (int k = 0; k < 8; k++)
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (board[x][y] == me && isInBound(x + DIR[k][0], y + DIR[k][1]) && board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
			{
				Copy_Board(board, My_Board);
				My_place(x, y, k, cur_flag, My_Board);
				value = Min(My_Board, depth - 1, alpha, beta, 3 - cur_flag);
				if (value >= Best_value)
				{
					preferedPos.x = x;
					preferedPos.y = y;
					preferedPos.option = k;
					Best_value = value;
				}
			}
		}
	}
}
return preferedPos;


/*≥ı≤Ωπ¿÷µ*/
int First_evaluate(char cur_board[12][12])
{
	int value = 0;

}


void swap()
{
	int n = 0;
	struct PreferPos temp;
	n = sizeof(preferpos[64].value) / 4;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
		{
			if (preferpos[j].value < preferpos[j + 1].value) 
			{
				temp = preferpos[j]; preferpos[j] = preferpos[j + 1]; preferpos[j + 1] = temp;
			}
		}
}