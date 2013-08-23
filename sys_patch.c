//typedef int32_t DWORD;

#include "sys_patch.h"
#include <string.h>
/*

#include <stdlib.h>
void Sys_RetriveData(){

    #define startADR 0x817539b
    #define endADR 0x81753c4

    FILE * fdout;
    byte* adr;
    int i;

    adr = (byte*)(startADR);

    char buf[32];

    fdout=fopen("diffout.bin", "w");
    if(fdout){

        fwrite("static byte patchblock_??[] = {", 1, 31 ,fdout);

        Com_sprintf(buf, sizeof(buf), " 0x%X, 0x%X, 0x%X, 0x%X, ", (int)adr & 0xff, ((int)adr >> 8) & 0xff, ((int)adr >> 16) & 0xff, ((int)adr >> 24) & 0xff);

        fwrite(buf, 1, strlen(buf),fdout);

        for(i = 0; i < endADR - startADR +1; i++, adr++)
        {
            if(i % 16 == 0)
            {
                fwrite("\n\t", 1, 2 ,fdout);
            }

            Com_sprintf(buf, sizeof(buf), "0x%X, ", *adr);
            fwrite(buf, 1, strlen(buf) ,fdout);
        }

        fwrite("\n};\n", 1, 3 ,fdout);
        fclose(fdout);
    }

    exit(0);
}

*/

void Sys_PatchImageWithBlock(byte *block, int blocksize)
{

    int startadr;
    byte* startadrasbytes = (byte*)&startadr;

    startadrasbytes[0] = block[0];
    startadrasbytes[1] = block[1];
    startadrasbytes[2] = block[2];
    startadrasbytes[3] = block[3];

//    printf("Block Start address is: %X\n", startadr);

    memcpy((void*)startadr, &block[4], blocksize - 4);

}

DWORD SetCall(DWORD addr, void* destination){

	DWORD callwidth;
	DWORD restore;
	byte* baddr = (byte*)addr;

	callwidth = (DWORD)( destination - (void*)baddr - 5);
	*baddr = 0xe8;
	baddr++;

	restore = *(DWORD*)baddr;
	*(DWORD*)baddr = callwidth;

	return restore;
}


DWORD SetJump(DWORD addr, void* destination){

	DWORD jmpwidth;
	DWORD restore;
	byte* baddr = (byte*)addr;

	jmpwidth = (DWORD)( destination - (void*)baddr - 5);
	*baddr = 0xe9;
	baddr++;

	restore = *(DWORD*)baddr;
	*(DWORD*)baddr = jmpwidth;

	return restore;
}