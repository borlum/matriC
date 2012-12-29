matriC (pronounced ma-tri-ce, shortname = ma3c) by #roevhat
==================
A hobby project for learning C. Implementing Linear Algebra, more specific the concepts of matrix calculations, in a C library. The project also consists of a CLI, together with a logging-feature, which logs the calculations to JSON-files.

Usage
-----
matriC is, at its current stage, able to find the row echelon and reduced row echelon form of any matrix (hopefully!). Though the maximum size is limited to 100x100 - change it in the source, if you have other needs!

The tool has the following commandline syntax:

    ma3c -(Arguments) (input)

There are a few arguments to choose from. 2 main arguments: R or I. Whether to find the reduced row echelon form (R), or the inverse (I) of the given matrix. Furthermore, you can specify if you want expanded/verbose-like output with the sub-argument "all" (all). The syntax is then:

    ma3c -Rall (input)

Or

    ma3c -Iall (input)

It is also possible to time the calculations, and get results in microseconds. This is added with the sub-argument t:

    ma3c -(R/I)t (input)

You can specify both expanded output and the timer:

    ma3c -(R/I)allt (input)

The order at which you pass the arguments is meaningless; this is just as valid:

    ma3c -tallR (input)

The input argument is, per default, specified as a matrix in matlab format ([1 2 3; 5 6 7;]).
Though the format is very strict at this point, so you have to include a trailing semicolon, after the last row in the matrix:

    ma3c -R "[1 2 3; 4 5 6;]"

You also have the possibility of loading the matrix from a plain file. To do this, specify the sub-argument f (f), and instead of the matrix in matlab format, you pass along the file:

    ma3c -Rf /path/to/mymatrix

The logging-feature can't be disabled, and saves all uses of matriC to logfiles in JSON-format. Each use of matriC is saved in its own logfile, with filename being the timestamp of matriC execution. Why JSON? API ftw. Maybe you can come up with a clever way to use it? A webinterface? At the moment, it only saves the input matrix and output matrix + metadata. I would love to see it also save all reduction steps - but as a C newbie, I am having trouble finding the best way to seperate the mathematical logic level, and the output level. I would rather not smear my library with printf()/fprintf()...