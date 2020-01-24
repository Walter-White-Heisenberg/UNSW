'''
Assumption:

'''
import pytest
from datetime import datetime as dt
from auth_function import *
from channel_function import *
from stand_up_function import *

def test_standup_start_success():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    time_start = dt.now()
    time_finish = standup_start(token, channel_id)
    assert (time_start.minute + 15) == time_finish.minute

    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    auth_login("minglang@gmail.com", "12345678")

    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    time_start = dt.now()
    time_finish = standup_start(token, channel_id)
    u_id = 5228006

    standup_send(token, channel_id, "hi")
    assert channel_messages(token, channel_id, 0) == {{"u_id": u_id, "message": "hi", "time_created": time_finish, "is_unread": False}, 0, -1}
    assert (time_start.minute + 15) == time_finish

def test_standup_start_fail1():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")
    
    channel_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    with pytest.raises(ValueError) as e:
        standup_start(token, channel_id * (-1))
    assert str(e) == "Channel (based on ID) does not exist"

def test_standup_start_fail2():
    user_info = auth_register("minglang@gmail.com", "12345678", "minglang", "xie")
    token = user_info["token"]

    auth_login("minglang@gmail.com", "12345678")
    
    user_info = channels_create(token, "credible4", True)
    channel_id = channel_info["channel_id"]

    auth_logout(token)

    user_info2 = auth_register("liyu@gmail.com", "987654321", "li", "yu")
    token2 = user_info2["token"]

    auth_login("liyu@gmail.com", "987654321")
    
    with pytest.raises(AccessError) as e:
        standup_start(token2, channel_id)
    assert str(e) == "The authorised user is not a member of the channel that the message is within"
