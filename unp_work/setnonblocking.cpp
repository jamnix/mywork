#include "iostream"
#include "fcntl.h"
using namespace std;

int setnonblocking(int fd) 
{
    int flags;
    flags = fcntl(fd, F_GETFL);
    if(flags < 0)
    {   
        return -1; 
    }   
    if(! (flags & O_NONBLOCK))
    {   
        return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    }   
}

int main()
{
    int port = 80; 
    char addr[] = "127.0.0.0";
    int backlog = 128;
    int MAX_EVENTS = 128;
    struct epoll_event ev, events[MAX_EVENTS];
    char buf[BUFSIZ];

    int listenfd, epfd, nfds, accept_sock;
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listenfd < 0)
        return -1; 
    setnonblocking(listenfd);
    struct sockaddr_in svr_addr ,remote_addr;
    size_t remote_addr_len;

    memset((char*)svr_addr, 0, sizeof(struct sock_addr));
    svr_addr.sin_port = htons(port);
    //svr_addr.sin_addr.s_addr = inet_addr(addr);
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_addr.sin_family = AF_INET;

    int rv = 0;
    rv = ::bind(listenfd, (struct sockaddr*) &svr_addr, sizeof(sockaddr));

    ::listen(listenfd, backlog);

    epfd = epoll_create(MAX_EVENTS);
    if(epfd == -1)
        return -1;


    ev.events = EPOLLIN;
    ev.fd = listenfd;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
        return -1;
    for(;;)
    {
            nfds = epoll_wait(epfd, events, MAXEVENTS, -1);
            if(nfds == -1)
                return -1;
            for(int i=0; i < nfds; i++)
            {
                fd = events[i].data.fd;
                if(fd == listenfd)
                {
                    while((accept_sock = accept(fd, (struct sockaddr*)&remote_addr), &remote_addr_len) > 0)  //$$$$$                  
		    {
                        setnonblocking(remote_addr);
                        ev.events = EPOLLIN |EPOLLET;
                        ev.data.fd = accept_sock;
                        if(epoll_ctl(epfd, EPOLL_CTL_ADD, accept_sock, &ev) == -1)
                        {
                            return -1;
                        }

                    }
                    if(accept_sock == -1)
                    {
                        if(errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
                            cout << "accept error";
                    }
                    continue;         //$$$$$
                }
                if(events.[i].events & EPOLLIN)
                {
                    int n = 0;
                    while((nread = read(fd, buf + n, BUFSIZ-1)) > 0)
                    {
                        n += nread;
                    }
                    if(nread == -1 && errno != EAGAIN)
                        cout << "error";
                    ev.events = events[i].events | EPOLLOUT;
                    ev.data.fd = fd;
                    if(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1)
                        cout << "error";

                }
                if(events.[i].events & EPOLLOUT)
                {
                    sprintf(buf, "fuckyou", 7);
                    int n = strlen(buf), nwrite;
                    int finish = 0;
                    int left = n;
                    while(n > 0)
                    {
                        nwrite = write(fd, buf-finish, n);
                        if(nwrite == -1 && )
                        if(left <= 0)
                        {
                            break;
                        }

                    }

                }

            }

    }
}
