# Filter data by id

A command line tool to filter data from data file using id's from index file.

## Usage

The tool reads two text files:

- id file: id strings, one in each line -- *only* the id, nothing else, one per line for data which interests you;
- data file: one record per line, perhaps *including* an id and whatever else there is.

Empty lines from both files are ignored.

After building (see below), launch the tool to find data from data files, matching the id's in the id file:

`filter id-file data-file [outputfile]`

Output file is optional; if not included output will be displayed in the console. Output includes those students from data-file, whose id is listed in the id-file.

Lauch the tool without parameters to see the usage instructions.

Project contains sample files you can try out after building the binary (from the build directory):

`./filter ../sample-id.txt ../sample-data.txt`

Output looks like this:

```
./filter ../sample-id.txt ../sample-data.txt
Reading id's into memory...
Read 4 id's.
Id's read.
Reading data-file into memory...
Read 6 entries.
Finding matching id's from the data file...
1    1234 Lare Nisula  Society for sober lecturers
2    2345 Zipped File  Unpack me please
3    3456 Tina London  C++ coders unite agains JavaScript
Found 3 entries of id's in the datafile.
```
Please note that data and id files are read into memory, so if you have very large files and little RAM, this might become an issue.

## Dependencies

Uses C++ STL, C++17. Build file is CMake so install [CMake](https://cmake.org) or build it manually / write your own makefile.

## Building

With CMake, do in the project directory:

1. `mkdir build`
2. `cd build`
3. `cmake ..` (or `cmake -GNinja ..` if you use [Ninja](https://ninja-build.org), or `cmake -GXcode ..` to create a Xcode project, for example)
4. `make` (or `ninja`, if you created build files using `-GNinja`)

BInary should be in the build directory. Then launch the tool as instructed above.

If you have Doxygen installed and wish to generate documentation of the code, run

```
make doc
```
and you'll have HTML docs in the build/docs directory.


## Who made this

(c) Antti Juustila, 2019-2020. All rights reserved. [INTERACT Research Unit](http://interact.oulu.fi), University of Oulu, Finland.

## License

License is [MIT](https://opensource.org/licenses/MIT).

