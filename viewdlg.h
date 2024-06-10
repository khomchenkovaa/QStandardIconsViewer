#ifndef INFODLGMBOX_H
#define INFODLGMBOX_H

#include <QDialog>

class QLabel;
class QTextEdit;

class ViewDlg : public QDialog
{
    Q_OBJECT

    struct ViewDlgUi {
        QLabel    *lblIcon  = Q_NULLPTR;
        QTextEdit *editText = Q_NULLPTR;

        void setupUI(QWidget *parent = Q_NULLPTR);
    };

public:
    explicit ViewDlg(QWidget *parent = nullptr);

    void setIcon(const QIcon icon);
    void setText(const QString &text);

public:
    static void info(QWidget *parent, const QIcon icon, const QString &text);

private:
    ViewDlgUi ui;
};

#endif // INFODLGMBOX_H
