#include <iostream>
#include <string>
#include <vector>
#include "Payment.h"
#include "Card.h"
#include "Customer.h"
#include "Mobile.h"
#include "misc_functions.h"

int verify_prov_id()
{
    int otp;
    std::string prov_id;
    std::cout << "Enter your provisioner ID: ";
    std::cin >> prov_id;

    std::cout << "Enter the OTP sent to your registered mobile number: ";
    std::cin >> otp;

    std::cout << "Validated" << std::endl;
    return 0;
}

void mobile_provisioning(Mobile &connection)
{
    std::string iccid;
    std::cout << "Enter the ICCID: ";
    std::cin >> iccid;

    connection.iccid = iccid;

    if (connection.mobile_no != "")
    {
        connection.generate_mobile_no();
    }

    connection.status = "Provisioned";
}

std::ostream &operator<<(std::ostream &out, const Mobile &sr)
{
    if (sr.status == "Pending")
    {
        out << sr.crn << std::endl;
    }
    else if (sr.status == "Rejected")
    {
        out << sr.crn << "\t\t" << sr.reason << std::endl;
    }
    else if (sr.status == "Provisioned")
    {
        std::cout << sr.crn << "\t\t" << sr.iccid << std::endl;
    }

    return out;
}

void get_customer_details(Customer* new_customer)
{
    std::string name;
    unsigned int pincode;
    std::string aadhaar;
    std::string email;

    std::cout << "Enter the following details: " << std::endl;
    std::cout << "Name as per Govt ID.: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Pincode: ";
    std::cin >> pincode;
    std::cout << "Aadhaar Number: ";
    std::cin >> aadhaar;
    std::cout << "Email Address: ";
    std::cin >> email;

    new_customer = new Customer(name,pincode,aadhaar,email);
}

void new_connection_prepaid(Customer& new_customer,std::vector<Mobile>& mobile_connections)
{
    mobile_connections.emplace_back(new_customer, "PR");
}

void port_in_prepaid(Customer& new_customer,std::vector<Mobile>& mobile_connections)
{
    std::string phone_no;

    std::cout << "Enter your phone number: ";
    std::cin >> phone_no;

    mobile_connections.emplace_back(new_customer, "PR", phone_no);
}

void new_connection_postpaid(Customer& new_customer,std::vector<Mobile>& mobile_connections)
{
    mobile_connections.emplace_back(new_customer, "PO");
}

void port_in_postpaid(Customer& new_customer,std::vector<Mobile>& mobile_connections)
{
    std::string phone_no;

    std::cout << "Enter your phone number: ";
    std::cin >> phone_no;

    mobile_connections.emplace_back(new_customer, "PR", phone_no);
}

bool make_payment(Payment* pay)
{
    unsigned int option{};
    std::cout<<"Please pay Rs.299 to place the connection request\n";
    std::cout<<"Choose your preferred payment method: \n";
    std::cout<<"1. Credit/Debit Card\n";
    std::cin>>option;

    switch (option)
    {
        case 1:
            pay = new Card;
            pay->get_payment_details();
            if(pay->make_payment() == false)
            {
                std::cout<<"Invalid card details";
                return false;
            }
            else
            {
                return true;
            }
            break;

        default:
            std::cout<<"Invalid choice!";
            return false;
    }
}
