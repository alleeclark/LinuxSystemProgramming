#add up sizes of all files in current directory

import os
total = 0

for file in os.listdir(".") : # returns a list of files
    statinfo = os.stat(file) ## stat the file
    total = total + statinfo.st_size # add the size in to the running total

print ("total is", total)