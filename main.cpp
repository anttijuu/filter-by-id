#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
   std::cout << "Found " << matchCount << " entries of indexes in datafile" << std::endl;
   return EXIT_SUCCESS;
}
