import pytest
import tempfile
import json
from src.checker import AMLCryptoChecker


class TestAMLCryptoChecker:
    def test_known_high_risk(self):
        checker = AMLCryptoChecker()
        result = checker.check_address("1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa")
        assert result["risk_level"] == "high"
        assert result["flagged"] is True

    def test_unknown_address(self):
        checker = AMLCryptoChecker()
        result = checker.check_address("unknown_address_123")
        assert result["risk_level"] == "unknown"
        assert result["flagged"] is False

    def test_add_risk_entry(self):
        checker = AMLCryptoChecker()
        checker.add_risk_entry("test_addr", "high")
        result = checker.check_address("test_addr")
        assert result["risk_level"] == "high"

    def test_invalid_risk_value(self):
        checker = AMLCryptoChecker()
        with pytest.raises(ValueError):
            checker.add_risk_entry("addr", "invalid")

    def test_export_and_load(self):
        with tempfile.NamedTemporaryFile(mode="w", suffix=".json", delete=False) as f:
            temp_path = f.name
        try:
            checker1 = AMLCryptoChecker()
            checker1.add_risk_entry("custom_addr", "low")
            checker1.export_risk_db(temp_path)

            checker2 = AMLCryptoChecker(risk_db_path=temp_path)
            result = checker2.check_address("custom_addr")
            assert result["risk_level"] == "low"
        finally:
            import os
            os.unlink(temp_path)