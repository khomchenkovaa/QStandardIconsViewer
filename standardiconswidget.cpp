#include "standardiconswidget.h"
#include "ui_standardiconswidget.h"

#include <QtXml>

/******************************************************************/

StandardIconsWidget::StandardIconsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandardIconsWidget)
{
    ui->setupUi(this);
    init();
}

/******************************************************************/

StandardIconsWidget::~StandardIconsWidget()
{
    delete ui;
}

/******************************************************************/

void StandardIconsWidget::init()
{
    initActions();
    initAnimations();
    initApps();
    initCategories();
    initDevices();
    initEmblems();
    initEmotes();
    initMimeTypes();
    initPlaces();
    initStatus();
    initQt();
}

/******************************************************************/

void StandardIconsWidget::initActions()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("actions");
    ui->treeActions->addTopLevelItems(items);
}

/******************************************************************/

void StandardIconsWidget::initAnimations()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("animations");
    ui->treeAnimations->addTopLevelItems(items);
}

/******************************************************************/

void StandardIconsWidget::initApps()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("apps");
    ui->treeApplications->addTopLevelItems(items);
}

/******************************************************************/

void StandardIconsWidget::initCategories()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("categories");
    ui->treeCategories->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initDevices()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("devices");
    ui->treeDevices->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initEmblems()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("emblems");
    ui->treeEmblems->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initEmotes()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("emotes");
    ui->treeEmotes->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initMimeTypes()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("mimetypes");
    ui->treeMimeTypes->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initPlaces()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("places");
    ui->treePlaces->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initStatus()
{
    QList<QTreeWidgetItem *> items = loadFromHtml("status");
    ui->treeStatus->addTopLevelItems(items);

}

/******************************************************************/

void StandardIconsWidget::initQt()
{
    QList<QTreeWidgetItem *> result;
    QDomDocument doc("name");
    QString fileName = QString(":/tables/qt.html");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open for read" << fileName;
        return;
    }
    QString errMsg;
    int errLine = -1;
    int errColumn = -1;
    if (!doc.setContent(&file, false, &errMsg, &errLine, &errColumn)) {
        qDebug() << "Error reading document\n" << errMsg << "\nline:" << errLine << ", column:" << errColumn;
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomElement htmlElem = doc.firstChildElement("html");
    if (htmlElem.isNull()) {
        qDebug() << "No html tag found";
        return;
    }
    QDomElement bodyElem = htmlElem.firstChildElement("body");
    if (bodyElem.isNull()) {
        qDebug() << "No body tag found";
        return;
    }
    QDomElement tableElem = bodyElem.firstChildElement("table");
    if (tableElem.isNull()) {
        qDebug() << "No table tag found";
        return;
    }
    QDomElement trElem = tableElem.firstChildElement("tr");
    for (; !trElem.isNull(); trElem = trElem.nextSiblingElement("tr")) {
        QDomElement nameElem = trElem.firstChildElement("td");
        if(nameElem.isNull()) continue;
        QDomElement valueElem = nameElem.nextSiblingElement("td");
        QDomElement descrElem = valueElem.nextSiblingElement("td");
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, nameElem.firstChildElement("code").text().trimmed());
        item->setText(1, descrElem.text().trimmed().replace("\n"," "));
        item->setIcon(0, style()->standardIcon(static_cast<QStyle::StandardPixmap>(valueElem.firstChildElement("code").text().toInt())));
        result.append(item);
    }
    ui->treeQt->addTopLevelItems(result);
}

/******************************************************************/

QList<QTreeWidgetItem *> StandardIconsWidget::loadFromHtml(QString name)
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
