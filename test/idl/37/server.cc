
#include "double.h"
#ifdef HAVE_ANSI_CPLUSPLUS_HEADERS
#include <fstream>
#else
#include <fstream.h>
#endif

using namespace std;

class Test_impl
    : virtual public POA_Test
{
    void
    op(double d)
    {
        cout.precision(16);
        cout << "server: received: " << d << endl;
    }
};

int
main (int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  CORBA::Object_var poaobj = orb->resolve_initial_references ("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow (poaobj);
  PortableServer::POAManager_var mgr = poa->the_POAManager();

  Test_impl* impl = new Test_impl;
  PortableServer::ObjectId_var oid = poa->activate_object (impl);

  ofstream of ("test.ref");
  CORBA::Object_var ref = poa->id_to_reference (oid.in());
  CORBA::String_var str = orb->object_to_string (ref.in());
  of << str.in() << endl;
  of.close ();

  cout << "Running." << endl;

  mgr->activate ();
  orb->run();

  poa->destroy (TRUE, TRUE);
  delete impl;

  return 0;
}
