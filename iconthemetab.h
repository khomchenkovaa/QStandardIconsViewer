#ifndef ICONTHEMETAB_H
#define ICONTHEMETAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class IconThemeTab : public QWidget
{
    Q_OBJECT
public:
    explicit IconThemeTab(QWidget *parent = nullptr);
    ~IconThemeTab();

private slots:
    void updateView(const QString &ctxName);

private:
    void setupUi();
    QList<QTreeWidgetItem*> loadFromHtml(const QString &name);

private:
    QComboBox   *ctxName;
    QTreeWidget *iconList;
};

#endif // ICONTHEMETAB_H
