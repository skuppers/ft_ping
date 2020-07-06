# ft_ping
A recreation of the **ping** program written entierly in C.

##  Supported Platforms:
Tested on **Ubuntu 20.04** (Clang 10.0.0)  and **Debian 10.4.0** (Clang 7.0.1-8)

## How to build:
```make```

## Usage:
![image](https://user-images.githubusercontent.com/29956389/86370842-7ef45900-bc80-11ea-86d3-497b210bad65.png)
## Features:
 
![image](https://user-images.githubusercontent.com/29956389/86371654-70f30800-bc81-11ea-8c9f-106e89ec8b2c.png)
Ft_ping:
- resolves DNS
- reverse DNS on icmp responses
- Error reporting
- Statistics and medium deviation

**As this program uses RAW sockets, you will need to be root or execute with sudo**

## About the code

For better understanding of **RFC 791**, i reimplemented the IPv4 header data structure.

![image](https://user-images.githubusercontent.com/29956389/86371329-093cbd00-bc81-11ea-8b97-e2be4c86c3f6.png)

Aswell as **RFC 792** and **RFC 777**: reimplentation of the ICMP header data structure.

![image](https://user-images.githubusercontent.com/29956389/86371350-10fc6180-bc81-11ea-814e-02592dc17a0c.png)

### Used Syscalls and functions :
 - Used the libft library
 - Used different printf functions
 - alarm()
 - getaddrinfo() / freeaddrinfo()
 - getnameinfo()
 - getpid() / getuid()
 - gettimeofday()
 - htons() / ntohs()
 - inet_pton () / inet_ntop()
 - sendto() & receivefrom()
 - socket() & setsocketopt()
 - signal () / malloc() / free()
 -  exit()
