cmake_minimum_required(VERSION 3.10)
project(aml-crypto-checker-tool VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aml_crypto_checker
    src/main.cpp
    src/aml_checker.cpp
    src/transaction.cpp
    src/risk_evaluator.cpp
)

target_include_directories(aml_crypto_checker PRIVATE include)

enable_testing()
add_test(NAME test_aml_checker COMMAND aml_crypto_checker --test)