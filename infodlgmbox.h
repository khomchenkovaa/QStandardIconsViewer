#ifndef INFODLGMBOX_H
#define INFODLGMBOX_H

#include <QDialog>

namespace Ui {
class InfoDlgMbox;
}

class InfoDlgMbox : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDlgMbox(QWidget *parent = nullptr);
    ~InfoDlgMbox();

    void setIcon(const QIcon icon);
    void setText(const QString &text);

public:
    static void info(QWidget *parent, const QIcon icon, const QString &text);
    static void info(QWidget *parent, const QString &text);

private:
    Ui::InfoDlgMbox *ui;
};

#endif // INFODLGMBOX_H
