# muParser#

In this example we provide a simple C++ interface to the muParser and muParserX
libraries and a simple example to illustrate their basic usage.

[muParser](https://beltoforion.de/article.php?a=muparser) and 
[muParserX](https://beltoforion.de/article.php?a=muparserx)
are tools to parse and execute mathematical
expression. There are useful to be able to specify functions without
recompiling the code, for instance reading them from a file or, like
in this example, input them from the terminal. MuParserX is more advanced since
it allows to use vector variables and functions. However, muparser is more efficient. In the given pages you have more details.

First of all you have to install muParser and muParserX 
 The library is composed by a library file (libmuparser.so/libmuparserx.so)
and a set of header files. You can install it in the standard
directories of this Examples by going into `Example/muparser(x)/` and running the shell script `install_PACS.sh`.
You must have `cmake` installed in your system.


##Description of the code in this directory#

The makefile produces an executable and two versions of the library
`libMuParserInterface` (the static and the shared one).

The executable is called test_Muparser and it is just a simple test of
the interfaces.

* `make`cProduces the libraries and the executable (in debug mode)

* `make DEBUG=no` if you want optimised versione

* `make static`  produces only static library (`DEBUG=no` if you want optimized version)

* `make dynamic` produces only dynamic library (`DEBUG=no` if you want optimized version)

* `make test_Muparser`  produces the executable. (`DEBUG=no` for optimiser).

* `make install` Installs header files and the libraries in the directory
used for that purpose: `$(PACS_ROOT_DIR)/include` and
`$(PACS_ROOT_DIR)/lib`. Necessary for other Examples that uses the
interface.

# What do I learn here? #
- The basic usage of [muparser](https://github.com/beltoforion/muparser) and [muparserX](https://beltoforion.de/en/muparserx/)
- An example on how to hide complex details (muparser and muparserX syntax is not trivial) and provide a simplified interface to the used. This is an simple example of a facade design pattern (the real facade design pattern is more complex though).