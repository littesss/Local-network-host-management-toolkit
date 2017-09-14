#ifndef __NFSUTILS__
#define __NFSUTILS__


#include <string>

//server side 
class nfsutils
{
    public:
        //server side
        static int nfsstart();
        static int nfsstop();
        static int nfsstatus();
        
        static int isexported(string sharedir);     
        static int confignfs(string sharedir, string nfsopt
                ="*(rw,sync,no_root_squash)");

        //client side bool 
        static bool ismounted(string nfsloc, string sharedir, string mpt);
        static int mountnfs(string nfsloc, string sharedir, 
                string mpt, string mountopts="");
        static int umount(string mpt, int isforce = 0);
};
#endif
