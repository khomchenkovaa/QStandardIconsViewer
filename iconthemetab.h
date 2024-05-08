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
public:
    explicit IconThemeTab(QWidget *parent = nullptr);
    ~IconThemeTab();

private slots:
    void doPrevious();
    void doNext();
    void updateButtons(int index);
    void updateView(const QString &ctxName);

    void copyOnDoubleClick();

    void onTableCustomMenuRequested(const QPoint &pos);
private:
    void setupUI();
    QList<QTreeWidgetItem*> loadFromHtml(const QString &name);

private:
    QComboBox   *ctxName;
    QPushButton *btnPrevious;
    QPushButton *btnNext;
    QTreeWidget *iconList;
};

#endif // ICONTHEMETAB_H
