#include "aml_checker.h"
#include <algorithm>
#include <iostream>

AMLChecker::AMLChecker() {
    load_sanctions_list();
}

void AMLChecker::load_sanctions_list() {
    sanctioned_addresses = {
        "0xSanctionedAddress1",
        "0xSanctionedAddress2",
        "0xBadActorWallet3"
    };
    high_risk_currencies = {"XMR", "DASH", "ZEC"};
}

bool AMLChecker::is_sanctioned_address(const std::string& address) {
    return std::find(sanctioned_addresses.begin(), sanctioned_addresses.end(), address) != sanctioned_addresses.end();
}

bool AMLChecker::is_high_risk_amount(double amount, const std::string& currency) {
    if (currency == "BTC" && amount > 10.0) return true;
    if (currency == "ETH" && amount > 100.0) return true;
    if (currency == "USDT" && amount > 50000.0) return true;
    return false;
}

std::vector<std::string> AMLChecker::check_transaction(const Transaction& tx) {
    std::vector<std::string> flags;
    if (is_sanctioned_address(tx.from_address) || is_sanctioned_address(tx.to_address)) {
        flags.push_back("SANCTIONED_ADDRESS");
    }
    if (is_high_risk_amount(tx.amount, tx.currency)) {
        flags.push_back("HIGH_RISK_AMOUNT");
    }
    if (std::find(high_risk_currencies.begin(), high_risk_currencies.end(), tx.currency) != high_risk_currencies.end()) {
        flags.push_back("PRIVACY_COIN");
    }
    return flags;
}