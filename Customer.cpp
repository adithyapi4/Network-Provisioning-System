#include <iostream>
#include <string>
#include "Customer.h"

Customer::Customer(std::string name, unsigned int pincode, std::string aadhaar_no, std::string email) : name(name), pincode(pincode), aadhaar_no(aadhaar_no), email(email)
{
    verify_email();
}

void Customer::verify_email()
{
    std::cout << "Enter the OTP sent to " << email << ": ";
    std::cin >> otp;
    std::cout << "Verified Successfully" << std::endl;
}
