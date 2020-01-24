class AccessError:
    pass 

def channel_invite(token, channel_id, u_id):
    pass 
    # return {}

def channel_details(token, channel_id):
    pass
    # return {name, owner_members, all_members}

def channel_messages(token, channel_id, start):
    pass
    # return {messages, start, end}

def channel_leave(token, channel_id):
    pass
    # return {}

def channel_join(token, channel_id):
    pass
    # return {}

def channel_addowner(token, channel_id, u_id):
    pass
    # return {}

def channel_removeowner(token, channel_id, u_id):
    pass
    # return {}

def channels_list(token):
    pass
    # return {channels}

def channels_listall(token):
    pass
    # return {channels}

def channels_create(token, name, is_public):
    pass
    # return {channel_id}
