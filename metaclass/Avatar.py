#import sys
#sys.path.append("./")

from MetaClass import MetaClass

class Avatar(metaclass=MetaClass):
    def __init__(self):
        print("Avatar init")
    
    def func1(self):
        print("func1")
    

if __name__ == "__main__":

    print(hasattr(Avatar, "func1"))
    print(hasattr(Avatar, "func2"))
    a = Avatar()
    a.func1()
    a.func2()
    a.func3()
