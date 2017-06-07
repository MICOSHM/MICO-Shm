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

/************************* CSharedMemory ***************************/

MICO::CSharedMemory::CSharedMemory() {

}

MICO::CSharedMemory::CSharedMemory( const string& sName ):m_sName(sName),m_Ptr(NULL),m_iD(-1),
m_nSize(0)
{
  m_SemiD = NULL;
}

std::string MICO::CSharedMemory::sLockSemaphoreName;

bool
MICO::CSharedMemory::openSem(std::string sem)
{
  sLockSemaphoreName = sem;

  m_SemiD = sem_open(sLockSemaphoreName.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 1);
  return true;
}

bool
MICO::CSharedMemory::Create( size_t nSize)
{
   m_nSize = nSize;
   m_iD = shm_open(m_sName.c_str(), O_CREAT | O_RDWR, 0777);

   /* adjusting mapped file size (make room for the whole segment to map)      --  ftruncate() */
   ftruncate(m_iD, m_nSize);
   return true;
}

bool
MICO::CSharedMemory::Attach()
{
   /* requesting the shared segment    --  mmap() */
   m_Ptr = mmap(NULL, m_nSize, PROT_READ | PROT_WRITE, MAP_SHARED, m_iD, 0);
   return true;
}

bool
MICO::CSharedMemory::Detach()
{
   //munmap(m_Ptr, m_nSize);
}

bool
MICO::CSharedMemory::Lock()
{
   sem_wait(m_SemiD);
}

bool
MICO::CSharedMemory::UnLock()
{
   sem_post(m_SemiD);
}

//Destructor, why is it called after Create.  Have commented out, shm works now

//MICO::CSharedMemory::~CSharedMemory()
//{
  // Clear();
//}

void
MICO::CSharedMemory::Clear()
{
   if(m_iD != -1)
   {
      if ( shm_unlink(m_sName.c_str()) < 0 )
      {
         perror("shm_unlink");
      }
   }
   /**
   * Semaphore unlink: Remove a named semaphore  from the system.
   */
   if(m_SemiD != NULL)
   {
      /**
      * Semaphore Close: Close a named semaphore
      */
      if ( sem_close(m_SemiD) < 0 )
      {
         perror("sem_close");
      }
      /**
      * Semaphore unlink: Remove a named semaphore  from the system.
      */
      if ( sem_unlink(sLockSemaphoreName.c_str()) < 0 )
      {
         perror("sem_unlink");
      }
   }
}

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


    //shm_fd = shm_open(shmFDAddress->address().c_str(), O_RDWR, 0);
    //OSNet::sock_block(shm_fd, FALSE);
    //OSMisc::TimeVal tm;
  	//int addsec = timeout / 1000;
  	//int addusec = (timeout % 1000) * 1000;
  	//tm.tv_sec  = addsec;
  	//tm.tv_usec = addusec;
  	//fd_set rset;
  	//fd_set wset;
  	//fd_set xset;
  	//FD_ZERO(&rset);
  	//FD_ZERO(&wset);
  	//FD_ZERO(&xset);
  	//FD_SET(fd, &wset);

    assert (state == Open);
    shmFDAddress = (SharedMemoryAddress *)a;
    shm_fd = shm_open(shmFDAddress->address().c_str(), O_RDWR, 0);

    //if (timeout != 0) {
    // kcg: by default socket is in blocking mode
    // for connect call, but we need to switch it
    // to the non-blocking mode for a timeout implementation
    //OSNet::sock_block(shm_fd, FALSE);
    //}

    return TRUE;
}

void
MICO::SharedMemoryTransport::open (CORBA::Long thefd)
{
  assert(state == Closed);

  shm_fd = thefd;
  assert(thefd >= 0);
  OSNet::sock_ndelay(thefd, TRUE);
  //OSNet::sock_block(thefd, TRUE);

  SocketTransport::open(thefd);

  is_buffering = FALSE;

  is_blocking = FALSE;
  this->block(TRUE);
  state = Open;
}

void
MICO::SharedMemoryTransport::close ()
{
    if(state != Open);
      return;

    state = Closed;
    OSNet::sock_shutdown(fd);
    OSNet::sock_close(fd);

    SocketTransport::close();
}

CORBA::Long
MICO::SharedMemoryTransport::read (void *_b, CORBA::Long len)
{
  void *addr;
  addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  CORBA::Long todo = len;
  CORBA::Octet *b = (CORBA::Octet *)_b;
  memcpy(b, addr, len);

  while (todo > 0) {
     CORBA::Long r = OSNet::sock_read(shm_fd, b, todo);
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

CORBA::Long
MICO::SharedMemoryTransport::write (const void *_b, CORBA::Long len)
{
    void *addr;
    addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;
    memcpy(addr, b, len);

    while (todo > 0) {
       CORBA::Long r = OSNet::sock_write(shm_fd, b, todo);
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


MICO::SharedMemoryTransportServer::SharedMemoryTransportServer (std::string addr, int length)
{
    OSNet::sock_init();

    CORBA::Long shmfd = shm_open("foo", O_CREAT | O_RDWR, 0777);
    ftruncate(shmfd, 8096);
    assert(shmfd >= 0);

    fd = shmfd;
    shm_fd = shmfd;

    is_blocking = FALSE;
    this->block(TRUE);

    OSNet::sock_reuse(fd, TRUE);
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

  OSNet::sock_shutdown(fd);
  MICO_Long result = OSNet::sock_close (fd);
  assert (!result);

  //fd = ::socket (PF_INET, SOCK_STREAM, 0);
  //assert (fd >= 0);

  // force blocking mode directly on fd
  is_blocking = FALSE;
  this->block(TRUE);

  OSNet::sock_reuse (fd, TRUE);

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

    #if defined(HAVE_THREADS) && defined(HAVE_POLL_H)
        ::pollfd pfd;

        pfd.fd = shm_fd;
        pfd.events = POLLIN | POLLOUT | POLLPRI | POLLHUP | POLLERR | POLLNVAL;

        if (poll (&pfd, 1, -1) < 0) {
    	if (MICO::Logger::IsLogged (MICO::Logger::Transport)) {
    	    MICOMT::AutoDebugLock __lock;
    	    MICO::Logger::Stream (MICO::Logger::Transport)
    		<< "TCPTransportServer::accept () return:" << errno << endl;
    	}
    	return 0;
        }
        if (MICO::Logger::IsLogged (MICO::Logger::Transport)) {
    	MICOMT::AutoDebugLock __lock;
    	MICO::Logger::Stream (MICO::Logger::Transport)
    	    << "TCPTransportServer::poll () return:" << pfd.revents << endl;
        }

    #endif // HAVE_THREADS && HAVE_POLL_H

    ret = new SharedMemoryTransport ();
    ret->open(shm_fd);
    return ret;
}

const CORBA::Address *
MICO::SharedMemoryTransportServer::addr ()
{
  return shmFDAddress;
}
