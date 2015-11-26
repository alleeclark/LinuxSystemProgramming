import os

bsize = 1638
fin = os.open("foo", os.O_RDONLY)
fout = os.open("bar", os.O_WRONLY | os.O_CREAT, 0o644)

while 1:
    buf = os.read(find, bsize) # returns a new buffer each time and the old ones are garbage collected
    if buf:
        os.write(fout, buf)
    else:
        break

os.close(fin)
os.close(fout)