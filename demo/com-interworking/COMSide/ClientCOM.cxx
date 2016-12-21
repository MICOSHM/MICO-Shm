#include <windows.h>
#include <stdio.h>
#include "account.h"     // generated by MIDL from account.idl

void PrintErrorMessage(HRESULT hr);

//+---------------------------------------------------------------------------
//
//  Function:   main
//
//  Synopsis:   Main entry point for the client application.  First we 
//              call CoCreateInstance to create an instance of the server
//              object.  Next, we use the IAccount custom interface to 
//              call the server.
//              Finally, we release the IAccount interface pointer and
//              terminate.
//
//----------------------------------------------------------------------------
void __cdecl main(int argc, char *argv[])
{
    HRESULT hr;
    IAccount *pIAccount = 0;
    //IClassFactory *pClassFactory;

    hr = CoInitialize(NULL);

    if(SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_Account, 0, CLSCTX_LOCAL_SERVER, IID_IAccount, (void **) &pIAccount);
        if(SUCCEEDED(hr))
        {
            hr = pIAccount->deposit(1000);

            if(SUCCEEDED(hr))
            {
                printf("Successfully deposit (1000).\n");
            }
            else
            {
                printf("IAccount::deposit failed.\n");
                PrintErrorMessage(hr);
            }

            printf(" <pausing for 5 sec>\n");
            Sleep( 5000 ); // 5000 msec = 5 sec

            hr = pIAccount->withdraw(500);

            if(SUCCEEDED(hr))
            {
                printf("Successfully withdraw (500).\n");
            }
            else
            {
                printf("IAccount::withdraw failed.\n");
                PrintErrorMessage(hr);
            }

            printf(" <pausing for 5 sec>\n");
            Sleep( 5000 ); // 5000 msec = 5 sec

            long amount;
            hr = pIAccount->balance(&amount);

            if(SUCCEEDED(hr))
            {
                printf("Successfully balance : %d.\n", amount);
            }
            else
            {
                printf("IAccount::withdraw failed.\n");
                PrintErrorMessage(hr);
            }

            pIAccount->Release();
        }
        else
        {
            printf("CoCreateInstance failed.\n");
            PrintErrorMessage(hr);

            if(hr == REGDB_E_CLASSNOTREG)
                printf("Run serverCOM.exe /REGSERVER to install the server program.\n");
        }

        CoUninitialize();
    }
    else
    {
        printf("CoInitialize failed.\n");
        PrintErrorMessage(hr);
    }   
}


