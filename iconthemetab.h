#ifndef ICONTHEMETAB_H
#define ICONTHEMETAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
QT_END_NAMESPACE

class IconThemeTab : public QWidget
{
    Q_OBJECT

    struct IconThemeTabUi {
        QComboBox   *ctxName     = Q_NULLPTR;
        QPushButton *btnPrevious = Q_NULLPTR;
        QPushButton *btnNext     = Q_NULLPTR;
        QTreeWidget *iconList    = Q_NULLPTR;

        void setupUI(QWidget *parent = Q_NULLPTR);
    };

public:
    explicit IconThemeTab(QWidget *parent = nullptr);

private slots:
    void doPrevious();
    void doNext();
    void updateButtons(int index);
    void updateView(const QString &ctxName);
    void doCopy();
    void doView();
    void showCustomMenu();

private:
    void setupActions();
    QList<QTreeWidgetItem*> loadFromHtml(const QString &name);

private:
    IconThemeTabUi ui;
};

#endif // ICONTHEMETAB_H
