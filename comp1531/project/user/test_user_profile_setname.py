'''
Assumption:
    1. 
'''
import pytest
from auth_function import *
from user_function import *

def test_user_profile_setname():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    name_first = "mingpeng"
    name_last = "Xie"
    handle = "lang"

    old_profile = user_profile(user_info["token"])
    user_profile_setname(user_info["token"], name_first, name_last)
    new_profile = user_profile(user_info["token"])
    assert new_profile is not old_profile

def test_user_profile_setname_fail1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    name_first = "minglang" * 50
    name_last = "Xie"
    handle = "lang"

    with pytest.raises(ValueError) as e:
        user_profile_setname(user_info["token"], name_first, name_last)
    assert str(e) == "name_first is more than 50 characters"

def test_user_profile_setname_fail2():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    name_first = "minglang"
    name_last = "Xie" * 50
    handle = "lang"
    
    with pytest.raises(ValueError) as e:
        user_profile_setname(user_info["token"], name_first, name_last)
    assert str(e) == "name_last is more than 50 characters"

