#ifndef STANDARDICONSWIDGET_H
#define STANDARDICONSWIDGET_H

#include <QtWidgets>

class StandardIconsWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit StandardIconsWidget(QWidget *parent = nullptr);

private:
    void setupUI();
};

#endif // STANDARDICONSWIDGET_H
