/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
#ifndef __NET_GAME_H__
#define __NET_GAME_H__

#include "q_shared.h"
#include "sys_net.h"
#include "msg.h"

void NET_UDPPacketEvent(netadr_t* from, void* data, int len);
unsigned int NET_TimeGetTime();

void NET_TCPConnectionClosed(netadr_t* adr, int sock, int connectionId, int serviceId);
tcpclientstate_t NET_TCPAuthPacketEvent(netadr_t* remote, byte* bufData, int cursize, int sock, int* connectionId, int *serviceId);
void NET_TCPPacketEvent(netadr_t* remote, byte* bufData, int cursize, int sock, int connectionId, int serviceId);

void NET_TCPAddEventType(
        qboolean (*tcpevent)(netadr_t* from, msg_t* msg, int socketfd, int connectionId),
        tcpclientstate_t (*tcpauthevent)(netadr_t* from, msg_t* msg, int socketfd, int *connectionId),
        void (*tcpconncloseevent)(netadr_t* from, int socketfd, int connectionId),
        int serviceId
);

#endif

