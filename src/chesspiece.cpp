#include "../header/chesspiece.h"
#include <QDebug>
#include <QFile>

ChessPiece::ChessPiece(const QString& imagePath, QGraphicsItem* parent)
    : QGraphicsSvgItem(parent), 
    imagePath(imagePath) 
{
    resetPieceImage(0, imagePath);
}

void ChessPiece::resetPieceImage(const int theme, const QString& pieceType) {
	imagePath = pieceType;    
    if (pieceType.isEmpty()) {
        // If the path is empty, set the renderer to a null/empty renderer
        setSharedRenderer(new QSvgRenderer());
        return;
    }

    imagePath = ":/assets/images/Theme_" + QString::number(theme) + "/" + pieceType;

    // Load the SVG file directly into QGraphicsSvgItem
    setSharedRenderer(new QSvgRenderer(imagePath, this));
    //setElementId("");  // Optional: You can specify an ID for individual elements within the SVG

    QRectF originalRect = boundingRect();

    qreal scaleX = static_cast<qreal>(sizePiece) / originalRect.width();
    qreal scaleY = static_cast<qreal>(sizePiece) / originalRect.height();

    // Apply the scaling (proportional or non-proportional as desired)
    setTransform(QTransform::fromScale(scaleX, scaleY));
}

void ChessPiece::setImageWithPath(const QString& imagePath) {
    setSharedRenderer(new QSvgRenderer(imagePath, this));
    setTransform(QTransform::fromScale(40, 40));
}

QString ChessPiece::currentImage() const {
	return imagePath;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	emit clicked();
	QGraphicsSvgItem::mousePressEvent(event);
}
