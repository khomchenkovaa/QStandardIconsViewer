#include "standardiconswidget.h"

#include "iconthemetab.h"
#include "iconmimetab.h"
#include "standardpixmaptab.h"
#include "iconlisttab.h"
#include "iconfonttab.h"

/******************************************************************/

StandardIconsWidget::StandardIconsWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setupUI();
}

/******************************************************************/

StandardIconsWidget::~StandardIconsWidget()
{
}

/******************************************************************/

void StandardIconsWidget::setupUI()
{
    setWindowTitle("Standard Icon Viewer");
    resize(977, 637);
    addTab(new IconThemeTab(this), "freedesktop.org icons");
    addTab(new IconMimeTab(this), "QMimeDatabase icons");
    addTab(new StandardPixmapTab(this), "Qt's Standard Pixmap");
    addTab(new IconListTab(this), "Files");
    addTab(new IconFontTab(this), "Fonts");
}

/******************************************************************/
