#include "includes.h"
#include "common.h"
#include "Packet32.h"

#define GENMAC_MINVERSION_WPA  0x00010008
#define MINOR_VERSION(v)     ((USHORT)(ULONG)(v))
#define MAJOR_VERSION(v)     ((USHORT)((ULONG)v >> 16))

#define     GENMAC_CATEGORY         0x99
#define     GENMAC_WRAPPER_OID_GET  0x40
#define     GENMAC_WRAPPER_OID_SET  0x41

#define OID_PRIVATE_WRAPPER_LANNUMBER           0xFFFFFF00
#define OID_PRIVATE_WRAPPER_ISWIRELESS          0xFFFFFF01
#define OID_PRIVATE_WRAPPER_GENMAC_VERSION      0xFFFFFF09

#define OID_PRIVATE_WRAPPER_802_1X_STATE        0xFFFFFF0B
#define OID_PRIVATE_WRAPPER_802_1X_READY        0xFFFFFF0C
#define OID_PRIVATE_WRAPPER_802_1X_RX           0xFFFFFF0D
#define OID_PRIVATE_WRAPPER_802_1X_TX           0xFFFFFF0E

#define OID_GEN_CURRENT_PACKET_FILTER           0x0001010E

#define NDIS_PACKET_TYPE_DIRECTED               0x00000001
#define NDIS_PACKET_TYPE_MULTICAST              0x00000002
#define NDIS_PACKET_TYPE_ALL_MULTICAST          0x00000004
#define NDIS_PACKET_TYPE_BROADCAST              0x00000008
#define NDIS_PACKET_TYPE_SOURCE_ROUTING         0x00000010
#define NDIS_PACKET_TYPE_PROMISCUOUS            0x00000020
#define NDIS_PACKET_TYPE_SMT                    0x00000040
#define NDIS_PACKET_TYPE_ALL_LOCAL              0x00000080
#define NDIS_PACKET_TYPE_GROUP                  0x00001000
#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL         0x00002000
#define NDIS_PACKET_TYPE_FUNCTIONAL             0x00004000
#define NDIS_PACKET_TYPE_MAC_FRAME              0x00008000


#define INCL_DOS
#include <os2.h>

static char Pversion[] = "V1.0.0" ;

//----------------------------------------------------------------------------
char *  PacketGetVersion()
{
    wpa_printf(MSG_DEBUG,"%s",__FUNCTION__);
    return Pversion ;
}
//----------------------------------------------------------------------------
int PacketRequest( void *Handle, int Set, PACKET_OID_DATA *p)
{
//  wpa_printf(MSG_DEBUG,"%s 0x%08x %d",__FUNCTION__,p->Oid,p->Length);

    ULONG ParmInOut,DataInOut,rc ;
    ULONG Paras[10] ;

    Paras[0]  = 0 ;
    ParmInOut = 10*4 ;

    DataInOut = p->Length ;
    Paras[0]  = p->Oid ;
    Paras[1]  = p->Length ;

    if( Paras[1] > 10000 )Paras[1] = 10000 ;

    if(Set){

        rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_SET,
                          &Paras[0]  ,ParmInOut,&ParmInOut,
                          &p->Data[0],DataInOut,&DataInOut);
    }
    else{
        rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                          &Paras[0],ParmInOut,&ParmInOut,
                          &p->Data[0],DataInOut,&DataInOut);

    }



    if( rc == 0 )p->Length = Paras[2]  ;
    if( Paras[1]||rc){

        wpa_printf(MSG_DEBUG,"%s 0x%08lx %ld 0x%08lx 0x%08lx",__FUNCTION__,rc,Paras[2],Paras[3],p->Oid);
        return 0 ;
    }
    return 1;
}
//----------------------------------------------------------------------------
static int IsWireless( char *name, int *lannr )
{
    int Handle = (int)PacketOpenAdapter( name);
    if( Handle == 0 )return 0 ;


    ULONG ParmInOut,DataInOut,rc,Dummy ;
    ULONG Paras[10] ;

    Paras[0]  = 0 ;
    ParmInOut = 10*4 ;

    DataInOut = 4 ;
    Paras[1]  = 4 ;
    Paras[0]  = OID_PRIVATE_WRAPPER_ISWIRELESS  ;

    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &Dummy,DataInOut,&DataInOut);


    if( rc != 0 || Dummy == 0){
        PacketCloseAdapter((void*)Handle);
        return 0 ;
    }

    // check for mnimum version number of genmac
    Paras[0]  = OID_PRIVATE_WRAPPER_GENMAC_VERSION   ;
    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &Dummy,DataInOut,&DataInOut);

    if( rc != 0 || Dummy < GENMAC_MINVERSION_WPA){
        PacketCloseAdapter((void*)Handle);
        return 0 ;
    }

    Paras[0]  = OID_PRIVATE_WRAPPER_LANNUMBER   ;
    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &Dummy,DataInOut,&DataInOut);

    *lannr = Dummy ;

    PacketCloseAdapter((void*)Handle);
    return 1 ;

}
//----------------------------------------------------------------------------
static struct aNames_ {

    char dName[16] ;
    char lName[16] ;

}ANames[] = {
    {"WRND32$" ,"lan "},
    {"WRND322$","lan "},
    {"WRND323$","lan "},
    {"WRND324$","lan "},
    {"WRND325$","lan "},
    {"WRND326$","lan "},
    {"WRND327$","lan "},
    {"WRND328$","lan "},
};
//----------------------------------------------------------------------------
int PacketGetAdapterNames( char *Names, ULONG *length)
{
    char myName[32] ;

    wpa_printf(MSG_DEBUG,"%s",__FUNCTION__);
    int i,l,p=0,lan ;
    for( i = 0 ; i < 8 ; i++ ){

        if(!IsWireless(ANames[i].dName,&lan))continue ;
        sprintf(myName,"lan%d",lan);
        ANames[i].lName[3] = '0' + lan ;

        l = strlen(myName);
        strcpy(Names+p,myName);
        Names[p+l] = 0 ;
        p = p + l + 1 ;
    }
    Names[p++] = 0 ;
    Names[p]   = 0 ;
    *length = p ;

    for( i = 0 ; i < 8 ; i++ ){
        wpa_printf(MSG_DEBUG,"%10s %10s",ANames[i].dName,ANames[i].lName);

    }
    if (*length == 1)
       wpa_printf(MSG_ERROR,"%s error: cannot find Genmac V%u.%02u or better",
                   __FUNCTION__,
                   MAJOR_VERSION( GENMAC_MINVERSION_WPA),
                   MINOR_VERSION( GENMAC_MINVERSION_WPA));

    return *length ;
}
//----------------------------------------------------------------------------
void * PacketOpenAdapter( char *name)
{

    char devname[32] ;
    strcpy(devname,name);

    if( name[0] == 'l' && name[1] == 'a' && name[2] == 'n'){
        int i ;
        for( i = 0 ; i < 8 ; i++ ){
            if( strcmp(name,ANames[i].lName))continue;
            strcpy(devname,ANames[i].dName);
            break ;
        }
    }

    wpa_printf(MSG_DEBUG,"%s %s %s",__FUNCTION__,name,devname);

    long openmode,rc,Handle,Action;
    openmode = OPEN_FLAGS_NOINHERIT|OPEN_ACCESS_READWRITE|OPEN_SHARE_DENYNONE;
    rc = DosOpen( (PSZ)devname,&Handle,&Action,0,0,0x01,openmode,0);
    if( rc )return NULL ;
    return (void*)Handle ;
}
//----------------------------------------------------------------------------
int PacketCloseAdapter( void *Handle)
{
    wpa_printf(MSG_DEBUG,"%s",__FUNCTION__);
    return 0 ;
}
//----------------------------------------------------------------------------
int PacketReceiveStart( void *Handle )
{
    ULONG ParmInOut,DataInOut,rc,Count,PacketMode ;
    ULONG Paras[10] ;

    Paras[0]  = 0 ;
    ParmInOut = 10*4 ;

    DataInOut = 4 ;
    Paras[0]  = OID_PRIVATE_WRAPPER_802_1X_STATE;
    Paras[1]  = 4 ;

    Count = 1 ;

    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_SET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &Count,DataInOut,&DataInOut);



    PacketMode = 0 ;

    PacketMode |= NDIS_PACKET_TYPE_DIRECTED;
    PacketMode |= NDIS_PACKET_TYPE_BROADCAST;
    PacketMode |= NDIS_PACKET_TYPE_ALL_MULTICAST;

    DataInOut = 4 ;
    Paras[0]  = OID_GEN_CURRENT_PACKET_FILTER ;
    Paras[1]  = 4 ;

    u8 buf[2000] ;

    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_SET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &PacketMode,DataInOut,&DataInOut);

    Count = 1 ;
    while(Count){

        Paras[0]  = OID_PRIVATE_WRAPPER_802_1X_READY;

        rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                          &Paras[0],ParmInOut,&ParmInOut,
                          &Count,DataInOut,&DataInOut);

        if( rc != 0 || Count == 0 )return 0 ;

        if(Count){
            PacketReceive( Handle, buf);

        // wait a while before next try
        wpa_printf(MSG_DEBUG,"%s wait for driver being ready", __FUNCTION__);
        os_sleep( 1,0);
        }
    }

return rc;
}
//----------------------------------------------------------------------------
int PacketSend( void *Handle, unsigned char *buf, int len)
{
    ULONG ParmInOut,DataInOut,rc ;
    ULONG Paras[10] ;

    Paras[0]  = 0 ;
    ParmInOut = 10*4 ;

    DataInOut = 4 ;
    Paras[1]  = len ;
    Paras[0]  = OID_PRIVATE_WRAPPER_802_1X_TX;

//  wpa_hexdump(MSG_DEBUG,"TXDATA ",buf,len);

    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_SET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      buf,DataInOut,&DataInOut);

    return rc ;

}
//----------------------------------------------------------------------------
int PacketReceive( void *Handle, unsigned char *buf)
{
    ULONG ParmInOut,DataInOut,rc,Count ;
    ULONG Paras[10] ;

    Paras[0]  = 0 ;
    ParmInOut = 10*4 ;

    DataInOut = 4 ;
    Paras[0]  = OID_PRIVATE_WRAPPER_802_1X_READY;
    Paras[1]  = 4 ;



    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &Count,DataInOut,&DataInOut);

    if( rc != 0 || Count == 0 )return 0 ;


    DataInOut = 4 ;
    Paras[0]  = OID_PRIVATE_WRAPPER_802_1X_RX;
    Paras[1]  = 2000 ;

    rc = DosDevIOCtl( (int)Handle,GENMAC_CATEGORY,GENMAC_WRAPPER_OID_GET,
                      &Paras[0],ParmInOut,&ParmInOut,
                      &buf[0],DataInOut,&DataInOut);

    if( rc != 0 || Count == 0 )return 0 ;

    return Paras[2] ;

}

