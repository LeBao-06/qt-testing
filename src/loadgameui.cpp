#include "../header/loadgameui.h"


LoadGameUI::LoadGameUI(QObject* parent) :
    QGraphicsScene(parent),
    tilesTheme(0),
    piecesTheme(0)
{
    setSceneRect(0, 0, 1000, 600);
    setBackgroundBrush(QBrush(QColor(59, 66, 82)));

    newTileSize = 50;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            tiles[row][col] = new ChessTile(row, col);
            tiles[row][col]->setRect(0, 0, newTileSize, newTileSize);
            tiles[row][col]->setX(500 + 50 + col * newTileSize);
            tiles[row][col]->setY(40 + row * newTileSize);
            addItem(tiles[row][col]);

            pieces[row][col] = new ChessPiece("");
            pieces[row][col]->setX(500 + 50 + col * newTileSize);
            pieces[row][col]->setY(40 + row * newTileSize);
            pieces[row][col]->setSizePiece(newTileSize);
            addItem(pieces[row][col]);
            pieces[row][col]->setZValue(1);

        }
    }
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            tiles[row][col]->setTheme(tilesTheme);
        }
    }

    btnBack = new SvgButton(":/assets/buttons/back.svg");
    btnBack->fixSize(50);
    btnBack->setPos(10, 10);
    addItem(btnBack);

    connect(btnBack, &SvgButton::clicked, this, [&]() {
        emit backActivated();
    });

    btnDeleteFile = new ButtonGame("Delete", QRect(0, 0, 150, 40));
    btnDeleteFile->setPos(500 + 90, 40 + 400 + 60);
    addItem(btnDeleteFile);
    connect(btnDeleteFile, &ButtonGame::clicked, this, &LoadGameUI::deleteFileJson);
    btnPlayGame = new ButtonGame("Play", QRect(0, 0, 150, 40));
    btnPlayGame->setPos(500 + 90 + 150 + 20, 40 + 400 + 60);
    addItem(btnPlayGame);
    connect(btnPlayGame, &ButtonGame::clicked, this, [&](){
        GameData data;
        data.boardFen = boardFen;
        data.playerSide = playerSide;
        data.reverseBoard = reverseBoard;
        data.gameMode = gameMode;
        data.gameDifficulty = gameDifficulty;
        data.tilesTheme = tilesTheme;
        data.piecesTheme = piecesTheme;
        data.curMove = currentMove;
        emit playgameActivated(data);
    });

    jsonFileList.setGeometry((500 - 350)/2, (600 - 500)/2, 350, 500);
    jsonFileList.setFont(QFont("Courier New", 14));
    jsonFileList.show();
    addWidget(&jsonFileList);
    reloadJsonFileList();

    jsonFileList.setFocusPolicy(Qt::NoFocus);
    jsonFileList.setStyleSheet(
        "QListWidget {"
        "   background: transparent;"
        "   border: 2px solid #8a2be2;"
        "   border-radius: 15px;"
        "   padding: 5px;"
        "   font: bold 14px 'Arial';"
        "}"
        "QListWidget::item {"
        "   color: #4b0082;"
        "   background: #e6e6fa;"
        "   margin: 5px;"
        "   padding: 10px;"
        "   border-radius: 10px;"
        "}"
        "QListWidget::item:selected {"
        "   background: #8a2be2;"
        "   color: white;"
        "}"
        "QListWidget::item:hover {"
        "   background: #d8bfd8;"
        "}"
    );

    connect(&jsonFileList, &QListWidget::itemClicked, this, &LoadGameUI::changeJsonFile);
}

void LoadGameUI::syncBoard(){
    board.setFen(boardFen);
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            tiles[row][col]->setTheme(tilesTheme);
        }
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int displayRow = reverseBoard ? row : (8 - 1 - row);
            int displayCol = reverseBoard ? col : (8 - 1 - col);
            tiles[displayRow][displayCol]->resetTitle();
            chess::Square source(chess::Rank(7 - row), chess::File(col));
            chess::Piece piece = board.at<chess::Piece>(source);
            pieces[displayRow][displayCol]->setX(500 + 50 + displayCol * newTileSize);
            pieces[displayRow][displayCol]->setY(40 + displayRow * newTileSize);
            if (piece != chess::Piece::NONE) {
                pieces[displayRow][displayCol]->resetPieceImage(piecesTheme, getPieceIcon(piece));
            }
            else {
                pieces[displayRow][displayCol]->resetPieceImage(piecesTheme, "");
            }
        }
    }
    if (board.getFen() != "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
        int x = reverseBoard ? 7 - currentMove.from().rank() : (int)currentMove.from().rank();
        int y = reverseBoard ? (int)currentMove.from().file() : 7 - currentMove.from().file();
        tiles[x][y]->toggleHighlight();
        x = reverseBoard ? 7 - currentMove.to().rank() : (int)currentMove.to().rank();
        y = reverseBoard ? (int)currentMove.to().file() : 7 - currentMove.to().file();
        tiles[x][y]->toggleHighlight();
    }
    if (board.inCheck()) {
        chess::Square king= board.kingSq(board.sideToMove());
        int x = reverseBoard ? 7 - king.rank() : (int)king.rank();
        int y = reverseBoard ? (int)king.file() : 7 - king.file();
        tiles[7 - king.rank()][king.file()]->canAttackHighlight();
    }
}

void LoadGameUI::reloadJsonFileList(){
    QDir dir(QCoreApplication::applicationDirPath());

    while (!dir.exists("savefiles")) {
        if (!dir.cdUp()) {
            // Nếu không thể cdUp() thêm nữa, tạo thư mục "savefiles" trong thư mục hiện tại
            QDir().mkpath(QCoreApplication::applicationDirPath() + "/savefiles");
            break;
        }
    }

    QString path = dir.absolutePath() + "/savefiles";
    initJsonFileList(path);
}

void LoadGameUI::initJsonFileList(const QString& path) {
    jsonFileList.clear();
    QDir dir(path);
    QStringList files = dir.entryList(QDir::Files);
    for (const QString& file : files) {
        QListWidgetItem* item = new QListWidgetItem(file);
        QString text = item->text();
        if(text.endsWith(".json")){
            text.chop(5);
            item->setText(text);
        }
        jsonFileList.addItem(item);
    }
}

// chess::uci::uciToMove(board, move);
// chess::uci::moveToUci(board, move);


void LoadGameUI::changeJsonFile(QListWidgetItem *item){
    QDir dir(QCoreApplication::applicationDirPath());

    // if(dir.absolutePath().contains("build")){
    //     dir.cdUp();
    //     dir.cdUp();
    //     dir.cdUp();
    // }

    while (!dir.exists("savefiles")) {
        if (!dir.cdUp()) {
            // Nếu không thể cdUp() thêm nữa, thoát khỏi vòng lặp
            //qDebug() << "Folder 'savefiles' không tồn tại trong bất kỳ thư mục cha nào.";
            break;
        }
    }

    rowItem = jsonFileList.row(item);
    curPathItem= dir.absolutePath() + "/savefiles/" + item->text() + ".json";

    QFile loadFile(curPathItem);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        //qDebug() << "Couldn't open load file.";
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject gameState = loadDoc.object();

    boardFen = gameState["boardFen"].toString().toStdString();
    playerSide = gameState["playerSide"].toInt();
    reverseBoard = gameState["reverseBoard"].toInt();
    currentMove = chess::uci::uciToMove(board, gameState["currentMove"].toString().toStdString());
    gameMode = gameState["gameMode"].toInt();
    gameDifficulty = gameState["gameDifficulty"].toInt();
    tilesTheme = gameState["tilesTheme"].toInt();
    piecesTheme = gameState["piecesTheme"].toInt();

    // undoFen = std::stack<std::pair<std::string, chess::Move>>();
    // QJsonArray undoMoves = gameState["undoMoves"].toArray();
    // for (const QJsonValue& value : undoMoves) {
    //     QJsonObject move = value.toObject();
    //     undoFen.push({move["fen"].toString().toStdString(), chess::Move::fromString(move["move"].toString().toStdString())});
    // }

    // redoFen = std::stack<std::pair<std::string, chess::Move>>();
    // QJsonArray redoMoves = gameState["redoMoves"].toArray();
    // for (const QJsonValue& value : redoMoves) {
    //     QJsonObject move = value.toObject();
    //     redoFen.push({move["fen"].toString().toStdString(), chess::Move::fromString(move["move"].toString().toStdString())});
    // }

    syncBoard();
}

void LoadGameUI::deleteFileJson(){
    if (curPathItem.isEmpty()) return;

    if (!QFile::exists(curPathItem)) {
        //qDebug() << "File does not exist.";
        return;
    }

    if (QFile::remove(curPathItem)) {
        //qDebug() << "Success", "Save file deleted successfully!";
        for(int row = 0; row < 8; ++row){
            for(int col = 0; col < 8; ++col){
                tiles[row][col]->resetTitle();
                pieces[row][col]->resetPieceImage(piecesTheme, "");
            }
        }
        delete jsonFileList.takeItem(rowItem);
        rowItem = -1;
        curPathItem = "";
    } else {
        //qDebug() << "Error", "Failed to delete the file.";
    }
}

LoadGameUI::~LoadGameUI() {
    // // Delete dynamically allocated chess tiles and pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete tiles[i][j];
            delete pieces[i][j];
        }
    }

    // Delete dynamically allocated QGraphicsTextItems
    delete txtPiecesTheme;
    delete txtTilesTheme;

    // Delete dynamically allocated buttons
    delete btnDeleteFile;
    delete btnPlayGame;
    delete btnBack;
}
