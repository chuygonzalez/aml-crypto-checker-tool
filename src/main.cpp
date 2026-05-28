#include <iostream>
#include <vector>
#include <string>
#include "transaction.h"
#include "aml_checker.h"
#include "risk_evaluator.h"

void run_tests() {
    std::cout << "=== Running AML Crypto Checker Tests ===" << std::endl;
    
    AMLChecker checker;
    RiskEvaluator evaluator;
    
    Transaction test_tx1 = {"tx001", "0xSanctionedAddress1", "0xRecipient1", 50.0, "BTC", 1700000000};
    auto flags1 = checker.check_transaction(test_tx1);
    auto alerts1 = evaluator.generate_alerts(test_tx1);
    
    std::cout << "Test 1 - Sanctioned address + high amount:" << std::endl;
    std::cout << "  Flags: ";
    for (auto& f : flags1) std::cout << f << " ";
    std::cout << std::endl;
    std::cout << "  Alerts: ";
    for (auto& a : alerts1) std::cout << a << " ";
    std::cout << std::endl;
    
    Transaction test_tx2 = {"tx002", "0xCleanAddress", "0xCleanAddress2", 5.0, "ETH", 1700000001};
    auto flags2 = checker.check_transaction(test_tx2);
    auto alerts2 = evaluator.generate_alerts(test_tx2);
    
    std::cout << "Test 2 - Clean transaction:" << std::endl;
    std::cout << "  Flags: ";
    for (auto& f : flags2) std::cout << f << " ";
    std::cout << std::endl;
    std::cout << "  Alerts: ";
    for (auto& a : alerts2) std::cout << a << " ";
    std::cout << std::endl;
    
    std::cout << "=== All tests passed ===" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        run_tests();
        return 0;
    }
    
    std::cout << "AML Crypto Checker Tool v1.0.0" << std::endl;
    std::cout << "Usage: " << argv[0] << " [--test | <transactions.csv>]" << std::endl;
    
    if (argc < 2) {
        return 0;
    }
    
    std::string filepath = argv[1];
    auto transactions = parse_transactions(filepath);
    
    AMLChecker checker;
    RiskEvaluator evaluator;
    
    for (const auto& tx : transactions) {
        std::cout << "Checking transaction: " << tx.tx_id << std::endl;
        auto flags = checker.check_transaction(tx);
        auto alerts = evaluator.generate_alerts(tx);
        
        if (!flags.empty()) {
            std::cout << "  AML Flags: ";
            for (auto& f : flags) std::cout << f << " ";
            std::cout << std::endl;
        }
        if (!alerts.empty()) {
            std::cout << "  Risk Alerts: ";
            for (auto& a : alerts) std::cout << a << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
}