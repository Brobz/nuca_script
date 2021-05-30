#include <vector>
#include <string>
#include <fstream>

#ifndef FileIO_H_
#define FileIO_H_

using namespace std;

class FileIO{
    public:

      static vector<string> parse_file(string file_path, string separator, int buffer_size){
        if (!separator.length()){
          cout << ">> Fatal Error: cannot parse " << file_path << " using an empty string separator" << endl;
          exit(EXIT_FAILURE);
        }
        vector<string> entries;
        entries.resize(buffer_size);
        int separator_index;
        int entry_index = -1;
        string line, entry;
        ifstream input_file (file_path);
        if (input_file.is_open()){
          while (getline (input_file, line)){

            if(!line.length()) continue; // Empty line

            separator_index = line.find(separator); // Where in this line is the separator?

            while(separator_index != -1){
              entry_index++;
              FileIO::overflow_check(entry_index, buffer_size, file_path);
              entry = line.substr(0, separator_index);
              if (entry.empty()){
                entry_index--; // Nevermind adding this entry; Its empty
              }else{
                entries[entry_index] = entry;
              }
              line.erase(0, line.find(separator) + separator.length());
              separator_index = line.find(separator);
            }

            if (line.length()){ // Is there leftovers on the line?
              entry_index++;
              FileIO::overflow_check(entry_index, buffer_size, file_path);
              entries[entry_index] += line; // Add them!
            }

          }

          entry_index++;
          if (entry_index < buffer_size) entries[entry_index] = "END_OF_STREAM"; // If it is not overflowing, add END_OF_STREAM so that the user knows this is the end of the file data

          input_file.close();

        }else{
          cout << ">> Fatal Error: could not open " << file_path << endl;
          exit(EXIT_FAILURE);
        }

        return entries;
      }

      static void write_to_file(vector<string> buffer, string file_path, string separator){
        ofstream output_file(file_path);
        if (output_file.is_open()){
          for (const auto &data : buffer){
            output_file << data << separator;
          }
        }else{
          cout << ">> Fatal Error: could not open " << file_path << endl;
          exit(EXIT_FAILURE);
        }
      }

    private:

      static void overflow_check(int index, int size, string file_path){
        if (index + 1 > size){
          cout << ">> Fatal Error: buffer overflow while reading from " << file_path << endl;
          exit(EXIT_FAILURE);
        }
      }


};

#endif /*FileIO_H_*/
