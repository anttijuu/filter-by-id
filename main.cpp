#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 Our learning environment Moodle does not currently have information what is the study program of the student. In analysing student performance, this background can be an important piece of information. The performance (points, grade) is included in the data in Moodle, obviously.
 Study program of a student can be found in another system, Oodi. Therefore, to match this data, I need to export:
 <p><ul>
 <li>course data from Moodle, containing student id, filtering in only those students who have the grade(s) I am interested at any moment. For example, students who failed the course.</li>
 <li>data from Weboodi in text format, containing student id and study program, possibly other information too, for all students registered in the course.</li>
  </ul><p>
 And then match these two files using the student id. Then I can analyze if the student background has any relevance to the performance of the student.
 This command line tool enables you to do this.
 */


/**
 Reads lines from a text file and puts one line as a string in a vector.
 @param fileName The file to read lines from.
 @param entries The vector to put lines to.
 @return The count of lines read, -1 if failed to open or read the file.
 */
int readFile(const std::string & fileName, std::vector<std::string> & entries) {
   int count = 0;
   std::ifstream file(fileName);
   std::string entry;
   if (file.is_open()) {
      while (std::getline(file, entry)) {
         if (entry.length() > 0) {
            entries.push_back(entry);
            count++;
         }
      }
      file.close();
   } else {
      std::cout << "Error in opening the  file." << std::endl;
      return -1;
   }
   return count;
}

/**
 Main function of the tool. Lauch the tool without parameters to see usage information.
 @param argc Count of arguments. Expecting 3-4 (including the app binary name in the first slot.
 @param argv The parametersf.
 */
int main(int argc, char ** argv) {
   
   std::string indexFileName;
   std::string dataFileName;
   std::string outputFileName;
   std::vector<std::string> indexes;
   std::vector<std::string> dataEntries;
   
   if (argc < 3) {
      std::cout << "Usage: filterstudents id-file studentdatafile [outputfile]" << std::endl;
      std::cout << "  Where id-file contains selected student id's" << std::endl;
      std::cout << "  and studentdatafile contains student data in text format, one line per student." << std::endl;
      std::cout << "  and output file will contain the results. If not given, output is to console." << std::endl;
      return 0;
   } else {
      switch (argc) {
         case 4:
            outputFileName = argv[3];
            // [[fallthrough]];
            
         case 3:
            indexFileName = argv[1];
            dataFileName = argv[2];
            break;
            
         default:
            std::cout << "Usage: filter-id indexfile datafile [outputfile]" << std::endl;
            break;
      }
   }
   
   std::cout << "Read student id's into memory" << std::endl;
   int count = readFile(indexFileName, indexes);
   if (count > 0) {
      std::cout << "Read " << indexes.size() << " id's." << std::endl;
   } else {
      std::cout << "Error in opening the id file." << std::endl;
      return EXIT_FAILURE;
   }

   
   std::cout << "Reading studentdata file into memory..." << std::endl;
   count = readFile(dataFileName, dataEntries);
   if (count > 0) {
      std::cout << "Read " << dataEntries.size() << " entries." << std::endl;
   } else {
      std::cout << "Error in opening the data file." << std::endl;
      return EXIT_FAILURE;
   }

   // Prepare output either to cout or file.
   std::ofstream outputFile;
   std::ostream * output;
   if (outputFileName.length() > 0) {
      outputFile.open(outputFileName);
      std::cout << "Output will be in file " << outputFileName << std::endl;
      output = &outputFile;
   } else {
      output = &std::cout;
   }

   std::cout << "Finding matching student id's from the data file..." << std::endl;
   int matchCount = 0;
   for (auto iter = indexes.begin(); iter != indexes.end(); iter++) {
      for (auto iter2 = dataEntries.begin(); iter2 != dataEntries.end(); iter2++) {
         if ((*iter2).find(*iter) != std::string::npos) {
            *output << matchCount+1 << "    " << *iter2 << std::endl;
            matchCount++;
            break;
         }
      }
   }
   std::cout << "Found " << matchCount << " entries of id's in the datafile." << std::endl;
   return EXIT_SUCCESS;
}
