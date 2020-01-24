
'''
Assumption:
    1. we have a database for all email and its matching password, user_info
    2. user_info is the same as email address
'''
import pytest

from auth_function import *

def test_valid_email():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    assert auth_login("minglang@gmail.com", "12345678") == user_info

    user_info = auth_register("liyu@unsw.edu.au", "qwertyuio", "li", "yu")
    assert auth_login("liyu@unsw.edu.au", "qwertyuio") == user_info

    user_info = auth_register("zeyi@yahoo.com", "zxcvbn12", "zeyi", "lim")
    assert auth_login("zeyi@yahoo.com", "zxcvbn12") == user_info

    
    user_info = auth_register("kar@edu.unsw.edu.au", "zxcvbn12", "kar", "chan")
    assert auth_login("kar@edu.unsw.edu.au", "zxcvbn12") == user_info

def test_invalid_email():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    with pytest.raises(ValueError) as e:
        auth_login("minglang_gmail.com", "12345678")
    assert str(e) == "Email entered is not a valid email"   
    
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    with pytest.raises(ValueError) as e:
        auth_login("", "12345678")
    assert str(e) == "Email entered is not a valid email"  

    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    with pytest.raises(ValueError) as e:
        auth_login("1324sdvva.com", "12345678")
    assert str(e) == "Email entered is not a valid email" 

def test_invalid_password():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    with pytest.raises(ValueError) as e:
        auth_login("minglang@gmail.com", "")
    assert str(e) == "Your Sign On details are incorrect" 

    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    with pytest.raises(ValueError) as e:
        auth_login("minglang@gmail.com", "98765432")
    assert str(e) == "Your Sign On details are incorrect" 

def test_invalid_login():
    with pytest.raises(ValueError) as e:
        auth_login("minglang@gmail.com", "98765432")
    assert str(e) == "Email entered does not belong to a user" 
    
    
    
