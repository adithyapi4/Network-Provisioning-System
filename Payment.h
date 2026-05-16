#ifndef PAYMENT_H
#define PAYMENT_H

class Payment
{
public:
    virtual void get_payment_details() = 0;
    virtual bool make_payment() = 0;
    virtual ~Payment() = 0;
};

#endif