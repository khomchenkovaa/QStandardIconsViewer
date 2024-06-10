#include "infodlgmbox.h"
#include "ui_infodlgmbox.h"

#include <QIcon>

InfoDlgMbox::InfoDlgMbox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDlgMbox)
{
    ui->setupUi(this);
}

InfoDlgMbox::~InfoDlgMbox()
{
    delete ui;
}

void InfoDlgMbox::setIcon(const QIcon icon)
{
    ui->label->clear();
    ui->label->setPixmap(icon.pixmap(36, 36));
}

void InfoDlgMbox::setText(const QString &text)
{
    ui->textEdit->clear();
    ui->textEdit->insertPlainText(text);
}

void InfoDlgMbox::info(QWidget *parent, const QIcon icon, const QString &text)
{
    InfoDlgMbox box(parent);
    box.setIcon(icon);
    box.setText(text);
    box.exec();
}

void InfoDlgMbox::info(QWidget *parent, const QString &text)
{
    InfoDlgMbox box(parent);
    box.setText(text);
    box.exec();
}
