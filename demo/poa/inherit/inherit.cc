/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <inherit.h>


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class Base
 */

Base::~Base()
{
}

void *
Base::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Base:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

Base_ptr
Base::_narrow( CORBA::Object_ptr _obj )
{
  Base_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Base:1.0" )))
      return _duplicate( (Base_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Base:1.0") || _obj->_is_a_remote ("IDL:Base:1.0")) {
      _o = new Base_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Base_ptr
Base::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Base : public ::CORBA::StaticTypeInfo {
    typedef Base_ptr _MICO_T;
  public:
    ~_Marshaller_Base();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Base::~_Marshaller_Base()
{
}

::CORBA::StaticValueType _Marshaller_Base::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Base::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Base::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Base::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Base::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Base::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Base::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Base::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Base;


/*
 * Stub interface for class Base
 */

Base_stub::~Base_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Base::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:Base:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_Base *
POA_Base::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Base:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Base *) p;
  }
  return NULL;
}

Base_stub_clp::Base_stub_clp ()
{
}

Base_stub_clp::Base_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Base_stub_clp::~Base_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void Base_stub::BaseOp()
{
  CORBA::StaticRequest __req( this, "BaseOp" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
Base_stub_clp::BaseOp()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Base * _myserv = POA_Base::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->BaseOp();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return;
    }
    _postinvoke ();
  }

  Base_stub::BaseOp();
}

#endif // MICO_CONF_NO_POA


/*
 * Base interface for class Derived
 */

Derived::~Derived()
{
}

void *
Derived::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Derived:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if ((_p = Base::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

Derived_ptr
Derived::_narrow( CORBA::Object_ptr _obj )
{
  Derived_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Derived:1.0" )))
      return _duplicate( (Derived_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Derived:1.0") || _obj->_is_a_remote ("IDL:Derived:1.0")) {
      _o = new Derived_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Derived_ptr
Derived::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Derived : public ::CORBA::StaticTypeInfo {
    typedef Derived_ptr _MICO_T;
  public:
    ~_Marshaller_Derived();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Derived::~_Marshaller_Derived()
{
}

::CORBA::StaticValueType _Marshaller_Derived::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Derived::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Derived::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Derived::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Derived::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Derived::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Derived::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Derived::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Derived;


/*
 * Stub interface for class Derived
 */

Derived_stub::~Derived_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Derived::_narrow_helper (const char * repoid)
{
  void * p;
  if (strcmp (repoid, "IDL:Derived:1.0") == 0) {
    return (void *) this;
  }
  if ((p = POA_Base::_narrow_helper (repoid)) != NULL) 
  {
    return p;
  }
  return NULL;
}

POA_Derived *
POA_Derived::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Derived:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Derived *) p;
  }
  return NULL;
}

Derived_stub_clp::Derived_stub_clp ()
{
}

Derived_stub_clp::Derived_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Derived_stub_clp::~Derived_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void Derived_stub::DerivedOp()
{
  CORBA::StaticRequest __req( this, "DerivedOp" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
Derived_stub_clp::DerivedOp()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Derived * _myserv = POA_Derived::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->DerivedOp();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return;
    }
    _postinvoke ();
  }

  Derived_stub::DerivedOp();
}

#endif // MICO_CONF_NO_POA

struct __tc_init_INHERIT {
  __tc_init_INHERIT()
  {
    _marshaller_Base = new _Marshaller_Base;
    _marshaller_Derived = new _Marshaller_Derived;
  }

  ~__tc_init_INHERIT()
  {
    delete static_cast<_Marshaller_Base*>(_marshaller_Base);
    delete static_cast<_Marshaller_Derived*>(_marshaller_Derived);
  }
};

static __tc_init_INHERIT __init_INHERIT;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface Base
POA_Base::~POA_Base()
{
}

::Base_ptr
POA_Base::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Base::_narrow (obj);
}

CORBA::Boolean
POA_Base::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Base:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Base::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Base:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Base::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Base:1.0");
}

CORBA::Object_ptr
POA_Base::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Base_stub_clp (poa, obj);
}

bool
POA_Base::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "BaseOp" ) == 0 ) {

      if( !__req->read_args() )
        return true;

      BaseOp();
      __req->write_results();
      return true;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    CORBA::UNKNOWN _ex (CORBA::OMGVMCID | 1, CORBA::COMPLETED_MAYBE);
    __req->set_exception (_ex->_clone());
    __req->write_results ();
    return true;
  }
  #endif

  return false;
}

void
POA_Base::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}


// PortableServer Skeleton Class for interface Derived
POA_Derived::~POA_Derived()
{
}

::Derived_ptr
POA_Derived::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Derived::_narrow (obj);
}

CORBA::Boolean
POA_Derived::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Derived:1.0") == 0) {
    return TRUE;
  }
  if (POA_Base::_is_a (repoid)) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Derived::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Derived:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Derived::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Derived:1.0");
}

CORBA::Object_ptr
POA_Derived::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Derived_stub_clp (poa, obj);
}

bool
POA_Derived::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "DerivedOp" ) == 0 ) {

      if( !__req->read_args() )
        return true;

      DerivedOp();
      __req->write_results();
      return true;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    CORBA::UNKNOWN _ex (CORBA::OMGVMCID | 1, CORBA::COMPLETED_MAYBE);
    __req->set_exception (_ex->_clone());
    __req->write_results ();
    return true;
  }
  #endif

  if (POA_Base::dispatch (__req)) {
    return true;
  }

  return false;
}

void
POA_Derived::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

