#ifndef WIND_SERVER_HPP
#define WIND_CLIENT_HPP

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
    class Client
    {
        private:
            int sockfd; //= socket(AF_INET,SOCK_STREAM,0);
            std::string ip_adress;
            int port;
            char buff[SIZE];
            struct sockaddr_in clientaddr;
            socklen_t infolegth;
            int recivelength;
            std::string message;
        public:
            Client(int port,std::string ip_adress);
            ~Client();

            void connect();

        private:
            void init();
            void receive();
            void process();
            void send();

    };


}

#endif // WIND_CLIENT_HPP