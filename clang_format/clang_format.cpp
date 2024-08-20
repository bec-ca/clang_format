#include "clang_format.hpp"

#include "bee/sub_process.hpp"

namespace clang_format {

namespace {

std::optional<std::string> get_env(const std::string& variable_name)
{
  char* c_path = getenv(variable_name.data());
  if (c_path == nullptr) return std::nullopt;
  return c_path;
}

bee::FilePath get_clang_cmd()
{
  return bee::FilePath(get_env("CLANG_FORMAT").value_or("clang-format"));
}

} // namespace

bee::OrError<> ClangFormat::format_file(const bee::FilePath& file)
{
  return bee::SubProcess::run({
    .cmd = get_clang_cmd(),
    .args = {"-i", file.to_string()},
  });
}

bee::OrError<std::string> ClangFormat::format_code(
  const std::string& code, const bee::FilePath& assume_filename)
{
  auto input_spec = bee::SubProcess::InputFromString::create(code);
  auto output_spec = bee::SubProcess::OutputToString::create();
  bail_unit(bee::SubProcess::run({
    .cmd = get_clang_cmd(),
    .args = {"--assume-filename", assume_filename.to_string()},
    .stdin_spec = input_spec,
    .stdout_spec = output_spec,
  }));
  return output_spec->get_output();
}

} // namespace clang_format
