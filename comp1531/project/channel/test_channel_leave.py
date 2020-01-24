'''
Assumption:
    1. Channel_id always a positive number
    2. The user need to login first
'''
import pytest
from auth_function import *
from channel_function import *

def test_channel_leave_success():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    channel_leave(token, channel_id)
    assert channel_details(token, channel_id) == None

def test_channel_leave_fail1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    with pytest.raises(ValueError) as e:
        channel_leave(token, channel_id * (-1))
    assert str(e) == "Channel (based on ID) does not exist"

def test_channel_fail2():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    with pytest.raises(AccessError) as e:
        channel_leave(token, channel_id)
    assert str(e) == "Need to login first"
