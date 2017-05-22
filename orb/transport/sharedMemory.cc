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
   munmap(m_Ptr, m_nSize);
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
    return TRUE;
}

CORBA::Boolean
MICO::SharedMemoryTransport::connect (const CORBA::Address *a, CORBA::ULong timeout, CORBA::Boolean& timedout)
{
    shmFDAddress = (SharedMemoryAddress *)a;

    shm_fd = shm_open(shmFDAddress->address().c_str(), O_RDWR, 0);

    return TRUE;
}

void
MICO::SharedMemoryTransport::open (CORBA::Long thefd)
{

}

void
MICO::SharedMemoryTransport::close ()
{

}

CORBA::Long
MICO::SharedMemoryTransport::read (void *_b, CORBA::Long len)
{
    CORBA::Octet *b = (CORBA::Octet *)_b;
    void *addr;

    addr = mmap(NULL, len, PROT_READ, MAP_SHARED, shm_fd, 0);
    memcpy(b, addr, len);

    return len;
}

CORBA::Long
MICO::SharedMemoryTransport::write (const void *_b, CORBA::Long len)
{
    void *addr;

    CORBA::Octet *b = (CORBA::Octet *)_b;
    addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    memcpy(addr, b, len);

    return len;
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


MICO::SharedMemoryTransportServer::SharedMemoryTransportServer ()
{

}

void
MICO::SharedMemoryTransportServer::listen ()
{
  listening = TRUE;
}

void
MICO::SharedMemoryTransportServer::close ()
{

}

CORBA::Boolean
MICO::SharedMemoryTransportServer::bind (const CORBA::Address *a)
{
    return TRUE;
}

CORBA::Transport *
MICO::SharedMemoryTransportServer::accept ()
{
    SharedMemoryTransport *ret;

    ret = new SharedMemoryTransport ();
    return ret;
}

const CORBA::Address *
MICO::SharedMemoryTransportServer::addr ()
{
  return shmFDAddress;
}
