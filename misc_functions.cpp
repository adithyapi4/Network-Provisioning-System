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

static std::string return_prov_passwd()
{
    std::string prov_passwd{};
    std::fstream fpassword("prov.key", std::ios::in);
    if (fpassword.is_open())
    {
        std::getline(fpassword, prov_passwd);
        return prov_passwd;
    }
    else
    {
        throw "Provisioner password not found!";
    }
}

bool verify_prov_id()
{
    std::string password{};
    std::string prov_id;
    std::cout << "Enter your provisioner ID: ";
    std::cin >> prov_id;

    std::cout << "Enter your password: ";
    std::cin >> password;
    if (password == return_prov_passwd())
    {
        std::cout << "Validated" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
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
    std::string pincode;
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
        if (pay->make_payment() == true)
        {
            return true;
        }
        else
        {
            std::cout << "Invalid card details" << std::endl;
            return false;
        }

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

static std::string return_key()
{
    static std::string key{};

    if (!key.empty())
        return key;

    std::ifstream fkey("rw.key");
    if (!fkey.is_open())
        throw "Key not found!";

    std::getline(fkey, key);
    return key;
}

static std::string hash_gen(const std::string &data)
{
    unsigned long hash = 5381;
    for (char c : data)
        hash = ((hash << 5) + hash) + c;
    return std::to_string(hash);
}

static std::string xor_encrypt(const std::string &data)
{
    std::string key = return_key();
    std::string encrypted_data{};
    unsigned int i{0};

    for (char c : data)
    {
        if (c == delimiter)
        {
            encrypted_data += delimiter;
            continue;
        }
        encrypted_data += c ^ key[i % key.size()];
        i++;
    }

    return encrypted_data;
}

static std::string xor_decrypt(const std::string &encrypted_data)
{
    std::string key = return_key();
    std::string data{};
    unsigned int i{0};

    for (char c : encrypted_data)
    {
        if (c == delimiter)
        {
            data += delimiter;
            continue;
        }
        data += c ^ key[i % key.size()];
        i++;
    }

    return data;
}

void write_to_file(const std::vector<Mobile> &mobile_connections)
{
    std::fstream fwrite;
    fwrite.open("connections.dat", std::ios::out);
    std::string data{};

    if (fwrite.is_open())
    {
        std::cout << "Saving to file. Please wait... " << std::endl;
        fwrite << hash_gen(return_key()) << std::endl;

        for (const Mobile &connection : mobile_connections)
        {
            data = connection.name + delimiter + connection.pincode + delimiter + connection.aadhaar_no + delimiter + connection.email + delimiter + connection.type + delimiter + connection.connection_type + delimiter + connection.mobile_no + delimiter + connection.status + delimiter + connection.iccid + delimiter + connection.reason + delimiter + connection.crn;
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
    std::fstream fread("connections.dat", std::ios::in);
    std::string hash{};
    std::string encrypted_data{};
    std::string data{};
    std::string name, pincode, aadhaar, email, type, connection_type, mobile_no, status, iccid, reason, crn;

    if (fread.is_open())
    {
        std::cout << "Reading from file. Please wait... " << std::endl;
        std::getline(fread, hash);
        if (hash != hash_gen(return_key()))
        {
            std::cout << "Key mismatch! Not loading data!!!" << std::endl;
            return;
        }

        while (getline(fread, encrypted_data))
        {
            data = xor_decrypt(encrypted_data);
            std::stringstream sdata(data);

            std::getline(sdata, name, delimiter);
            std::getline(sdata, pincode, delimiter);
            std::getline(sdata, aadhaar, delimiter);
            std::getline(sdata, email, delimiter);
            std::getline(sdata, type, delimiter);
            std::getline(sdata, connection_type, delimiter);
            std::getline(sdata, mobile_no, delimiter);
            std::getline(sdata, status, delimiter);
            std::getline(sdata, iccid, delimiter);
            std::getline(sdata, reason, delimiter);
            std::getline(sdata, crn, delimiter);

            mobile_connections.emplace_back(name, pincode, aadhaar, email, type, connection_type, mobile_no, status, iccid, reason, crn);
        }

        fread.close();
    }
    else
    {
        std::cout << "Error reading from file!" << std::endl;
    }
}
