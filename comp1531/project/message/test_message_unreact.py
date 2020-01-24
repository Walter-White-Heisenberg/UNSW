'''
Assumption:
    1. this is not testable since we have not function to get a "react" list
'''
import pytest

from message_function import *

def test_message_unreact():
    pass

def test_message_unreact_fail1():
    try:
        message_unreact()
    except ValueError:
        assert True
    else:
        assert False

def test_message_unreact_fail2():
    try:
        message_unreact()
    except ValueError:
        assert True
    else:
        assert False

def test_message_unreact_fail3():
    try:
        message_unreact()
    except ValueError:
        assert True
    else:
        assert False
