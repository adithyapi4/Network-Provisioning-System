#include <iostream>
#include <string>
#include "Customer.h"

Customer::Customer(std::string name, unsigned int pincode, std::string aadhaar_no, std::string email) : name(name), pincode(pincode), aadhaar_no(aadhaar_no), email(email)
{
    if(aadhaar_no.size() != 12)
    {
        throw "Invalid Aadhaar number!";
    }
    if(std::to_string(pincode).size() != 6)
    {
        throw "Invalid Pincode!";
    }
    verify_email();
}

void Customer::verify_email()
{
    std::cout << "Enter the OTP sent to " << email << ": ";
    std::cin >> otp;
    std::cout << "Verified Successfully" << std::endl;
}
