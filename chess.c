#include "chess.h"
#define PawnWhite 2
#define PawnBlack 1
#define rookWhite 10
#define rookBlack 5
#define KnightWhite 11
#define KnightBlack 4
#define QueenWhite 13
#define QueenBlack 6
#define BishopWhite 12
#define BishopBlack 3
#define KingBlack 7
#define KingWhite 14

void fillBoard(chessBoard *boardStruct) {
    /*     {
      {5,4,3,6,7,3,4,5},
      {1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {2,2,2,2,2,2,2,2},
      {10,11,12,13,14,12,11,10}
  }; */
}

void updateBoard(chessBoard *boardStruct, movePiece *mPiece) {
    // boardStruct->board[4][5] = 3;
    switch (boardStruct->board[mPiece->i][mPiece->j]) {
        case 1:
        case 2:
            validateMovePawn(boardStruct, mPiece);
            break;
        case 3:
        case 12:
            validateMoveBishop(boardStruct, mPiece);
            break;
        case 4:
        case 11:
            validateMoveKnight(boardStruct, mPiece);
            break;
        case 5:
        case 10:
            validateMoveRook(boardStruct, mPiece);
            break;
        case 6:
        case 13:
            validateMoveKing(boardStruct, mPiece);
            break;
        case 7:
        case 14:
            validateMoveQueen(boardStruct, mPiece);
            break;
        default:
            break;
    }
}

int gameWin(chessBoard *boardStruct, movePiece *mPiece) {}

int gameDraw(chessBoard *boardStruct, movePiece *mPiece) {}

int isInCheckWhite(chessBoard *boardStruct, movePiece *mPiece) {
    // find where king is
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (boardStruct->board[i][j] == KingWhite) {
                boardStruct->whiteKing.i = i;
                boardStruct->whiteKing.j = j;
            }
        }
    }
    // check king vertical
    int KINGI = boardStruct->whiteKing.i;
    int KINGJ = boardStruct->whiteKing.j;

    for (int i = boardStruct->whiteKing.i + 1; i < 8; ++i) {
        if (boardStruct->board[i][KINGJ]) {
            if (boardStruct->board[i][KINGJ] == 6 ||
                boardStruct->board[i][KINGJ] == 5) {
                return 1;
            } else {
                break;
            }
        }
    }

    // reverse vertical
    for (int i = boardStruct->whiteKing.i - 1; i >= 0; --i) {
        if (boardStruct->board[i][KINGJ]) {
            if (boardStruct->board[i][KINGJ] == 6 ||
                boardStruct->board[i][KINGJ] == 5) {
                return 1;
            } else {
                break;
            }
        }
    }

    // check king horizontal
    for (int i = boardStruct->whiteKing.j + 1; i < 8; ++i) {
        if (boardStruct->board[KINGI][i]) {
            if (boardStruct->board[KINGI][i] == 6 ||
                boardStruct->board[KINGI][i] == 5) {
                return 1;
            } else {
                break;
            }
        }
    }
    // reverse horizontal
    for (int i = boardStruct->whiteKing.j - 1; i >= 0; --i) {
        if (boardStruct->board[KINGI][i]) {
            if (boardStruct->board[KINGI][i] == 6 ||
                boardStruct->board[KINGI][i] == 5) {
                return 1;
            } else {
                break;
            }
        }
    }

    // diagonal TODO 
	// up left/ down right
	int temp = boardStruct->whiteKing.j+1;
	for (int i = boardStruct->whiteKing.i + 1; i < 8 ; ++i){
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BishopBlack ||
                boardStruct->board[i][temp] == QueenBlack) {
                return 1;
            } else {
                break;
            }
        }
		++temp;
	}

	temp = boardStruct->whiteKing.j-1;
	for (int i = boardStruct->whiteKing.i - 1; i >= 0 ; --i){
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BishopBlack ||
                boardStruct->board[i][temp] == QueenBlack) {
                return 1;
            } else {
                break;
            }
        }
		--temp;
	}
	// up right/ down left
	temp = boardStruct->whiteKing.j-1;
	for (int i = boardStruct->whiteKing.i + 1; i < 8 ; ++i){
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BishopBlack ||
                boardStruct->board[i][temp] == QueenBlack) {
                return 1;
            } else {
                break;
            }
        }
		--temp;
	}

	temp = boardStruct->whiteKing.j+1;
	for (int i = boardStruct->whiteKing.i - 1; i >= 0 ; --i){
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BishopBlack ||
                boardStruct->board[i][temp] == QueenBlack) {
                return 1;
            } else {
                break;
            }
        }
		++temp;
	}

    // knights!
    // 2 up, one left/right
    if (boardStruct->board[KINGI + 2][KINGJ + 1] == KnightBlack) return 1;
    if (boardStruct->board[KINGI + 2][KINGJ - 1] == KnightBlack) return 1;
    // 2 down, one left/right
    if (boardStruct->board[KINGI - 2][KINGJ + 1] == KnightBlack) return 1;
    if (boardStruct->board[KINGI - 2][KINGJ - 1] == KnightBlack) return 1;
    // 2 right ,one up/down
    if (boardStruct->board[KINGI + 1][KINGJ + 2] == KnightBlack) return 1;
    if (boardStruct->board[KINGI - 1][KINGJ + 2] == KnightBlack) return 1;
    // 2 left, one up/down
    if (boardStruct->board[KINGI + 1][KINGJ - 2] == KnightBlack) return 1;
    if (boardStruct->board[KINGI - 1][KINGJ - 2] == KnightBlack) return 1;

    return 0;
}

int isInCheckBlack(chessBoard*boardStruct,movePiece*mPiece){
	
}
int whitePinned(chessBoard *boardStruct, movePiece *mPiece) {
    // there's some diagonal on pawn or vertical/horizontal
    // for white
    int orgI = mPiece->i;
    int orgJ = mPiece->j;
    int temp = boardStruct->board[mPiece->goalI][mPiece->goalJ];

    boardStruct->board[orgI][orgJ] = 0;
    boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;

    if (isInCheckWhite(boardStruct, mPiece)) {
        boardStruct->board[orgI][orgJ] = 1;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = temp;
        return 1;
    }
    return 0;
}

int whiteRemovesChecks(chessBoard *boardStruct, movePiece *mPiece) {
    // for white
    int orgI = mPiece->i;
    int orgJ = mPiece->j;
    int temp = boardStruct->board[mPiece->goalI][mPiece->goalJ];
    boardStruct->board[orgI][orgJ] = 0;
    boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;

    if (!isInCheckWhite(boardStruct, mPiece)) {
        boardStruct->board[orgI][orgJ] = 1;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = temp;
        return 1;
    }
    return 0;
}

int validateMovePawn(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int validateMoveBishop(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int validateMoveKing(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int validateMoveQueen(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int validateMoveRook(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int validateMoveKnight(chessBoard *boardStruct, movePiece *mPiece) {
    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = 1;
        return 1;
    }

    return 0;
}

int canEnpassant(chessBoard *boardStruct, movePiece *mPiece) {}
