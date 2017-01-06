/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <account.h>


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class Account
 */

Account::~Account()
{
}

void *
Account::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Account:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

Account_ptr
Account::_narrow( CORBA::Object_ptr _obj )
{
  Account_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Account:1.0" )))
      return _duplicate( (Account_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Account:1.0") || _obj->_is_a_remote ("IDL:Account:1.0")) {
      _o = new Account_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Account_ptr
Account::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Account : public ::CORBA::StaticTypeInfo {
    typedef Account_ptr _MICO_T;
  public:
    ~_Marshaller_Account();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Account::~_Marshaller_Account()
{
}

::CORBA::StaticValueType _Marshaller_Account::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Account::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Account::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Account::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Account::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Account::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Account::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Account::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Account;


/*
 * Stub interface for class Account
 */

Account_stub::~Account_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Account::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:Account:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_Account *
POA_Account::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Account:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Account *) p;
  }
  return NULL;
}

Account_stub_clp::Account_stub_clp ()
{
}

Account_stub_clp::Account_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Account_stub_clp::~Account_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void Account_stub::deposit( CORBA::ULong _par_amount )
{
  CORBA::StaticAny _sa_amount( CORBA::_stc_ulong, &_par_amount );
  CORBA::StaticRequest __req( this, "deposit" );
  __req.add_in_arg( &_sa_amount );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
Account_stub_clp::deposit( CORBA::ULong _par_amount )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Account * _myserv = POA_Account::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->deposit(_par_amount);
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

  Account_stub::deposit(_par_amount);
}

#endif // MICO_CONF_NO_POA

void Account_stub::withdraw( CORBA::ULong _par_amount )
{
  CORBA::StaticAny _sa_amount( CORBA::_stc_ulong, &_par_amount );
  CORBA::StaticRequest __req( this, "withdraw" );
  __req.add_in_arg( &_sa_amount );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
Account_stub_clp::withdraw( CORBA::ULong _par_amount )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Account * _myserv = POA_Account::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->withdraw(_par_amount);
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

  Account_stub::withdraw(_par_amount);
}

#endif // MICO_CONF_NO_POA

CORBA::Long Account_stub::balance()
{
  CORBA::Long _res;
  CORBA::StaticAny __res( CORBA::_stc_long, &_res );

  CORBA::StaticRequest __req( this, "balance" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

CORBA::Long
Account_stub_clp::balance()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Account * _myserv = POA_Account::_narrow (_serv);
    if (_myserv) {
      CORBA::Long __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->balance();
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
      return __res;
    }
    _postinvoke ();
  }

  return Account_stub::balance();
}

#endif // MICO_CONF_NO_POA


/*
 * Base interface for class Bank
 */

Bank::~Bank()
{
}

void *
Bank::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Bank:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

Bank_ptr
Bank::_narrow( CORBA::Object_ptr _obj )
{
  Bank_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Bank:1.0" )))
      return _duplicate( (Bank_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Bank:1.0") || _obj->_is_a_remote ("IDL:Bank:1.0")) {
      _o = new Bank_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Bank_ptr
Bank::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Bank : public ::CORBA::StaticTypeInfo {
    typedef Bank_ptr _MICO_T;
  public:
    ~_Marshaller_Bank();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Bank::~_Marshaller_Bank()
{
}

::CORBA::StaticValueType _Marshaller_Bank::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Bank::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Bank::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Bank::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Bank::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Bank::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Bank::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Bank::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Bank;


/*
 * Stub interface for class Bank
 */

Bank_stub::~Bank_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Bank::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:Bank:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_Bank *
POA_Bank::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Bank:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Bank *) p;
  }
  return NULL;
}

Bank_stub_clp::Bank_stub_clp ()
{
}

Bank_stub_clp::Bank_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Bank_stub_clp::~Bank_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

Account_ptr Bank_stub::create()
{
  Account_ptr _res = Account::_nil();
  CORBA::StaticAny __res( _marshaller_Account, &_res );

  CORBA::StaticRequest __req( this, "create" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

Account_ptr
Bank_stub_clp::create()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Bank * _myserv = POA_Bank::_narrow (_serv);
    if (_myserv) {
      Account_ptr __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->create();
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
      return __res;
    }
    _postinvoke ();
  }

  return Bank_stub::create();
}

#endif // MICO_CONF_NO_POA

struct __tc_init_ACCOUNT {
  __tc_init_ACCOUNT()
  {
    _marshaller_Account = new _Marshaller_Account;
    _marshaller_Bank = new _Marshaller_Bank;
  }

  ~__tc_init_ACCOUNT()
  {
    delete static_cast<_Marshaller_Account*>(_marshaller_Account);
    delete static_cast<_Marshaller_Bank*>(_marshaller_Bank);
  }
};

static __tc_init_ACCOUNT __init_ACCOUNT;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface Account
POA_Account::~POA_Account()
{
}

::Account_ptr
POA_Account::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Account::_narrow (obj);
}

CORBA::Boolean
POA_Account::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Account:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Account::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Account:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Account::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Account:1.0");
}

CORBA::Object_ptr
POA_Account::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Account_stub_clp (poa, obj);
}

bool
POA_Account::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "deposit" ) == 0 ) {
      CORBA::ULong _par_amount;
      CORBA::StaticAny _sa_amount( CORBA::_stc_ulong, &_par_amount );

      __req->add_in_arg( &_sa_amount );

      if( !__req->read_args() )
        return true;

      deposit( _par_amount );
      __req->write_results();
      return true;
    }
    if( strcmp( __req->op_name(), "withdraw" ) == 0 ) {
      CORBA::ULong _par_amount;
      CORBA::StaticAny _sa_amount( CORBA::_stc_ulong, &_par_amount );

      __req->add_in_arg( &_sa_amount );

      if( !__req->read_args() )
        return true;

      withdraw( _par_amount );
      __req->write_results();
      return true;
    }
    if( strcmp( __req->op_name(), "balance" ) == 0 ) {
      CORBA::Long _res;
      CORBA::StaticAny __res( CORBA::_stc_long, &_res );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = balance();
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
POA_Account::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}


// PortableServer Skeleton Class for interface Bank
POA_Bank::~POA_Bank()
{
}

::Bank_ptr
POA_Bank::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Bank::_narrow (obj);
}

CORBA::Boolean
POA_Bank::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Bank:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Bank::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Bank:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Bank::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Bank:1.0");
}

CORBA::Object_ptr
POA_Bank::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Bank_stub_clp (poa, obj);
}

bool
POA_Bank::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "create" ) == 0 ) {
      ::Account_ptr _res;
      CORBA::StaticAny __res( _marshaller_Account, &_res );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = create();
      __req->write_results();
      CORBA::release( _res );
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
POA_Bank::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

