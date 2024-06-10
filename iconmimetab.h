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
    void copyOnDoubleClick();

    void onTableCustomMenuRequestedMime(const QPoint &pos);

private:
    //QTreeWidget *IconListMime;
    QTreeWidget *iconList;
};

#endif // ICONMIMETAB_H
