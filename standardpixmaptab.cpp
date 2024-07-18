#include "standardpixmaptab.h"
#include "viewdlg.h"

#include <QApplication>
#include <QClipboard>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QHeaderView>
#include <QtXml>
#include <QMenu>
#include <QPoint>
#include <QMouseEvent>

enum {
    ConstantColumn,
    ValueColumn,
    DescriptionColumn
};

/******************************************************************/

StandardPixmapTab::StandardPixmapTab(QWidget *parent)
    : QWidget(parent),
    iconList(Q_NULLPTR)
{
    setupUI();
}

/******************************************************************/

void StandardPixmapTab::setupUI()
{
    iconList = new QTreeWidget(this);
    iconList->setColumnCount(3);
    iconList->header()->setDefaultSectionSize(250);
    iconList->headerItem()->setText(ConstantColumn, tr("Constant"));
    iconList->headerItem()->setTextAlignment(ConstantColumn, Qt::AlignCenter);
    iconList->headerItem()->setText(ValueColumn, tr("Value"));
    iconList->headerItem()->setTextAlignment(ValueColumn, Qt::AlignCenter);
    iconList->headerItem()->setText(DescriptionColumn, tr("Description"));
    iconList->headerItem()->setTextAlignment(DescriptionColumn, Qt::AlignCenter);
    iconList->setColumnWidth(ValueColumn, 50);
    iconList->setAlternatingRowColors(true);
    iconList->addTopLevelItems(loadStandardPixmaps());
    iconList->setContextMenuPolicy(Qt::CustomContextMenu);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addWidget(iconList);

    connect(iconList, &QWidget::customContextMenuRequested,
            this,     &StandardPixmapTab::showCustomMenu);
    connect(iconList, &QTreeWidget::itemDoubleClicked,
            this,     &StandardPixmapTab::doView);
}

/******************************************************************/

QList<QTreeWidgetItem *> StandardPixmapTab::loadStandardPixmaps()
{
    QList<QTreeWidgetItem *> result;
    QDomDocument doc("name");
    QString fileName = QString(":/tables/qt.html");
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
    QDomElement trElem = tableElem.firstChildElement("tr");
    for (; !trElem.isNull(); trElem = trElem.nextSiblingElement("tr")) {
        QDomElement nameElem = trElem.firstChildElement("td");
        if(nameElem.isNull()) continue;
        QDomElement valueElem = nameElem.nextSiblingElement("td");
        QDomElement descrElem = valueElem.nextSiblingElement("td");
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(ConstantColumn, nameElem.firstChildElement("code").text().trimmed());
        item->setText(ValueColumn, valueElem.firstChildElement("code").text().trimmed());
        item->setTextAlignment(ValueColumn, Qt::AlignCenter);
        item->setText(DescriptionColumn, descrElem.text().trimmed().replace("\n"," "));
        item->setIcon(ConstantColumn, style()->standardIcon(static_cast<QStyle::StandardPixmap>(valueElem.firstChildElement("code").text().toInt())));
        result.append(item);
    }
    return result;
}

/******************************************************************/

void StandardPixmapTab::doCopy()
{
    auto curItem = iconList->currentItem();
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(ConstantColumn)));
}

/******************************************************************/

void StandardPixmapTab::doView()
{
    auto curItem = iconList->currentItem();
    auto icon    = style()->standardIcon(static_cast<QStyle::StandardPixmap>(curItem->text(ValueColumn).toInt()));
    auto text    = QString("auto icon = style()->standardIcon(%1);").arg(curItem->text(ConstantColumn));
    ViewDlg::info(this, icon, text);
}

/******************************************************************/

void StandardPixmapTab::showCustomMenu()
{
    auto menu    = new QMenu(this);
    auto actView = new QAction(QIcon::fromTheme("zoom-original"), tr("View"), this);
    auto actCopy = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this);
    menu->addAction(actView);
    menu->addAction(actCopy);

    connect(actView, &QAction::triggered,
            this,    &StandardPixmapTab::doView);
    connect(actCopy, &QAction::triggered,
            this,    &StandardPixmapTab::doCopy);

    menu->exec(QCursor::pos());
}

/******************************************************************/
