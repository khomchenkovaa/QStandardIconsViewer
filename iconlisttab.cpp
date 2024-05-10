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
    : QWidget(parent),
      editName(new QLineEdit(this)),
      iconList(new QListWidget(this))
{
    setupUI();
}

/******************************************************************/

IconListTab::~IconListTab()
{
    editName->deleteLater();
    iconList->deleteLater();
}

/******************************************************************/

void IconListTab::doDirSelect()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Folder with icons"),editName->text());
    if (!dirName.isEmpty()) {
        editName->setText(dirName);
        savedPath=dirName;
    }
}

/******************************************************************/

void IconListTab::updateView(const QString &dirName)
{
    iconList->clear();
    QDirIterator it(dirName, QDir::Files);
    while (it.hasNext()) {
        it.next();
        QPixmap pixmap(it.filePath());
        if (!pixmap.isNull()) {
            QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), it.fileName());
            iconList->addItem(item);
        }
    }
}

/******************************************************************/

void IconListTab::setupUI()
{
    editName->setReadOnly(true);
    QPushButton *btnDir = new QPushButton("...",this);
    btnDir->setMaximumSize(QSize(27, 27));
    iconList->setWrapping(true);
    iconList->setAlternatingRowColors(true);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Folder:", this));
    horizontalLayout->addWidget(editName);
    horizontalLayout->addWidget(btnDir);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);

    connect(btnDir, SIGNAL(clicked()),
            this, SLOT(doDirSelect()));
    connect(editName, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateView(const QString &)));

    iconList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(iconList,&QWidget::customContextMenuRequested, this, &IconListTab::onTableCustomMenuRequested);

    connect(iconList,&QListWidget::itemDoubleClicked,this,&IconListTab::copyOnDoubleClick);
}

void IconListTab::copyOnDoubleClick()
{
    auto curItem = iconList->currentItem()->text();

    QString dirNameToCopy = QFileDialog::getExistingDirectory(this, tr("Select Folder to save"));
    if(QFile::copy(savedPath+QDir::separator()+curItem,dirNameToCopy+QDir::separator()+QDir::separator()+curItem)){
        qDebug() << "Ok";
        qDebug() << "Скопировано из " <<savedPath+QDir::separator()+curItem;
        qDebug() << "Скопировано в " <<dirNameToCopy;
    }else qDebug()<<"Not ok";

}


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
