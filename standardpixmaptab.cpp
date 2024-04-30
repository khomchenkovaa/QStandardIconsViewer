#include "standardpixmaptab.h"
#include "infodlgmbox.h"
#include "qapplication.h"
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

StandardPixmapTab::~StandardPixmapTab()
{

}

/******************************************************************/

void StandardPixmapTab::setupUI()
{
    iconList = new QTreeWidget(this);
    iconList->setColumnCount(3);
    iconList->header()->setDefaultSectionSize(250);
    iconList->headerItem()->setText(0, tr("Constant"));
    iconList->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    iconList->headerItem()->setText(1, tr("Value"));
    iconList->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    iconList->headerItem()->setText(2, tr("Description"));
    iconList->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    iconList->setColumnWidth(3, 50);
    iconList->setAlternatingRowColors(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addWidget(iconList);

    iconList->addTopLevelItems(loadStandardPixmaps());

    iconList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(iconList,&QWidget::customContextMenuRequested, this, &StandardPixmapTab::onTableCustomMenuRequested);
    //connect(iconList,&StandardPixmapTab::copyOnDoubleClick,this,&QTreeWidget::itemSelectionChanged);
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

void QWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(ConstantColumn)));
        qDebug() << "Копировать" << curItem->text(ConstantColumn);
    }
}

void StandardPixmapTab::copyOnDoubleClick(const QPoint &pos)
{


    connect(mouseDoubleClickEvent(event), &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(ConstantColumn)));
        qDebug() << "Копировать" << curItem->text(ConstantColumn);
    });
}


void StandardPixmapTab::onTableCustomMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);
    QAction * showToCopy = new QAction("Показать", this);
    QAction * copyOnClick = new QAction("Копировать", this);
    menu->addAction(showToCopy);
    menu->addAction(copyOnClick);

    connect(showToCopy, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QIcon icon = style()->standardIcon(static_cast<QStyle::StandardPixmap>(curItem->text(ValueColumn).toInt()));
        QString text = QString("style()->standardIcon(%1)").arg(curItem->text(ConstantColumn));
        InfoDlgMbox::info(this, icon, text);
        qDebug() << "Показать" << text;
    });

    connect(copyOnClick, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(ConstantColumn)));
        qDebug() << "Копировать" << curItem->text(ConstantColumn);
    });

    menu->exec(QCursor::pos());
}
//works

/******************************************************************/
