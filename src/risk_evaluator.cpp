#include "risk_evaluator.h"
#include <cmath>

RiskEvaluator::RiskEvaluator() : threshold_high(0.8), threshold_medium(0.4) {}

double RiskEvaluator::calculate_risk_score(const Transaction& tx) {
    double score = 0.0;
    if (tx.amount > 10000) score += 0.3;
    if (tx.amount > 100000) score += 0.4;
    if (tx.currency == "XMR" || tx.currency == "DASH") score += 0.3;
    if (tx.from_address.find("0x0000000000000000000000000000000000000000") != std::string::npos) score += 0.5;
    score = std::min(score, 1.0);
    return score;
}

std::string RiskEvaluator::evaluate_risk_level(double score) {
    if (score >= threshold_high) return "HIGH";
    if (score >= threshold_medium) return "MEDIUM";
    return "LOW";
}

std::vector<std::string> RiskEvaluator::generate_alerts(const Transaction& tx) {
    std::vector<std::string> alerts;
    double score = calculate_risk_score(tx);
    std::string level = evaluate_risk_level(score);
    if (level == "HIGH") {
        alerts.push_back("IMMEDIATE_REVIEW_REQUIRED");
    } else if (level == "MEDIUM") {
        alerts.push_back("MANUAL_REVIEW_RECOMMENDED");
    }
    alerts.push_back("RISK_SCORE:" + std::to_string(score));
    return alerts;
}