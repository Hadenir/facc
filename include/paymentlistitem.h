#ifndef PAYMENTLISTITEM_H
#define PAYMENTLISTITEM_H

#include <QListWidgetItem>

class PaymentListItem : public QListWidgetItem
{
public:
    // This class overrides QListWidgetItem so that it can store custom information inside the list.
    // PaymentListItem discribes single shopping payment. It contains information about who did
    // the shopping (buyer), who did they do it for (everybody or single flatmate, recipient)
    // and how much was it (amount).
    PaymentListItem(const QString& buyer, const QString& recipient, double amount, QListWidget* parent = nullptr);

    // Returns the name of the person who paid for shopping.
    QString buyer() const;

    // Returns the name (or "All" for everybody) of shopping recipient.
    QString recipient() const;

    // Returns the price of shopping.
    double amount() const;

    // This function allows to edit information stored in the item.
    void edit(const QString& buyer, const QString& recipient, double amount);

private:
    QString m_buyer;
    QString m_recipient;
    double m_amount;
};

#endif // PAYMENTLISTITEM_H
