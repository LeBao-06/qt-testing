#pragma once

#include <QtSvgWidgets/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QObject>
#include <QDebug>
#include <QFile>


class ChessPiece : public QGraphicsSvgItem {
    Q_OBJECT
public:
    ChessPiece(const QString& imagePath, QGraphicsItem* parent = nullptr);
    void resetPieceImage(const int, const QString& imagePath);
	void setImageWithPath(const QString& imagePath);
    void setSizePiece(int size) { sizePiece = size;}
    QString currentImage() const; 

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
	int sizePiece = 60;
	QString imagePath;
};