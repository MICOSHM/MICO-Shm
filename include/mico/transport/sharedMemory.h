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
#include <sys/stat.h>        /* For mode constants */
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <pthread.h>

namespace MICO {

class CSharedMemory {

public:
   static std::string sLockSemaphoreName;

   CSharedMemory();
   CSharedMemory(const std::string& sName );
   //~CSharedMemory();

   bool openSem(std::string sem);
   bool Create(size_t nSize, int mode = O_RDWR);
   bool Attach(int mode = PROT_READ | PROT_WRITE);
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
