#pragma once

// TODO: check open/close status

#include <assert.h>

#include <fstream>
#include <string>
#include <vector>

typedef unsigned int FileID;
typedef union {
  std::ifstream* i;
  std::ofstream* o;
} Stream;

enum FileState { IN, OUT };

struct File {
  FileID id;
  bool open;
  FileState state;
  Stream stream;
};

class FileService {
 public:
  virtual ~FileService() {}
  virtual FileID open_i(std::string path) = 0;
  virtual FileID open_o(std::string path) = 0;
  virtual std::ifstream* query_i(FileID id) = 0;
  virtual std::ofstream* query_o(FileID id) = 0;
  virtual void close(FileID id) = 0;
};

class FileManager : public FileService {
 public:
  FileManager();
  ~FileManager();
  FileID open_i(std::string path);
  FileID open_o(std::string path);

  std::ifstream* query_i(FileID id);
  std::ofstream* query_o(FileID id);

  void close(FileID id);

 private:
  std::vector<File> m_files;
  FileID m_next_id;
  static bool m_existing;

  inline File* mGetFile(FileID id);
};
