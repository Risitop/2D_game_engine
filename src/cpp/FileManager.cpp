#include "../inc/FileManager.hpp"

bool FileManager::m_existing = false;

FileManager::FileManager() : m_files(), m_next_id(0) {
  // We want only one file manager for the whole engine.
  assert(!FileManager::m_existing);
  FileManager::m_existing = true;
}

FileManager::~FileManager() {
  FileManager::m_existing = false;
  for (File& file : m_files) {
    close(file.id);
  }
}

FileID FileManager::open_i(std::string path) {
  std::ifstream* filestream = new std::ifstream(path);

  assert(filestream->is_open());

  File file;
  file.id = m_next_id;
  file.open = true;
  file.state = FileState::IN;
  file.stream.i = filestream;

  m_files.push_back(file);

  m_next_id += 1;
  return (m_next_id - 1);
}

FileID FileManager::open_o(std::string path) {
  std::ofstream* filestream = new std::ofstream(path);

  assert(filestream->is_open());

  File file;
  file.id = m_next_id;
  file.open = true;
  file.state = FileState::OUT;
  file.stream.o = filestream;

  m_files.push_back(file);

  m_next_id += 1;
  return (m_next_id - 1);
}

std::ifstream* FileManager::query_i(FileID id) {
  File* file = mGetFile(id);
  assert(file->open);
  return file->stream.i;
}

std::ofstream* FileManager::query_o(FileID id) {
  File* file = mGetFile(id);
  assert(file->open);
  return file->stream.o;
}

void FileManager::close(FileID id) {
  File* file = mGetFile(id);

  if (file->open == false) return;

  file->open = false;

  if (file->state == FileState::IN)
    file->stream.i->close();
  else if (file->state == FileState::OUT)
    file->stream.o->close();
}

File* FileManager::mGetFile(FileID id) {
  assert(id < m_files.size());
  File* file = &(m_files[id]);
  assert(file->id == id);
  return file;
}
