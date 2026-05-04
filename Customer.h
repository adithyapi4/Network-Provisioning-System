#include <iostream>

class Customer
{
    protected:

    std::string name;
    unsigned int pincode;
    std::string aadhaar_no;
    std::string email;
    std::string status;
    int otp;

    public:

    Customer(std::string name,unsigned int pincode,std::string aadhaar_no,std::string email);

    private:

    void verify_email();
};