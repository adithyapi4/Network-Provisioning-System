#ifndef MOBILE_H
#define MOBILE_H
#include <vector>

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

    friend void write_to_file(const std::vector<Mobile> &mobile_connections);
    friend void mobile_provisioning(Mobile &);
    friend std::ostream &operator<<(std::ostream &, const Mobile &);

    void verify_no();
    void verify_upc();
    void generate_crn();
    void generate_mobile_no();

public:
    Mobile(const Customer &customer_info, const std::string_view &c_type);
    Mobile(const Customer &customer_info, const std::string_view &c_type, const std::string &m_no);
    Mobile(const std::string &name, const std::string &pincode, const std::string &aadhaar, const std::string &email, const std::string &type, const std::string &c_type, const std::string &m_no, const std::string &status, const std::string &iccid, const std::string &reason, const std::string &crn);
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
