'''
(outputs only) named exactly channels

List of dictionaries, where each dictionary contains types {id, name}

Assumption:
    1. Channel_id always a positive number
    2. A user can have 0 or more channels
'''
import pytest
from auth_function import *
from channel_function import *

def test_channels_list1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "comp1531", True)
    channel_id = channel_info["channel_id"]

    assert channels_list(token) == [{"id": channel_id, "name": "comp1511"}]

    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    assert channels_list(token) == []

def test_channels_list2():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    # Assume these channels are already created
    channel_join(token, 53)
    channel_join(token, 2234)
    channel_join(token, 2)
    channel_join(token, 1)
    
    assert channels_list(token) == [{"id": 53, "name": "credible4"}, {"id": 2234, "name": "nice"}, {"id": 2, "name": "comp1521"}, {"id": 1, "name": "comp1511"}]