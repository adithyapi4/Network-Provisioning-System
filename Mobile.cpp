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

Mobile::Mobile(const Customer &customer_info, const std::string_view &c_type) : Customer(customer_info), type("NE"), connection_type(c_type), status("Pending")
{
    generate_crn();
    total_no_of_connections_requests++;
    no_of_pending_requests++;
}

Mobile::Mobile(const Customer &customer_info, const std::string_view &c_type, const std::string &m_no) : Customer(customer_info), type("PI"), connection_type(c_type), mobile_no(m_no), status("Pending")
{
    verify_no();
    verify_upc();
    generate_crn();
    total_no_of_connections_requests++;
    no_of_pending_requests++;
}

Mobile::Mobile(const std::string &name, const std::string &pincode, const std::string &aadhaar, const std::string &email, const std::string &type, const std::string &c_type, const std::string &m_no, const std::string &status, const std::string &iccid, const std::string &reason, const std::string &crn) : Customer(name, pincode, aadhaar, email), type(type), connection_type(c_type), mobile_no(m_no), status(status), iccid(iccid), reason(reason), crn(crn)
{
    total_no_of_connections_requests++;
    if (status == "Pending")
    {
        no_of_pending_requests++;
    }
    else if (status == "Provisioned")
    {
        no_of_provisioned_requests++;
    }
    else if (status == "Rejected")
    {
        no_of_rejected_requests++;
    }
}

inline std::string Mobile::get_status() const
{
    return status;
}

inline void Mobile::set_status(std::string_view s)
{
    status = s;
}

inline std::string Mobile::get_reason() const
{
    return reason;
}

inline void Mobile::set_reason(std::string_view r)
{
    reason = r;
}

void Mobile::verify_no()
{
    int otp;
    std::cout << "Enter the OTP sent to " << mobile_no << ": ";
    std::cin >> otp;
    if (otp < 0)
    {
        throw "Invalid OTP!";
    }
    std::cout << "Verified Successfully" << std::endl;
}

inline void Mobile::generate_crn()
{
    crn = type + connection_type + aadhaar_no.substr(8) + pincode.substr(1);
}

inline std::string Mobile::get_crn() const
{
    return crn;
}

inline void Mobile::generate_mobile_no()
{
    mobile_no = "93" + aadhaar_no.substr(8) + pincode.substr(2);
}

inline void Mobile::display_no() const
{
    std::cout << "Mobile Number: " << mobile_no << std::endl;
}

inline void Mobile::display_stats()
{
    std::cout << "Total number of connection requests: " << total_no_of_connections_requests;
    std::cout << "\nNumber of pending connection requests: " << no_of_pending_requests;
    std::cout << "\nNumber of provisioned connection requests: " << no_of_provisioned_requests;
    std::cout << "\nNumber of rejected connection requests: " << no_of_rejected_requests << std::endl;
}

void Mobile::prov_increment()
{
    if (no_of_pending_requests > 0)
        no_of_pending_requests--;
    no_of_provisioned_requests++;
}

void Mobile::rej_increment()
{
    if (no_of_pending_requests > 0)
        no_of_pending_requests--;
    no_of_rejected_requests++;
}

void Mobile::verify_upc()
{
    std::cout << "Enter your UPC Code: ";
    std::cin >> upc;
    if (upc.empty())
    {
        throw "Rejected! Invalid UPC code";
    }
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

        throw "Rejected! Invalid UPC code";
    }
}
