#pragma once

#include "bee/file_path.hpp"
#include "bee/or_error.hpp"

namespace clang_format {

struct ClangFormat {
 public:
  static bee::OrError<> format_file(const bee::FilePath& file);
  static bee::OrError<std::string> format_code(
    const std::string& code, const bee::FilePath& assume_filename);
};

} // namespace clang_format
