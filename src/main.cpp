#define DEFAULT_IP_ADDRESS "127.0.0.1:8000"

#include <argparse/argparse.hpp>
#include <string>
#include <filesystem>

using std::filesystem::path;
using std::filesystem::absolute;
using std::filesystem::exists;
using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::exception;


int main(int argc, char* argv[]){
  argparse::ArgumentParser program("ftp_client");
  program.add_argument("filename")
         .help("Path to the input file");
  program.add_argument("-i", "-ip_address")
         .help("IP address to the server")
         .default_value(DEFAULT_IP_ADDRESS);

  try{
    program.parse_args(argc, argv);
  }
  catch(const exception& err){
    std::cerr << err.what() << std:: endl;
    std::cerr << program;
    return 1;
  }
 
  auto filename = program.get<string>("filename");
  path filename_path = path(filename);
  string filename_abspath = absolute(filename_path);

  if (!exists(filename_abspath)){
    throw std::invalid_argument("Error: Filepath does not exist.");
  }

  cout << filename_abspath << endl;

  return 0;
}
