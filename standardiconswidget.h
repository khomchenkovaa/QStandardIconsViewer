#ifndef STANDARDICONSWIDGET_H
#define STANDARDICONSWIDGET_H

#include <QtWidgets>

class StandardIconsWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit StandardIconsWidget(QWidget *parent = nullptr);
    ~StandardIconsWidget();

private:
    void setupUi();
};

#endif // STANDARDICONSWIDGET_H
