#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

int verify_prov_id();
void mobile_provisioning(Mobile &connection);
void get_customer_details(Customer *&new_customer);
void new_connection_prepaid(Customer &new_customer, std::vector<Mobile> &mobile_connections);
void port_in_prepaid(Customer &new_customer, std::vector<Mobile> &mobile_connections);
void new_connection_postpaid(Customer &new_customer, std::vector<Mobile> &mobile_connections);
void port_in_postpaid(Customer &new_customer, std::vector<Mobile> &mobile_connections);
bool make_payment(Payment *&pay);

#endif