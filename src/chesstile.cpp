#include "../header/chesstile.h"
#include <QLinearGradient>
#include <iostream>

ChessTile::ChessTile(int row, int col) :
    QGraphicsRectItem(col* tileSize, row* tileSize, tileSize, tileSize),
    isHighlighted(false)
{
    setData(0, row);
    setData(1, col);
    QPen transparentPen(Qt::transparent);
    setPen(transparentPen);
    setBrush(QColor(1, 2, 3));
}

void ChessTile::toggleHighlight() {
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
	QColor mixColor = mixColors(darkColor, Qt::yellow, ratioMixColor);
    gradient.setColorAt(0, mixColor.lighter());
    gradient.setColorAt(1, mixColor);
    setBrush(gradient);
}

void ChessTile::canMoveHighlight() {
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
	QColor mixColor = mixColors(darkColor, Qt::green, ratioMixColor);
    gradient.setColorAt(0, mixColor.lighter());
    gradient.setColorAt(1, mixColor);
    setBrush(gradient);
}

void ChessTile::canAttackHighlight() {
	QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
	QColor mixColor = mixColors(darkColor, Qt::red, ratioMixColor);
	gradient.setColorAt(0, mixColor.lighter());
	gradient.setColorAt(1, mixColor);
	//gradient.setColorAt(0, QColor(Qt::red).lighter());
	//gradient.setColorAt(1, Qt::red);
	setBrush(gradient);
}

void ChessTile::setTheme(int index) {
    switch (index) {
    case 0: // Classic
        lightColor = Qt::white; // Light gray
        darkColor = Qt::gray;
        break;
    case 1: // Modern
        lightColor = QColor(222, 184, 135); // Light brown
        darkColor = QColor(139, 69, 19); // Dark brown
        break;
    case 2: // High Contrast
        lightColor = QColor(235, 236, 208); // White
        darkColor = QColor(115, 149, 82); // Green
        break;
    case 3: // Forest Green
        lightColor = QColor(144, 238, 144); // Light green
        darkColor = QColor(0, 100, 0); // Dark green
        break;
    case 4: // Ocean Blue
        lightColor = QColor(173, 216, 230); // Light blue
        darkColor = QColor(25, 25, 112); // Navy blue
        break;
    case 5: // Warm Tones
        lightColor = QColor(255, 165, 0); // Light orange
        darkColor = QColor(178, 34, 34); // Dark red
        break;
    case 6: // Monochrome
        lightColor = QColor(176, 224, 230); // Light cyan
        darkColor = QColor(72, 61, 139); // Dark slate blue
        break;
    case 7: // Retro
        lightColor = QColor(255, 20, 147); // Bright pink
        darkColor = QColor(0, 0, 205); // Medium blue
        break;
    case 8: // Minimalist
        lightColor = QColor(245, 245, 220); // Beige
        darkColor = QColor(105, 105, 105); // Dim gray
        break;
    default:
        return;
    }
	if ((data(0).toInt() + data(1).toInt()) % 2 == 0) {
		setBrush(lightColor);
		originalColor = lightColor;
	}
    else {
        setBrush(darkColor);
        originalColor = darkColor;
    }
}

void ChessTile::resetTitle() {
    setBrush(originalColor);
    setPen(QPen(Qt::transparent));
}

QColor ChessTile::mixColors(QColor color1, QColor color2, float ratio){
    int red = static_cast<int>(color1.red() * (1 - ratio) + color2.red() * ratio);
    int green = static_cast<int>(color1.green() * (1 - ratio) + color2.green() * ratio);
    int blue = static_cast<int>(color1.blue() * (1 - ratio) + color2.blue() * ratio);
    return QColor(red, green, blue);
}
