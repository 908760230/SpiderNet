#include "SpiderNetEpoll.h"
#include "SpiderNetSocketInfo.h"

namespace SpiderNet
{
    int Epoll::create(){
        return epoll_create(1024);
    }
    void Epoll::release(int fd){
        close(fd);
    }
    bool Epoll::invalid(int fd){
        return fd == -1;
    }

    int Epoll::add(int fd,int socket,void *ud){
        epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.ptr = ud;
        if(epoll_ctl(fd,EPOLL_CTL_ADD,socket,&ev) == -1) return 1;
        return 0;
    }

    void Epoll::del(int fd,int socket){
        epoll_ctl(fd,EPOLL_CTL_DEL,socket,NULL);
    }

    void Epoll::write(int fd,int socket,void *ud,bool enable){
        epoll_event ev;
	    ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);
	    ev.data.ptr = ud;
	    epoll_ctl(fd, EPOLL_CTL_MOD, socket, &ev);
    }

    int Epoll::wait(int fd, Event *e, int max){
        epoll_event ev[max];
	    int n = epoll_wait(fd , ev, max, -1);
	    int i;
	    for (i=0;i<n;i++) {
		e[i].s = ev[i].data.ptr;
		unsigned flag = ev[i].events;
		e[i].write = (flag & EPOLLOUT) != 0;
		e[i].read = (flag & (EPOLLIN | EPOLLHUP)) != 0;
		e[i].error = (flag & EPOLLERR) != 0;
		e[i].eof = false;
	    }

	    return n;
    }

    void Epoll::nonblocking(int fd){
        int flag = fcntl(fd, F_GETFL, 0);
	    if ( -1 == flag )  return;
	    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    }
} // namespace SpiderNet