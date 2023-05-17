#include"Wind_server.hpp"

Net::Server::Server(int port,std::string ip_adress)
:
port(port),
ip_adress(ip_adress),
sockfd(socket(AF_INET, SOCK_DGRAM, 0)),
infolegth(sizeof(servaddr))
{
    memset(&servaddr, 0, infolegth);

    if(sockfd == -1)
    {
        std::cerr << ("Server: Failed to create socket");
        close(sockfd);
        std::exit(static_cast<int>(std::errc::not_a_socket));
    }
    else
        {
        int optval = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("Error setting socket options");
        close(sockfd); 
        }
            
        std::cout<< "Server: Socket created" << std::endl;

    }  
}

void Net::Server::init()
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());

    std::cout << "Server: bind socket ...\n";
    int bind_result = bind(sockfd,(const sockaddr*)&servaddr,infolegth);

    if(bind_result < 0)
    {
        std::cerr << "Server: Failed to bind socket\n";
        std::exit(static_cast<int>(std::errc::address_in_use));
    }
    else
    {
        std::cout<< "Server: socket binded" << std::endl;
        std::cout<< "Server started: " << inet_ntoa(servaddr.sin_addr) <<" "<< "Port: " << ntohs(servaddr.sin_port) << std::endl;
    } 
}

void Net::Server::start()
{
    init();

    for(;;)
    {
        receive();
        process();
        send();
    }
}

void Net::Server::receive()
{
    if((recivelength = recvfrom(sockfd,buff,SIZE,0,(struct sockaddr*)&servaddr,&infolegth))== -1)
    {
         perror("Server: Error receiving data");
    }

    // .... что-то делаем с информацией
}
void Net::Server::process()
{
    std::cout << "Server: paket from: " << inet_ntoa(servaddr.sin_addr) << " " << "Port: " << ntohs(servaddr.sin_port) << std::endl;
    for(size_t i = 0; i < recivelength; ++i)
    {
        std::cout << buff[i];
    }
    std::cout<< std::endl;
}

void Net::Server::send()
{
    int sent_bytes = sendto(sockfd,buff,recivelength,0,(struct sockaddr*)&servaddr,infolegth);
    if((sent_bytes) == -1)
    {
        perror("Server: Error sending data\n");
        //close(sockfd);
    }
    std::cout << "Sent " << sent_bytes << " bytes" << std::endl;
    
}
void Net::Server::stop()
{
    close(sockfd);
}
Net::Server::~Server()
{
    close(sockfd);
}



int main()
{
    Net::Server server(3333,"127.0.0.1");
    server.start();

    return 0;
}