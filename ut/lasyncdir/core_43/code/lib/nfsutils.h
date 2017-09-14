#ifndef __NFSUTILS__
#define __NFSUTILS__


#include <string>

//server side 
class nfsutils
{
    public:
        //query functions
        static bool isexported(string sharedir);
        static bool ismounted(string nfsloc, string sharedir, string mpt);

        //server side
        static int nfsstart();
        static int nfsstop();
        static int nfsstatus();
        
        static int confignfs(string sharedir, string nfsopts="*(rw,sync,no_root_squash)");

        //client side 
        static int mountnfs(string nfsloc, string sharedir, 
                string mpt, string mountopts="");
        static int umount(string mpt, int isforce = 0);
};
#endif
