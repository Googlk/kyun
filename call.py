#!/bin/env python
# coding=UTF-8
import ctypes
from ctypes import *

# def callfoo():
#     #print 'input:\n%s' %str_in
#     #调用库
#     input = ctypes.c_char_p()  #对应c指针类型 char *p
#     # input.value=str_in  #字符串赋值
#     ll = ctypes.cdll.LoadLibrary
#     lib = ll("./libtest.so")  #调用so
#     p=ctypes.create_string_buffer(50) #申请出参的内存大小
#     lib.test()
#     print(p.raw)     #出参的访问方式
# python中结构体定义
# names = c_char(44)

class StructPointer ( Structure ) :
    _fields_ = [("names", c_ubyte*44)]


if __name__ == "__main__":
    # callfoo()
    lib = cdll.LoadLibrary("./libtest.so")
    # age = c_char_p('abc')
    # t = StructPointer()
    lib.test.restype = POINTER(StructPointer)
    # t.age = age
    # print(type(age))
    # print(len(age))
    val = bytes('192.168.1.152', encoding='utf-8')
    # lib.strTest(val)

    for i in range(0,3):
        p = lib.test(val)
        listy = list(bytes(p.contents.names))
        for i in range(len(listy)):
            print("%02X " % listy[i], end="")

    # print("%s: %d" % (p.contents.names, p.contents.age))
        # print(type(p.contents.names))
        # print(len(p.contents.names))
    # print("call C")
    # p = lib.test(val)
    # listy = list(bytes(p.contents.names))
    # for i in range(len(listy)):
    #     print("%02X " % listy[i], end="")
