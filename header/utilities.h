#pragma once

#include "chess.hpp"
#include <QString>
#include <string>

inline float volumeEffect = 1.0;

struct GameData{
    std::string boardFen;
    int playerSide;
    int reverseBoard;
    int gameMode;
    int gameDifficulty;
    int tilesTheme;
    int piecesTheme;
    chess::Move curMove;
    GameData(){
        boardFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        playerSide = 1;
        reverseBoard = 1;
        gameMode = 0;
        gameDifficulty = 0;
        tilesTheme = 0;
        piecesTheme = 0;
    }
};

const QString _piecesOrder[] = {
	"pawn",
	"knight",
	"bishop",
	"rook",
	"queen",
	"king"
};

inline QString getPieceColor(chess::Piece piece) {
	return (piece.color() == chess::Color::WHITE) ? "white" : "black";
}

inline QString getPieceType(chess::Piece piece) {
	return _piecesOrder[piece.type()];
}

inline QString getPieceIcon(chess::Piece piece) {
	return getPieceColor(piece) + '_' + getPieceType(piece) + ".svg";
}
