# Questions

## What's `stdint.h`?
It's a header file in C99 library.

TODO

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
To store data of different lengths, such as, 8, 32, 32, and 16 bits, respectively.

TODO

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
1, 4, 4, and 2 bytes.

TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
The first two bytes of any BMP file are used to identify the file. A typical application reads this block (the first two bytes) first to ensure that the file is actually a BMP file and that it is not damaged. The first 2 bytes of the BMP file format are the character "B" and "M" in ASCII or 0x4D42 in hexadecimal.

TODO

## What's the difference between `bfSize` and `biSize`?
bfSize and biSize are the data members of BITMAPFILEHEADER and BITMAPINFOHEADER, respectively. bfSize stores the size of the bitmap file in bytes; whereas, biSize stores the number of bytes required by the structure. 

TODO

## What does it mean if `biHeight` is negative?
If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

TODO

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits that define each pixel and the maximum number of colors in the bitmap. 

TODO

## Why might `fopen` return `NULL` in `copy.c`?
The function fopen might returns NULL, when the file is actually not present on the disk or it is opened in a mode that doesn't allow other accesses.

TODO

## Why is the third argument to `fread` always `1` in our code?
The main reason is because we wanted to copy file pixel-by-pixel,i.e, read the 1 pixel from source file and write it in destination file simultaneously.

TODO

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?
int padding = (4 - (3 * 3) % 4) % 4 = (4 - 9 % 4) % 4 = (4 - 1) % 4 = 3 % 4 = 3 

TODO

## What does `fseek` do?
Fseek allows to rewind or fast-forward within a file (changes the location of the file pointer). In copy.c fseek skips over padding, if any, and looks for the next pixel.

TODO

## What is `SEEK_CUR`?
This is an integer constant which, when used as the whence argument to the fseek function, specifies that the padding provided is relative to the current file position.