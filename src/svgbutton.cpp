#include "../header/svgbutton.h"

SvgButton::SvgButton(const QString& imagePath, QGraphicsItem* parent)
	: QGraphicsSvgItem(parent)
{
    setImageWithPath(imagePath);
}

void SvgButton::setImageWithPath(const QString& imagePath) {
	setSharedRenderer(new QSvgRenderer(imagePath, this));
	QRectF originalRect = boundingRect();
	qreal scaleX = static_cast<qreal>(50) / originalRect.width();
	qreal scaleY = static_cast<qreal>(50) / originalRect.height();
	setTransform(QTransform::fromScale(scaleX, scaleY));
}

void SvgButton::fixSize(int size) {
	QRectF originalRect = boundingRect();
	qreal scaleX = static_cast<qreal>(size) / originalRect.width();
	qreal scaleY = static_cast<qreal>(size) / originalRect.height();
	setTransform(QTransform::fromScale(scaleX, scaleY));
}

void SvgButton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setScale(0.9);
    QTimer::singleShot(50, [this]() {
        setScale(1.0);
    });
    emit clicked();
	QGraphicsSvgItem::mousePressEvent(event);
}

void SvgButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	setScale(1.1);
	QGraphicsSvgItem::hoverEnterEvent(event);
}

void SvgButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	setScale(1.0);
	QGraphicsSvgItem::hoverLeaveEvent(event);
}
