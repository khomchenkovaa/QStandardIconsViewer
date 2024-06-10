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

    struct IconFontTabUi {
        QLineEdit   *editFont    = Q_NULLPTR;
        QSpinBox    *spinCode    = Q_NULLPTR;
        QSpinBox    *spinSize    = Q_NULLPTR;
        QPushButton *btnPrevious = Q_NULLPTR;
        QPushButton *btnNext     = Q_NULLPTR;
        QListWidget *iconList    = Q_NULLPTR;

        void setupUI(QWidget *parent = Q_NULLPTR);
    };
public:
    explicit IconFontTab(QWidget *parent = nullptr);

private slots:
    void doPrevious();
    void doNext();
    void updateButtons();
    void updateView();
    void doCopy();
    void showCustomMenu();

private:
    void setupActions();

private:
    IconFontTabUi ui;
};

#endif // ICONFONTTAB_H
