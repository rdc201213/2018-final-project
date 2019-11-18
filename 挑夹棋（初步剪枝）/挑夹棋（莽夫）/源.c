#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// board information
#define BOARD_SIZE 12
#define EMPTY 0
#define BLACK 1
#define WHITE 2

// bool
typedef int BOOL;
#define TRUE 1
#define FALSE 0

// option
typedef int OPTION;
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_LEFT 6
#define DOWN_RIGHT 7

#define MAX_BYTE 10000

#define START "START"
#define PLACE "PLACE"
#define TURN  "TURN"
#define END   "END"

struct Command
{
	int x;
	int y;
	OPTION option;
};


char buffer[MAX_BYTE] = { 0 };
char board[BOARD_SIZE][BOARD_SIZE] = { 0 };
int me_flag;
int other_flag;

const int DIR[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

void debug(const char *str) {
	printf("DEBUG %s\n", str);
	fflush(stdout);
}

void printBoard() {
	char visual_board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == EMPTY) {
				visual_board[i][j] = '.';
			}
			else if (board[i][j] == BLACK) {
				visual_board[i][j] = 'O';
			}
			else if (board[i][j] == WHITE) {
				visual_board[i][j] = 'X';
			}
		}
		printf("%s\n", visual_board[i]);
	}
}

BOOL isInBound(int x, int y) {
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

/**
 * YOUR CODE BEGIN
 * 你的代码开始
 */

 /**
  * You can define your own struct and variable here
  * 你可以在这里定义你自己的结构体和变量
  */
#define INFINITY 100000
#pragma warning(disable : 4996)
  /*
   * 你可以在这里初始化你的AI
   */
void initAI(int me)
{

}

/*
*估值函数
*/

/*
*棋子估值
*/
int Count_Stone(char board[12][12])
{
	int value = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (board[i][j] == me_flag)
			{
				value = value + 100;
			}
		}
	}
	return value;
}

/*
*阵型估值
*/
/*int Formation_evaluate(char board[12][12])
{

}
*/

/*
*寻找敌方
*/
int Find_enemy(char board[12][12])
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
					if (board[i + DIR[k][0]][j + DIR[k][1]] == other_flag|| board[i + DIR[k][0]][j + DIR[k][1]] == me_flag)
						value = value + 3;
					for (int a = 0; a < 8; a++)
					{
						if (board[i + DIR[k][0] + DIR[a][0]][j + DIR[k][1] + DIR[a][1]] == other_flag)
							value = value + 3;
					}
				}
			}
		}
	}
	return value;
}

/*
*寻找友方
*/
/*int Find_Brother(char board[12][12])
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
					if (board[i + DIR[k][0]][j + DIR[k][1]] == me_flag)
						value = value + 2;
				}
			}
		}
	}
	return value;
}
*/
/*
*落子函数
*/
void My_place(int x, int y, OPTION option, int cur_flag, char board[12][12])
{
	int cur_other_flag = 3 - cur_flag;
	int new_x = x + DIR[option][0];
	int new_y = y + DIR[option][1];
	board[x][y] = EMPTY;
	board[new_x][new_y] = cur_flag;
	// 挑
	int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	for (int i = 0; i < 4; i++)
	{
		int x1 = new_x + intervention_dir[i][0];
		int y1 = new_y + intervention_dir[i][1];
		int x2 = new_x - intervention_dir[i][0];
		int y2 = new_y - intervention_dir[i][1];
		if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == cur_other_flag && board[x2][y2] == cur_other_flag)
		{
			board[x1][y1] = cur_flag;
			board[x2][y2] = cur_flag;
		}
	}

	// 夹
	for (int i = 0; i < 8; i++)
	{
		int x1 = new_x + DIR[i][0];
		int y1 = new_y + DIR[i][1];
		int x2 = new_x + DIR[i][0] * 2;
		int y2 = new_y + DIR[i][1] * 2;
		if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == cur_flag && board[x1][y1] == cur_other_flag)
		{
			board[x1][y1] = cur_flag;
		}
	}
}


/*
*复制棋盘
*/
void Copy_Board(char Last_Board[12][12], char New_Board[12][12])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			New_Board[i][j] = Last_Board[i][j];
		}
	}
}

/*
*alpha_beta剪枝
*/
int Min(char cur_board[12][12], int depth, int alpha, int beta, int cur_flag)
{
	char Temp_Board[12][12];
	int value;
	Copy_Board(cur_board, Temp_Board);
	for (int k = 0; k < 8; k++)
	{
		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 12; y++)
			{

				if (cur_board[x][y] == cur_flag && isInBound(x + DIR[k][0], y + DIR[k][1]) && cur_board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
				{
					My_place(x, y, k, cur_flag, Temp_Board);
					value = Max(Temp_Board, depth - 1, alpha, beta, 3 - cur_flag);
					if (depth == 3)
					{
						value = value + Find_enemy(Temp_Board);
					}
					Copy_Board(cur_board, Temp_Board);
					if (alpha >= value)
					{
						return alpha;
					}
					if (value < beta)
					{
						beta = value;
					}
				}
			}
		}
	}
	return beta;
}

int Max(char cur_board[12][12], int depth, int alpha, int beta, int cur_flag)
{
	char Temp_Board[12][12];
	int value;
	Copy_Board(cur_board, Temp_Board);
	if (depth == 0)
	{
		int value = Count_Stone(cur_board);
		return value;
	}
	for (int k = 0; k < 8; k++)
	{
		for (int x = 0; x < 12; x++)
		{
			for (int y = 0; y < 12; y++)
			{
				if (cur_board[x][y] == cur_flag && isInBound(x + DIR[k][0], y + DIR[k][1]) && cur_board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
				{
					My_place(x, y, k, cur_flag, Temp_Board);
					value = Min(Temp_Board, depth - 1, alpha, beta, 3 - cur_flag);
					Copy_Board(cur_board, Temp_Board);
					if (value >= beta)
					{
						return beta;
					}
					if (value > alpha)
					{
						alpha = value;
					}
				}
			}
		}
	}
	return alpha;
}




/**
 * 轮到你落子。
 * 棋盘上0表示空白，1表示黑棋，2表示白旗
 * me表示你所代表的棋子(1或2)
 * 你需要返回一个结构体Command，在x属性和y属性填上你想要移动的棋子的位置，option填上你想要移动的方向。
 */
struct Command aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int me)
{
	/*
	 * TODO：在这里写下你的AI。
	 */
	struct Command preferedPos;
	char My_Board[12][12];
	int value = 0, Best_value = -INFINITY;
	int alpha = -INFINITY, beta = INFINITY;
	int depth = 4;
	int cur_flag = me;
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
}

/**
 * 你的代码结束
 */


BOOL place(int x, int y, OPTION option, int cur_flag) {
	// 移动之前的位置没有我方棋子
	if (board[x][y] != cur_flag) {
		return FALSE;
	}

	int new_x = x + DIR[option][0];
	int new_y = y + DIR[option][1];
	// 移动之后的位置超出边界, 或者不是空地
	if (!isInBound(new_x, new_y) || board[new_x][new_y] != EMPTY) {
		return FALSE;
	}

	board[x][y] = EMPTY;
	board[new_x][new_y] = cur_flag;

	int cur_other_flag = 3 - cur_flag;

	// 挑
	int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	for (int i = 0; i < 4; i++) {
		int x1 = new_x + intervention_dir[i][0];
		int y1 = new_y + intervention_dir[i][1];
		int x2 = new_x - intervention_dir[i][0];
		int y2 = new_y - intervention_dir[i][1];
		if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == cur_other_flag && board[x2][y2] == cur_other_flag) {
			board[x1][y1] = cur_flag;
			board[x2][y2] = cur_flag;
		}
	}

	// 夹
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int i = 0; i < 8; i++) {
		int x1 = new_x + custodian_dir[i][0];
		int y1 = new_y + custodian_dir[i][1];
		int x2 = new_x + custodian_dir[i][0] * 2;
		int y2 = new_y + custodian_dir[i][1] * 2;
		if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == cur_flag && board[x1][y1] == cur_other_flag) {
			board[x1][y1] = cur_flag;
		}
	}

	return TRUE;
}


//........
//........
//..XXXX..
//XXXX....
//....OOOO
//..OOOO..
//........
//........
void start(int flag) {
	memset(board, 0, sizeof(board));

	for (int i = 0; i < 3; i++) {
		board[2][2 + i] = WHITE;
		board[6][6 + i] = WHITE;
		board[5][3 + i] = BLACK;
		board[9][7 + i] = BLACK;
	}

	for (int i = 0; i < 2; i++) {
		board[8 + i][2] = WHITE;
		board[2 + i][9] = BLACK;
	}

	initAI(flag);
}

void turn() {
	// AI
	struct Command command = aiTurn((const char(*)[BOARD_SIZE])board, me_flag);
	place(command.x, command.y, command.option, me_flag);
	printf("%d %d %d\n", command.x, command.y, command.option);
	fflush(stdout);
}

void end(int x) {

}

void loop() {
	//  freopen("../input", "r", stdin);
	while (TRUE)
	{
		memset(buffer, 0, sizeof(buffer));
		gets(buffer);

		if (strstr(buffer, START))
		{
			char tmp[MAX_BYTE] = { 0 };
			sscanf(buffer, "%s %d", tmp, &me_flag);
			other_flag = 3 - me_flag;
			start(me_flag);
			printf("OK\n");
			fflush(stdout);
		}
		else if (strstr(buffer, PLACE))
		{
			char tmp[MAX_BYTE] = { 0 };
			int x, y;
			OPTION option;
			sscanf(buffer, "%s %d %d %d", tmp, &x, &y, &option);
			place(x, y, option, other_flag);
		}
		else if (strstr(buffer, TURN))
		{
			turn();
		}
		else if (strstr(buffer, END))
		{
			char tmp[MAX_BYTE] = { 0 };
			int x;
			sscanf(buffer, "%s %d", tmp, &x);
			end(x);
		}
		//    printBoard();
	}
}


int main(int argc, char *argv[]) {
	loop();
	return 0;
}