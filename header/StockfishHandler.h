#pragma once

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>


class StockFish : public QObject {
    Q_OBJECT
public:
    StockFish(QObject *parent);

    void send(QString cmd);
    void setDifficulty(int level);
    void setMode(int);
    void setELO(int elo);
    void genNextMove(std::string);
    void kill();
signals:
    void bestMove(QString move);
private slots:
    void dataAvailable();
    void engineStarted();
    void error(QProcess::ProcessError);
private :
    QProcess *engine;
    int skill = 0, depth = 1;
};
