# Filter students by id

Our learning environment Moodle does not currently have information what is the study program of the student. In analysing student performance, this background can be an important piece of information. The performance (points, grade) is included in the data in Moodle, obviously.

Study program of a student can be found in *another* system, Oodi. Therefore, to match this data, I need to export:

1. course data from Moodle, containing student id, *filtering* in only those students who have the grade(s) I am interested at any moment. For example, students who failed the course.
2. data from Weboodi in text format, containing student id and study program, possibly other information too, for all students registered in the course.

And then match these two files using the student id. Then I can analyze if the student background has any relevance to the performance of the student.

This command line tool enables you to do this.

## Usage

You need two text files:

- id file: student id's, one in each line -- only the id, nothing else, per line for those students whose grades interest you (from Moodle);
- student data file: containing student information, *including* the id and whatever else you want, in *one* line per student, from WebOodi.

After building (see below), launch the tool to find matching students from data files:

`filterstudents id-file data-file [outputfile]`

Output file is optional; if not included output will be displayed in the console. Output includes those students from data-file, whose id is listed in the id-file.

## Dependencies

Uses C++ STL, requires C++14. Build file is CMake so install [CMake](https://cmake.org) or build it manually / write your own makefile.

## Building

With CMake, do in the project directory:

1. mkdir build
2. cd build
3. cmake ..
4. make

BInary should be in the build directory. Then launch the tool as instructed above.

## Who made this

(c) Antti Juustila, 2019

## License

License is MIT.

