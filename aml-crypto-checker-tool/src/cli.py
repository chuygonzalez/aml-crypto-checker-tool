import argparse
import sys
from .checker import AMLCryptoChecker


def main():
    parser = argparse.ArgumentParser(description="AML Crypto Checker Tool")
    parser.add_argument("address", help="Cryptocurrency address to check")
    parser.add_argument(
        "--risk-db", "-r", default=None, help="Path to custom risk database JSON"
    )
    args = parser.parse_args()

    checker = AMLCryptoChecker(risk_db_path=args.risk_db)
    result = checker.check_address(args.address)

    print(f"Address: {result['address']}")
    print(f"Hash:    {result['address_hash']}")
    print(f"Risk:    {result['risk_level']}")
    print(f"Flagged: {result['flagged']}")

    if result["flagged"]:
        sys.exit(1)


if __name__ == "__main__":
    main()