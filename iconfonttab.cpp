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
    : QWidget(parent),
      editFont(new QLineEdit(this)),
      spinCode(new QSpinBox(this)),
      spinSize(new QSpinBox(this)),
      btnPrevious(new QPushButton(QIcon::fromTheme("go-previous"),QString(), this)),
      btnNext(new QPushButton(QIcon::fromTheme("go-next"),QString(), this)),
      iconList(new QListWidget(this))
{
    setupUI();
    QFontIcon::addFont(editFont->text());
    updateButtons();
    updateView();
}

/******************************************************************/

void IconFontTab::doPrevious()
{
    int endCode   = spinCode->value();
    int startCode = endCode - spinSize->value();
    if (startCode < spinCode->minimum()) {
        startCode = spinCode->minimum();
    }
    spinCode->setValue(startCode);
}

/******************************************************************/

void IconFontTab::doNext()
{
    int startCode = spinCode->value();
    int endCode   = startCode + spinSize->value();
    if (endCode < spinCode->maximum()) {
        spinCode->setValue(endCode);
    }
}

/******************************************************************/

void IconFontTab::updateButtons()
{
    int startCode = spinCode->value();
    int endCode   = startCode + spinSize->value();
    btnPrevious->setEnabled(startCode > spinCode->minimum());
    btnNext->setEnabled(endCode < spinCode->maximum());
}

/******************************************************************/

void IconFontTab::updateView()
{
    iconList->clear();
    int startCode = spinCode->value();
    int endCode   = startCode + spinSize->value();
    for(int code = startCode; code < endCode; ++code) {
        QString text = QString("0x%1").arg(QString::number(code, 16));
        QListWidgetItem *item = new QListWidgetItem(QFontIcon::icon(code), text);
        iconList->addItem(item);
    }
}

/******************************************************************/

void IconFontTab::setupUI()
{
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
    horizontalLayout->addWidget(new QLabel("Font:", this));
    horizontalLayout->addWidget(editFont);
    horizontalLayout->addWidget(spinCode);
    horizontalLayout->addWidget(spinSize);
    horizontalLayout->addWidget(btnPrevious);
    horizontalLayout->addWidget(btnNext);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);

    connect(spinCode, SIGNAL(valueChanged(int)),
            this, SLOT(updateView()));
    connect(spinCode, SIGNAL(valueChanged(int)),
            this, SLOT(updateButtons()));
    connect(spinSize, SIGNAL(valueChanged(int)),
            this, SLOT(updateView()));
    connect(spinSize, SIGNAL(valueChanged(int)),
            this, SLOT(updateButtons()));
    connect(btnPrevious, SIGNAL(clicked()),
            this, SLOT(doPrevious()));
    connect(btnNext, SIGNAL(clicked()),
            this, SLOT(doNext()));
}

/******************************************************************/
