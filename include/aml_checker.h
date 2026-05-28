#ifndef AML_CHECKER_H
#define AML_CHECKER_H

#include <string>
#include <vector>
#include "transaction.h"

class AMLChecker {
public:
    AMLChecker();
    bool is_sanctioned_address(const std::string& address);
    bool is_high_risk_amount(double amount, const std::string& currency);
    std::vector<std::string> check_transaction(const Transaction& tx);
private:
    std::vector<std::string> sanctioned_addresses;
    std::vector<std::string> high_risk_currencies;
    void load_sanctions_list();
};

#endif