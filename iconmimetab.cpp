#include "iconmimetab.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>

#include <QMimeDatabase>

/******************************************************************/

IconMimeTab::IconMimeTab(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

/******************************************************************/

void IconMimeTab::setupUI()
{
    QTreeWidget *iconList = new QTreeWidget(this);
    iconList->setColumnCount(4);
    iconList->header()->setDefaultSectionSize(200);
    iconList->headerItem()->setText(0, "Name");
    iconList->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    iconList->headerItem()->setText(1, "Comment");
    iconList->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    iconList->headerItem()->setText(2, "Filter");
    iconList->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    iconList->headerItem()->setText(3, "Parent");
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

/******************************************************************/
