#include "iconlisttab.h"
#include "qapplication.h"
#include "qclipboard.h"
#include "qdebug.h"
#include "qmenu.h"
#include "viewdlg.h"
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
    auto dirName = QFileDialog::getExistingDirectory(this, tr("Select Folder with icons"), ui.editDir->text());
    if (!dirName.isEmpty()) {
        ui.editDir->setText(dirName);
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
            auto item = new QListWidgetItem(QIcon(pixmap), it.fileName());
            ui.iconList->addItem(item);
        }
    }
}

/******************************************************************/

void IconListTab::setupActions()
{
    connect(ui.btnDir,   &QPushButton::clicked,
            this,        &IconListTab::doDirSelect);
    connect(ui.editDir, &QLineEdit::textChanged,
            this,        &IconListTab::updateView);
    connect(ui.iconList, &QWidget::customContextMenuRequested, 
            this,        &IconListTab::showCustomMenu);
    connect(ui.iconList, &QListWidget::itemDoubleClicked,
            this,        &IconListTab::doView);
}

/******************************************************************/

void IconListTab::IconListTabUi::setupUI(QWidget *parent)
{
    editDir  = new QLineEdit(parent);
    iconList = new QListWidget(parent);
    btnDir   = new QPushButton("...",parent);

    editDir->setReadOnly(true);
    iconList->setWrapping(true);
    iconList->setAlternatingRowColors(true);
    iconList->setContextMenuPolicy(Qt::CustomContextMenu);
    btnDir->setMaximumSize(QSize(27, 27));

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(2);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(new QLabel("Folder:", parent));
    horizontalLayout->addWidget(editDir);
    horizontalLayout->addWidget(btnDir);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(11, 11, 11, 11);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(iconList);
}

/******************************************************************/

void IconListTab::doCopy()
{
    auto fileName  = ui.iconList->currentItem()->text();
    auto sourceDir = ui.editDir->text();
    auto targetDir = QFileDialog::getExistingDirectory(this, tr("Select Folder to save"));
    if (targetDir.isEmpty()) return;
    QFile::copy(sourceDir + QDir::separator() + fileName, targetDir + QDir::separator() + fileName);
}

/******************************************************************/

void IconListTab::doView()
{
    auto fileName  = ui.iconList->currentItem()->text();
    auto sourceDir = ui.editDir->text();
    auto filePath  = sourceDir + QDir::separator() + fileName;
    QPixmap pixmap(filePath);
    auto icon = QIcon(pixmap);
    auto text = QString("QPixmap pixmap(\"%1\");\nauto icon = QIcon(pixmap);")
            .arg(filePath);
    ViewDlg::info(this, icon, text);
}

/******************************************************************/

void IconListTab::showCustomMenu()
{
    auto menu    = new QMenu(this);
    auto actView = new QAction(QIcon::fromTheme("zoom-original"), tr("View"), this);
    auto actCopy = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy file to"), this);
    menu->addAction(actView);
    menu->addAction(actCopy);

    connect(actView, &QAction::triggered,
            this,    &IconListTab::doView);
    connect(actCopy, &QAction::triggered,
            this,    &IconListTab::doCopy);

    menu->exec(QCursor::pos());
}

/******************************************************************/
