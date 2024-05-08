#include "iconmimetab.h"
#include "qclipboard.h"
#include "qdebug.h"
#include "infodlgmbox.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>

#include <QMimeDatabase>
#include <QMenu>
#include <QPoint>
#include <QGuiApplication>
/******************************************************************/

enum {
    NameColumn,
    CommentColumn,
    FilterColumn,
    ParentColumn

};
IconMimeTab::IconMimeTab(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

/******************************************************************/

IconMimeTab::~IconMimeTab()
{

}

/******************************************************************/

void IconMimeTab::setupUI()
{
    iconList = new QTreeWidget(this);
    iconList->setColumnCount(4);
    iconList->header()->setDefaultSectionSize(200);
    iconList->headerItem()->setText(NameColumn, "Name");
    iconList->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    iconList->headerItem()->setText(CommentColumn, "Comment");
    iconList->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    iconList->headerItem()->setText(FilterColumn, "Filter");
    iconList->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    iconList->headerItem()->setText(ParentColumn, "Parent");
    iconList->headerItem()->setTextAlignment(3, Qt::AlignCenter);
    iconList->setAlternatingRowColors(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addWidget(iconList);

    iconList->addTopLevelItems(loadFromMimeDb());

    iconList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(iconList,&QWidget::customContextMenuRequested, this, &IconMimeTab::onTableCustomMenuRequestedMime);
    connect(iconList,&QTreeWidget::itemDoubleClicked,this,&IconMimeTab::copyOnDoubleClick);
}

/******************************************************************/

QList<QTreeWidgetItem *> IconMimeTab::loadFromMimeDb()
{
    QList<QTreeWidgetItem *> result;

    QMimeDatabase mimeDatabase;
    QList<QMimeType> allTypes = mimeDatabase.allMimeTypes();
    std::sort(allTypes.begin(), allTypes.end(),
          [](QMimeType a, QMimeType b) -> bool { return a.name() < b.name(); });

    for (auto mime : allTypes) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, mime.name());
        item->setText(1, mime.comment());
        item->setText(2, mime.filterString());
        item->setText(3, mime.parentMimeTypes().join(", "));
        QString iconName = mime.iconName();
        if (iconName.isEmpty()) iconName = mime.genericIconName();
        if (!iconName.isEmpty()) {
            item->setIcon(0, QIcon::fromTheme(iconName));
        }
        result.append(item);
    }
    return result;
}

void IconMimeTab::copyOnDoubleClick()
{
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("%1").arg(curItem->text(NameColumn)));
        qDebug() << "Копировать" << curItem->text(NameColumn);

}

void IconMimeTab::onTableCustomMenuRequestedMime(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);
    QAction * showToCopy = new QAction("Показать", this);
    QAction * copyOnClick = new QAction("Копировать", this);
    menu->addAction(showToCopy);
    menu->addAction(copyOnClick);

    connect(showToCopy, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QIcon icon = style()->standardIcon(static_cast<QStyle::StandardPixmap>(curItem->text(NameColumn).toInt()));
        QString text = QString("%1").arg(curItem->text(NameColumn));
        InfoDlgMbox::info(this, icon, text);
        qDebug() << "Показать" << text;
    });

    connect(copyOnClick, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem();
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(QString("%1").arg(curItem->text(NameColumn)));
        qDebug() << "Копировать" << curItem->text(NameColumn);
    });

    menu->exec(QCursor::pos());
}
//not works
/******************************************************************/
