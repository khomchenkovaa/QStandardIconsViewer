/*
MIT License

Copyright (c) 2017 Sacha Schutz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef QFONTICON_H
#define QFONTICON_H

#include <QObject>
#include <QColor>

class QFontIcon : public QObject
{
    Q_OBJECT

public:
    explicit QFontIcon(QObject *parent = 0);

    /// @return added fonts
    const QStringList& families() const;

public: // static
    /// add Font. By default, the first one is used
    static bool addFont(const QString& filename);

    /// main methods. Return icons from code
    static QIcon icon(const QChar& code, const QColor& baseColor = QColor(), const QString& family = QString());

protected:
    void addFamily(const QString& family);

private:
    QStringList fontFamilies;
};

#define FIcon(code) QFontIcon::icon(code)

#endif // QFONTICON_H
