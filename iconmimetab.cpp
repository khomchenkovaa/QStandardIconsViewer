#include "iconmimetab.h"
#include "qdebug.h"
#include "infodlgmbox.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>

#include <QMimeDatabase>
#include <QMenu>
#include <QPoint>
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
    QTreeWidget *iconList = new QTreeWidget(this);
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

}

void IconMimeTab::onTableCustomMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);
    QAction * copyDevice = new QAction("Копировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);
    menu->addAction(copyDevice);
    menu->addAction(deleteDevice);

    connect(copyDevice, &QAction::triggered, this, [this](){
        auto curItem = IconListMime->currentItem();
        //QIcon icon = style()->standardIcon(static_cast<QStyle::StandardPixmap>(curItem->text(ValueColumn).toInt()));
        QString text = QString("style()->standardIcon(%1)").arg(curItem->text(0));
        InfoDlgMbox::info(this, text);
        qDebug() << "Копировать" << text;
    });

    connect(deleteDevice, &QAction::triggered, this, [this](){
        auto curItem = IconListMime->currentItem();
        qDebug() << "Удалить" << curItem->text(0);
    });

    menu->exec(QCursor::pos());
}
//not works
/******************************************************************/
