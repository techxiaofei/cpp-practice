import types
import inspect
from Chat import Chat
from Item import Item

SaveObjMembers = {
    "Chat" : Chat,
    "Item" : Item,
}

class MetaClass(type):
    _class_filter_list = ('__module__', '__doc__')
    
    def __init__(cls, name, bases, dic):
        super().__init__(name, bases, dic)
        print("MetaClass init",cls)
        funset = set()
        #处理函数
        for memClsName, memCls in SaveObjMembers.items():
            print("out funcName:",memClsName, memCls)
            print("member:",inspect.getmembers(memCls))
            print("member:",inspect.getmembers(memCls, inspect.isfunction))
            for funcName, func in inspect.getmembers(memCls, inspect.isfunction):
                print("in funcName")
                if funcName in ('__init__', '__new__', '__call__', '__setattr__', '__str__'):
                    continue
                if funcName in funset:
                    raise Exception('got duplicate method name: %s, %s' % (memCls.__name__, funcName))
                funset.add(funcName)
                print("funcName:",funcName)
                setattr(cls, funcName, func)
        
            for membName, memb in inspect.getmembers(memCls):
                if membName in MetaClass._class_filter_list:
                    continue

                if isinstance(memb, int) or \
                    isinstance(memb, str) or\
                    isinstance(memb, bytes) or \
                    isinstance(memb, list) or \
                    isinstance(memb, dict) or \
                    isinstance(memb, tuple) or \
                    isinstance(memb, float) or \
                    isinstance(memb, set) or \
                    isinstance(memb, frozenset):
                    #检查属性是否重复
                    if hasattr(cls, membName):
                        raise Exception('got duplicate attr name: %s, %s' % (memCls.__name__, membName))
                    #设置属性内容
                    setattr(cls, membName, memb)
