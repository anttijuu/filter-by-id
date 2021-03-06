
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

/** \file main.cpp */

/**
 \mainpage A command line tool to filter data from datafile using id's from index file.
 <p>
 Files must be text only. Index file must contain only the id's (one word; numbers, strings),
 and after space (or tab) other data if needed to use it for filtering by id file contents.
 Files are read into memory, so very large files might be a problem.
 
 @author Antti Juustila
 */

// Forward declaration of the helper function.
[[nodiscard]]
int readIdFile(const std::string & fileName, std::vector<std::string> & entries, const std::string & filter);
int readDataFile(const std::string & fileName, std::vector<std::string> & entries);

/**
 \fn int main(int argc, char ** argv)
 Main function of the tool. Lauch the tool without parameters to see usage information.
 @param argc Count of arguments. Expecting 4-5 (including the app binary name in the first slot).
 @param argv The parameters.
 */
int main(int argc, char ** argv) {
   
   std::string indexFileName;                // Text file, contains the student id's one per line
   std::string dataFileName;                 // Text file, contains student data, one per line
   std::string outputFileName;               // Text file to write the matching students.
   std::string filter;                       // Filter, if given in startup parameter.
   std::vector<std::string> indexes;         // Student id's read from file.
   std::vector<std::string> dataEntries;     // Student data read from file.
   
   if (argc < 3) {
      std::cout << "Usage: " << argv[0] << " id-file data-file outputfile [filter]" << std::endl;
      std::cout << "  Where id-file contains id's of interest" << std::endl;
      std::cout << "   data-file contains data in text format, one line per data item." << std::endl;
      std::cout << "   output file will contain the results." << std::endl;
      std::cout << "   filter (if given) includes only those records in id-file having said string." << std::endl;
      return EXIT_SUCCESS;
   } else {
      switch (argc) {
         case 5:
            filter = argv[4];
            [[fallthrough]];
            
         case 4:
            indexFileName = argv[1];
            dataFileName = argv[2];
            outputFileName = argv[3];
            break;
            
         default:
            std::cout << "Launch without parameters to see usage instructions" << std::endl;
            return EXIT_SUCCESS;
      }
   }
   
   std::cout << "Reading id's into memory..." << std::endl;
   int count = readIdFile(indexFileName, indexes, filter);
   if (count > 0) {
      std::cout << "Read " << indexes.size() << " id's." << std::endl;
   } else {
      std::cout << "Error in opening the id file or file empty." << std::endl;
      return EXIT_FAILURE;
   }
   std::cout << "Id's read." << std::endl;
   
   std::cout << "Reading data-file into memory..." << std::endl;
   count = readDataFile(dataFileName, dataEntries);
   if (count > 0) {
      std::cout << "Read " << dataEntries.size() << " entries." << std::endl;
   } else {
      std::cout << "Error in opening the data file or file empty." << std::endl;
      return EXIT_FAILURE;
   }

   // Prepare output either to cout or file.
   std::ofstream outputFile;
   outputFile.open(outputFileName);
   if (outputFile.is_open()) {
      std::cout << "Output will be in file " << outputFileName << std::endl;
   } else {
      std::cout << "Error: could not open the output file" << std::endl;
      return EXIT_FAILURE;
   }

   std::cout << "Finding matching id's from the data file..." << std::endl;
   int matchCount = 0;
   std::for_each(std::begin(indexes), std::end(indexes), [&matchCount, &dataEntries, &outputFile](const std::string & index) {
      std::any_of(std::begin(dataEntries), std::end(dataEntries), [&matchCount, &index, &outputFile](const std::string & dataEntry) {
         if (dataEntry.find(index) != std::string::npos) {
            outputFile << matchCount + 1 << "   " << dataEntry << std::endl;
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
 Helper function to extract the first word from the id file record.
 This is the id we are using to find matches from the data file.
 @param entry The data record
 @return The id from the record.
 */
std::string firstWord(const std::string & entry) {
   std::vector<std::string> strs;
   boost::split(strs, entry, boost::is_any_of("\t "));
   if (strs.size() >= 1) {
      return strs.at(0);
   }
   return entry;
}

/**
 \fn int readIdFile(const std::string & fileName, std::vector<std::string> & entries, const std::string & filter)
 Reads lines from a text file and puts the first word of the line as a string in a vector.
 If filter is used, only records where the rest of the string contains the filter string are included in
 the entries.
 @param fileName The file to read lines from.
 @param entries The vector to put lines to.
 @param filter A value to filter the records to include in the process that satisfy the filter.
 @return The count of lines read, -1 if failed to open or read the file.
 */
int readIdFile(const std::string & fileName, std::vector<std::string> & entries, const std::string & filter) {
   int count = 0;
   std::ifstream file(fileName);
   if (file.is_open()) {
      std::string entry;
      while (std::getline(file, entry)) {
         if (entry.length() > 0) {
            // Are we using a filter to include only records with certain values
            if (filter.length() > 0) {
               // Ignore the first word (id) of the entry, and look for the
               // remainder of the record if it contains the filter word.
               auto pos = entry.find_first_of(" \t");
               if (pos >= 0) {
                  const std::string & substring = entry.substr(pos);
                  if (substring.find(filter) != std::string::npos) {
                     // Filter found in record, add to entries
                     entries.push_back(firstWord(entry));
                  }
               }
            } else { // no filter used, put to entries
               entries.push_back(firstWord(entry));
            }
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

/**
 \fn int readDataFile(const std::string & fileName, std::vector<std::string> & entries)
 Reads lines from a text file and puts the the line as a string in a vector.
 @param fileName The file to read lines from.
 @param entries The vector to put lines to.
 @return The count of lines read, -1 if failed to open or read the file.
 @todo Could already do the matching and saving to output file already here for each datafile record.
 Would save memory.
 */
int readDataFile(const std::string & fileName, std::vector<std::string> & entries) {
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

