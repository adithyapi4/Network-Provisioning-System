#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

bool verify_prov_id();
void mobile_provisioning(Mobile &connection);
void get_customer_details(Customer *&new_customer);
void new_connection_prepaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections);
void port_in_prepaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections);
void new_connection_postpaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections);
void port_in_postpaid(const Customer &new_customer, std::vector<Mobile> &mobile_connections);
bool make_payment(Payment *&pay);
void payment_failure_message(std::vector<Mobile> &mobile_connections);
void payment_success_message(const std::vector<Mobile> &mobile_connections);
inline std::string return_key();
std::string xor_encrypt(const std::string &data);
std::string xor_decrypt(const std::string &encrypted_data);
void read_from_file(std::vector<Mobile> &mobile_connections);
void write_to_file(const std::vector<Mobile> &mobile_connections);
void mobile_provisioning(Mobile &);
std::ostream &operator<<(std::ostream &, const Mobile &);
inline std::string return_prov_passwd();
std::string hash_gen(const std::string &data);

#endif