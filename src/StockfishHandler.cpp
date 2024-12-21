#include "../header/StockfishHandler.h"
#include <QDir>

StockFish::StockFish(QObject* parent) {
    engine = new QProcess(parent);

    connect(engine, SIGNAL(started()), this, SLOT(engineStarted()));
    connect(engine, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));
    connect(engine, SIGNAL(readyRead()), this, SLOT(dataAvailable()));

    QDir dir(QCoreApplication::applicationDirPath());
    // if(dir.absolutePath().contains("build")){
    //     dir.cdUp();
    //     dir.cdUp();
    //     dir.cdUp();
    // }

    while (!dir.exists("assets")) {
        if (!dir.cdUp()) {
            // Nếu không thể cdUp() thêm nữa, thoát khỏi vòng lặp
            qDebug() << "Folder 'savefiles' không tồn tại trong bất kỳ thư mục cha nào.";
            break;
        }
    }

    QString path = dir.absolutePath() + "/assets/engineAI/stockfish.exe";
    //qDebug() << path;
    engine->start(path);
}

/// =========================================================================
///                                COMMANDS
/// =========================================================================



void StockFish::send(QString cmd) {
    //qDebug() << "Sending to Stockfish : " << cmd;
    cmd.append("\n");
    engine->write(cmd.toLocal8Bit().data());
}

void StockFish::setDifficulty(int level) {
    send("setoption name Skill Level value "+QString::number(level));
}

void StockFish::setELO(int elo) {
    if(elo<1350)
        elo = 1350;
    else if(elo>2850)
        elo = 2850;
    send("setoption name UCI_LimitStrength value 1");
    send("setoption name UCI_ELO value "+QString::number(elo));
}

void StockFish::setMode(int mode){
    switch (mode) {
        case 0:
            skill = 0;
            depth = 1;
            break;
        case 1:
            skill = 5;
            depth = 10;
            break;
        case 2:
            skill = 20;
            depth = 15;
            setELO(2850);
            break;
        default:
            depth = 10;
            skill = 10;
            break;
    }
    setDifficulty(skill);
}

void StockFish::genNextMove(std::string posFen){
    send("position fen " + QString::fromStdString(posFen));
    send("go depth " + QString::number(depth));
}

/// =========================================================================
///                          SIGNALS FROM ENGINE
/// =========================================================================

void StockFish::dataAvailable() {
    QByteArray array = engine->readAll();
    QString received = QString::fromStdString(array.toStdString()).replace("\r","\n");
    for(int i=0; i<received.count("\n");i+=2) {
        QString line = received.section("\n",i,i+1).replace("\n","");
        if(line.contains("bestmove")){
            emit(bestMove(line));
        }
    }
}

/// =========================================================================
///                             PROCESS MANAGEMENT
/// =========================================================================

void StockFish::engineStarted() {
    //qDebug() << "Started";
}

void StockFish::error(QProcess::ProcessError) {
    //qDebug() << engine->error();
}

void StockFish::kill() {
    engine->terminate();
}

