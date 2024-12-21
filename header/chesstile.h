#pragma once

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QGraphicsDropShadowEffect>

constexpr int tileSize = 60;  // Kích thước mỗi ô vuông
constexpr int boardSize = 8;  // Số ô vuông trên mỗi hàng/cột

class ChessTile : public QGraphicsRectItem {
public:
    ChessTile(int, int);
    void toggleHighlight();
    void canMoveHighlight();
	void canAttackHighlight();
    void setTheme(int);
    void resetTitle();
    static QColor mixColors(QColor, QColor, float);

protected:

private:
    QColor lightColor, darkColor, originalColor;
    bool isHighlighted;
    double ratioMixColor = 0.8;
};
