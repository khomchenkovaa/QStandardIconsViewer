#include "qfonticonengine.h"

#include <QFont>
#include <QApplication>
#include <QPalette>
#include <QPainter>

/******************************************************/

void QFontIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    Q_UNUSED(state);
    QFont font = QFont(d.fontFamily);
    int drawSize = qRound(rect.height() * 0.8);
    font.setPixelSize(drawSize);

    QColor penColor;
    if (!d.baseColor.isValid())
        penColor = QApplication::palette("QWidget").color(QPalette::Normal,QPalette::ButtonText);
    else
        penColor = d.baseColor;

    if (mode == QIcon::Disabled)
        penColor = QApplication::palette("QWidget").color(QPalette::Disabled,QPalette::ButtonText);


    if (mode == QIcon::Selected)
        penColor = QApplication::palette("QWidget").color(QPalette::Active,QPalette::ButtonText);


    painter->save();
    painter->setPen(QPen(penColor));
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter|Qt::AlignVCenter, d.letter);

    painter->restore();
}

/******************************************************/

QPixmap QFontIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QPixmap pix(size);
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    paint(&painter, QRect(QPoint(0,0),size), mode, state);
    return pix;

}

/******************************************************/

QIconEngine *QFontIconEngine::clone() const
{
    QFontIconEngine * engine = new QFontIconEngine;
    engine->setFontFamily(d.fontFamily);
    engine->setBaseColor(d.baseColor);
    return engine;
}

/******************************************************/
