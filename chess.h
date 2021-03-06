#pragma once
#include <stdio.h>
#include <stdlib.h>
/*

Game()
Turn()
DoesMoveGiveExposedCheck()
DoesCaptureGiveExposedCheck()
MoveXWhiteNoCapture()
MoveXBlackNoCapture()
MoveXBlack/WhiteCapture()
IsWhiteCheck?()
IsBlackCheck?()
CastleQueenSideWhite/Back()
CastleKingSideWhite/Black()
Enpassant-White/Black()
canXCapturePiece?(White/Black)()
Draw?()
Mate?()



*/
typedef struct{
    int WhiteKingMoved;
    int WhiteRookKMoved;
    int WhiteRookQMoved;
    int BlackKingMoved;
    int BlackRookKMoved;
    int BlackRookQMoved;
} thingMoved;

typedef struct{
    int i;
    int j;
} intPair;

typedef struct
{
    int i;
    int j;
} kingPos;

typedef struct
{
    int board[8][8];
    int lostPieces[16];
    int lastMovePawnTwoUp;
    intPair lastPieceMoveCord;
    kingPos whiteKing;
    kingPos blackKing;
    thingMoved castleStats;
    int turn;
} chessBoard;

typedef struct
{
    int i;
    int j;
    int goalI;
    int goalJ;
} movePiece;

int updateBoard(chessBoard*boardStruct,movePiece*mPiece);

int gameWin();

int gameDraw();

int isInCheck();

int castleKingSide(chessBoard*,movePiece*);

int castleQueenSide(chessBoard*,movePiece*);

int validateMovePawn(chessBoard *boardStruct, movePiece *movePiece);

int validateMoveBishop(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveKing(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveQueen(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveRook(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveKnight(chessBoard *boardStruct, movePiece *movePiece); 