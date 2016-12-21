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
#include "sharedMemory.h"
#include <sys/mman.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <CORBA-SMALL.h>
#include <mico/os-net.h>
#include <semaphore.h>
#include <pthread.h>


using namespace std;

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
MICO::CSharedMemory::Create( size_t nSize, int mode /*= READ_WRITE*/ )
{
   m_nSize = nSize;
   m_iD = shm_open(m_sName.c_str(), O_CREAT | O_RDWR, 0777);
   cout << "\nIn Create:" << m_sName;
   cout << "\nmID  " << m_iD;
   if(m_iD < 0)
   {
      switch(errno)
      {
      case EACCES:
         throw CSharedMemoryException("Permission Exception ");
         cout << "\nEACCES";
         break;
      case EEXIST:
         cout << "\nEEXIST";
         throw CSharedMemoryException("Shared memory object specified by name already exists.");
         break;
      case EINVAL:
         cout << "\nEINVAL";
         throw CSharedMemoryException("Invalid shared memory name passed.");
         break;
      case EMFILE:
         throw CSharedMemoryException("The process already has the maximum number of files open.");
         break;
      case ENAMETOOLONG:
         throw CSharedMemoryException("The length of name exceeds PATH_MAX.");
         break;
      case ENFILE:
         throw CSharedMemoryException("The limit on the total number of files open on the system has been reached");
         break;
      default:
         cout << "\ndefault";
         throw CSharedMemoryException("Invalid exception occurred in shared memory creation");
         break;
      }
   }

   /* adjusting mapped file size (make room for the whole segment to map)      --  ftruncate() */
   ftruncate(m_iD, m_nSize);
   return true;
}

bool
MICO::CSharedMemory::Attach( int mode /*= A_READ | A_WRITE*/ )
{
   /* requesting the shared segment    --  mmap() */
   m_Ptr = mmap(NULL, m_nSize, PROT_READ | PROT_WRITE, MAP_SHARED, m_iD, 0);
   if (m_Ptr == NULL)
   {
     cout << "Error in attach";
      throw CSharedMemoryException("Exception in attaching the shared memory region");
   }
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

MICO::CSharedMemoryException::CSharedMemoryException( const string &message, bool bSysMsg /*= false*/ ) throw()
{

}

MICO::CSharedMemoryException::~CSharedMemoryException() throw ()
{

}
