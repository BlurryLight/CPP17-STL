#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "USAGE" << argv[0] << "+ <PATH>" << std::endl;
    return -1;
  }

  auto dir = std::filesystem::path{argv[1]};

  if (!std::filesystem::exists(dir)) {
    std::cerr << "path" << dir << "NOT EXSITS" << std::endl;
    return -1;
  }

  auto canonicaled_dir = std::filesystem::canonical(dir);
  std::cout << canonicaled_dir << std::endl;
  std::cout << canonicaled_dir.c_str() << std::endl;
  std::cout << canonicaled_dir.string() << std::endl;
  return 0;
}
