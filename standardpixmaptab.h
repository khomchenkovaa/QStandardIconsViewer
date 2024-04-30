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
    ~StandardPixmapTab();

private:
    void setupUI();
    QList<QTreeWidgetItem*> loadStandardPixmaps();
private slots:
    void copyOnDoubleClick(const QPoint &pos);

    void onTableCustomMenuRequested(const QPoint &pos);

private:
    QTreeWidget *iconList;
};

#endif // STANDARDPIXMAPTAB_H
