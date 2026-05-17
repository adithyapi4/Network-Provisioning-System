#ifndef CARD_H
#define CARD_H
#include <string>

class Card : public Payment
{
    std::string card_no{};
    std::string expiry{};
    std::string card_holder_name{};
    unsigned int cvv{};
    bool validity{true};

    void validate_card_details();

public:
    void get_payment_details() override;
    bool make_payment() override;
};

#endif