#include "UdpPiper.h"
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


// initialize some private variable
UdpPiper::UdpPiper(){
    strcpy(this->UDP_ip,"");
    this->UDP_port = 12345;
    this->UDP_sockfd = 0;
    memset(this->buffer, 0, sizeof(this->buffer));
}

// destructor
UdpPiper::~UdpPiper(){
    strcpy(this->UDP_ip,"");
    this->UDP_port = 12345;
    this->UDP_sockfd = 0;
    memset(this->buffer, 0, sizeof(this->buffer));
    close(this->UDP_sockfd);
}

// initialize the server
void UdpPiper::init_as_server(){
    
    this->UDP_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->UDP_sockfd == -1){
        PRINTSTR("server socket create error");
    }

    // struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->UDP_port);
    addr.sin_addr.s_addr = inet_addr(this->UDP_ip);

    PRINTSTR("config port = ");
    PRINTINT(this->UDP_port);
    PRINTSTR("sin_port port = ");
    PRINTINT(addr.sin_port);

    if(bind(this->UDP_sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        PRINTSTR("UDP server bind error");
        exit(EXIT_FAILURE);
    } else {
        PRINTSTR("UDP server bind success");
    }
}

// set the ip and port according to the config file
void UdpPiper::set_config_info(char file_path[256]){
    CIni ini;
    ini.OpenFile(file_path,"r");

    char* ini_ip = ini.GetStr("UDPNetInfo","ip");
    PRINTSTR("config ip = ");
    PRINTSTR(ini_ip);
    strcpy(this->UDP_ip,ini_ip);

    PRINTSTR("read ip = ");
    PRINTSTR(this->UDP_ip);

    this->UDP_port = ini.GetInt("UDPNetInfo","port");
    PRINTSTR("config port = ");
    PRINTINT(this->UDP_port);

}

// client link to the server
void UdpPiper::init_as_client(){

    if( (this->UDP_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        PRINTSTR("UDP client socket init error");
        exit(EXIT_FAILURE);
    } else {
        PRINTSTR("UDP client socket init success");
    }


    int is_broadcast = 1;
    setsockopt(this->UDP_sockfd, SOL_SOCKET, SO_BROADCAST, &is_broadcast, sizeof(is_broadcast));

    // struct  sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->UDP_port);
    addr.sin_addr.s_addr = inet_addr(this->UDP_ip);

    PRINTSTR("config port = ");
    PRINTINT(this->UDP_port);
    PRINTSTR("sin_port port = ");
    PRINTINT(addr.sin_port);

}

// read data from the pipe
int UdpPiper::do_read(Frame& mail){

    int length;

    memset(&mail, 0, sizeof(Frame));

    memset(this->buffer, 0, sizeof(this->buffer));

    socklen_t in_socklen ;

    length = recvfrom(this->UDP_sockfd, this->buffer, sizeof(this->buffer), 0, (struct sockaddr* ) &addr, &in_socklen);

    PRINTSTR("recv from port :");
    PRINTINT(addr.sin_port);

    if (length < 0) {
        PRINTSTR("UDP read error");
        return 0;
    } else if (length >= 0) {
        memcpy(&mail, this->buffer, sizeof(this->buffer));
        if(mail.error_id == WZ_ERROR_ID_SUCCESS) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;

}

// write data to the pipe
void UdpPiper::do_write(Frame write_frame){
    int length;

    memset(this->buffer, 0, sizeof(this->buffer));
    
    length = sendto(this->UDP_sockfd, (char* ) &write_frame, sizeof(write_frame), 0, (struct sockaddr*) &addr, sizeof(addr) );

    PRINTSTR("writing to port :");
    PRINTINT(addr.sin_port);

    if (!length) {
    	PRINTSTR("writing error");
    } else {
    	PRINTSTR("wrote successfully");
        PRINTINT(length);
    }
}
