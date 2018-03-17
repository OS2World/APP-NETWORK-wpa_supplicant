/*
 * WPA Supplicant - Layer2 packet handling with OS/2 TCP/IP and genmac
 * Copyright (c) 2003-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 *
 * This file can be used as a starting point for layer2 packet implementation.
 */
#include "includes.h"
#include "common.h"
#include "eloop.h"
#include "l2_packet.h"
#include "..\drivers\packet32.h"  // 20180308 AB changed //

#define WPA_DEBUG       MSG_DEBUG

struct l2_packet_data {
        char ifname[17];
        u8 own_addr[ETH_ALEN];
        void (*rx_callback)(void *ctx, const u8 *src_addr,
                            const u8 *buf, size_t len);
        void *rx_callback_ctx;
        int l2_hdr; /* whether to include layer 2 (Ethernet) header data
                     * buffers */
        int fd;
};

static void *WPA_Event = NULL ;

extern void wpa_driver_ndis_event_connect(void *drv);
extern void wpa_driver_ndis_event_disconnect(void *drv);
extern void wpa_driver_ndis_event_media_specific(void *drv,u8*,int);


void wpa_driver_register_event_cb(void *h)
{
    WPA_Event = h ;
}

int l2_packet_get_own_addr(struct l2_packet_data *l2, u8 *addr)
{
        memcpy(addr, l2->own_addr, ETH_ALEN);
        return 0;
}

int l2_packet_send(struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
                   const u8 *buf, size_t len)
{

        wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);

        if (l2 == NULL)
                return -1;
        /*
         * TODO: Send frame (may need different implementation depending on
         * whether l2->l2_hdr is set).
         */

        unsigned char *Buffer = malloc(2000);

        memcpy(&Buffer[ 0],dst_addr,6);

        memcpy(&Buffer[ 6],l2->own_addr,6);
        Buffer[12] = 0x88 ;
        Buffer[13] = 0x8e ;

        memcpy(&Buffer[14],buf,len);

        PacketSend( (void*)l2->fd,Buffer,len+14 );

        free(Buffer) ;

        return 0;
}

static void l2_packet_receive(int sock, void *eloop_ctx, void *sock_ctx)
{

        //wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);

        struct l2_packet_data *l2 = eloop_ctx;
        u8 buf[2300];
        int res;
        /* TODO: receive frame (e.g., recv() using sock */
        buf[0] = 0;
        res = 0;

        res = PacketReceive((void*)l2->fd,buf);
        if( res & 0x8000000 ){

            int len = res & 0xFFF ;

            //wpa_hexdump(MSG_DEBUG,"STATUS XXXXXX ",buf,len);

            ULONG *ulP = (ULONG*)buf ;
            if( ulP[0] == 0x4001000b ){
                wpa_driver_ndis_event_connect(WPA_Event);
            }
            else if( ulP[0] == 0x4001000C ){
                wpa_driver_ndis_event_disconnect(WPA_Event);
            }
            else if( ulP[0] == 0x40010012 ){
                wpa_driver_ndis_event_media_specific(WPA_Event,&buf[4],len-4);
            }
            return ;
        }

        if( res ){

            //wpa_hexdump(MSG_DEBUG,"RXDATA ",buf,res);

            l2->rx_callback(l2->rx_callback_ctx, &buf[6],
                            &buf[6+6+2], res-14);
        }
}

static void l2_packet_receive_timeout(void *eloop_ctx, void *timeout_ctx)
{
        struct l2_packet_data *l2 = eloop_ctx;

        void *pcap = timeout_ctx;

        /* Register new timeout before calling l2_packet_receive() since
         * receive handler may free this l2_packet instance (which will
         * cancel this timeout). */

        eloop_register_timeout(0,100000,l2_packet_receive_timeout,l2,pcap);
        l2_packet_receive(l2->fd, eloop_ctx, timeout_ctx);

}

struct l2_packet_data * l2_packet_init(
        const char *ifname, const u8 *own_addr, unsigned short protocol,
        void (*rx_callback)(void *ctx, const u8 *src_addr,
                            const u8 *buf, size_t len),
        void *rx_callback_ctx, int l2_hdr)
{

        wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);

        struct l2_packet_data *l2;
        l2 = malloc(sizeof(struct l2_packet_data));
        if (l2 == NULL)
                return NULL;
        memset(l2, 0, sizeof(*l2));
        strncpy(l2->ifname, ifname, sizeof(l2->ifname));
        l2->rx_callback = rx_callback;
        l2->rx_callback_ctx = rx_callback_ctx;
        l2->l2_hdr = l2_hdr;

        /*
         * TODO: open connection for receiving frames
         */


        l2->fd = (int)PacketOpenAdapter(l2->ifname);

        PacketReceiveStart((void*)l2->fd);

        if (own_addr)memcpy(l2->own_addr, own_addr, ETH_ALEN);

        eloop_register_timeout(0,100000,l2_packet_receive_timeout,l2,l2);
   //   eloop_register_read_sock(l2->fd, l2_packet_receive, l2, NULL);
        return l2;
}

struct l2_packet_data * l2_packet_init_bridge(
	const char *br_ifname, const char *ifname, const u8 *own_addr,
	unsigned short protocol,
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len),
	void *rx_callback_ctx, int l2_hdr)
{
	return l2_packet_init(br_ifname, own_addr, protocol, rx_callback,
			      rx_callback_ctx, l2_hdr);
}

void l2_packet_deinit(struct l2_packet_data *l2)
{

        wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);


        if (l2 == NULL)
                return;
        if (l2->fd >= 0) {
                eloop_unregister_read_sock(l2->fd);
                /* TODO: close connection */
        }

        free(l2);
}

int l2_packet_get_ip_addr(struct l2_packet_data *l2, char *buf, size_t len)
{
        wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);


        /* TODO: get interface IP address */
        return -1;
}

void l2_packet_notify_auth_start(struct l2_packet_data *l2)
{
        wpa_printf(WPA_DEBUG,"%s",__FUNCTION__);


        /* This function can be left empty */
}
