#include "brickinfodialog.h"
#include "ui_brickinfodialog.h"

BrickInfoDialog::BrickInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrickInfoDialog)
{
    ui->setupUi(this);
}

BrickInfoDialog::~BrickInfoDialog()
{
    delete ui;
}

void BrickInfoDialog::on_buttonBox_accepted()
{
    emit accepted(ui->widthDoubleSpinBox->value(), ui->heightDoubleSpinBox->value(), ui->depthDoubleSpinBox->value());
}
