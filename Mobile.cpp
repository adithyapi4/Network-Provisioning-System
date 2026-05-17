#include <iostream>
#include <string>
#include <string_view>
#include "Customer.h"
#include "Mobile.h"
#include "Payment.h"

unsigned int Mobile::total_no_of_connections_requests = 0;
unsigned int Mobile::no_of_pending_requests = 0;
unsigned int Mobile::no_of_provisioned_requests = 0;
unsigned int Mobile::no_of_rejected_requests = 0;

Mobile::Mobile(const Customer &customer_info, std::string_view c_type) : Customer(customer_info), type("NE"), connection_type(c_type), status("Pending")
{
    generate_crn();
    total_no_of_connections_requests++;
    no_of_pending_requests++;
}

Mobile::Mobile(const Customer &customer_info, std::string_view c_type, std::string m_no) : Customer(customer_info), type("PI"), connection_type(c_type), mobile_no(m_no), status("Pending")
{
    verify_no();
    verify_upc();
    generate_crn();
    total_no_of_connections_requests++;
    no_of_pending_requests++;
}

Mobile::Mobile(std::string name,unsigned int pincode,std::string aadhaar,std::string email,std::string type,std::string c_type,std::string m_no,std::string status,std::string iccid,std::string reason,std::string crn) : Customer(name,pincode,aadhaar,email),type(type),connection_type(c_type),mobile_no(m_no),status(status),iccid(iccid),reason(reason),crn(crn)
{
    total_no_of_connections_requests++;
    if(status == "Pending")
    {
        no_of_pending_requests++;
    }
    else if(status == "Provisioned")
    {
        no_of_provisioned_requests++;
    }
    else if(status == "Rejected")
    {
        no_of_rejected_requests++;
    }
}

std::string Mobile::get_status() const
{
    return status;
}

void Mobile::set_status(std::string_view s)
{
    status = s;
}

std::string Mobile::get_reason() const
{
    return reason;
}

void Mobile::set_reason(std::string_view r)
{
    reason = r;
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

void Mobile::display_no() const
{
    std::cout << "Mobile Number: " << mobile_no << std::endl;
}

void Mobile::display_stats()
{
    std::cout << "Total number of connection requests: " << total_no_of_connections_requests;
    std::cout << "\nNumber of pending connection requests: " << no_of_pending_requests;
    std::cout << "\nNumber of provisioned connection requests: " << no_of_provisioned_requests;
    std::cout << "\nNumber of rejected connection requests: " << no_of_rejected_requests << std::endl;
}

void Mobile::prov_increment()
{
    no_of_pending_requests--;
    no_of_provisioned_requests++;
}

void Mobile::rej_increment()
{
    no_of_pending_requests--;
    no_of_rejected_requests++;
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
        }
        std::cout << "Invalid UPC code\nTry again" << std::endl;
        check++;
        goto UPC_VERIF;
    }
}
