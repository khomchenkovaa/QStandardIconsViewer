#include "iconfonttab.h"

#include "qfonticon.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>

/******************************************************************/

IconFontTab::IconFontTab(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUI(this);
    setupActions();
    QFontIcon::addFont(ui.editFont->text());
    updateButtons();
    updateView();
}

/******************************************************************/

void IconFontTab::doPrevious()
{
    int endCode   = ui.spinCode->value();
    int startCode = endCode - ui.spinSize->value();
    if (startCode < ui.spinCode->minimum()) {
        startCode = ui.spinCode->minimum();
    }
    ui.spinCode->setValue(startCode);
}

/******************************************************************/

void IconFontTab::doNext()
{
    int startCode = ui.spinCode->value();
    int endCode   = startCode + ui.spinSize->value();
    if (endCode < ui.spinCode->maximum()) {
        ui.spinCode->setValue(endCode);
    }
}

/******************************************************************/

void IconFontTab::updateButtons()
{
    int startCode = ui.spinCode->value();
    int endCode   = startCode + ui.spinSize->value();
    ui.btnPrevious->setEnabled(startCode > ui.spinCode->minimum());
    ui.btnNext->setEnabled(endCode < ui.spinCode->maximum());
}

/******************************************************************/

void IconFontTab::updateView()
{
    ui.iconList->clear();
    int startCode = ui.spinCode->value();
    int endCode   = startCode + ui.spinSize->value();
    for(int code = startCode; code < endCode; ++code) {
        QString text = QString("0x%1").arg(QString::number(code, 16));
        QListWidgetItem *item = new QListWidgetItem(QFontIcon::icon(code), text);
        ui.iconList->addItem(item);
    }
}

/******************************************************************/

void IconFontTab::setupActions()
{
    connect(ui.spinCode, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](){
        updateView();
        updateButtons();
    });
    connect(ui.spinSize, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](){
        updateView();
        updateButtons();
    });
    connect(ui.btnPrevious, &QPushButton::clicked,
            this,           &IconFontTab::doPrevious);
    connect(ui.btnNext,     &QPushButton::clicked,
            this,           &IconFontTab::doNext);
}

/******************************************************************/

void IconFontTab::IconFontTabUi::setupUI(QWidget *parent)
{
    editFont    = new QLineEdit(parent);
    spinCode    = new QSpinBox(parent);
    spinSize    = new QSpinBox(parent);
    btnPrevious = new QPushButton(QIcon::fromTheme("go-previous"),QString(), parent);
    btnNext     = new QPushButton(QIcon::fromTheme("go-next"),QString(), parent);
    iconList    = new QListWidget(parent);

    editFont->setText(":/ttf/fontawesome.ttf");
    editFont->setReadOnly(true);

    spinCode->setDisplayIntegerBase(16);
    spinCode->setPrefix("0x");
    spinCode->setRange(0xf000, 0xf2e0);
    spinCode->setValue(0xf030);
    spinSize->setRange(0xf, 0xff);
    spinSize->setValue(100);

    iconList->setSpacing(6);
    iconList->setWrapping(true);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Font:", parent));
    horizontalLayout->addWidget(editFont);
    horizontalLayout->addWidget(spinCode);
    horizontalLayout->addWidget(spinSize);
    horizontalLayout->addWidget(btnPrevious);
    horizontalLayout->addWidget(btnNext);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);
}
