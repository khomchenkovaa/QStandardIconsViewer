#include "iconthemetab.h"
#include "qapplication.h"
#include "qclipboard.h"
#include "qmenu.h"
#include "infodlgmbox.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTreeWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QtXml>

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

void IconThemeTab::copyOnDoubleClick()
{
    auto curItem = iconList->currentItem();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(0)));
    qDebug() << "Копировать" << curItem->text(0);

}

void IconThemeTab::onTableCustomMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);
    QAction * showToCopy = new QAction("Показать", this);
    QAction * copyOnClick = new QAction("Копировать", this);
    menu->addAction(showToCopy);
    menu->addAction(copyOnClick);

    connect(showToCopy, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        //QIcon icon = style()->standardIcon(static_cast<QStyle::StandardPixmap>(curItem->text(ValueColumn).toInt()));
        QString text = QString("style()->standardIcon(%1)").arg(curItem->text(0));
        InfoDlgMbox::info(this, text);
        qDebug() << "Показать" << text;
    });

    connect(copyOnClick, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("style()->standardIcon(%1)").arg(curItem->text(0)));
        qDebug() << "Копировать" << curItem->text(0);
    });

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
            this,           &IconThemeTab::onTableCustomMenuRequested);
    connect(iconList,       &QTreeWidget::itemDoubleClicked,
            this,           &IconThemeTab::copyOnDoubleClick);
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
    iconList->headerItem()->setText(0, "Name");
    iconList->headerItem()->setText(1, "Description");
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
