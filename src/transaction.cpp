#include "transaction.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Transaction> parse_transactions(const std::string& filepath) {
    std::vector<Transaction> transactions;
    std::ifstream file(filepath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return transactions;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Transaction tx;
        std::getline(ss, tx.tx_id, ',');
        std::getline(ss, tx.from_address, ',');
        std::getline(ss, tx.to_address, ',');
        std::string amount_str;
        std::getline(ss, amount_str, ',');
        tx.amount = std::stod(amount_str);
        std::getline(ss, tx.currency, ',');
        std::string ts_str;
        std::getline(ss, ts_str, ',');
        tx.timestamp = std::stol(ts_str);
        transactions.push_back(tx);
    }

    file.close();
    return transactions;
}