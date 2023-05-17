#ifndef WIND_SERVER_HPP
#define WIND_SERVER_HPP

#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>

const int SIZE = 1024;

namespace Net
{
    class Server
    {
        private:
            int sockfd; //= socket(AF_INET,SOCK_STREAM,0);
            std::string ip_adress;
            int port;
            char buff[SIZE];
            struct sockaddr_in servaddr;
            socklen_t infolegth;
            int recivelength;
        public:
            Server(int port,std::string ip_adress);
            ~Server();

            
            void start();
            void stop();

        private:

            void init();
            void receive();
            void process();
            void send();

    };


}

#endif // WIND_SERVER_HPP