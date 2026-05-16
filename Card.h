#ifndef CARD_H
#define CARD_H

class Card : public Payment
{
    std::string card_no{};
    std::string expiry{};
    std::string card_holder_name{};
    unsigned int cvv{};
    bool validity{false};

public:
        void get_payment_details() override;
    void validate_card_details();
    bool make_payment() override;
};

#endif