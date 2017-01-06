/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __INHERIT_H__
#define __INHERIT_H__




class Base;
typedef Base *Base_ptr;
typedef Base_ptr BaseRef;
typedef ObjVar< Base > Base_var;
typedef ObjOut< Base > Base_out;

class Derived;
typedef Derived *Derived_ptr;
typedef Derived_ptr DerivedRef;
typedef ObjVar< Derived > Derived_var;
typedef ObjOut< Derived > Derived_out;




/*
 * Base class and common definitions for interface Base
 */

class Base : 
  virtual public CORBA::Object
{
  public:
    virtual ~Base();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Base_ptr _ptr_type;
    typedef Base_var _var_type;
    #endif

    static Base_ptr _narrow( CORBA::Object_ptr obj );
    static Base_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Base_ptr _duplicate( Base_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Base_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void BaseOp() = 0;

  protected:
    Base() {};
  private:
    Base( const Base& );
    void operator=( const Base& );
};

// Stub for interface Base
class Base_stub:
  virtual public Base
{
  public:
    virtual ~Base_stub();
    void BaseOp();

  private:
    void operator=( const Base_stub& );
};

#ifndef MICO_CONF_NO_POA

class Base_stub_clp :
  virtual public Base_stub,
  virtual public PortableServer::StubBase
{
  public:
    Base_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~Base_stub_clp ();
    void BaseOp();

  protected:
    Base_stub_clp ();
  private:
    void operator=( const Base_stub_clp & );
};

#endif // MICO_CONF_NO_POA


/*
 * Base class and common definitions for interface Derived
 */

class Derived : 
  virtual public ::Base
{
  public:
    virtual ~Derived();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Derived_ptr _ptr_type;
    typedef Derived_var _var_type;
    #endif

    static Derived_ptr _narrow( CORBA::Object_ptr obj );
    static Derived_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Derived_ptr _duplicate( Derived_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Derived_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void DerivedOp() = 0;

  protected:
    Derived() {};
  private:
    Derived( const Derived& );
    void operator=( const Derived& );
};

// Stub for interface Derived
class Derived_stub:
  virtual public Derived,
  virtual public ::Base_stub
{
  public:
    virtual ~Derived_stub();
    void DerivedOp();

  private:
    void operator=( const Derived_stub& );
};

#ifndef MICO_CONF_NO_POA

class Derived_stub_clp :
  virtual public Derived_stub,
  virtual public ::Base_stub_clp
{
  public:
    Derived_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~Derived_stub_clp ();
    void DerivedOp();

  protected:
    Derived_stub_clp ();
  private:
    void operator=( const Derived_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_Base : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~POA_Base ();
    Base_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_Base * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void BaseOp() = 0;

  protected:
    POA_Base () {};

  private:
    POA_Base (const POA_Base &);
    void operator= (const POA_Base &);
};

template<class T>
class POA_Base_tie : 
  virtual public POA_Tie_Base<T>,
  virtual public POA_Base
{
  public:
    POA_Base_tie (T &t)
      : POA_Tie_Base<T> (&t, PortableServer::POA::_nil(), FALSE)
    {}
    POA_Base_tie (T &t, PortableServer::POA_ptr _poa)
      : POA_Tie_Base<T> (&t, _poa, FALSE)
    {}
    POA_Base_tie (T *t, CORBA::Boolean _rel = TRUE)
      : POA_Tie_Base<T> (t, PortableServer::POA::_nil(), _rel)
    {}
    POA_Base_tie (T *t, PortableServer::POA_ptr _poa, CORBA::Boolean _rel = TRUE)
      : POA_Tie_Base<T> (t, _poa, _rel)
    {}
    virtual ~POA_Base_tie ();

    PortableServer::POA_ptr _default_POA ();

    void BaseOp();

  protected:
    POA_Base_tie () {};

  private:
    POA_Base_tie (const POA_Base_tie<T> &);
    void operator= (const POA_Base_tie<T> &);
};

template<class T>
POA_Base_tie<T>::~POA_Base_tie ()
{
}

template<class T>
PortableServer::POA_ptr
POA_Base_tie<T>::_default_POA ()
{
  if (!CORBA::is_nil (POA_Tie_Base<T>::poa)) {
    return PortableServer::POA::_duplicate (POA_Tie_Base<T>::poa);
  }
  return PortableServer::ServantBase::_default_POA ();
}

template<class T>
void
POA_Base_tie<T>::BaseOp ()
{
  POA_Tie_Base<T>::ptr->BaseOp ();
}

class POA_Derived : 
  virtual public POA_Base
{
  public:
    virtual ~POA_Derived ();
    Derived_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_Derived * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void DerivedOp() = 0;

  protected:
    POA_Derived () {};

  private:
    POA_Derived (const POA_Derived &);
    void operator= (const POA_Derived &);
};

template<class T>
class POA_Derived_tie : 
  virtual public POA_Base_tie<T>,
  virtual public POA_Derived
{
  public:
    POA_Derived_tie (T &t)
      : POA_Tie_Base<T> (&t, PortableServer::POA::_nil(), FALSE)
    {}
    POA_Derived_tie (T &t, PortableServer::POA_ptr _poa)
      : POA_Tie_Base<T> (&t, _poa, FALSE)
    {}
    POA_Derived_tie (T *t, CORBA::Boolean _rel = TRUE)
      : POA_Tie_Base<T> (t, PortableServer::POA::_nil(), _rel)
    {}
    POA_Derived_tie (T *t, PortableServer::POA_ptr _poa, CORBA::Boolean _rel = TRUE)
      : POA_Tie_Base<T> (t, _poa, _rel)
    {}
    virtual ~POA_Derived_tie ();

    PortableServer::POA_ptr _default_POA ();

    void DerivedOp();

  protected:
    POA_Derived_tie () {};

  private:
    POA_Derived_tie (const POA_Derived_tie<T> &);
    void operator= (const POA_Derived_tie<T> &);
};

template<class T>
POA_Derived_tie<T>::~POA_Derived_tie ()
{
}

template<class T>
PortableServer::POA_ptr
POA_Derived_tie<T>::_default_POA ()
{
  if (!CORBA::is_nil (POA_Tie_Base<T>::poa)) {
    return PortableServer::POA::_duplicate (POA_Tie_Base<T>::poa);
  }
  return PortableServer::ServantBase::_default_POA ();
}

template<class T>
void
POA_Derived_tie<T>::DerivedOp ()
{
  POA_Tie_Base<T>::ptr->DerivedOp ();
}

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_Base;

extern CORBA::StaticTypeInfo *_marshaller_Derived;

#endif
