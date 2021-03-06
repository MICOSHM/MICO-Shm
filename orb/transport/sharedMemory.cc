/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2007 by The Mico Team
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  For more information, visit the MICO Home Page at
 *  http://www.mico.org/
 */

#define MICO_CONF_IMR

#include <string>
#include <sys/stat.h>        /* For mode constants */
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <semaphore.h>
#include <pthread.h>
#include <fstream>
#include <unistd.h>

#include <CORBA-SMALL.h>
#include <mico/os-net.h>
#include <mico/impl.h>

using namespace std;

/***************************** SharedMemoryTransport **********************************/
MICO::SharedMemoryTransport::~SharedMemoryTransport () {
    close();
}

CORBA::Boolean
MICO::SharedMemoryTransport::bind (const CORBA::Address *a)
{
    assert(state == Open);
    shmFDAddress = (SharedMemoryAddress *)a;
    //shm_fd = shm_open(shmFDAddress->address().c_str(), O_RDWR, 0);
    return TRUE;
}

CORBA::Boolean
MICO::SharedMemoryTransport::connect (const CORBA::Address *a, CORBA::ULong timeout, CORBA::Boolean& timedout)
{




    assert (state == Open);


    return TRUE;
}

void
MICO::SharedMemoryTransport::open (CORBA::Long thefd)
{
  assert(state == Closed);

  shm_fd = thefd;
  assert(thefd >= 0);
  //OSNet::sock_ndelay(thefd, TRUE);

  //SocketTransport::open(thefd);

  is_buffering = FALSE;

  is_blocking = FALSE;
  state = Open;
}

void
MICO::SharedMemoryTransport::open_sem(std::string semName){
  _semName = semName;
  _sem = sem_open("/sem", O_RDWR);

}

void
MICO::SharedMemoryTransport::post(){
  sem_t *sem;

  if((sem = sem_open("/sem", O_RDWR)) == NULL){
    return;
  } else {
      sem_post(sem);
      sem_close(sem);
  }
}

void
MICO::SharedMemoryTransport::wait(){
  sem_t *sem;

  if((sem = sem_open("/sem", O_RDWR)) == NULL){
    return;
  } else {
      int svalue;
      sem_getvalue(sem, &svalue);
        if(svalue > 0){
          sem_wait(sem);
    }
  }

  sem_close(sem);
}

int
MICO::SharedMemoryTransport::get_sem_value(){
  int svalue = -1;
  sem_t *sem;

  if((sem = sem_open("/sem", O_RDWR)) == NULL){
    return svalue;
  } else {
      sem_getvalue(sem, &svalue);
      sem_close(sem);
  }

  return svalue;
}

void
MICO::SharedMemoryTransport::close ()
{
    if(state != Open);
      return;

    state = Closed;
    //OSNet::sock_shutdown(fd);
    //OSNet::sock_close(fd);
    munmap(_addr, _length);

    //SocketTransport::close();
}

CORBA::Long
MICO::SharedMemoryTransport::read (void *_b, CORBA::Long len, CORBA::Boolean _msgRecv)
{
  void *__addr;
  __addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  //Added a boolean after msg received statment in do_read
  //Variable to be added to all read methods, this is so shm knows when to
  //stop reading

  //add an offset to the mmap ptr to function like read, as reading sequentially
  //with read moves the file offset by bytes read

  CORBA::Long todo = len;
  CORBA::Octet *b = (CORBA::Octet *)_b;

  while (todo > 0) {
     memmove(b, __addr+offset, todo);
     CORBA::Long r = todo;
     offset+=todo;
if (r < 0) {
          OSNet::set_errno();
    if (state != Open)
  return r;
    if (errno == EINTR)
  continue;
          // Cygnus CDK sometimes returns errno 0 when read would block
    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
              todo != len)
  break;
    err = xstrerror (errno);
    return r;
} else if (r == 0 || _msgRecv == TRUE) {
    len = 0;
    todo = 0;
    ateof = TRUE;
    break;
}
b += r;
todo -= r;
  }
  return len - todo;
}

CORBA::Long
MICO::SharedMemoryTransport::write (const void *_b, CORBA::Long len)
{

    _addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (todo > 0) {
       memmove(_addr, b, todo);
       CORBA::Long r = todo;
	if (r < 0) {
            OSNet::set_errno();
	    if (state != Open)
		return r;
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
                todo != len)
		break;
	    err = xstrerror (errno);
	    return r;
	} else if (r == 0) {
	    break;
	}
	b += r;
	todo -= r;
    }
    return len - todo;
}

const CORBA::Address *
MICO::SharedMemoryTransport::addr ()
{
    return shmFDAddress;
}

const CORBA::Address *
MICO::SharedMemoryTransport::peer ()
{
    return shmFDAddress;
}

/*********************** SharedMemoryTransportServer **********************/


MICO::SharedMemoryTransportServer::SharedMemoryTransportServer (CORBA::Address *addr)
{
    //OSNet::sock_init();

    SharedMemoryAddress *shmAddr;
    shmAddr = (SharedMemoryAddress *)addr;

    std::string _addr = shmAddr->address();
    int _len = shmAddr->length();
    std::string sem = shmAddr->semName();
    //std::string __addr = _addr;
}

MICO::SharedMemoryTransportServer::SharedMemoryTransportServer (){

}

CORBA::Boolean
MICO::SharedMemoryTransportServer::open_shm()
{
    try{
      CORBA::Long shmfd = shm_open("foo", O_CREAT | O_RDWR, 0777);
      ftruncate(shmfd, 8096);
      assert(shmfd >= 0);

      shm_fd = shmfd;
      //_length = length;
      //_semName = semName;

      is_blocking = FALSE;
      sem_unlink("/sem");
      _sem = sem_open("/sem", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    } catch (...) {
      return FALSE;
    }
    return TRUE;
}

int
MICO::SharedMemoryTransportServer::get_sem_value(){
  int svalue = -1;
  sem_t *sem;

  if((sem = sem_open("/sem", O_RDWR)) == NULL){
    return svalue;
  } else {
      sem_getvalue(sem, &svalue);
      sem_close(sem);
  }

  return svalue;
}

void
MICO::SharedMemoryTransportServer::listen ()
{
  if(!listening){
  listening = TRUE;
  }
}

void
MICO::SharedMemoryTransportServer::close ()
{
  #ifdef HAVE_THREADS
      if (MICO::Logger::IsLogged (MICO::Logger::Transport)) {
    MICOMT::AutoDebugLock __lock;
    MICO::Logger::Stream (MICO::Logger::Transport)
        << "MICO::TCPTransportServer::close ()" << endl;
      }
  #endif // HAVE_THREADS

  remove_aselect();

  //OSNet::sock_shutdown(fd);
  //MICO_Long result = OSNet::sock_close (fd);
  //assert (!result);
  munmap(_addr, _length);
  shm_unlink("foo");
  sem_close(_sem);


  //fd = ::socket (PF_INET, SOCK_STREAM, 0);
  //assert (fd >= 0);

  // force blocking mode directly on fd
  is_blocking = FALSE;
  this->block(TRUE);

  //OSNet::sock_reuse (fd, TRUE);

  listening = FALSE;
}

CORBA::Boolean
MICO::SharedMemoryTransportServer::bind (const CORBA::Address *a)
{
  //SharedMemoryAddress *shma = (SharedMemoryAddress *)a;

  //try{
    //MICO::CSharedMemory shmMemory(shma->address());
    //shmMemory.Create((short)shma->length());
    //shmMemory.Attach();
  //} catch(std::exception& e){
    //cout << "Exception: " << e.what();
  //}

  //shm_fd = shm_open(shma->address().c_str(), O_RDWR, 0);

  return TRUE;
}

CORBA::Transport *
MICO::SharedMemoryTransportServer::accept ()
{
    SharedMemoryTransport *ret;

    listen();

    //#if defined(HAVE_THREADS) && defined(HAVE_POLL_H)
      //  ::pollfd pfd;

        //pfd.fd = shm_fd;
        //pfd.events = POLLIN | POLLOUT | POLLPRI | POLLHUP | POLLERR | POLLNVAL;

        //if (poll (&pfd, 1, -1) < 0) {
    	//if (MICO::Logger::IsLogged (MICO::Logger::Transport)) {
    	  //  MICOMT::AutoDebugLock __lock;
    	  //  MICO::Logger::Stream (MICO::Logger::Transport)
    		//<< "TCPTransportServer::accept () return:" << errno << endl;
    	//}
    	//return 0;
        //}
        //if (MICO::Logger::IsLogged (MICO::Logger::Transport)) {
    	//MICOMT::AutoDebugLock __lock;
    	//MICO::Logger::Stream (MICO::Logger::Transport)
    	  //  << "TCPTransportServer::poll () return:" << pfd.revents << endl;
        //}

    //#endif // HAVE_THREADS && HAVE_POLL_H

    ret = new SharedMemoryTransport ();
    ret->open(shm_fd);
    return ret;
}

const CORBA::Address *
MICO::SharedMemoryTransportServer::addr ()
{
  return shmFDAddress;
}
