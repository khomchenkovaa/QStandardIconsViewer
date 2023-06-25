#ifndef ICONMIMETAB_H
#define ICONMIMETAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE

class IconMimeTab : public QWidget
{
    Q_OBJECT
public:
    explicit IconMimeTab(QWidget *parent = nullptr);
    ~IconMimeTab();

private:
    void setupUI();
    QList<QTreeWidgetItem*> loadFromMimeDb();
};

#endif // ICONMIMETAB_H
