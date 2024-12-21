#include "../header/themesSetting.h"

#include <iostream>

ThemesSetting::ThemesSetting(QObject* parent) :
	QGraphicsScene(parent),
	board()
{
	setSceneRect(0, 0, 1000, 600);

	int newTileSize = 55;
	for (int row = 0; row < boardSize; ++row) {
		for (int col = 0; col < boardSize; ++col) {
			tiles[row][col] = new ChessTile(row, col);
			tiles[row][col]->setRect(0, 0, newTileSize, newTileSize);
			tiles[row][col]->setX(400 + 80 + col * newTileSize);
			tiles[row][col]->setY(40 + row * newTileSize);
			addItem(tiles[row][col]);

			chess::Square source(chess::Rank(7 - row), chess::File(col));
			chess::Piece piece = board.at<chess::Piece>(source);
			pieces[row][col] = new ChessPiece("");
			pieces[row][col]->setX(400 + 80 + col * newTileSize);
			pieces[row][col]->setY(40 + row * newTileSize);
			pieces[row][col]->setSizePiece(newTileSize);
			if (piece != chess::Piece::NONE) {
				pieces[row][col]->resetPieceImage(piecesTheme, getPieceIcon(piece));
			}
			addItem(pieces[row][col]);
			pieces[row][col]->setZValue(1);

		}
	}
	for (int row = 0; row < boardSize; ++row) {
		for (int col = 0; col < boardSize; ++col) {
			tiles[row][col]->setTheme(tilesTheme);
		}
	}

	txtTilesTheme = new QGraphicsTextItem("Tiles Theme");
	txtTilesTheme->setFont(QFont("Arial", 20, QFont::Bold));
	txtTilesTheme->setDefaultTextColor(Qt::white);
	txtTilesTheme->setPos(125 - txtTilesTheme->boundingRect().width()/2, 80);
	addItem(txtTilesTheme);	
	for (int i = 0; i < 9; ++i) {
		btnTilesTheme[i] = new ButtonGame("Tile " + QString::number(i+1), QRect(0, 0, 150, 40));
		btnTilesTheme[i]->setPos(50, 120 + i * 40);
		addItem(btnTilesTheme[i]);
		connect(btnTilesTheme[i], &ButtonGame::clicked, [this, i]() {
			tilesTheme = i;
			syncBoard();
		});
	}

	txtPiecesTheme = new QGraphicsTextItem("Pieces Theme");
	txtPiecesTheme->setFont(QFont("Arial", 20, QFont::Bold));
	txtPiecesTheme->setDefaultTextColor(Qt::white);
	txtPiecesTheme->setPos(305 - txtPiecesTheme->boundingRect().width() / 2, 200);
	addItem(txtPiecesTheme);
	for (int i = 0; i < 3; ++i) {
		btnPiecesTheme[i] = new ButtonGame("Piece " + QString::number(i+1), QRect(0, 0, 150, 40));
		btnPiecesTheme[i]->setPos(230, 240 + i * 40);
		addItem(btnPiecesTheme[i]);
		connect(btnPiecesTheme[i], &ButtonGame::clicked, [this, i]() {
			piecesTheme = i;
			syncBoard();
		});
	}
    btnBack = new SvgButton(":/assets/buttons/back.svg");
	btnBack->fixSize(50);
	btnBack->setPos(10, 10);
	addItem(btnBack);
	btnSaveChange = new ButtonGame("Save Change", QRect(0, 0, 150, 40));
	btnSaveChange->setPos(400 + 225, 40 + 440 + 40);
	addItem(btnSaveChange);

	connect(btnBack, &SvgButton::clicked, [this]() {
		emit backActivated();
	});
	connect(btnSaveChange, &ButtonGame::clicked, [this]() {
		emit saveChangeActivated();
	});
}

void ThemesSetting::syncBoard() {
	std::cout << tilesTheme << " " << piecesTheme << std::endl;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			tiles[i][j]->setTheme(tilesTheme);
			chess::Square source(chess::Rank(7 - i), chess::File(j));
			chess::Piece piece = board.at<chess::Piece>(source);
			if (piece != chess::Piece::NONE) {
				pieces[i][j]->resetPieceImage(piecesTheme, getPieceIcon(piece));
			}
		}
	}
}

ThemesSetting::~ThemesSetting() {
    // Delete dynamically allocated chess tiles and pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete tiles[i][j];
            delete pieces[i][j];
        }
    }

    // Delete dynamically allocated QGraphicsTextItems
    delete txtPiecesTheme;
    delete txtTilesTheme;

    // Delete dynamically allocated ButtonGame objects
    for (int i = 0; i < 3; ++i) {
        delete btnPiecesTheme[i];
    }
    for (int i = 0; i < 9; ++i) {
        delete btnTilesTheme[i];
    }

    // Delete dynamically allocated buttons
    delete btnSaveChange;
    delete btnBack;
}

