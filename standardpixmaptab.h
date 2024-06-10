 #ifndef STANDARDPIXMAPTAB_H
#define STANDARDPIXMAPTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class StandardPixmapTab : public QWidget
{
    Q_OBJECT
public:
    explicit StandardPixmapTab(QWidget *parent = nullptr);

private:
    void setupUI();
    QList<QTreeWidgetItem*> loadStandardPixmaps();
private slots:
    void copyOnDoubleClick();

    void onTableCustomMenuRequested(const QPoint &pos);
private:
    QTreeWidget *iconList;


};

#endif // STANDARDPIXMAPTAB_H
