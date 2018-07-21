def Singleton(cls):
    """装饰器"""
    _instance = None
    def wrap(*args, **kwargs):
        nonlocal _instance
        if _instance is None:
            _instance = cls(*args, **kwargs)
        return _instance
    return wrap

class Singleton2():
    """继承"""
    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, "_instance"):
            cls._instance = super().__new__(cls, *args, **kwargs)
        return cls._instance

class Singleton3(type):
    """MetaClass"""
    def __call__(cls, *args, **kwargs):
        if not hasattr(cls, "_instance"):
            cls._instance = super().__call__(*args, **kwargs)
        return cls._instance


#@Singleton
#class TestClass(Singleton2):
class TestClass(metaclass = Singleton3):
    def __init__(self):
        print("TestClass init")



if __name__ == "__main__":
    a = TestClass()
    b = TestClass()

    print("id of a:",id(a))
    print("id of b:",id(b))

#https://segmentfault.com/q/1010000007818814

