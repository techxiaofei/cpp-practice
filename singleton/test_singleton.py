class Singleton(object):
    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            cls._instance = super(Singleton, cls).__new__(cls, *args, **kwargs)
        print('__new__')
        return cls._instance

    def __call__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            cls._instance = super(Singleton, cls).__call__(*args, **kwargs)
        print('__call__')
        return cls._instance

class Foo(Singleton):
    pass

print('1')
foo1 = Foo()
#print('2')
#foo2 = Foo()

#print(foo1 is foo2)  # True