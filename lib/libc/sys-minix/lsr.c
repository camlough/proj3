#include <unistd.h>
#include <lib.h>

int lsr( char *path){
	message m;
	_loadname(path, &m);

	return(_syscall(VFS_PROC_NR, LSR, &m));

}
