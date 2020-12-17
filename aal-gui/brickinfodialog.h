#ifndef BRICKINFODIALOG_H
#define BRICKINFODIALOG_H

#include <QDialog>
#include "aal/inc/brick.h"
#include "mainwindow.h"

namespace Ui {
class BrickInfoDialog;
}

class BrickInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrickInfoDialog(QWidget *parent = nullptr);
    ~BrickInfoDialog();

signals:
    void accepted(double, double, double);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::BrickInfoDialog *ui;
};

#endif // BRICKINFODIALOG_H
