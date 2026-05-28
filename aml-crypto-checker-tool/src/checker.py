import hashlib
import json
import os
from typing import Optional, Dict, Any

RISK_DATABASE = {
    "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa": "high",
    "bc1qar0srrr7xfkvy5l643lydnw9re59gtzzwf5mdq": "medium",
    "3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy": "low",
}


class AMLCryptoChecker:
    def __init__(self, risk_db_path: Optional[str] = None):
        self.risk_db: Dict[str, str] = {}
        if risk_db_path and os.path.exists(risk_db_path):
            with open(risk_db_path, "r") as f:
                self.risk_db = json.load(f)
        else:
            self.risk_db = RISK_DATABASE.copy()

    def check_address(self, address: str) -> Dict[str, Any]:
        address_hash = hashlib.sha256(address.encode()).hexdigest()[:16]
        risk_level = self.risk_db.get(address, "unknown")
        return {
            "address": address,
            "address_hash": address_hash,
            "risk_level": risk_level,
            "flagged": risk_level in ("high", "medium"),
        }

    def add_risk_entry(self, address: str, risk: str) -> None:
        if risk not in ("low", "medium", "high"):
            raise ValueError("Risk must be low, medium, or high")
        self.risk_db[address] = risk

    def export_risk_db(self, path: str) -> None:
        with open(path, "w") as f:
            json.dump(self.risk_db, f, indent=2)