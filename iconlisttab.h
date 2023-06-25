#ifndef ICONLISTTAB_H
#define ICONLISTTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QListWidget;
QT_END_NAMESPACE

class IconListTab : public QWidget
{
    Q_OBJECT
public:
    explicit IconListTab(QWidget *parent = nullptr);
    ~IconListTab();

private slots:
    void doDirSelect();
    void updateView(const QString &dirName);

private:
    void setupUI();

private:
    QLineEdit   *editName;
    QListWidget *iconList;
};

#endif // ICONLISTTAB_H
