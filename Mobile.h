#include <vector>
#ifndef MOBILE_H
#define MOBILE_H

class Mobile : public Customer
{
    static unsigned int total_no_of_connections_requests;
    static unsigned int no_of_pending_requests;
    static unsigned int no_of_provisioned_requests;
    static unsigned int no_of_rejected_requests;

    std::string type{};
    std::string connection_type{};
    std::string mobile_no{};
    std::string status{};
    std::string iccid{};
    std::string upc{};
    std::string reason{};
    std::string crn{};
    int otp{};

    friend void write_to_file(const std::vector<Mobile> &mobile_connections);
    friend void mobile_provisioning(Mobile &);
    friend std::ostream &operator<<(std::ostream &, const Mobile &);

    void verify_no();
    void verify_upc();
    void generate_crn();
    void generate_mobile_no();

public:
    Mobile(const Customer &customer_info, std::string_view c_type);
    Mobile(const Customer &customer_info, std::string_view c_type, std::string m_no);
    Mobile(std::string name,unsigned int pincode,std::string aadhaar,std::string email,std::string type,std::string c_type,std::string m_no,std::string status,std::string iccid,std::string reason,std::string crn);
    std::string get_status() const;
    void set_status(std::string_view s);
    std::string get_crn() const;
    std::string get_reason() const;
    void set_reason(std::string_view r);
    void display_no() const;
    static void display_stats();
    static void prov_increment();
    static void rej_increment();
};

#endif
