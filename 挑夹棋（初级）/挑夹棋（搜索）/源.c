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
int Count_Step = 0,Board_Value=0;
char Cur_Board[12][12];

/**
 * 你可以在这里初始化你的AI
 */
void initAI(int me)
{
}
/*
计算当前棋子数量
*/
int Count_Stone(int me)
{
	int My_Stone, i, j;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (board[i][j] == me)
			{
				My_Stone++;
			}
		}
	}
}
/*
*随机下子
*/
struct Command findValidPos(const char board[BOARD_SIZE][BOARD_SIZE], int flag) {
	struct Command command = { 0, 0, 0 };
	for (int k = 0; k < 8; k++) {
		const int* delta = DIR[k];
		for (int x = 0; x < BOARD_SIZE; x++) {
			for (int y = 0; y < BOARD_SIZE; y++) {
				if (board[x][y] != flag) {
					continue;
				}
				int new_x = x + delta[0];
				int new_y = y + delta[1];
				if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY) {
					command.x = x;
					command.y = y;
					command.option = k;
					return command;
				}
			}
		}
	}
	return command;
}
/*
*计算棋子移动的防御价值
*/
int Defence_evaluate(int x, int y, int* delta,int cur_flag)
{
	int value;
	value = IF_Danger_After(x, y, delta, cur_flag) + IF_Together(x, y, delta, cur_flag)-IF_Danger_Before(x,y, cur_flag)+IF_Be_Mak(x, y, delta, cur_flag);
	return value;
}
/*
*判断移动前是否危险
*/
int IF_Danger_Before(int x, int y,int cur_flag)
{
	int Safe_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[x + custodian_dir[k][0]][y + custodian_dir[k][1]] == 3- cur_flag)
		{
			Safe_value = Safe_value - 2;
		}
	}
	return Safe_value;
}
/*
*判断移动后是否危险
*/
int IF_Danger_After(int x, int y, int* delta,int cur_flag)
{
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int Safe_value = 0;
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int k = 0; k < 8; k++)
	{
		if (board[new_x + custodian_dir[k][0]][new_y + custodian_dir[k][1]] == 3- cur_flag)
		{
			Safe_value = Safe_value - 5;
		}
		if (board[new_x + custodian_dir[k][0]*2][new_y + custodian_dir[k][1]*2] == 3- cur_flag)
		{
			Safe_value = Safe_value - 3;
		}
	}
	return Safe_value;
}


/*判断是否被挑吃*/
int IF_Be_Mak(int x, int y, int*delta,int cur_flag)
{
	int Danger = 0;
	int new_x = x + delta[0];
	int new_y = y + delta[1];
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

	if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY)
	{
		for (int i = 0; i < 8; i++)
		{
			if (board[x + custodian_dir[i][0]][y + custodian_dir[i][1]] == cur_flag && board[x - custodian_dir[i][0]][y - custodian_dir[i][0]] == cur_flag)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board[x + custodian_dir[i][0]][y + custodian_dir[i][1]] == 3- cur_flag)
						Danger = Danger - 10;
				}
			}
			if (board[new_x + custodian_dir[i][0] * 2][custodian_dir[i][1]] == cur_flag)
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
int Attack_evaluate(int x, int y, int* delta,int cur_flag)
{
	int value;
	value = IF_Yak(x, y, delta, cur_flag) + IF_Mak(x, y, delta, cur_flag);
	return value;
}

/*
*判断是否挑吃
*/
int IF_Mak(int x, int y, int* delta,int cur_flag)
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
			if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == 3- cur_flag && board[x2][y2] == 3- cur_flag)
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
int IF_Yak(int x, int y, int* delta,int cur_flag)
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
			if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == 3- cur_flag && board[x1][y1] == 3- cur_flag)
			{
				Yak_value = Yak_value + 5;
			}
		}
	}
	return Yak_value;
}


/*
*做出判断
*/
struct Command Make_jugement(char board[BOARD_SIZE][BOARD_SIZE], int cur_flag)
{
	struct Command command = { 0, 0, 0 };
	int k, i = 0, j, Temp_value, Value = -100;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (board[i][j] == cur_flag)
			{
				int x = i;
				int y = j;
				for (k = 0; k < 8; k++)
				{
					const int* delta = DIR[k];
					if (Count_Step > 9)
					{
						Temp_value = 4 * Attack_evaluate(x, y, delta, cur_flag) + 6 * Defence_evaluate(x, y, delta, cur_flag);
					}
					else
					{
						Temp_value = 8 * Attack_evaluate(x, y, delta, cur_flag) + 2 * Defence_evaluate(x, y, delta, cur_flag);
					}
					if (Temp_value > Value&&isInBound(x + delta[0], y + delta[1]) && board[x + delta[0]][y + delta[1]] == EMPTY)
					{
						Value = Temp_value;
						command.x = x;
						command.y = y;
						command.option = k;
					}
				}
			}
		}
	}
	place(command.x, command.y, command.option, cur_flag);
}





/**
 * 轮到你落子。
 * 棋盘上0表示空白，1表示黑棋，2表示白旗
 * me表示你所代表的棋子(1或2)
 * 你需要返回一个结构体Command，在x属性和y属性填上你想要移动的棋子的位置，option填上你想要移动的方向。
 */
struct Command aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int me) {
	/*
	 * TODO：在这里写下你的AI。
	 */
	struct Command preferedPos;
	if (Count_Step < 1)
	{
		if (me == 1)
		{
			preferedPos.x = 9;
			preferedPos.y = 7;
			preferedPos.option = UP;
		}
		else
		{
			if (board[8][6] == other_flag ^ board[8][7] == other_flag ^ board[8][8] == other_flag)
			{
				preferedPos.x = 6;
				preferedPos.y = 8;
				preferedPos.option = DOWN_LEFT;
			}
			else
			{
				preferedPos.x = 2;
				preferedPos.y = 4;
				preferedPos.option = DOWN;
			}

		}
	}
	if (Count_Step >= 1)
	{
		if (Count_Step == 1 && board[7][7] == EMPTY && board[6][6] == other_flag)
		{
			preferedPos.x = 8;
			preferedPos.y = 7;
			preferedPos.option = UP;
		}
		else if (Count_Step == 2 && board[6][6] == me_flag && board[6][7] == other_flag && board[5][7] == EMPTY)
		{
			preferedPos.x = 6;
			preferedPos.y = 6;
			preferedPos.option = UP_RIGHT;

		}
		else
		{
			preferedPos = Make_jugement(board, me);
		}
	}
	Count_Step++;
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

int Start_sousuo(int me)
{
	sousuo(0, me);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			board[i][j] = Cur_Board[i][j];
		}
	}

}


int sousuo(int i,int me)
{
	if (i == 2)
	{
		if (Count_Stone(me) > Board_Value)
		{
			Board_Value = Count_Stone(me);

		}
	}
	Make_jugement(board, me);
	me = 3 - me;
	sousuo(i + 1,me);
	me = 3 - me;
}