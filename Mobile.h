#include <iostream>
#include "Customer.h"

class Mobile : public Customer
{
    static int no_of_connections_requests;
    std::string type;
    std::string connection_type;
    std::string mobile_no;
    std::string status;
    std::string iccid;
    std::string upc;
    std::string reason;
    std::string crn;
    int otp;

    friend void mobile_provisioning(Mobile&);
    friend std::ostream& operator << (std::ostream&,const Mobile&);

    void verify_no();
    void verify_upc();
    void generate_crn();
    void generate_mobile_no();

    public:

    Mobile(std::string name,unsigned int pincode,std::string aadhaar_no,std::string email,std::string_view connection_type);

    Mobile(std::string name,unsigned int pincode,std::string aadhaar_no,std::string email,std::string_view connection_type,std::string mobile_no);

    std::string get_status() const;

    void set_status(std::string s);

    void display_details() const;

    std::string get_crn() const;
};
