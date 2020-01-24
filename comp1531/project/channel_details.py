'''
description:
channel_details(token, channel_id)
return: { name, owner_members, all_members }
ValueError when:Channel (based on ID) does not exist
AccessError when:Authorised user is not a member of channel with channel_id
function should :      Given a Channel with ID channel_id that the authorised user is part of, provide basic details about the channel
'''
'''
assumption:
1.the channel
2.the email in the channel_detail must be the valid

check for the non-existed channel id
'''

class AccessError(Exception):
    pass

def test_invalid_channel_id():
    assert auth_register("llalla@gmail.com", "12345678","llalla","lla") == {"token": "llalla@gmail.com"}  # success if assert return TRUE 
    with pytest.raise(ValueError) as e
        channel_details("llalla@gmail.com",1);
    assert str(e) == "The id doesn't exist"

def test_invalid_channel_id():
    assert auth_register("llalla@gmail.com", "12345678","llalla","lla") == {"token": "llalla@gmail.com"}  # success if assert return TRUE 
    channel_invite()
    with pytest.raise(AccessError) as e
        channel_details("llalla@gmail.com",1);
    assert str(e) == "The id doesn't exist"
