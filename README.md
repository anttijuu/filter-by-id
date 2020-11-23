# Filter data by id

A command line tool to filter data from data file using id's from index file.

## Usage

The tool reads two text files:

- id file: id strings, one in each line --  the id (one word) must be the first word in the line;
- data file: one record per line, perhaps *including* an id and whatever else there is.

Empty lines from both files are ignored.

After building (see below), launch the tool to find data from data files, matching the id's in the id file:

`filter id-file data-file outputfile [filter]`

Filter is optional; if not included id file is not filtered by the value it contains. Otherwise only those lines from the id file containing the filter word are included.

Output file includes those records from the data-file, whose id is listed in the id-file, if not filtered out because of the filter word.

Lauch the tool without parameters to see the usage instructions.

Project contains sample files you can try out after building the binary (from the build directory):

`./filter ../sample-id.txt ../sample-data.txt output.txt`

Execution looks like this:

```
./filter ../sample-id.txt ../sample-data.txt output.txt
Reading id's into memory...
Read 4 id's.
Id's read.
Reading data-file into memory...
Read 6 entries.
Finding matching id's from the data file...
Found 3 entries of id's in the datafile.
```
And the contents of the output file are:

```
1   1234 Lare Nisula  Society for sober lecturers
2   2345 Zipped File  Unpack me please
3   3456 Tina London  C++ coders unite agains JavaScript
```
Another example, using a filter:

```
./filter ../id-grade-2020.txt ../all-studs-2020.txt output.txt fail
```
Here, the id file contains the student id and grade, of which one may be "fail":

```
1915774     fail
2728090     5
2836322     2
```
Data file contains full student information, including student id, department, etc.

Result file then includes information about all failed students:

```
1915774     John Smith              Dept of Mathematics
```

Please note that data and id files are read into memory, so if you have very large files and little RAM, this might become an issue.

## Dependencies

Uses C++ STL, C++17 and Boost 1.74. Build file is CMake so install [CMake](https://cmake.org) or build it manually / write your own makefile.

## Building

With CMake, do in the project directory:

1. `mkdir build`
2. `cd build`
3. `cmake ..` (or `cmake -GNinja ..` if you use [Ninja](https://ninja-build.org), or `cmake -GXcode ..` to create a Xcode project, for example)
4. `make` (or `ninja`, if you created build files using `-GNinja`)

Binary should be in the build directory. Then launch the tool as instructed above.

If you have Doxygen installed and wish to generate documentation of the code, run

```
make doc
```
and you'll have HTML docs in the build/docs directory.


## Who made this

(c) Antti Juustila, 2019-2020. All rights reserved. [INTERACT Research Unit](http://interact.oulu.fi), University of Oulu, Finland.

## License

License is [MIT](https://opensource.org/licenses/MIT).

