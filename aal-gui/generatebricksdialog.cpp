#include "generatebricksdialog.h"
#include "ui_generatebricksdialog.h"

GenerateBricksDialog::GenerateBricksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateBricksDialog)
{
    ui->setupUi(this);
}

GenerateBricksDialog::~GenerateBricksDialog()
{
    delete ui;
}

void GenerateBricksDialog::on_buttonBox_accepted()
{
    emit accepted(ui->amountSpinBox->value(), ui->minSpinBox->value(), ui->maxSpinBox->value());
}
