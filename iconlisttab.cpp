#include "iconlisttab.h"
#include "qapplication.h"
#include "qclipboard.h"
#include "qdebug.h"
#include "qmenu.h"
#include "infodlgmbox.h"
#include "qmimedata.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QDirIterator>

/******************************************************************/

IconListTab::IconListTab(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUI(this);
    setupActions();
}

/******************************************************************/

void IconListTab::doDirSelect()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Folder with icons"), ui.editName->text());
    if (!dirName.isEmpty()) {
        savedPath=dirName;
        ui.editName->setText(dirName);
    }
}

/******************************************************************/

void IconListTab::updateView(const QString &dirName)
{
    ui.iconList->clear();
    QDirIterator it(dirName, QDir::Files);
    while (it.hasNext()) {
        it.next();
        QPixmap pixmap(it.filePath());
        if (!pixmap.isNull()) {
            QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), it.fileName());
            ui.iconList->addItem(item);
        }
    }
}

/******************************************************************/

void IconListTab::setupActions()
{
    connect(ui.btnDir,   &QPushButton::clicked,
            this,        &IconListTab::doDirSelect);
    connect(ui.editName, &QLineEdit::textChanged,
            this,        &IconListTab::updateView);
    connect(ui.iconList, &QWidget::customContextMenuRequested, 
            this,        &IconListTab::onTableCustomMenuRequested);
    connect(ui.iconList, &QListWidget::itemDoubleClicked,
            this,        &IconListTab::copyOnDoubleClick);
}

/******************************************************************/

void IconListTab::IconListTabUi::setupUI(QWidget *parent)
{
    editName = new QLineEdit(parent);
    iconList = new QListWidget(parent);
    btnDir   = new QPushButton("...",parent);

    editName->setReadOnly(true);
    iconList->setWrapping(true);
    iconList->setAlternatingRowColors(true);
    iconList->setContextMenuPolicy(Qt::CustomContextMenu);
    btnDir->setMaximumSize(QSize(27, 27));

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Folder:", parent));
    horizontalLayout->addWidget(editName);
    horizontalLayout->addWidget(btnDir);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);
}

/******************************************************************/

void IconListTab::copyOnDoubleClick()
{
    auto curItem = iconList->currentItem()->text();

    QString dirNameToCopy = QFileDialog::getExistingDirectory(this, tr("Select Folder to save"));
    if(QFile::copy(savedPath+QDir::separator()+curItem,dirNameToCopy+QDir::separator()+QDir::separator()+curItem)){
        qDebug() << "Ok";
        qDebug() << "Скопировано из " <<savedPath+QDir::separator()+curItem;
        qDebug() << "Скопировано в " <<dirNameToCopy;
    } else qDebug()<<"Not ok";

}

/******************************************************************/

void IconListTab::onTableCustomMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu(this);
    QAction * showToCopy = new QAction("Показать", this);
    menu->addAction(showToCopy);

    connect(showToCopy, &QAction::triggered, this, [this](){
        auto curItem = iconList->currentItem()->text();

        QString dirNameToCopy = QFileDialog::getExistingDirectory(this, tr("Select Folder to save"));
        if(QFile::copy(savedPath+QDir::separator()+curItem,dirNameToCopy+QDir::separator()+QDir::separator()+curItem)){
            qDebug() << "Ok";
            qDebug() << "Скопировано из " <<savedPath+QDir::separator()+curItem;
            qDebug() << "Скопировано в " <<dirNameToCopy;
        }else qDebug()<<"Not ok";
    });

    menu->exec(QCursor::pos());
}

/******************************************************************/
