#include "standardpixmaptab.h"

#include <QVBoxLayout>
#include <QTreeWidget>
#include <QHeaderView>
#include <QtXml>

/******************************************************************/

StandardPixmapTab::StandardPixmapTab(QWidget *parent)
    : QWidget(parent)
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
    QTreeWidget *iconList = new QTreeWidget(this);
    iconList->setColumnCount(3);
    iconList->header()->setDefaultSectionSize(250);
    iconList->headerItem()->setText(0, tr("Constant"));
    iconList->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    iconList->headerItem()->setText(1, tr("Value"));
    iconList->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    iconList->headerItem()->setText(2, tr("Description"));
    iconList->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    iconList->setColumnWidth(1, 50);
    iconList->setAlternatingRowColors(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addWidget(iconList);

    iconList->addTopLevelItems(loadStandardPixmaps());
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
        item->setText(0, nameElem.firstChildElement("code").text().trimmed());
        item->setText(1, valueElem.firstChildElement("code").text().trimmed());
        item->setTextAlignment(1, Qt::AlignCenter);
        item->setText(2, descrElem.text().trimmed().replace("\n"," "));
        item->setIcon(0, style()->standardIcon(static_cast<QStyle::StandardPixmap>(valueElem.firstChildElement("code").text().toInt())));
        result.append(item);
    }
    return result;
}

/******************************************************************/
