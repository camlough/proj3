#include "fs.h"
#include "buf.h"
#include "inode.h"
#include "super.h"
#include <minix/vfsif.h>

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <minix/com.h>
#include <minix/u64.h>
#include <assert.h>

int do_lsr(void){
	int i, num_blocks;
	mode_t file_type;
	struct inode *ip;

	ip = find_inode(fs_m_in.REQ_DEV, fs_m_in.REQ_INODE_NR);

	if(ip){


		if(!(ip->i_size) || ip->i_size == 0){
			printf("This is an EMPTY file\n");
			return OK;
		}

		else if((ip->i_mode & I_TYPE) == I_IMMEDIATE){
			printf(" This is an IMMEDIATE File\n");
		}

		num_blocks = 1 + (((ip->i_size)-1)/4096);// ceil((float)ip->i_size/(float)4096);
		printf("Here are the Blocks: \n ");
		for(i =0; i< num_blocks; i++){
			printf("Block = %d \n",read_map(ip, i*4096) );
		}
	}
	else{
		printf("I'm not sure but i don't think this file exists\n");
	}

	

return OK;

}
