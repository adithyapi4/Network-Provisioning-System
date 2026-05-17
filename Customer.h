#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer
{
protected:
    std::string name{};
    std::string pincode{};
    std::string aadhaar_no{};
    std::string email{};

public:
    Customer(const std::string &name, const std::string &pincode, const std::string &aadhaar_no, const std::string &email);

private:
    void verify_email();
};

#endif
