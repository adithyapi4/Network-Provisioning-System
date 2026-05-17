#include <iostream>
#include <string>
#include <algorithm>
#include "Customer.h"

Customer::Customer(const std::string &name, const std::string &pincode, const std::string &aadhaar_no, const std::string &email) : name(name), pincode(pincode), aadhaar_no(aadhaar_no), email(email)
{
    if (aadhaar_no.size() != 12 || !std::all_of(aadhaar_no.begin(), aadhaar_no.end(), ::isdigit))
    {
        throw "Invalid Aadhaar number!";
    }
    if (pincode.size() != 6 || !std::all_of(pincode.begin(), pincode.end(), ::isdigit))
    {
        throw "Invalid Pincode!";
    }
    verify_email();
}

void Customer::verify_email()
{
    int otp;
    std::cout << "Enter the OTP sent to " << email << ": ";
    std::cin >> otp;
    if (otp < 0)
    {
        throw "Invalid OTP!";
    }
    std::cout << "Verified Successfully" << std::endl;
}
