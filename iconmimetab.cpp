#include "iconmimetab.h"
#include "qclipboard.h"
#include "qdebug.h"
#include "viewdlg.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>

#include <QMimeDatabase>
#include <QMenu>
#include <QPoint>
#include <QGuiApplication>

namespace Utils {

inline QIcon iconForMimeType(const QString &mime, const QIcon &fallback = QIcon())
{
    QMimeDatabase db;
    QMimeType t = db.mimeTypeForName(mime);
    if (QIcon::hasThemeIcon(t.iconName())) {
        return QIcon::fromTheme(t.iconName());
    }
    if (QIcon::hasThemeIcon(t.genericIconName())) {
        return QIcon::fromTheme(t.genericIconName());
    }
    return fallback;
}

}

enum {
    NameColumn,
    CommentColumn,
    FilterColumn,
    ParentColumn
};

/******************************************************************/

IconMimeTab::IconMimeTab(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

/******************************************************************/

void IconMimeTab::setupUI()
{
    iconList = new QTreeWidget(this);
    iconList->setColumnCount(4);
    iconList->header()->setDefaultSectionSize(200);
    iconList->headerItem()->setText(NameColumn, "Name");
    iconList->headerItem()->setTextAlignment(NameColumn, Qt::AlignCenter);
    iconList->headerItem()->setText(CommentColumn, "Comment");
    iconList->headerItem()->setTextAlignment(CommentColumn, Qt::AlignCenter);
    iconList->headerItem()->setText(FilterColumn, "Filter");
    iconList->headerItem()->setTextAlignment(FilterColumn, Qt::AlignCenter);
    iconList->headerItem()->setText(ParentColumn, "Parent");
    iconList->headerItem()->setTextAlignment(ParentColumn, Qt::AlignCenter);
    iconList->setAlternatingRowColors(true);
    iconList->addTopLevelItems(loadFromMimeDb());
    iconList->setContextMenuPolicy(Qt::CustomContextMenu);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addWidget(iconList);

    connect(iconList, &QWidget::customContextMenuRequested,
            this,     &IconMimeTab::showCustomMenu);
    connect(iconList, &QTreeWidget::itemDoubleClicked,
            this,     &IconMimeTab::doView);
}

/******************************************************************/

QList<QTreeWidgetItem *> IconMimeTab::loadFromMimeDb()
{
    QList<QTreeWidgetItem *> result;

    QMimeDatabase mimeDatabase;
    QList<QMimeType> allTypes = mimeDatabase.allMimeTypes();
    std::sort(allTypes.begin(), allTypes.end(),
          [](QMimeType a, QMimeType b) -> bool { return a.name() < b.name(); });

    for (const auto &mime : qAsConst(allTypes)) {
        auto item = new QTreeWidgetItem();
        item->setText(NameColumn, mime.name());
        item->setText(CommentColumn, mime.comment());
        item->setText(FilterColumn, mime.filterString());
        item->setText(ParentColumn, mime.parentMimeTypes().join(", "));
        item->setIcon(NameColumn, Utils::iconForMimeType(mime.name()));
        if (!mime.parentMimeTypes().isEmpty()) {
            item->setIcon(ParentColumn, Utils::iconForMimeType(mime.parentMimeTypes().constFirst()));
        }
        result.append(item);
    }
    return result;
}

/******************************************************************/

void IconMimeTab::doCopy()
{
    auto curItem   = iconList->currentItem();
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(QString("Utils::iconForMimeType(\"%1\")").arg(curItem->text(NameColumn)));
}

/******************************************************************/

void IconMimeTab::doView()
{
    auto item = iconList->currentItem();
    auto icon = Utils::iconForMimeType(item->text(NameColumn));
    auto text = QString("auto icon = Utils::iconForMimeType(\"%1\");").arg(item->text(NameColumn));
    ViewDlg::info(this, icon, text);
}

/******************************************************************/

void IconMimeTab::showCustomMenu()
{
    auto menu    = new QMenu(this);
    auto actView = new QAction(QIcon::fromTheme("zoom-original"), tr("View"), this);
    auto actCopy = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this);
    menu->addAction(actView);
    menu->addAction(actCopy);

    connect(actView, &QAction::triggered,
            this,    &IconMimeTab::doView);
    connect(actCopy, &QAction::triggered,
            this,    &IconMimeTab::doCopy);

    menu->exec(QCursor::pos());
}

/******************************************************************/
