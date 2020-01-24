'''
(outputs only) named exactly messages

List of dictionaries, where each dictionary contains types {u_id, message, time_created, is_unread}
Assumption:
    1. u_id sent by frontend, don't need to worried
'''
import pytest
import datetime
from auth_function import *
from message_function import *
from channel_function import *

def test_message_send():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "comp1531", True)
    channel_id = channel_info["channel_id"]

    message = "hi"
    u_id = 5228006  # assume frontend send this u_id
    
    message_send(token, channel_id, message)
    time = datetime.datetime.now()
    assert channel_messages(token, channel_id, 0) == {{"u_id": u_id, "message": "hi", "time_created": time, "is_unread": False}, 0, -1}

def test_message_send_fail1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "comp1531", True)
    channel_id = channel_info["channel_id"]

    message = "hi"
    u_id = 5228006  # assume frontend send this u_id

    with pytest.raises(ValueError) as e:
        message_send(token, channel_id, message)
    assert str(e) == "Message is more than 1000 characters"

