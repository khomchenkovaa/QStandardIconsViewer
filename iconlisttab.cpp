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
    : QWidget(parent),
      editName(new QLineEdit(this)),
      iconList(new QListWidget(this))
{
    setupUi();
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

void IconListTab::setupUi()
{
    editName->setReadOnly(true);
    QPushButton *btnDir = new QPushButton("...",this);
    btnDir->setMaximumSize(QSize(27, 27));
    iconList->setWrapping(true);

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
}

/******************************************************************/
