#ifndef STANDARDICONSWIDGET_H
#define STANDARDICONSWIDGET_H

#include <QtWidgets>

namespace Ui {
class StandardIconsWidget;
}

class StandardIconsWidget : public QWidget
{
    Q_OBJECT

    Ui::StandardIconsWidget *ui;
public:
    explicit StandardIconsWidget(QWidget *parent = nullptr);
    ~StandardIconsWidget();

private:
    void init();
    void initActions();
    void initAnimations();
    void initApps();
    void initCategories();
    void initDevices();
    void initEmblems();
    void initEmotes();
    void initMimeTypes();
    void initPlaces();
    void initStatus();
    void initQt();
    QList<QTreeWidgetItem*> loadFromHtml(QString name);
};

#endif // STANDARDICONSWIDGET_H
