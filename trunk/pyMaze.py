#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      Gust
#
# Created:     21/04/2012
# Copyright:   (c) Gust 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

def main():
    pass

if __name__ == '__main__':
    main()

import numpy as np
from numpy.random import random_integers as rnd
import matplotlib.pyplot as plt

def maze(width=80, height=40, complexity=.75, density =.75):
    # Only odd shapes
    shape = ((height//2)*2+1, (width//2)*2+1)
    # Adjust complexity and density relative to maze size
    complexity = int(complexity*(5*(shape[0]+shape[1])))
    density    = int(density*(shape[0]//2*shape[1]//2))
    # Build actual maze
    Z = np.zeros(shape, dtype=bool)
    # Fill borders
    Z[0,:] = Z[-1,:] = 1
    Z[:,0] = Z[:,-1] = 1
    # Make isles
    for i in range(density):
        x, y = rnd(0,shape[1]//2)*2, rnd(0,shape[0]//2)*2
        Z[y,x] = 1
        for j in range(complexity):
            neighbours = []
            if x > 1:           neighbours.append( (y,x-2) )
            if x < shape[1]-2:  neighbours.append( (y,x+2) )
            if y > 1:           neighbours.append( (y-2,x) )
            if y < shape[0]-2:  neighbours.append( (y+2,x) )
            if len(neighbours):
                y_,x_ = neighbours[rnd(0,len(neighbours)-1)]
                if Z[y_,x_] == 0:
                    Z[y_,x_] = 1
                    Z[y_+(y-y_)//2, x_+(x-x_)//2] = 1
                    x, y = x_, y_
    return Z

tfile = open("exportTEST.txt", "w")
mapa = maze(81,41)
tfile.write("81-41\n")
for i in range(0,41):
    for j in range(0,81):
        tfile.write("[")
        if(mapa[i,j]):
            tfile.write("1")
        else:
            tfile.write("2")
        tfile.write("] ")
    tfile.write("\n")

tfile
tfile.close()

plt.figure(figsize=(10,5))
plt.imshow(maze(80,40),cmap=plt.cm.binary,interpolation='nearest')
plt.xticks([]),plt.yticks([])
plt.show()