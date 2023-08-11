#ifndef ICONFONTTAB_H
#define ICONFONTTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QSpinBox;
class QListWidget;
class QPushButton;
QT_END_NAMESPACE

class IconFontTab : public QWidget
{
    Q_OBJECT
public:
    explicit IconFontTab(QWidget *parent = nullptr);

private slots:
    void doPrevious();
    void doNext();
    void updateButtons();
    void updateView();

private:
    void setupUI();

private:
    QLineEdit     *editFont;
    QSpinBox      *spinCode;
    QSpinBox      *spinSize;
    QPushButton   *btnPrevious;
    QPushButton   *btnNext;
    QListWidget   *iconList;
};

#endif // ICONFONTTAB_H
