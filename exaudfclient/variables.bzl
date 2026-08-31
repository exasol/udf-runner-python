PYTHON_VM_ENABLED_DEFINE=select({
        "//:python": ["ENABLE_PYTHON_VM"],
        "//conditions:default": []
    })
VM_ENABLED_DEFINES=PYTHON_VM_ENABLED_DEFINE
