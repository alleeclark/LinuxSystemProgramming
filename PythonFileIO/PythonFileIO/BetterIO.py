#using the built in open fucntion
with open('foo', 'rb') as fin:
    with open('bar', 'wb') as fout:
        fout.write(fin.read()) #slurping the file