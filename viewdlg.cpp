#include "viewdlg.h"

#include <QLabel>
#include <QIcon>
#include <QTextEdit>
#include <QHBoxLayout>

/******************************************************************/

ViewDlg::ViewDlg(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUI(this);
}

/******************************************************************/

void ViewDlg::setIcon(const QIcon icon)
{
    ui.lblIcon->clear();
    ui.lblIcon->setPixmap(icon.pixmap(36, 36));
}

/******************************************************************/

void ViewDlg::setText(const QString &text)
{
    ui.editText->clear();
    ui.editText->insertPlainText(text);
}

/******************************************************************/

void ViewDlg::info(QWidget *parent, const QIcon icon, const QString &text)
{
    ViewDlg dlg(parent);
    dlg.setIcon(icon);
    dlg.setText(text);
    dlg.exec();
}

/******************************************************************/

void ViewDlg::ViewDlgUi::setupUI(QWidget *parent)
{
    parent->setWindowTitle(tr("View icon"));

    lblIcon  = new QLabel(parent);
    editText = new QTextEdit(parent);

    lblIcon->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

    auto mainLayout = new QHBoxLayout(parent);
    mainLayout->addWidget(lblIcon);
    mainLayout->addWidget(editText);
}

/******************************************************************/
