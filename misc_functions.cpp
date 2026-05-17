#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Payment.h"
#include "Card.h"
#include "Customer.h"
#include "Mobile.h"
#include "misc_functions.h"

extern char delimiter;

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

    if (connection.mobile_no == "")
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
        out << sr.crn << "\t\t" << sr.iccid << std::endl;
    }

    return out;
}

void get_customer_details(Customer *&new_customer)
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

    new_customer = new Customer(name, pincode, aadhaar, email);
}

void new_connection_prepaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections)
{
    mobile_connections.emplace_back(new_customer, "PR");
}

void port_in_prepaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections)
{
    std::string phone_no;

    std::cout << "Enter your phone number: ";
    std::cin >> phone_no;

    mobile_connections.emplace_back(new_customer, "PR", phone_no);
}

void new_connection_postpaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections)
{
    mobile_connections.emplace_back(new_customer, "PO");
}

void port_in_postpaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections)
{
    std::string phone_no;

    std::cout << "Enter your phone number: ";
    std::cin >> phone_no;

    mobile_connections.emplace_back(new_customer, "PO", phone_no);
}

bool make_payment(Payment *&pay)
{
    unsigned int option{};
    std::cout << "Please pay Rs.299 to place the connection request\n";
    std::cout << "Choose your preferred payment method: \n";
    std::cout << "1. Credit/Debit Card\n";
    std::cin >> option;

    switch (option)
    {
    case 1:
        pay = new Card;
        pay->get_payment_details();
        if (pay->make_payment() == false)
        {
            std::cout << "Invalid card details" << std::endl;
            return false;
        }
        else
        {
            return true;
        }
        break;

    default:
        std::cout << "Invalid choice!";
        return false;
    }
}

void payment_failure_message(std::vector<Mobile> &mobile_connections)
{
    std::cout << "Transaction Failed! Your request will be submitted only upon successful payment\n";
    std::cout << "CRN: " << mobile_connections.back().get_crn() << std::endl;
    std::cout << "You can retry the payment using the given CRN" << std::endl;
    mobile_connections.back().set_reason("Payment failed");
}

void payment_success_message(const std::vector<Mobile> &mobile_connections)
{
    std::cout << "Connection request placed successfully!\n";
    std::cout << "CRN: " << mobile_connections.back().get_crn() << std::endl;
    std::cout << "To track your connection request use the given CRN" << std::endl;
}

std::string return_key()
{
    std::string key = "my_key";
    return key;
}

std::string xor_encrypt(const std::string &data)
{
    std::string encrypted_data{};
    unsigned int i{0};

    for (char c : data)
    {
        if (c == delimiter)
        {
            encrypted_data += delimiter;
        }
        encrypted_data += c ^ return_key()[i % return_key().size()];
    }

    return encrypted_data;
}

void write_to_file(const std::vector<Mobile> &mobile_connections)
{
    std::cout << "Saving to file. Please wait... " << std::endl;
    std::fstream fwrite;
    fwrite.open("connections.dat", std::ios::out);
    unsigned int i{0};
    std::string data{};
    std::string encrypted_key{};

    if (fwrite.is_open())
    {
        for (int k : return_key())
        {
            int add{};
            add = (i % 2 == 0) ? 6 : -6;

            encrypted_key += static_cast<char>(k + add);
            i++;
        }
        fwrite << encrypted_key << std::endl;

        for (const Mobile &connection : mobile_connections)
        {
            data = connection.name + delimiter + std::to_string(connection.pincode) + delimiter + connection.aadhaar_no + delimiter + connection.email + delimiter + connection.type + delimiter + connection.connection_type + delimiter + connection.mobile_no + delimiter + connection.status + delimiter + connection.iccid + delimiter + connection.reason + delimiter + connection.crn;
            fwrite << xor_encrypt(data) << std::endl;
        }

        fwrite.close();
    }
    else
    {
        std::cout << "Error writing to file! Data lost!!!" << std::endl;
    }
}

void read_from_file(std::vector<Mobile> &mobile_connections)
{
    std::cout << "Reading from file. Please wait... " << std::endl;
    std::fstream fread("connections.dat",std::ios::in);
    std::string decrypted_key{};
    std::string encrypted_data{};
    std::string data{};
    std::string encrypted_key{};
    std::string name,str_pincode,aadhaar,email,type,connection_type,mobile_no,status,iccid,reason,crn;
    std::getline(fread,encrypted_key);
    unsigned int i{0};
    unsigned int pincode{};

    if(fread.is_open())
    {
        for (int k : encrypted_key)
        {
            int add{};
            add = (i % 2 == 0) ? 6 : -6;

            decrypted_key += static_cast<char>(k - add);
            i++;
        }
        if(decrypted_key != return_key())
        {
            std::cout << "Key mismatch! Not loading data!!!" << std::endl;
            return;
        }

        while(getline(fread,encrypted_data))
        {
            data = xor_decrypt(encrypted_data);
            std::stringstream sdata(data);

            std::getline(sdata,name,delimiter);
            std::getline(sdata,str_pincode,delimiter);
            std::getline(sdata,aadhaar,delimiter);
            std::getline(sdata,email,delimiter);
            std::getline(sdata,type,delimiter);
            std::getline(sdata,connection_type,delimiter);
            std::getline(sdata,mobile_no,delimiter);
            std::getline(sdata,status,delimiter);
            std::getline(sdata,iccid,delimiter);
            std::getline(sdata,reason,delimiter);
            std::getline(sdata,crn,delimiter);

            pincode = (str_pincode[0] * 100000) + (str_pincode[1] * 10000) + (str_pincode[2] * 1000) + (str_pincode[3] * 100) + (str_pincode[4] * 10) + (str_pincode[5]);

            mobile_connections.emplace_back(name,pincode,aadhaar,email,type,connection_type,mobile_no,status,iccid,reason,crn);
        }
    }
    else
    {
        std::cout << "Error reading from file!" << std::endl;
    }
}

std::string xor_decrypt(const std::string &encrypted_data)
{
    std::string data{};
    unsigned int i{0};

    for (char c : encrypted_data)
    {
        if (c == delimiter)
        {
            data += delimiter;
        }
        data += c ^ return_key()[i % return_key().size()];
    }

    return data;
}
