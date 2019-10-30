#include "standardiconswidget.h"

#include "iconthemetab.h"
#include "standardpixmaptab.h"
#include "iconlisttab.h"

/******************************************************************/

StandardIconsWidget::StandardIconsWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setupUi();
}

/******************************************************************/

StandardIconsWidget::~StandardIconsWidget()
{
}

/******************************************************************/

void StandardIconsWidget::setupUi()
{
    setWindowTitle("Standard Icon Viewer");
    resize(977, 637);
    addTab(new IconThemeTab(this), "freedesktop.org icons");
    addTab(new StandardPixmapTab(this), "Qt's Standard Pixmap");
    addTab(new IconListTab(this), "Files");
}

/******************************************************************/
