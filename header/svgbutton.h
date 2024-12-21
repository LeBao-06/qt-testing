#pragma once

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsDropShadowEffect>
#include <QObject>
#include <QTimer>


class SvgButton : public QGraphicsSvgItem {
    Q_OBJECT
public:
	SvgButton(const QString& imagePath, QGraphicsItem* parent = nullptr);
	void setImageWithPath(const QString& imagePath);
	void fixSize(int);

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};
