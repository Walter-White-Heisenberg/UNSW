from flask import Flask
APP = Flask(__name__)

@APP.route("/hahaha")
def hello():
    return {"first" : "bkjjk", "second": 2 * 4 }
    
@APP.route("/first", method == ['POST'])
def byebye():

@APP.route("/first", method == ['GET'])
def byebye():

@APP.route("/first", method == ['DELETE'])
def byebye():
    
    
if __name__ == "__main__":
    APP.run(debug=1)
