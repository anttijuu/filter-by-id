
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/** \file main.cpp */

/**
 \mainpage A command line tool to filter data from datafile using id's from index file.
 <p>
 Files must be text only. Index file must contain only the id's (numbers, strings), nothing more.
 Files are read into memory, so very large files might be a problem.
 
 @author Antti Juustila
 */

// Forward declaration of the helper function.
[[nodiscard]]
int readFile(const std::string & fileName, std::vector<std::string> & entries);

/**
 \fn int main(int argc, char ** argv)
 Main function of the tool. Lauch the tool without parameters to see usage information.
 @param argc Count of arguments. Expecting 3-4 (including the app binary name in the first slot).
 @param argv The parameters.
 */
int main(int argc, char ** argv) {
   
   std::string indexFileName;                // Text file, contains the student id's one per line
   std::string dataFileName;                 // Text file, contains student data, one per line
   std::string outputFileName;               // Text file to write the matching students.
   std::vector<std::string> indexes;         // Student id's read from file.
   std::vector<std::string> dataEntries;     // Student data read from file.
   
   if (argc < 3) {
      std::cout << "Usage: filter id-file data-file [outputfile]" << std::endl;
      std::cout << "  Where id-file contains id's of interest" << std::endl;
      std::cout << "  and data-file contains data in text format, one line per data item." << std::endl;
      std::cout << "  and output file will contain the results. If parameter not given, output is to console." << std::endl;
      return EXIT_SUCCESS;
   } else {
      switch (argc) {
         case 4:
            outputFileName = argv[3];
            [[fallthrough]];
            
         case 3:
            indexFileName = argv[1];
            dataFileName = argv[2];
            break;
            
         default:
            std::cout << "Usage: filter id-file data-file [outputfile]" << std::endl;
            break;
      }
   }
   
   std::cout << "Reading id's into memory..." << std::endl;
   int count = readFile(indexFileName, indexes);
   if (count > 0) {
      std::cout << "Read " << indexes.size() << " id's." << std::endl;
   } else {
      std::cout << "Error in opening the id file or file empty." << std::endl;
      return EXIT_FAILURE;
   }
   std::cout << "Id's read." << std::endl;
   
   std::cout << "Reading data-file into memory..." << std::endl;
   count = readFile(dataFileName, dataEntries);
   if (count > 0) {
      std::cout << "Read " << dataEntries.size() << " entries." << std::endl;
   } else {
      std::cout << "Error in opening the data file or file empty." << std::endl;
      return EXIT_FAILURE;
   }

   // Prepare output either to cout or file.
   std::ofstream outputFile;
   std::ostream * output;
   if (outputFileName.length() > 0) {
      outputFile.open(outputFileName);
      if (outputFile.is_open()) {
         std::cout << "Output will be in file " << outputFileName << std::endl;
         output = &outputFile;
      } else {
         std::cout << "Error: could not open the output file" << std::endl;
         return EXIT_FAILURE;
      }
   } else {
      output = &std::cout;
   }

   std::cout << "Finding matching id's from the data file..." << std::endl;
   int matchCount = 0;
   std::for_each(std::begin(indexes), std::end(indexes), [&matchCount, &dataEntries, &output](const std::string & index) {
      std::any_of(std::begin(dataEntries), std::end(dataEntries), [&matchCount, &index, &output](const std::string & dataEntry) {
         if (dataEntry.find(index) != std::string::npos) {
            *output << matchCount+1 << "   " << dataEntry << std::endl;
            matchCount++;
            return true; // Not returning from the app but from the lambda function.
         }
         return false;   // Not returning from the app but from the lambda function.
      });
   });
   
   std::cout << "Found " << matchCount << " entries of id's in the datafile." << std::endl;
   return EXIT_SUCCESS;
}

/**
 \fn int readFile(const std::string & fileName, std::vector<std::string> & entries)
 Reads lines from a text file and puts one line as a string in a vector.
 @param fileName The file to read lines from.
 @param entries The vector to put lines to.
 @return The count of lines read, -1 if failed to open or read the file.
 */
int readFile(const std::string & fileName, std::vector<std::string> & entries) {
   int count = 0;
   std::ifstream file(fileName);
   if (file.is_open()) {
      std::string entry;
      while (std::getline(file, entry)) {
         if (entry.length() > 0) {
            entries.push_back(entry);
            count++;
         }
      }
      file.close();
   } else {
      std::cout << "Error in opening the file." << std::endl;
      return -1;
   }
   return count;
}

