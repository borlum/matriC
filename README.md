matriC by #roevhat
==================
A hobby project for learning C. Implementing linear algebra and the concepts of matrix calculations in a C program. The purpose is to cover the basics of first year linear algebra, and to construct a simple to use CLI.

Usage
-----
matriC (pronounced ma-tri-ce, shortname = ma3c) is at its current stage able to find the row echelon and reduced row echelon form of any matrix. Though atm. the maximum size is limited to 100x100.
The tool has the following commandline syntax:

    ma3c -(Arguments) (input)

There are a few arguments to choose from. 2 main arguments: R or I. Whether to find the reduced row echelon form (R), or the inverse (I) of the given matrix. Further more, you can specify if you want expanded output with the sub-argument all (all). The syntax is then:

    ma3c -Rall (input)

Or

    ma3c -Iall (input)

It is also possible to time the calculations, and get result in microseconds. This is added with the sub-argument t:

    ma3c -(R/I)t (input)

You can specify both expanded output and the timer:

    ma3c -(R/I)allt (input)

The order at which you pass the arguments is meaningless; this is just as valid:

    ma3c -tallR (input)

The input argument is per default specified as a matrix in matlab format ([1 2 3; 5 6 7;]).
Though the format is very strict at this point, so you have to include a trailing semicolon:

    ma3c -R "[1 2 3; 4 5 6;]"

You also have the possibility of loading the matrix from a plain file. To do this, specify the sub-argument f (f), and instead of the matrix in matlab format, you pass along the file location:

    ma3c -Rf mymatrix