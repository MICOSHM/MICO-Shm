// -*- c++ -*-
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

#ifndef __mico_transport_sharedMemory_h_
#define __mico_transport_sharedMemory_h_

#include <string>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <pthread.h>

namespace MICO {

/**
 *   Signals a problem with the execution of a SharedMemory call.
 */

class CSharedMemoryException: public std::exception
{
public:
    /**
   *   Construct a SharedMemoryException with a explanatory message.
   *   @param message explanatory message
   *   @param bSysMsg true if system message (from strerror(errno))
   *   should be postfixed to the user provided message
   */
    CSharedMemoryException(const std::string &message, bool bSysMsg = false) throw();


    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~CSharedMemoryException() throw ();

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw (){  return m_sMsg.c_str(); }

protected:
    /** Error message.
     */
    std::string m_sMsg;
};

class CSharedMemory
{
public:
   enum
   {
      C_READ_ONLY  = O_RDONLY,
      C_READ_WRITE = O_RDWR,
   } CREATE_MODE;

   enum
   {
      A_READ  = PROT_READ,
      A_WRITE = PROT_WRITE,
   } ATTACH_MODE;

   static std::string sLockSemaphoreName;
public:
   CSharedMemory(const std::string& sName );
   ~CSharedMemory();

   bool openSem(std::string sem);
   bool Create(size_t nSize, int mode = C_READ_WRITE);
   bool Attach(int mode = A_READ | A_WRITE);
   bool Detach();
   bool Lock();
   bool UnLock();
   int GetID() { return m_iD; }
   void* GetData() { return m_Ptr; };
   const void* GetData() const { return m_Ptr; }
private:
   void Clear();
private:
   std::string m_sName;
   int m_iD;
   sem_t* m_SemiD;
   size_t m_nSize;
   void* m_Ptr;

};

}

#endif // __mico_transport_sharedMemory_h_
