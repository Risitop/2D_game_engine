#include <iostream>

#include "../inc/ServiceLocator.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Building the FileManager..."
            << "\n";
  FileManager* fm = new FileManager();

  std::cout << "Building the ServiceLocator..."
            << "\n";
  ServiceLocator::provide(fm);

  std::cout << "Getting the FileManager through ServiceLocator..."
            << "\n";

  FileService* fm_from_sl = ServiceLocator::File();

  std::cout << "Opening a test output file..."
            << "\n";
  FileID fid = fm_from_sl->open_o("data/test_o.txt");
  std::cout << "Successfully opened a file. id:" << fid << "\n";

  std::cout << "Writing stuff..."
            << "\n";
  std::ofstream* fstr = fm_from_sl->query_o(fid);
  (*fstr) << "This is a final test message."
          << "\n";

  std::cout << "Finished."
            << "\n";

  delete fm;

  return 0;
}
