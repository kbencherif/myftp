# myftp
## Description
FTP server made in the context of my second year of study at Epitech.  
The purpose of the project is to develop an FTP server using C sockets and following the RFC 959.

  
## How to use it
```bash 
git clone git@github.com:kbencherif/myfyp.git  
cd myft  
make && ./myftp 8080 /path/to/directory
```

After the server running, you need to use a client to test it like telnet or netcat.  
An Anonymous user exist, you should use it.

### Commands
PASS  
USER  
QUIT  
NOOP  
PWD  
CWD  
CDUP  
PASV  
STOR  
RETR  
DELE  
LIST  
PORT  
HELP  
