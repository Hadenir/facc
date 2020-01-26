#include "mainwindow.h"

#include "paymentlistitem.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
    setupUi(this);

    buyerComboBox->addItems({"Konrad", "Olek", "Ola"});
    recipientComboBox->addItems({tr("All"), "Konrad", "Olek", "Ola"});

    paymentListWidget->addItem(tr("New Item..."));
    paymentListWidget->setCurrentRow(0);

    connect(addPushButton, &QPushButton::clicked, this, &MainWindow::addPayment);
    connect(paymentListWidget, &QListWidget::currentItemChanged, this, &MainWindow::editPayment);
    connect(removePushButton, &QPushButton::clicked, this, &MainWindow::removePayment);
    connect(summaryPushButton, &QPushButton::clicked, this, &MainWindow::createSummary);
}

MainWindow::~MainWindow()
{}

void MainWindow::addPayment()
{
    QListWidgetItem* currentItem = paymentListWidget->currentItem();

    QString buyer = buyerComboBox->currentText();
    QString recipient = recipientComboBox->currentText();

    bool ok = false;
    double amount = amountLineEdit->text().toDouble(&ok);   // Handily, rejects empty strings.
    if(ok == false)
        return;

    if(currentItem == nullptr || currentItem->text() == tr("New Item..."))
    {
        // Adding new item to the list.
        int row = paymentListWidget->count() - 1;   // To keep "New Item..." as last element, we insert at second-to-last row.
        paymentListWidget->insertItem(row, new PaymentListItem(buyer, recipient, amount));
    }
    else
    {
        // Editing existing item in the list.
        PaymentListItem* payment = (PaymentListItem*) currentItem;
        payment->edit(buyer, recipient, amount);
    }
}

void MainWindow::editPayment(QListWidgetItem* currentItem)
{
    if(currentItem == nullptr || currentItem->text() == tr("New Item..."))
    {
        addPushButton->setText(tr("Add"));
        removePushButton->setEnabled(false);
        return;
    }

    PaymentListItem* payment = (PaymentListItem*) currentItem;

    QString buyer = payment->buyer();
    QString recipient = payment->recipient();
    double amount = payment->amount();

    buyerComboBox->setCurrentIndex(buyerComboBox->findText(buyer));
    recipientComboBox->setCurrentIndex(recipientComboBox->findText(recipient));
    amountLineEdit->setText(QString::number(amount));

    addPushButton->setText(tr("Edit"));
    removePushButton->setEnabled(true);
}

void MainWindow::removePayment()
{
    QListWidgetItem* currentItem = paymentListWidget->currentItem();
    if(currentItem == nullptr || currentItem->text() == tr("New Item..."))
        return;

    QListWidgetItem* item = paymentListWidget->takeItem(paymentListWidget->currentRow());
    delete item;
}

void MainWindow::createSummary()
{
    QMap<QString, double> debts;
    int count = buyerComboBox->count();
    for(int i = 0; i < count; ++i)
    {
        QString mate = buyerComboBox->itemText(i);
        debts.insert(mate, 0.0);
    }

    for(int i = 0; i < paymentListWidget->count() - 1; ++i) // Need to skip last item.
    {
        PaymentListItem* item = (PaymentListItem*) paymentListWidget->item(i);
        QString buyer = item->buyer();
        QString recipient = item->recipient();
        double amount = item->amount();

        if(recipient == tr("All"))
        {
            double fract = amount / count;  // Split price equally.
            for(const QString& mate : debts.keys())
                debts[mate] += fract;
           debts[buyer] -= amount;
        }
        else
        {
            debts[recipient] += amount;
            debts[buyer] -= amount;
        }
    }

    QString summary = tr("Summary of debts:\n");
    for(const QString& mate : debts.keys())
    {
        double debt = debts[mate];
        summary.append(mate).append('\t').append(QString::number(debt, 'f', 2).append(" PLN\n"));
    }

    QMessageBox messageBox;
    messageBox.setText(summary);
    messageBox.exec();
}














