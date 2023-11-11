#ifndef __EREADER_H__
#define __EREADER_H__

extern unsigned char* DotCodeData;
extern char filebuffer[];

#define FREAD_UNCHECKED(A,B,C,D) (void)(fread(A,B,C,D) + 1)

int OpenDotCodeFile(void);
int CheckEReaderRegion(void);
int LoadDotCodeData(int size, uint32_t* DCdata, unsigned long MEM1, unsigned long MEM2);
void EReaderWriteMemory(uint32_t address, uint32_t value);

void BIOS_EReader_ScanCard(int swi_num);

#endif