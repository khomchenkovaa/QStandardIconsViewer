#include "iconlisttab.h"

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
