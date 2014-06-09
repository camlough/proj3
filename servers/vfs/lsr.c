#include "fs.h"
#include <minix/com.h>
#include <minix/endpoint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "file.h"
#include "fproc.h"
#include "param.h"
#include "vmnt.h"
#include "path.h"
#include <minix/vfsif.h>
#include "vnode.h"

int do_lsr(void){
	vir_bytes virt_name = (vir_bytes) m_in.name;
	size_t virt_name_length = (size_t) m_in.name_length;
	struct lookup resolve;
	struct vmnt *vmp;
	char fullpath[PATH_MAX];

	struct filp *fil_tab;
	struct fproc *fprocP;
	struct vnode *vp;
	message m;
	int i, resources;

	if(copy_name(virt_name_length, fullpath) != OK){
		if(fetch_name(virt_name, virt_name_length, fullpath) != OK){
			return ENOENT;
		}
	}


	lookup_init(&resolve, fullpath, PATH_NOFLAGS, &vmp, &vp);
	resolve.l_vmnt_lock = VMNT_READ;
	resolve.l_vnode_lock = VNODE_READ;

	vp = eat_path(&resolve,fp);
	if(vp == NULL){
		printf("This file does not exist\n");
		return ENOENT;
	}


	printf("These proccesses have this file open:  \n");
	for(fil_tab = &filp[0]; fil_tab < &filp[NR_FILPS]; fil_tab++){
		if(fil_tab->filp_vno == vp && fil_tab->filp_count != 0){
			for(fprocP = &fproc[0]; fprocP < &fproc[NR_PROCS]; fprocP++){
				if(fprocP != NULL){
					for(i =0; i< OPEN_MAX; i++){
						if(fprocP->fp_filp[i]== fil_tab){
							printf("PID: %d \n",fprocP->fp_pid );
						}
					}
				}
			}
		}
	}
	m.m_type = 1; // without this asser fails in mfs main,,,,,,, i think? also is the type for the mfs table?
	m.REQ_INODE_NR = vp->v_inode_nr;
	m.REQ_DEV = vp->v_dev;

	resources = req_lsr(vp->v_fs_e, &m);
	unlock_vnode(vp);
	unlock_vmnt(vmp);
	put_vnode(vp);

	return resources;


//ZAMBONIES




}