import sys, random, argparse
import numpy as np
import math
from PIL import Image
from print_in_console import print_in_console
from print_with_turtle import print_with_turtle

gscale1 = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
gscale2 = '@%#*+=-:. '


def getAverage(image):

    information = np.array(image)
    w,h=information.shape
    return np.average(information.reshape(w*h))


def convertImageToAscii(fileName,cols, scale, morelevels):

    image= Image.open(fileName).convert('L')

    W,H = image.size[0], image.size[1]

    print('Input image dims: %d x %d' %(W,H))

    w=W/cols

    h =w/scale
    rows= int(H/h)

    print("cols: %d, rows: %d" %(cols,rows))
    print('tile dims: %d x %d' %(w,h))

    if cols> W or rows>H:
        print("Image is too small for specified cols")
        exit(0)


    aimg=[]

    for i in range(rows):
        y1=int(i*h)
        y2=int((i+1)*h)

        if i==rows-1:
            y2=H

        aimg.append("")

        for j in range(cols):
            x1=int(j*w)
            x2=int((j+1)*w)

            if x2==cols-1:
                x2=W

            portion=image.crop((x1,y1,x2,y2))
            bright=int(getAverage(portion))

            if morelevels:
                asciivalue=gscale1[int((bright*69)/255)]
            else:
                asciivalue = gscale2[int((bright*9)/255)]


            aimg[i] += asciivalue

    return aimg

def main():

    descStr = "This program converts an image into Ascii art"
    parser = argparse.ArgumentParser(descStr)

    parser.add_argument('--file', dest='imgFile', required = True)
    parser.add_argument('--way', dest='way', required = True)
    parser.add_argument('--scale', dest='scale', required=False)
    parser.add_argument('--out', dest='outFile', required=False)
    parser.add_argument('--cols',dest='cols', required=False)
    parser.add_argument('--morelevels',dest='moreLevels', action='store_true' )

    args= parser.parse_args()

    imgFile= args.imgFile

    outFile='out.txt'
    if args.outFile:
        outFile= args.outFile

    scale=0.43
    if args.scale:
        scale=float(args.scale)

    cols=80
    if args.cols:
        cols=int(args.cols)

    aimg = convertImageToAscii(imgFile ,cols,scale,args.moreLevels)

    f=open(outFile, 'w')

    for row in aimg:
        f.write(row + "\n")

    f.close()
    print('Ascii art has been saved to %s' % outFile)

    if args.way == '1':
        print_in_console(outFile)
    elif args.way == '2':
        print_with_turtle(outFile)

if __name__ == "__main__":
    main()