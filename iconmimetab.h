#ifndef ICONMIMETAB_H
#define ICONMIMETAB_H

#include "qtreewidget.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE

class IconMimeTab : public QWidget
{
    Q_OBJECT
public:
    explicit IconMimeTab(QWidget *parent = nullptr);

private:
    void setupUI();
    QList<QTreeWidgetItem*> loadFromMimeDb();

private slots:
    void doCopy();
    void doView();
    void showCustomMenu();

private:
    QTreeWidget *iconList;
};

#endif // ICONMIMETAB_H
