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



/**
 * YOUR CODE BEGIN
 * 你的代码开始
 */

 /**
  * You can define your own struct and variable here
  * 你可以在这里定义你自己的结构体和变量
  */
#include<math.h>
#define INFINITY 100000
#define max(a,b) (a>b? a:b)
#define isInBound(x,y) (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
#pragma warning(disable : 4996)
struct PreferPos
{
	int value;
	int x;
	int y;
	OPTION option;
};
const int first[8][2] = { {-3, -1}, {-3, 1}, {-1, 3}, {1, 3}, {3, 1}, {3, -1}, {1, -3}, {-1, -3} };//阵型1
const int second[8][2] = { {-2, -1}, {-2, 1}, {-1, 2}, {1,2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2} };//阵型2
/*
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
*估值函数
*/
int Count_Stone(char board[12][12])
{
	int value = 0;
	int count = 0;
	int i, j, k, a;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (board[i][j] == me_flag)
			{
				value = value + 1000 - 6 * max(abs(i - 6), abs(j - 6));//计算子数+向中靠拢
				for (k = 0; k < 8; k++)
				{
					if (isInBound(i + first[k][0], j + first[k][1]) && board[i + first[k][0]][j + first[k][1]] == me_flag)
					{
						value = value + 4;//阵型1
					}
					if (isInBound(i + second[k][0], j + second[k][1]) && board[i + second[k][0]][j + second[k][1]] == me_flag)
					{
						value = value + 2;//阵型2
					}
					if (isInBound(i + DIR[k][0], j + DIR[k][1]) && board[i + DIR[k][0]][j + DIR[k][1]] == other_flag)
					{
						value = value + 8;//寻找敌方
						for (a = 0; a < 8; a++)
						{
							//敌方夹位
							if (isInBound(i + 2 * DIR[k][0] + DIR[a][0], j + 2 * DIR[k][1] + DIR[a][1]) && isInBound(i + 2 * DIR[k][0], j + 2 * DIR[k][1]))
							{
								if (board[i + 2 * DIR[k][0] + DIR[a][0]][j + 2 * DIR[k][1] + DIR[a][1]] == me_flag && board[i + 2 * DIR[k][0]][j + 2 * DIR[k][1]] == EMPTY)
									value = value + 40;
							}
							//我方夹位
							if (isInBound(i - DIR[k][0] + DIR[a][0], j - DIR[k][1] + DIR[a][1]) && isInBound(i - DIR[k][0], j - DIR[k][1]))
							{
								if (board[i - DIR[k][0] + DIR[a][0]][j - DIR[k][1] + DIR[k][1]] == other_flag && board[i - DIR[k][0]][j - DIR[k][1]] == EMPTY)
									value = value - 44;
							}
						}
					}
					for (a = 0; a < 8; a++)
					{
						if (board[i + DIR[k][0] + DIR[a][0]][j + DIR[k][1] + DIR[a][1]] == other_flag)
						{
							value = value + 2;//寻找敌方
						}
					}
					//我方挑位
					if (isInBound(i + 2 * DIR[k][0], j + 2 * DIR[k][1]) && board[i + 2 * DIR[k][0]][j + DIR[k][1]] == me_flag)
					{
						for (a = 0; a < 8; a++)
						{
							if (board[i + DIR[k][0] + DIR[a][0]][j + DIR[k][1] + DIR[a][1]] == other_flag)
								value = value - 44;
						}
					}
					//敌方挑位
					if (board[i - 1][j - 1] == other_flag && board[i - 1][j + 1] == other_flag && board[i - 1][j] == EMPTY && isInBound(i - 1, j - 1) && isInBound(i - 1, j + 1))
						value = value + 40;
					if (board[i - 1][j - 1] == other_flag && board[i + 1][j - 1] == other_flag && board[i][j - 1] == EMPTY && isInBound(i - 1, j - 1) && isInBound(i + 1, j - 1))
						value = value + 40;
					if (board[i + 1][j - 1] == other_flag && board[i + 1][j + 1] == other_flag && board[i + 1][j] == EMPTY && isInBound(i + 1, j - 1) && isInBound(i + 1, j + 1))
						value = value + 40;
					if (board[i - 1][j + 1] == other_flag && board[i + 1][j + 1] == other_flag && board[i][j + 1] == EMPTY && isInBound(i - 1, j + 1) && isInBound(i + 1, j + 1))
						value = value + 40;
					if (board[i - 2][j] == other_flag && board[i][j - 2] == other_flag && board[i - 1][j - 1] == EMPTY && isInBound(i - 2, j) && isInBound(i, j - 1))
						value = value + 40;
					if (board[i - 2][j] == other_flag && board[i][j + 2] == other_flag && board[i - 1][j + 1] == EMPTY && isInBound(i - 2, j) && isInBound(i, j + 2))
						value = value + 40;
					if (board[i + 2][j] == other_flag && board[i][j - 2] == other_flag && board[i + 1][j - 1] == EMPTY && isInBound(i + 2, j) && isInBound(i, j - 2))
						value = value + 40;
					if (board[i + 2][j] == other_flag && board[i][j + 2] == other_flag && board[i + 1][j + 1] == EMPTY && isInBound(i + 2, j) && isInBound(i, j + 2))
						value = value + 40;
				}
			}
		}
	}
	return value;
}



/*
*落子函数
*/
void My_place(int x, int y, OPTION option, int cur_flag, char board[12][12])
{
	int cur_other_flag = 3 - cur_flag;
	int new_x = x + DIR[option][0];
	int new_y = y + DIR[option][1];
	int i;
	board[x][y] = EMPTY;
	board[new_x][new_y] = cur_flag;
	// 挑
	int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	for (i = 0; i < 4; i++)
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
	for (i = 0; i < 8; i++)
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
	int i, j;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
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
	int x, y, k;
	if (depth == 0)
	{
		int value = Count_Stone(cur_board);
		return value;
	}
	char Temp_Board[12][12];
	int value;
	Copy_Board(cur_board, Temp_Board);
	for (k = 0; k < 8; k++)
	{
		for (x = 0; x < 12; x++)
		{
			for (y = 0; y < 12; y++)
			{

				if (cur_board[x][y] == cur_flag && isInBound(x + DIR[k][0], y + DIR[k][1]) && cur_board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
				{
					My_place(x, y, k, cur_flag, Temp_Board);
					value = Max(Temp_Board, depth - 1, alpha, beta, 3 - cur_flag);
					Copy_Board(cur_board, Temp_Board);
					if (value < beta)
					{
						beta = value;
					}
					if (alpha >= beta)
					{
						return alpha;
					}
				}
			}
		}
	}
	return beta;
}

int Max(char cur_board[12][12], int depth, int alpha, int beta, int cur_flag)
{
	int x, y, k;
	if (depth == 0)
	{
		int value = Count_Stone(cur_board);
		return value;
	}
	char Temp_Board[12][12];
	Copy_Board(cur_board, Temp_Board);
	int value;
	for (k = 0; k < 8; k++)
	{
		for (x = 0; x < 12; x++)
		{
			for (y = 0; y < 12; y++)
			{
				if (cur_board[x][y] == cur_flag && isInBound(x + DIR[k][0], y + DIR[k][1]) && cur_board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
				{
					My_place(x, y, k, cur_flag, Temp_Board);
					value = Min(Temp_Board, depth - 1, alpha, beta, 3 - cur_flag);
					Copy_Board(cur_board, Temp_Board);
					if (value > alpha)
					{
						alpha = value;
					}
					if (alpha >= beta)
					{
						return beta;
					}

				}
			}
		}
	}
	return alpha;
}


/*
*排序
*/
void swap(int n, struct PreferPos preferpos[128])
{
	int i, j;
	struct PreferPos temp;
	for (i = 0; i < n; i++)
		for (j = 0; j < n - i - 1; j++)
		{
			if (preferpos[j].value < preferpos[j + 1].value)
			{
				temp = preferpos[j]; preferpos[j] = preferpos[j + 1]; preferpos[j + 1] = temp;
			}
		}
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
	struct PreferPos preferpos[128];
	char My_Board[12][12];
	int value = 0, Best_value = -INFINITY;
	int alpha = -INFINITY, beta = INFINITY;
	int depth;
	int cur_flag = me;
	int i = 0, j = 0;
	int x, y, k;
	 //初步落子
		depth = 2;
		for (k = 0; k < 8; k++)
		{
			for (x = 0; x < BOARD_SIZE; x++)
			{
				for (y = 0; y < BOARD_SIZE; y++)
				{
					if (board[x][y] == me && isInBound(x + DIR[k][0], y + DIR[k][1]) && board[x + DIR[k][0]][y + DIR[k][1]] == EMPTY)
					{
						Copy_Board(board, My_Board);
						My_place(x, y, k, cur_flag, My_Board);
						preferpos[i].value = Min(My_Board, depth - 1, alpha, beta, 3 - cur_flag);
						preferpos[i].x = x;
						preferpos[i].y = y;
						preferpos[i].option = k;
						i++;
					}
				}
			}
		}
		//排序
		swap(i, preferpos);
		//取价值较大者进行搜索
		depth = 4;
		for (j = 0; j < 25; j++)
		{
			Copy_Board(board, My_Board);
			My_place(preferpos[j].x, preferpos[j].y, preferpos[j].option, cur_flag, My_Board);
			value = Min(My_Board, depth - 1, Best_value, beta, 3 - cur_flag);
			if (value > Best_value)
			{
				Best_value = value;
				preferedPos.x = preferpos[j].x;
				preferedPos.y = preferpos[j].y;
				preferedPos.option = preferpos[j].option;
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
	count_step++;
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