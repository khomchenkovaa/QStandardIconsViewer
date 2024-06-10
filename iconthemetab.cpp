#include "iconthemetab.h"
#include "qapplication.h"
#include "qclipboard.h"
#include "qmenu.h"
#include "viewdlg.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTreeWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QtXml>

enum {
    NameColumn,
    DescriptionColumn
};

/******************************************************************/

IconThemeTab::IconThemeTab(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUI(this);
    setupActions();
    updateButtons(ui.ctxName->currentIndex());
    updateView(ui.ctxName->currentText());
}

/******************************************************************/

void IconThemeTab::doPrevious()
{
    int idx = ui.ctxName->currentIndex();
    if (idx) {
        idx--;
        ui.ctxName->setCurrentIndex(idx);
    }
}

/******************************************************************/

void IconThemeTab::doNext()
{
    int idx = ui.ctxName->currentIndex();
    if (idx < ui.ctxName->count()-1) {
        idx++;
        ui.ctxName->setCurrentIndex(idx);
    }
}

/******************************************************************/

void IconThemeTab::updateButtons(int index)
{
    ui.btnPrevious->setEnabled(index);
    ui.btnNext->setEnabled(index < ui.ctxName->count()-1);
}

/******************************************************************/

void IconThemeTab::updateView(const QString &ctxName)
{
    ui.iconList->clear();
    ui.iconList->addTopLevelItems(loadFromHtml(ctxName));
}

/******************************************************************/

void IconThemeTab::doCopy()
{
    auto curItem = ui.iconList->currentItem();
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(QString("QIcon::fromTheme(\"%1\")").arg(curItem->text(NameColumn)));
}

/******************************************************************/

void IconThemeTab::showCustomMenu()
{
    auto menu    = new QMenu(this);
    auto actView = new QAction(QIcon::fromTheme("zoom-original"), tr("View"), this);
    auto actCopy = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this);
    menu->addAction(actView);
    menu->addAction(actCopy);

    connect(actView, &QAction::triggered, this, [this](){
        auto item = ui.iconList->currentItem();
        auto icon = QIcon::fromTheme(item->text(NameColumn));
        auto text = QString("auto icon = QIcon::fromTheme(\"%1\")").arg(item->text(NameColumn));
        ViewDlg::info(this, icon, text);
    });

    connect(actCopy, &QAction::triggered,
            this,    &IconThemeTab::doCopy);

    menu->exec(QCursor::pos());
}

/******************************************************************/

void IconThemeTab::setupActions()
{
    connect(ui.ctxName,     &QComboBox::currentTextChanged,
            this,           &IconThemeTab::updateView);
    connect(ui.ctxName,     QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,           &IconThemeTab::updateButtons);
    connect(ui.btnPrevious, &QPushButton::clicked,
            this,           &IconThemeTab::doPrevious);
    connect(ui.btnNext,     &QPushButton::clicked,
            this,           &IconThemeTab::doNext);
    connect(ui.iconList,    &QWidget::customContextMenuRequested, 
            this,           &IconThemeTab::showCustomMenu);
    connect(ui.iconList,    &QTreeWidget::itemDoubleClicked,
            this,           &IconThemeTab::doCopy);
}

/******************************************************************/

QList<QTreeWidgetItem *> IconThemeTab::loadFromHtml(const QString &name)
{
    QList<QTreeWidgetItem *> result;
    QDomDocument doc("name");
    QString fileName = QString(":/tables/%1.html").arg(name);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open for read" << fileName;
        return result;
    }
    QString errMsg;
    int errLine = -1;
    int errColumn = -1;
    if (!doc.setContent(&file, false, &errMsg, &errLine, &errColumn)) {
        qDebug() << "Error reading document\n" << errMsg << "\nline:" << errLine << ", column:" << errColumn;
        file.close();
        return result;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomElement htmlElem = doc.firstChildElement("html");
    if (htmlElem.isNull()) {
        qDebug() << "No html tag found";
        return result;
    }
    QDomElement bodyElem = htmlElem.firstChildElement("body");
    if (bodyElem.isNull()) {
        qDebug() << "No body tag found";
        return result;
    }
    QDomElement tableElem = bodyElem.firstChildElement("table");
    if (tableElem.isNull()) {
        qDebug() << "No table tag found";
        return result;
    }
    QDomElement tbodyElem = tableElem.firstChildElement("tbody");
    if (tbodyElem.isNull()) {
        qDebug() << "No tbody tag found";
        return result;
    }
    QDomElement trElem = tbodyElem.firstChildElement("tr");
    for (; !trElem.isNull(); trElem = trElem.nextSiblingElement("tr")) {
        QDomElement nameElem = trElem.firstChildElement("td");
        QDomElement descrElem = trElem.lastChildElement("td");
        auto item = new QTreeWidgetItem();
        item->setText(NameColumn, nameElem.text().trimmed());
        item->setIcon(NameColumn, QIcon::fromTheme(nameElem.text().trimmed()));
        item->setText(DescriptionColumn, descrElem.text().trimmed().replace("\n"," "));
        result.append(item);
    }
    return result;
}

/******************************************************************/

void IconThemeTab::IconThemeTabUi::setupUI(QWidget *parent)
{
    ctxName     = new QComboBox(parent);
    btnPrevious = new QPushButton(QIcon::fromTheme("go-previous"),QString(), parent);
    btnNext     = new QPushButton(QIcon::fromTheme("go-next"),QString(), parent);
    iconList    = new QTreeWidget(parent);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ctxName->sizePolicy().hasHeightForWidth());
    ctxName->setSizePolicy(sizePolicy);
    ctxName->addItems( QStringList() << "actions" << "animations" << "apps"
                       << "categories" << "devices" << "emblems" << "emotes"
                       << "mimetypes" << "places" << "status");

    btnPrevious->setToolTip("Previous");
    btnPrevious->setMaximumSize(QSize(27, 27));

    btnNext->setToolTip("Next");
    btnNext->setMaximumSize(QSize(27, 27));

    iconList->setColumnCount(2);
    iconList->header()->setDefaultSectionSize(200);
    iconList->headerItem()->setText(NameColumn, "Name");
    iconList->headerItem()->setText(DescriptionColumn, "Description");
    iconList->setAlternatingRowColors(true);
    iconList->setContextMenuPolicy(Qt::CustomContextMenu);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Context:", parent));
    horizontalLayout->addWidget(ctxName);
    horizontalLayout->addWidget(btnPrevious);
    horizontalLayout->addWidget(btnNext);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);
}
