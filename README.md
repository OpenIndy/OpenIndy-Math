OpenIndy-Math
=============

OpenIndy-Math is the math library used in [OpenIndy](https://github.com/OpenIndy/OpenIndy) and its plugins. It is implemented as a wrapper and internally uses third party linear algebra libraries.
At the moment [amadillo c++ linear algebra library](http://arma.sourceforge.net) is used but this can easily be switched to another library.

IDE
----

OpenIndy-Math is developed with the Qt framework (Qt libs + Qt Creator IDE). You can download the framework [here](http://qt-project.org/downloads).

Dependencies
------------

- [amadillo c++ linear algebra library](http://arma.sourceforge.net)
- [BLAS/LAPACK](http://www.netlib.org/lapack/)
- [Qt](http://qt-project.org)

Build
-----

The easiest way to build OpenIndy-Math is to use the Qt Creator. You can build OpenIndy-Math in `debug` or `release` mode.  

BLAS and LAPACK
----------------

If using Linux:

  - Use the Terminal (command line): `sudo apt-get install liblapack-dev`

If using Windows:

  - Copy all dll's from `lib/armadillo-3.910.0/examples/lib_win64` to `bin/debug` || `bin/release` folder of the [OpenIndy](https://github.com/OpenIndy/OpenIndy) executable

If using Mac OS:

  - Copy `lib/armadillo-3.910.0/examples/framework_mac/Accelerate.framework` to the Mac OS Library `/Library/Frameworks`
