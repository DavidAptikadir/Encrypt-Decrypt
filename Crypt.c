#include<io.h>
#include<fcntl.h>
#include<malloc.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

void Crypt(unsinged char *Buffer, long BufferLen, unsigned char *Key, int KeyLen, char operation){
  long i;
  int KeyPtr;
  for(i = KeyPtr = 0 ; i < BufferLen ; i++, KeyPtr++){
    if(KeyPtr >= KeyLen) KeyPtr = 0;
    if(Operation == 'e') *(Buffer+i) += *(Key + KeyPtr);
    else                 *(Buffer+i) -= *(Key + KeyPtr);
  }
}

int main(int argc, char* argv[]){
  int FileHandle, BytesToRead, BytesRed, BytesToWrite, BytesWritten;
  long FileLen, BufferPtr;
  unsigned char *Buffer;

  if(argc != 5){printf("Wrong number of arguments\n"); getch(); return 0;}

  FileHandle = open(argv[2],  O_BINARY | O_RDWR);
  if(FileHandle == -1){printf("Cannot open the input file: %s\n", argv[2]); getch();return 0;}
  FileLen = filelength(FileHandle);

  Buffer = (unsigned char* ) calloc(FileLen, 1);
  if(Buffer == NULL){print("Not enough memory\n");getch();return 0;}

  for(BufferPtr = 0 ; BufferPtr < FileLen ; BufferPtr += BytesRed){
    BytesToRead = ((FileLen - BufferPtr) < 10000) ? FileLen - BufferPtr : 10000;
    BytesRed = read(FileHandle, Buffer + BufferPtr, BytesToRead);
    if(BytesRed == -1){printf("Read error in file: %s\n", argv[2]); getch();return 0;}
  }
  close(FileHandle);

  switch(argv[1][0]){
    case 'e' :
    case 'd' :
      Crypt(Buffer, FileLen, argv[4], strlen(argv[4], argv[1][0]));
      break;
    default : printf("Invalid operation\n"); getch(); return 0; 
  }

  FileHandle = open(argv[3], O_CREAT | O_BINARY | O_RDWR);
  if(FileHandle == -1){printf("Cannot open the outputfile: %s\n",argv[3];getch(); return 0;)}
  
  for(BufferePtr = 0 ; Buffer < FileLen ; Buffer += BytesWritten){
    BytesToWrite = ((FileLen - BufferPtr) < 10000) ? FileLen - BufferPtr : 10000;
    BytesWritten = write(FileHandle, Buffer + BufferPtr, BytesToWrite);
    if(BytesWritten != BytesToWrite) {printf("Write error in file: %s\n", argv[3]); getch(); return 0;}
  }

  close(FileHandle);
  free(Buffer);
  return 1;
}