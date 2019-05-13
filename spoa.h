/* Main SPOA server includes
 *
 * Copyright 2016 HAProxy Technologies, Christopher Faulet <cfaulet@haproxy.com>
 * Copyright 2018 OZON / Thierry Fournier <thierry.fournier@ozon.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef __SPOA_H__
#define __SPOA_H__

#include <stdbool.h>
#include <stdint.h>
#include <netinet/in.h>

#define MAX_FRAME_SIZE    16384
#define SPOP_VERSION      "1.0"
#define SPOA_CAPABILITIES ""

/* All supported data types */
enum spoe_data_type {
	SPOE_DATA_T_NULL = 0,
	SPOE_DATA_T_BOOL,
	SPOE_DATA_T_INT32,
	SPOE_DATA_T_UINT32,
	SPOE_DATA_T_INT64,
	SPOE_DATA_T_UINT64,
	SPOE_DATA_T_IPV4,
	SPOE_DATA_T_IPV6,
	SPOE_DATA_T_STR,
	SPOE_DATA_T_BIN,
	SPOE_DATA_TYPES
};

/* Scopes used for variables set by agents. It is a way to be agnotic to vars
 * scope. */
enum spoe_vars_scope {
	SPOE_SCOPE_PROC = 0, /* <=> SCOPE_PROC  */
	SPOE_SCOPE_SESS,     /* <=> SCOPE_SESS */
	SPOE_SCOPE_TXN,      /* <=> SCOPE_TXN  */
	SPOE_SCOPE_REQ,      /* <=> SCOPE_REQ  */
	SPOE_SCOPE_RES,      /* <=> SCOPE_RES  */
};

struct worker {
	unsigned int id;
	char         buf[MAX_FRAME_SIZE];
	unsigned int len;
	unsigned int size;
	int          status_code;
	unsigned int stream_id;
	unsigned int frame_id;
	bool         healthcheck;
	int          ip_score; /* -1 if unset, else between 0 and 100 */
};

struct chunk {
	char *str;	/* beginning of the string itself. Might not be 0-terminated */
	int len;	/* current size of the string from first to last char */
};

union spoe_value {
	bool            boolean; /* use for boolean */
	int32_t         sint32;  /* used for signed 32bits integers */
	uint32_t        uint32;  /* used for signed 32bits integers */
	int32_t         sint64;  /* used for signed 64bits integers */
	uint32_t        uint64;  /* used for signed 64bits integers */
	struct in_addr  ipv4;    /* used for ipv4 addresses */
	struct in6_addr ipv6;    /* used for ipv6 addresses */
	struct chunk    buffer;  /* used for char strings or buffers */
};

/* Used to store sample constant */
struct spoe_data {
	enum spoe_data_type type;  /* SPOE_DATA_T_* */
	union spoe_value    u;     /* spoe data value */
};

#endif /* __SPOA_H__ */
