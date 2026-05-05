#include <iostream>
#include <vector>
#include "Mobile.h"

int verify_prov_id();

int main()
{
    std::vector<Mobile> mobile_connections;
    unsigned int option;
    std::string name;
    unsigned int pincode;
    std::string aadhaar;
    std::string email;
    std::string phone_no;
    std::string crn;
    while (1)
    {
        std::cout << "--------AirConnect Provisioning and Allotment System--------\n\n";
        std::cout << "1. Customer\n";
        std::cout << "2. Provisioner\n";
        std::cout << "3. Exit\n";
        std::cin >> option;
        if (option == 3)
            return 0;
        switch (option)
        {
        case 1:
            std::cout << "Choose a connection type: \n";
            std::cout << "1. Prepaid\n";
            std::cout << "2. Postpaid\n";
            std::cin >> option;

            switch (option)
            {
            case 1:
                std::cout << "1. New Connection\n";
                std::cout << "2. Port In\n";
                std::cin >> option;

                switch (option)
                {
                case 1:

                    std::cout << "Enter the following details: " << std::endl;
                    std::cout << "Name as per Govt ID.: ";
                    std::getline(std::cin >> std::ws, name);
                    std::cout << "Pincode: ";
                    std::cin >> pincode;
                    std::cout << "Aadhaar Number: ";
                    std::cin >> aadhaar;
                    std::cout << "Email Address: ";
                    std::cin >> email;
                    mobile_connections.emplace_back(name, pincode, aadhaar, email, "PR");
                    std::cout << "Connection request submitted successfully"; << std::endl;
                    break;

                case 2:

                    std::cout << "Enter the following details: " << std::endl;
                    std::cout << "Name as per Govt ID.: ";
                    std::getline(std::cin >> std::ws, name);
                    std::cout << "Pincode: ";
                    std::cin >> pincode;
                    std::cout << "Aadhaar Number: ";
                    std::cin >> aadhaar;
                    std::cout << "Email Address: ";
                    std::cin >> email;
                    std::cout << "Enter your phone number: ";
                    std::cin >> phone_no;
                    mobile_connections.emplace_back(name, pincode, aadhaar, email, "PR", phone_no);
                    std::cout << "Connection request submitted successfully" << std::endl;
                    break;

                default:

                    std::cout << "Invalid Option" << std::endl;
                }
                break;

            case 2:
                std::cout << "1. New Connection\n";
                std::cout << "2. Port In\n";
                std::cin >> option;

                switch (option)
                {
                case 1:

                    std::cout << "Enter the following details: " << std::endl;
                    std::cout << "Name as per Govt ID.: ";
                    std::getline(std::cin >> std::ws, name);
                    std::cout << "Pincode: ";
                    std::cin >> pincode;
                    std::cout << "Aadhaar Number: ";
                    std::cin >> aadhaar;
                    std::cout << "Email Address: ";
                    std::cin >> email;
                    mobile_connections.emplace_back(name, pincode, aadhaar, email, "PO");
                    std::cout << "Connection request submitted successfully" << std::endl;
                    break;

                case 2:

                    std::cout << "Enter the following details: " << std::endl;
                    std::cout << "Name as per Govt ID.: ";
                    std::getline(std::cin >> std::ws, name);
                    std::cout << "Pincode: ";
                    std::cin >> pincode;
                    std::cout << "Aadhaar Number: ";
                    std::cin >> aadhaar;
                    std::cout << "Email Address: ";
                    std::cin >> email;
                    std::cout << "Enter your phone number: ";
                    std::cin >> phone_no;
                    mobile_connections.emplace_back(name, pincode, aadhaar, email, "PO", phone_no);
                    std::cout << "Connection request submitted successfully" << std::endl;
                    break;

                default:

                    std::cout << "Invalid option!" << std::endl;
                    break;
                }
                break;

            default:
                std::cout << "Invalid option!" << std::endl;
            }
            break;

        case 2:
            if (verify_prov_id() == 0)
            {
                while (1)
                {
                PROVISION_MENU:
                    std::cout << "1. View Pending Requests\n";
                    std::cout << "2. View Rejected Requests\n";
                    std::cout << "3. View Provisioned Requests\n";
                    std::cout << "4.Exit\n";
                    std::cin >> option;

                    if (option == 4)
                    {
                        return 0;
                    }

                    switch (option)
                    {
                    case 1:
                        for (const Mobile &connection : mobile_connections)
                        {
                            if (connection.get_status() == "Pending")
                            {
                                std::cout<<connection;
                            }
                        }
                        std::cout << "Enter the CRN you want to provision: ";
                        std::cin >> crn;
                        for (Mobile &connection : mobile_connections)
                        {
                            if (connection.get_crn() == crn)
                            {
                                mobile_provisioning(connection);
                                goto PROVISION_MENU;
                            }
                        }
                        std::cout << "Invalid CRN!"<<std::endl;
                        break;

                    case 2:
                        for (const Mobile &connection : mobile_connections)
                        {
                            if (connection.get_status() == "Rejected")
                            {
                                std::cout<<connection;
                            }
                        }
                        break;

                    case 3:
                        for (const Mobile &connection : mobile_connections)
                        {
                            if (connection.get_status() == "Provisioned")
                            {
                                std::cout<<connection;
                            }
                        }
                        break;

                    default:
                        break;
                    }
                }
            }

        default:
            std::cout << "Invalid choice";
        }
    }
    return 0;
}

int verify_prov_id()
{
    int otp;
    std::string prov_id;
    std::cout << "Enter your provisioner ID: ";
    std::cin >> prov_id;

    std::cout << "Enter the OTP sent to your registered mobile number: ";
    std::cin >> otp;

    std::cout << "Validated"<<std::endl;
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

std::ostream& operator << (std::ostream& out,const Mobile& sr)
{
    if(sr.status=="Pending")
    {
        out<<sr.crn<<std::endl;
    }
    else if(sr.status=="Rejected")
    {
        out<<sr.crn<<"\t\t"<<sr.reason<<std::endl;
    }
    else if(sr.status=="Provisioned")
    {
        std::cout<<sr.crn<<"\t\t"<<sr.iccid<<std::endl;
    }

    return out;
}
