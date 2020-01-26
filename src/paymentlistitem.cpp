#include "paymentlistitem.h"

PaymentListItem::PaymentListItem(const QString& buyer, const QString& recipient, double amount, QListWidget* parent)
    : QListWidgetItem(QString::number(amount, 'f', 2).append(" PLN"), parent, QListWidgetItem::UserType),
      m_buyer(std::move(buyer)), m_recipient(std::move(recipient)), m_amount(amount)
{}

QString PaymentListItem::buyer() const
{
    return m_buyer;
}

QString PaymentListItem::recipient() const
{
    return m_recipient;
}

double PaymentListItem::amount() const
{
    return m_amount;
}

void PaymentListItem::edit(const QString& buyer, const QString& recipient, double amount)
{
    m_buyer = buyer;
    m_recipient = recipient;
    m_amount = amount;
    setText(QString::number(amount, 'f', 2).append(" PLN"));
}
