#!/usr/bin/python3  tell linux what interpreter to use
import os
#create file if does not exist, same premission as in code
fout = os.open("foo", os.O_WRONLY| os.O_CREAT, 0o644)

os.write(fout, bytes("hello world", "utf-8"))
os.close(fout)