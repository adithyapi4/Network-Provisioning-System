#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include "Customer.h"
#include "Mobile.h"
#include "Payment.h"
#include "Card.h"
#include "misc_functions.h"

char delimiter = '|';

int main()
{
    Customer *new_customer{};
    std::vector<Mobile> mobile_connections;
    Payment *pay{};
    bool paid{};
    bool search{};
    std::string crn;
    unsigned int option{};

    try
    {
        read_from_file(mobile_connections);
    }
    catch (const char* msg)
    {
        std::cout << msg << " Error reading from file!!!" << std::endl;
    }

    while (1)
    {
    BEGIN:
        std::cout << "\n--------AirConnect Provisioning System--------\n\n";
        std::cout << "1. Customer\n";
        std::cout << "2. Provisioner\n";
        std::cout << "3. Exit\n";
        std::cin >> option;

        try
        {
            switch (option)
            {
            case 1:
                std::cout << "\n1. New connection request\n";
                std::cout << "2. Track exisiting connection request\n";
                std::cin >> option;
                std::cout << std::endl;

                switch (option)
                {
                case 1:

                    get_customer_details(new_customer);
                    std::cout << "\nChoose a connection type: \n";
                    std::cout << "1. Prepaid\n";
                    std::cout << "2. Postpaid\n";
                    std::cin >> option;

                    switch (option)
                    {
                    case 1:
                        std::cout << "\n1. New Number\n";
                        std::cout << "2. Port In\n";
                        std::cin >> option;
                        std::cout << std::endl;

                        switch (option)
                        {
                        case 1:
                            new_connection_prepaid(*new_customer, mobile_connections);
                            paid = make_payment(pay);
                            paid ? payment_success_message(mobile_connections) : payment_failure_message(mobile_connections);
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            break;

                        case 2:
                            port_in_prepaid(*new_customer, mobile_connections);
                            paid = make_payment(pay);
                            paid ? payment_success_message(mobile_connections) : payment_failure_message(mobile_connections);
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            break;

                        default:
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            std::cout << "Invalid Option" << std::endl;
                        }
                        break;

                    case 2:
                        std::cout << "\n1. New Number\n";
                        std::cout << "2. Port In\n";
                        std::cin >> option;
                        std::cout << std::endl;

                        switch (option)
                        {
                        case 1:
                            new_connection_postpaid(*new_customer, mobile_connections);
                            paid = make_payment(pay);
                            paid ? payment_success_message(mobile_connections) : payment_failure_message(mobile_connections);
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            break;

                        case 2:
                            port_in_postpaid(*new_customer, mobile_connections);
                            paid = make_payment(pay);
                            paid ? payment_success_message(mobile_connections) : payment_failure_message(mobile_connections);
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            break;

                        default:
                            delete pay;
                            pay = nullptr;
                            delete new_customer;
                            new_customer = nullptr;
                            std::cout << "Invalid option!" << std::endl;
                        }
                        break;

                    default:
                        delete pay;
                        pay = nullptr;
                        delete new_customer;
                        new_customer = nullptr;
                        std::cout << "Invalid option!" << std::endl;
                    }
                    break;

                case 2:
                    std::cout << "Enter your CRN: ";
                    std::cin >> crn;

                    search = false;
                    for (Mobile &connection : mobile_connections)
                    {
                        if (connection.get_crn() == crn)
                        {
                            search = true;
                            std::cout << "Status: " << connection.get_status() << std::endl;
                            if (connection.get_status() == "Provisioned")
                            {
                                connection.display_no();
                            }
                            else if ((connection.get_status() == "Pending") && (connection.get_reason() == "Payment failed"))
                            {
                                char option{};
                                std::cout << "Payment not yet done!" << std::endl;
                                std::cout << "Do you want to retry payment? (Y/N)";
                                std::cin >> option;
                                if (option == 'Y' || option == 'y')
                                {
                                    paid = make_payment(pay);
                                    if (paid == false)
                                    {
                                        std::cout << "Transaction Failed! Your request will be submitted only upon successful payment\n";
                                    }
                                    else
                                    {
                                        std::cout << "Connection request placed successfully!\n";
                                        connection.set_reason("");
                                    }
                                    delete pay;
                                    pay = nullptr;
                                }
                                else if (option == 'N' || option == 'n')
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Invalid input";
                                    break;
                                }
                            }
                            else if (connection.get_status() == "Rejected")
                            {
                                std::cout << "Reason: " << connection.get_reason() << std::endl;
                            }
                        }
                    }
                    if (search == false)
                    {
                        std::cout << "Invalid CRN!" << std::endl;
                    }
                    break;

                default:
                    std::cout << "Invalid choice";
                }
                break;

            case 2:
                if (verify_prov_id())
                {
                    while (1)
                    {
                        std::cout << std::endl;
                        Mobile::display_stats();
                        std::cout << "----------------------------------\n";
                        std::cout << "1. View Pending Requests\n";
                        std::cout << "2. View Rejected Requests\n";
                        std::cout << "3. View Provisioned Requests\n";
                        std::cout << "4. Exit\n";
                        std::cin >> option;
                        std::cout << std::endl;

                        switch (option)
                        {
                        case 1:
                            for (const Mobile &connection : mobile_connections)
                            {
                                if ((connection.get_status() == "Pending") && (connection.get_reason() != "Payment failed"))
                                {
                                    std::cout << connection;
                                }
                            }
                            std::cout << "Enter the CRN you want to provision/reject: ";
                            std::cin >> crn;
                            search = false;
                            for (Mobile &connection : mobile_connections)
                            {
                                if (connection.get_crn() == crn)
                                {
                                    search = true;
                                    std::string reason{};
                                    std::cout << "1. Provision\n";
                                    std::cout << "2. Reject\n";
                                    std::cin >> option;
                                    std::cout << std::endl;

                                    switch (option)
                                    {
                                    case 1:
                                        mobile_provisioning(connection);
                                        Mobile::prov_increment();
                                        std::cout << "Provisioned Successfully!" << std::endl;
                                        break;

                                    case 2:
                                        connection.set_status("Rejected");
                                        std::cout << "Enter the reason: ";
                                        std::getline(std::cin >> std::ws, reason);
                                        connection.set_reason(reason);
                                        Mobile::rej_increment();
                                        std::cout << "Rejected!" << std::endl;
                                        break;

                                    default:
                                        std::cout << "Invalid choice" << std::endl;
                                    }
                                }
                            }
                            if (search == false)
                            {
                                std::cout << "Invalid CRN!" << std::endl;
                                break;
                            }
                            break;

                        case 2:
                            for (const Mobile &connection : mobile_connections)
                            {
                                if (connection.get_status() == "Rejected")
                                {
                                    std::cout << connection;
                                }
                            }
                            break;

                        case 3:
                            for (const Mobile &connection : mobile_connections)
                            {
                                if (connection.get_status() == "Provisioned")
                                {
                                    std::cout << connection;
                                }
                            }
                            break;

                        case 4:
                            goto BEGIN;

                        default:
                            break;
                        }
                    }
                }
                else
                {
                    std::cout << "Authentication failed!";
                }
                break;

            case 3:
                try
                {
                    write_to_file(mobile_connections);
                }
                catch (const char* msg)
                {
                    std::cout << msg << " Error writing to file!!!" << std::endl;
                }
                return 0;

            default:
                std::cout << "Invalid choice";
            }
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
    }
    return 0;
}