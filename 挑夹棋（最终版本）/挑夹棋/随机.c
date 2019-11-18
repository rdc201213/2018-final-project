struct Command
{
	int x;
	int y;
	OPTION option;
};


struct Command preferedPos = findValidPos(board, me);
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