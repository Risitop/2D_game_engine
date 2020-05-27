#pragma once

#include "FileManager.hpp"

class ServiceLocator {
 public:
  static void provide(FileService* file_service) { m_file = file_service; }
  static FileService* File() { return m_file; }

 private:
  static FileService* m_file;
};

FileService* ServiceLocator::m_file = NULL;
