#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

static std::tuple<fs::path, fs::file_status, size_t> file_info(
    const fs::directory_entry& entry) {
  const auto fs(fs::status(entry));
  return {entry.path(), fs,
          fs::is_regular_file(fs) ? fs::file_size(entry.path()) : 0u};
}

static char type_char(fs::file_status fs) {
  switch (fs.type()) {
    case fs::file_type::directory:
      return 'd';
    case fs::file_type::socket:
      return 's';
    case fs::file_type::symlink:
      return 'l';
    case fs::file_type::fifo:
      return 'p';
    case fs::file_type::block:
      return 'b';
    case fs::file_type::character:
      return 'c';
    case fs::file_type::regular:
      return 'r';
    case fs::file_type::none:
      return 'o';
    default:
      return '?';
  }
}

static std::string permissions_check(fs::perms p) {
  std::stringstream os;
  os << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
     << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
     << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
     << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
     << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
     << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
     << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
     << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
     << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-");

  return os.str();
}
static std::string size_prettify(size_t size) {
  std::stringstream ss;
  if (size >= 1E+9) {
    ss << (size / 1E+9) << 'G';
  } else if (size >= 1E+6) {
    ss << (size / 1E+6) << 'M';
  } else if (size >= 1E+3) {
    ss << (size / 1E+3) << 'K';
  } else {
    ss << size << 'B';
  }
  return ss.str();
}

int main(int argc, char** argv) {
  fs::path dir{argc > 1 ? argv[1] : "."};

  if (!fs::exists(dir)) {
    throw std::runtime_error("DIR not exsits");
  }

  std::vector<std::tuple<fs::path, fs::file_status, size_t>> items;
  fs::directory_iterator begin{dir};
  fs::directory_iterator end;
  std::transform(begin, end, std::back_inserter(items), file_info);
  for (const auto& [path, status, size] : items) {
    std::cout << type_char(status) << permissions_check(status.permissions())
              << ' ' << std::setw(10) << std::right << size_prettify(size)
              << ' ' << path.filename().c_str() << std::endl;
  }
  std::cout.flush();
  return 0;
}
