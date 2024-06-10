#ifndef ICONLISTTAB_H
#define ICONLISTTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QListWidget;
class QPushButton;
QT_END_NAMESPACE

class IconListTab : public QWidget
{
    Q_OBJECT

    struct IconListTabUi {
        QLineEdit   *editName = Q_NULLPTR;
        QListWidget *iconList = Q_NULLPTR;
        QPushButton *btnDir   = Q_NULLPTR;

        void setupUI(QWidget *parent = Q_NULLPTR);
    };
public:
    explicit IconListTab(QWidget *parent = nullptr);

private slots:
    void doDirSelect();
    void updateView(const QString &dirName);
    void copyOnDoubleClick();
    void onTableCustomMenuRequested(const QPoint &pos);

private:
    void setupActions();

private:
    IconListTabUi ui;
    QString savedPath;
};

#endif // ICONLISTTAB_H
