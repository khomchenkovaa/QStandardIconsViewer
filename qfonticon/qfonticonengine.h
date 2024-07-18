#ifndef QFONTICONENGINE_H
#define QFONTICONENGINE_H

#include <QIconEngine>

class QFontIconEngine : public QIconEngine
{
    struct QFontIconEnginePrivate {
        QString fontFamily;
        QChar   letter;
        QColor  baseColor;
    };
public:
    virtual void paint(QPainter * painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE ;
    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE;
    virtual QIconEngine* clone() const Q_DECL_OVERRIDE;

    void setFontFamily(const QString& family) {
        d.fontFamily = family;
    }

    /// define icon code using QChar or implicit using ushort ...
    void setLetter(const QChar& letter) {
        d.letter = letter;
    }

    /// You can set a base color. I don't advice. Keep system color
    void setBaseColor(const QColor& baseColor) {
        d.baseColor = baseColor;
    }

private:
    QFontIconEnginePrivate d;
};

#endif // QFONTICONENGINE_H
