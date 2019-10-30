#include "iconthemetab.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTreeWidget>
#include <QHeaderView>
#include <QtXml>

/******************************************************************/

IconThemeTab::IconThemeTab(QWidget *parent)
    : QWidget(parent),
      ctxName(new QComboBox(this)),
      iconList(new QTreeWidget(this))
{
    setupUi();
    updateView(ctxName->currentText());
}

/******************************************************************/

IconThemeTab::~IconThemeTab()
{

}

/******************************************************************/

void IconThemeTab::updateView(const QString &ctxName)
{
    iconList->clear();
    QList<QTreeWidgetItem *> items = loadFromHtml(ctxName);
    iconList->addTopLevelItems(items);
}

/******************************************************************/

void IconThemeTab::setupUi()
{
    ctxName->addItems( QStringList() << "actions" << "animations" << "apps"
                       << "categories" << "devices" << "emblems" << "emotes"
                       << "mimetypes" << "places" << "status");

    iconList->setColumnCount(2);
    iconList->header()->setDefaultSectionSize(200);
    iconList->headerItem()->setText(0, "Name");
    iconList->headerItem()->setText(1, "Description");

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Context:", this));
    horizontalLayout->addWidget(ctxName);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);

    connect(ctxName, SIGNAL(currentTextChanged(const QString &)),
            this, SLOT(updateView(const QString &)));
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
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, nameElem.text().trimmed());
        item->setText(1, descrElem.text().trimmed().replace("\n"," "));
        item->setIcon(0, QIcon::fromTheme(nameElem.text().trimmed()));
        result.append(item);
    }
    return result;
}

/******************************************************************/
