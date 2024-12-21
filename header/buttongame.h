#pragma once

#include "utilities.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QSoundEffect>

class ButtonGame : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    ButtonGame(const QString& text, const QRectF& rect, QGraphicsItem* parent = nullptr);
    void setBackgroundImage(const QString& imagePath); // Thêm phương thức để thiết lập hình ảnh background
    void resetBackground(void);

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QPixmap backgroundImage;
    QSoundEffect clickySound;
};

