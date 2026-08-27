# Details for test-udf-runner-python-v1

This flavor provides a lightweight CPU-only test build for the Python UDF
runner.

It is derived from `template-Exasol-all-python-3.10` and uses the template's
build, test, release, and security-scan stages. The flavor-specific CI
configuration runs the core Python tests and language-definition setup checks.
