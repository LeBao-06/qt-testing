#include "../header/buttongame.h"
#include <QBrush>
#include <QPen>
#include <QFont>

ButtonGame::ButtonGame(const QString& text, const QRectF& rect, QGraphicsItem* parent)
    : QGraphicsRectItem(rect, parent) {
    setAcceptHoverEvents(true);
    setPen(Qt::NoPen);
    // Thêm văn bản vào button
    QGraphicsTextItem* label = new QGraphicsTextItem(text, this);
    label->setFont(QFont("Courier New", 14));
    label->setDefaultTextColor(Qt::white);
    label->setPos(rect.width() / 2 - label->boundingRect().width() / 2,
                  rect.height() / 2 - label->boundingRect().height() / 2); // Căn giữa văn bản
    setBackgroundImage(":/assets/buttons/button_1.png");
    clickySound.setSource(QUrl::fromLocalFile(":/assets/soundeffect/clicky.wav"));
    clickySound.setVolume(volumeEffect);
}

void ButtonGame::resetBackground(void) {
    setBrush(QBrush(backgroundImage.scaled(rect().size().toSize())));
}

/*....................Set Image Background....................*/
void ButtonGame::setBackgroundImage(const QString& imagePath) {
    backgroundImage.load(imagePath); // Tải hình ảnh
    setBrush(QBrush(backgroundImage.scaled(rect().size().toSize()))); // Thiết lập hình ảnh làm background
}
///////////////////////////////////////////////////////////////


/*....................Mouse Event....................*/
void ButtonGame::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    clickySound.setVolume(volumeEffect);
    clickySound.play();
    setScale(1.0);
    emit clicked();
    QGraphicsRectItem::mousePressEvent(event);
}

void ButtonGame::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setScale(1.05);
    QGraphicsRectItem::hoverEnterEvent(event);
}

void ButtonGame::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    setScale(1.0);
    QGraphicsRectItem::hoverLeaveEvent(event);
}
//////////////////////////////////////////////////////
