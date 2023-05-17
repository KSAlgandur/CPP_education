#include"Wind_client.hpp"

Net::Client::Client(int port,std::string ip_adress)
:
port(port),
ip_adress(ip_adress),
sockfd(socket(AF_INET, SOCK_DGRAM, 0)),
infolegth(sizeof(clientaddr))
{
    memset(&clientaddr, 0, infolegth);

    if(sockfd == -1)
    {
        std::cerr << ("Client: Failed to create socket");
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
            
        std::cout<< "Client: Socket created" << std::endl;

    }  
}

void Net::Client::init()
{
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(port);
    clientaddr.sin_addr.s_addr = inet_addr(ip_adress.c_str());

}

void Net::Client::connect()
{
    init();

    for(;;)
    {
        send();
        receive();
        process();
    }
}

void Net::Client::send()
{
    std::cout << "Enter a messege: " << std::endl;

    std::getline(std::cin,message);

    int sent_bytes = sendto(sockfd,message.c_str(),message.size(),0,(struct sockaddr*)&clientaddr,infolegth);
    if((sent_bytes) == -1)
    {
        perror("Client: Error sending data\n");
        //close(sockfd);
    }
    std::cout << "Sent " << sent_bytes << " bytes" << std::endl;
    
}

void Net::Client::receive()
{
    if((recivelength = recvfrom(sockfd,buff,SIZE,0,(struct sockaddr*)&clientaddr,&infolegth))== -1)
    {
         perror("Client: Error receiving data");
    }

    // .... что-то делаем с информацией
}

void Net::Client::process()
{
    std::cout << "Client: paket from: " << inet_ntoa(clientaddr.sin_addr) << " " << "Port: " << ntohs(clientaddr.sin_port) << std::endl;;
    for(size_t i = 0; i < recivelength; ++i)
    {
        std::cout << buff[i];
    }
    std::cout<< std::endl;
}


Net::Client::~Client()
{
    close(sockfd);
}



int main()
{
    Net::Client Client(3333,"127.0.0.1");
    Client.connect();

    return 0;
}