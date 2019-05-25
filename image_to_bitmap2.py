"""
Generates C++ character arrays containing encodings of bitmaps.

This script will search in a directory called "bitmaps", and convert any image
file there into a constant character array. The character array will have
the same name as the image without the extension. To use these arrays, you can
put "#include bitmaps.h" at the top of your Arduino program.

This script needs to be in directory containing the "bitmaps" directory (so,
one folder up from the image files themselves). For example, if the file
directories look like this:

MyCoolArduboyGame
 - MyCoolArduboyGame.ino
 - bitmaps
   - cat.png
   - dog.jpg
 - image_to_bitmap.py

and you run the script, two files will have been created, as such: 

MyCoolArduboyGame
 - MyCoolArduboyGame.ino
 - bitmaps
   - cat.png
   - dog.jpg
 - image_to_bitmap.py
 - bitmaps.cpp
 - bitmaps.h

Also, if you have an image file that ends in 'L' or 'R' (must be uppercase),
the script will also encode a flipped version of it too, with the opposite
name. So, "playerL.png" will result in two arrays, "playerL" and "playerR".

Because I don't fully understand how the drawBitmap function works, the script
only works on 8x8 images, and ignores any images that are not that size.
I guess in the future it could support those, and it would also need
some way of including the bitmap's dimensions.

Changelog:
v1.0 - First version. Works for 8x8 images only.
v1.1 - Updated this so that it also works for larger images!
"""

import os
import re
from PIL import Image

def getbitmapcode(image, spritename):
    """
    Creates the text that goes in a cpp and header file to encode an image
    """
    cpp_text = ('PROGMEM const unsigned char ' +
               spritename + '[] = {\n')
    h_text = ('extern const unsigned char ' +
             spritename + '[];\n')
    
    width, height = im.size
    # Break into chunks across the y axis
    for y in range(0, height, 8):
        for x in range(width):
            cpp_text += '\t0b'
            for y2 in reversed(range(8)):
                # Get the pixel
                if x < width and y + y2 < height:
                    pixels = im.getpixel((x, y + y2))
                    value = pixels[0] + pixels[1] + pixels[2]
                else:
                    # If the pixel is out of range, pad with black
                    value = 0

                if value < 0x180: # black
                    cpp_text += '0'
                else: #white
                    cpp_text += '1'
            cpp_text += ',\n'
        # Add a blank line to separate chunks
        cpp_text += '\n'
    cpp_text += '};\n\n'

    return (cpp_text, h_text)


files = [f for f in os.listdir('images') if
         re.match(r'\w+.*\.(png|jpg|jpeg|gif|tiff)', f)]

cpp_text = '#include "bitmaps.h"\n\n'
h_text = ('#ifndef BITMAPS_H\n' +
         '#define BITMAPS_H\n\n' +
         '#include <avr/pgmspace.h>\n\n')

images_saved = 0

for file in files:
    filepath = os.path.join('images', file)
    im = Image.open(filepath)
    spritename = os.path.splitext(file)[0]

    print(spritename)
    code = getbitmapcode(im, spritename)
    cpp_text += code[0]
    h_text += code[1]
    images_saved += 1

h_text += '\n#endif // BITMAPS_H'

if images_saved > 0:
    with open('bitmaps.cpp', 'w') as cpp_file:
        cpp_file.write(cpp_text)
    with open('bitmaps.h', 'w') as h_file:
        h_file.write(h_text)
