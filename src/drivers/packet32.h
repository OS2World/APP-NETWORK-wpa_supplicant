#ifndef PACKET32_H
#define PACKET32_H

typedef unsigned char      UCHAR ;
typedef unsigned short     USHORT;
typedef unsigned long      ULONG ;
typedef unsigned long      HANDLE;
typedef unsigned long long ULONGLONG ;

typedef          char      CHAR ;
typedef          short     SHORT;
typedef          long      LONG ;

typedef          char *    PTSTR ;
typedef unsigned char      BOOLEAN ;

typedef struct _Adapter {

    int     Dummy ;

}ADAPTER,*LPADAPTER ;

typedef struct _PACKET_OID_DATA {

    ULONG       Oid ;
    int         Length ;
    char        Data[16] ;

}PACKET_OID_DATA;


int     PacketRequest( void *, int , PACKET_OID_DATA *);
char *  PacketGetVersion();
int     PacketGetAdapterNames( char *, ULONG *);
void *  PacketOpenAdapter( char *);
int     PacketCloseAdapter( void *);
int     PacketReceive( void *, unsigned char *);
int     PacketSend( void *, unsigned char *, int);
int     PacketReceiveStart( void *);
int     PacketReceiveStop( void *);

#endif
