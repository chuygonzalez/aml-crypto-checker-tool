#ifndef RISK_EVALUATOR_H
#define RISK_EVALUATOR_H

#include <string>
#include <vector>
#include "transaction.h"

class RiskEvaluator {
public:
    RiskEvaluator();
    double calculate_risk_score(const Transaction& tx);
    std::string evaluate_risk_level(double score);
    std::vector<std::string> generate_alerts(const Transaction& tx);
private:
    double threshold_high;
    double threshold_medium;
};

#endif