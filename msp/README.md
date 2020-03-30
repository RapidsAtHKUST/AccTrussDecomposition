# K-Truss
OpenMP-based parallel software for computing the truss decomposition of a graph.


## Build requirements
  - [CMake 2.8](http://www.cmake.org/)
  - GNU `make`
  - A C99 compiler supporting OpenMP (we have tested with `gcc` and `icc`)
  - [GKlib](https://github.com/KarypisLab/GKlib) (can also be built as a git submodule)

Assuming that the above are available, two commands should suffice to build:
```
  make config
  make
```

## Configuring the build
Configuration is primarily by passing options to `make config`. For example:
```
  make config cc=icc
```
would configure it to be built using `icc`.

Configuration options are:
```
  cc=[compiler]     - The C compiler to use [default: gcc]
  prefix=[PATH]     - Set the installation prefix [default: ~/local]
  gklib_path=[PATH] - Where GKlib was installed [default: ~/local]
  openmp=not-set    - To build a serial version
```


### Including GKlib
`GKlib` is a dependency on `ktruss` and many of
[KarypisLab](https://github.com/KarypisLab)'s software. If you do not already
have it installed locally, you can add it to the build via:
```
  make gklib
  make config
  make
```
Note that this is achieved using a git submodule, and thus you must have `git`
installed and an open internet connection.


## Building and installing
To build and install, run the following
```
make
make install
```

## Other make commands
    make uninstall
         Removes all files installed by 'make install'.

    make clean
         Removes all object files but retains the configuration options.

    make distclean
         Performs clean and completely removes the build directory.


## Usage information
By default, the binary, called `ktruss`, will be installed in
`$HOME/local/bin`.  For usage information just type
```
ktruss -help

Usage: ktruss [options] infile [outfile]

 Options
  -kttype=text
     Specifies the type of k-truss algorithm to use.
     Possible values are:
        msp            multi-stage peeling [default]
        and            asynchronous nucleus decomposition (AND)
        base           the serial baseline

  -iftype=text
     Specifies the format of the input file.
     Possible values are:
        metis   Metis format [default]
        tsv     tsv format (i, j, v)

  -help
     Prints this message.
```

### Changing the number of threads
`ktruss` uses OpenMP for shared-memory parallelism (i.e., multithreading).
As such, it follows the standard OpenMP environment variable `$OMP_NUM_THREADS`
to configure the number of threads. By default, `ktruss` will use the
number of logical cores found on the system.


### Graph formats
The program supports two formats for its input files:

  - The one used by the [Metis](http://www.cs.umn.edu/~metis) graph
    partitioning program.
  - The tsv format used by the graphs in the
    [GraphChallenge 2017](http://graphchallenge.mit.edu/) competition (use the
    "adjacency TSV" format).

Note that the graph has to be undirected and it needs to include both pairs of
edges (i.e., (u,v) and (v,u)).

## Citing
The algorithm implemented in this software is based on the one described in

[__"Truss Decomposition on Shared-Memory Parallel Systems."__
Shaden Smith, Xing Liu, Nesreen K. Ahmed, Ancy Sarah Tom, Fabrizio Petrini, and
George Karypis.  IEEE High Performance Extreme Computing Conference (HPEC),
2017](http://glaros.dtc.umn.edu/gkhome/node/1213)

This was one of the finalists for the
[GraphChallenge 2017](http://graphchallenge.mit.edu/) competition.

