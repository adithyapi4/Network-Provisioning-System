#include <iostream>
#include "Mobile.h"

int Mobile::no_of_connections_requests = 0;

Mobile::Mobile(std::string name, unsigned int pincode, std::string aadhaar_no, std::string email, std::string_view connection_type) : Customer(name, pincode, aadhaar_no, email), connection_type(connection_type), status("Pending"), type("NE"), mobile_no(""), iccid("")
{
    generate_crn();
    no_of_connections_requests++;
}

Mobile::Mobile(std::string name, unsigned int pincode, std::string aadhaar_no, std::string email, std::string_view connection_type, std::string mobile_no) : Customer(name, pincode, aadhaar_no, email), connection_type(connection_type), mobile_no(mobile_no), status("Pending"), type("PI"), iccid("")
{
    verify_no();
    verify_upc();
    generate_crn();
    no_of_connections_requests++;
}

std::string Mobile::get_status() const
{
    return status;
}

void Mobile::set_status(std::string s)
{
    status = s;
}

void Mobile::verify_no()
{
    std::cout << "Enter the OTP sent to " << mobile_no << ": ";
    std::cin >> otp;
    std::cout << "Verified Successfully" << std::endl;
}

void Mobile::generate_crn()
{
    crn = type + connection_type + aadhaar_no.substr(8) + std::to_string(pincode).substr(1);
}

std::string Mobile::get_crn() const
{
    return crn;
}

void Mobile::generate_mobile_no()
{
    mobile_no = "93" + aadhaar_no.substr(8) + std::to_string(pincode).substr(1);
}

void Mobile::verify_upc()
{
    int check = 0;
UPC_VERIF:

    std::cout << "Enter your UPC Code: ";
    std::cin >> upc;
    std::cout << "Current Operator: ";
    switch (upc[0])
    {
    case 'V':

        std::cout << "Vodafone Idea\n"
                  << std::endl;
        break;

    case 'G':

        std::cout << "Reliance Jio\n"
                  << std::endl;
        break;

    case 'A':

        std::cout << "Airtel\n"
                  << std::endl;
        break;

    case 'B':

        std::cout << "BSNL\n"
                  << std::endl;
        break;

    case 'M':

        std::cout << "MTNL" << std::endl;
        break;

    default:

        if (check == 1)
        {
            throw "Rejected! Invalid UPC code";
            return;
        }
        std::cout << "Invalid UPC code\nTry again" << std::endl;
        check++;
        goto UPC_VERIF;
    }
}
