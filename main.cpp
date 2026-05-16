#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include "Customer.h"
#include "Mobile.h"
#include "Payment.h"
#include "Card.h"
#include "misc_functions.h"

int main()
{
    Customer* new_customer{};
    std::vector<Mobile> mobile_connections;
    Payment* pay{};
    bool paid{};
    std::string crn;
    unsigned int option;

    while (1)
    {
        std::cout << "--------AirConnect Provisioning System--------\n\n";
        std::cout << "1. Customer\n";
        std::cout << "2. Provisioner\n";
        std::cout << "3. Exit\n";
        std::cin >> option;
        if (option == 3)
            return 0;
        try
        {
            switch (option)
            {
            case 1:
                get_customer_details(new_customer);
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
                        new_connection_prepaid(*new_customer,mobile_connections);
                        paid = make_payment(pay);
                        if(paid == false)
                        {
                            std::cout<<"Transaction Failed! Your request will be submitted upon successful payment\n";
                            std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                            std::cout<<"You can retry the payment using the given CRN!"<<std::endl;
                        }
                        std::cout<<"Connection request placed successfully!\n";
                        std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                        std::cout<<"To track your connection request use the given CRN!"<<std::endl;
                        delete pay;
                        delete new_customer;
                        break;

                    case 2:
                        port_in_prepaid(*new_customer,mobile_connections);
                        paid = make_payment(pay);
                        if(paid == false)
                        {
                            std::cout<<"Transaction Failed! Your request will be submitted upon successful payment\n";
                            std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                            std::cout<<"You can retry the payment using the given CRN!"<<std::endl;
                        }
                        std::cout<<"Connection request placed successfully!\n";
                        std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                        std::cout<<"To track your connection request use the given CRN!"<<std::endl;
                        delete pay;
                        delete new_customer;
                        break;

                    default:
                        delete new_customer;
                        delete pay;
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
                        new_connection_postpaid(*new_customer,mobile_connections);
                        paid = make_payment(pay);
                        if(paid == false)
                        {
                            std::cout<<"Transaction Failed! Your request will be submitted upon successful payment\n";
                            std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                            std::cout<<"You can retry the payment using the given CRN!"<<std::endl;
                        }
                        std::cout<<"Connection request placed successfully!\n";
                        std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                        std::cout<<"To track your connection request use the given CRN!"<<std::endl;
                        delete pay;
                        delete new_customer;
                        break;

                    case 2:
                        port_in_postpaid(*new_customer,mobile_connections);
                        paid = make_payment(pay);
                        if(paid == false)
                        {
                            std::cout<<"Transaction Failed! Your request will be submitted upon successful payment\n";
                            std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                            std::cout<<"You can retry the payment using the given CRN!"<<std::endl;
                        }
                        std::cout<<"Connection request placed successfully!\n";
                        std::cout<<"CRN: "<< mobile_connections.back().get_crn() <<std::endl;
                        std::cout<<"To track your connection request use the given CRN!"<<std::endl;
                        delete pay;
                        delete new_customer;
                        break;

                    default:
                        delete new_customer;
                        delete pay;
                        std::cout << "Invalid option!" << std::endl;
                    }
                    break;

                default:
                    delete new_customer;
                    delete pay;
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
                                    std::cout << connection;
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
                            std::cout << "Invalid CRN!" << std::endl;
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

                        default:
                            break;
                        }
                    }
                }

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