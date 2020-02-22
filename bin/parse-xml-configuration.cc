// bin/parse-xml-configuration.cc



#include "parser/config-parser.h"

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      std::cout << "Parse the text XML configuration data. And Dump the "
        << "configuration in human readable format." << std::endl;
      std::cout << "Usage: parse-xml-configuration xml-file" << std::endl;
      return -1;
    }

    std::string file_name = argv[1];

    // Parse the XML file.
    ConfigParser parser;
    parser.Parse(file_name);
    parser.Print();

    return 0;
  } catch (const std::exception &e) {
    std::cerr << e.what();
    return -1;
  }
}
