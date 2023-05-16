#include"Wind_server.hpp"

Net::Server::Server(int port,std::string ip_adress)
:
port(port),
ip_adress(ip_adress),
sockfd(socket(AF_INET, SOCK_DGRAM, 0)),
servaddr{0},
infolegth(sizeof(servaddr))
{
    if(sockfd == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }
    else
        std::cout<< "Socket created" << std::endl;
    
    
}

void Net::Server::init()
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());


}