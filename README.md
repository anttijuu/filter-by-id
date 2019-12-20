# Filter data by id

A command line tool to filter data from datafile using id's from index file.

## Use case

Our learning environment Moodle does not currently have information what is the study program of the student. In analysing student performance, this background can be an important piece of information. The performance (points, grade) is included in the data in Moodle, obviously.

Study program of a student can be found in *another* system, Oodi. Therefore, to match this data, one needs to export:

1. course data from Moodle, containing student id, *filtering* in only those students who have the grade(s) I am interested at any moment. For example, students who failed the course.
2. data from Weboodi in text format, containing student id and study program, possibly other information too, for all students registered in the course.

And then match these two files using the student id. Then I can analyze if the student background has any relevance to the performance of the student.

This command line tool enables you to do this.

## Usage

You need two text files:

- id file: id strings, one in each line -- only the id, nothing else, per line for data which interests you;
- data file: one record per line, *including* the id and whatever else there is / you need.

After building (see below), launch the tool to find data from data files, matching the id's in the id file:

`filter id-file data-file [outputfile]`

Output file is optional; if not included output will be displayed in the console. Output includes those students from data-file, whose id is listed in the id-file.

Lauch the tool without parameters to see the usage instructions.

Project contains sample files you can try out:

`filter sample-id.txt sample-data.txt`

Output looks like this:

```
./build/filter sample-id.txt sample-data.txt
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


## Dependencies

Uses C++ STL, requires C++17. Build file is CMake so install [CMake](https://cmake.org) or build it manually / write your own makefile.

## Building

With CMake, do in the project directory:

1. mkdir build
2. cd build
3. cmake ..
4. make

BInary should be in the build directory. Then launch the tool as instructed above.

## Who made this

(c) Antti Juustila, 2019. INTERACT Research Unit, University of Oulu, Finland.

## License

License is [MIT](https://opensource.org/licenses/MIT).

