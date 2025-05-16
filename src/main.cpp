#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_SERVER_PORT 21 
#define DEFAULT_USER "USER"
#define DEFAULT_PASSWORD "PASSWORD"
#define BUFFER_SIZE 1024

#include <argparse/argparse.hpp>
#include <string>
#include <filesystem>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

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
  program.add_argument("-i", "--ip_address")
         .help("IP address to the server")
         .default_value(DEFAULT_SERVER_IP);
  program.add_argument("-p", "--port")
          .help("port")
          .default_value(DEFAULT_SERVER_PORT);
  program.add_argument("-u", "--user")
          .help("Username to connect to FTP Server")
          .default_value(DEFAULT_USER);
  program.add_argument("-p", "--password")
          .help("Password to connect to FTP Server")
          .default_value(DEFAULT_PASSWORD);

  
  try{
    program.parse_args(argc, argv);
  }
  catch(const exception& err){
    std::cerr << err.what() << std:: endl;
    std::cerr << program;
    return -1;
  }
 
  auto filename = program.get<string>("filename");
  path filename_path = path(filename);
  string filename_abspath = absolute(filename_path);

  if (!exists(filename_abspath)){
    throw std::invalid_argument("Error: Filepath does not exist.");
  }

  //initialize your socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1){
    std::cerr << "Error creating socket" << std::endl;
    return -1;
  }
  
  //setup a connection
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(DEFAULT_SERVER_PORT);

  //attempt a connection
  if (inet_pton(AF_INET, DEFAULT_SERVER_IP, &server_address.sin_addr) <= 0){
    cerr << "Error connecting to server" << endl;
    close(client_socket);
    return -1;
  }

  if (connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
    cerr << "Connection failed" << endl;
    close(client_socket);
    return -1;
  }

  //ftp recieve message
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  while (recv(client_socket, buffer, BUFFER_SIZE - 1, 0) == 0);
  cout << buffer;
  //load file 
    

  //send file
  return 0;
}
