#pragma once

#include "chesstile.h"
#include "chesspiece.h"
#include "buttongame.h"
#include "utilities.h"
#include "svgbutton.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QSoundEffect>

class ThemesSetting : public QGraphicsScene {
	Q_OBJECT

public:
	ThemesSetting(QObject* parent = nullptr);
    ~ThemesSetting();
	int piecesTheme = 0, tilesTheme = 0;

signals:
	void backActivated();
	void saveChangeActivated();

private:
	chess::Board board;
	ChessTile *tiles[8][8];
	ChessPiece *pieces[8][8];
	QGraphicsTextItem* txtPiecesTheme, * txtTilesTheme;
	ButtonGame *btnPiecesTheme[3], *btnTilesTheme[9];
	ButtonGame *btnSaveChange;
	SvgButton* btnBack;

	void syncBoard(void);
};
