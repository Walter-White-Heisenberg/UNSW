'''
Assumption:
    1. password will change after calling the function auth_passwordreset_reset()
    2. reset_code is "RESET##"

'''
import pytest
from auth_function import *

def test_password_reset_success():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    auth_passwordreset_request("minglang@gmail.com")

    reset_code = "RESET01"
    new_password = "87654321"

    auth_passwordreset_reset(reset_code, new_password)
    assert auth_login("minglang@gmail.com", "87654321") == user_info

def test_password_reset_fail1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    auth_passwordreset_request("minglang@gmail.com")

    reset_code = "Resethi"
    new_password = "87654321"

    with pytest.raises(ValueError) as e:
        auth_passwordreset_reset(reset_code, new_password)
    assert str(e) == "reset_code is not a valid reset code"
    
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    auth_passwordreset_request("minglang@gmail.com")

    reset_code = ""
    new_password = "87654321"

    with pytest.raises(ValueError) as e:
        auth_passwordreset_reset(reset_code, new_password)
    assert str(e) == "reset_code is not a valid reset code"

def test_password_reset_fail2():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    auth_passwordreset_request("minglang@gmail.com")

    reset_code = "RESET01"
    new_password = ""
    
    with pytest.raises(ValueError) as e:
        auth_passwordreset_reset(reset_code, new_password)
    assert str(e) == "Password entered is not a valid password"