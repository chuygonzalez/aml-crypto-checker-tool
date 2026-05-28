#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>

struct Transaction {
    std::string tx_id;
    std::string from_address;
    std::string to_address;
    double amount;
    std::string currency;
    long timestamp;
};

std::vector<Transaction> parse_transactions(const std::string& filepath);

#endif