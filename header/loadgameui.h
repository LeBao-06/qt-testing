#pragma once

#include "chess.hpp"
#include "chesstile.h"
#include "chesspiece.h"
#include "buttongame.h"
#include "svgbutton.h"
#include "utilities.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsRectItem>
#include <QCoreApplication>
#include <qDebug>

class LoadGameUI : public QGraphicsScene {
    Q_OBJECT
public:
    LoadGameUI(QObject* parent = nullptr);
    ~LoadGameUI();
    void reloadJsonFileList();

signals:
    void backActivated();
    void playgameActivated(const GameData& data);

private:
    chess::Board board;
    chess::Move currentMove;
    std::string boardFen;
    int playerSide;
    int reverseBoard;
    int gameMode, gameDifficulty;
    int tilesTheme, piecesTheme;
    int newTileSize;

    int rowItem;
    QString curPathItem;

    QListWidget jsonFileList;
    ChessTile *tiles[8][8];
    ChessPiece *pieces[8][8];
    QGraphicsTextItem* txtPiecesTheme, * txtTilesTheme;
    ButtonGame *btnDeleteFile, *btnPlayGame;
    SvgButton* btnBack;

    void syncBoard(void);
    void initJsonFileList(const QString&);

private slots:
    void changeJsonFile(QListWidgetItem*);
    void deleteFileJson();
};

