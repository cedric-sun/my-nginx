
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_TIMES_H_INCLUDED_
#define _NGX_TIMES_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


// precision to millisecond, with GMT offset
typedef struct {
    time_t      sec;     // time_t is in C99, being the # of sec since the epoch
    ngx_uint_t  msec;
    ngx_int_t   gmtoff;
} ngx_time_t;

// called by `main()` at very early stage to call the very first
// `ngx_time_update()`.
void ngx_time_init(void);

// update `ngx_cached_time` and all text representations immediately
// using hardware time
void ngx_time_update(void);
void ngx_time_sigsafe_update(void);


u_char *ngx_http_time(u_char *buf, time_t t);
u_char *ngx_http_cookie_time(u_char *buf, time_t t);
void ngx_gmtime(time_t t, ngx_tm_t *tp);

time_t ngx_next_time(time_t when);
#define ngx_next_time_n      "mktime()"

// the global cached time!
extern volatile ngx_time_t  *ngx_cached_time;

// the preferred ways to access the cached time value
#define ngx_time()           ngx_cached_time->sec
#define ngx_timeofday()      (ngx_time_t *) ngx_cached_time

extern volatile ngx_str_t    ngx_cached_err_log_time;
extern volatile ngx_str_t    ngx_cached_http_time;
extern volatile ngx_str_t    ngx_cached_http_log_time;
extern volatile ngx_str_t    ngx_cached_http_log_iso8601;
extern volatile ngx_str_t    ngx_cached_syslog_time;

/*
 * milliseconds elapsed since some unspecified point in the past
 * and truncated to ngx_msec_t, used in event timers
 */
extern volatile ngx_msec_t  ngx_current_msec;


#endif /* _NGX_TIMES_H_INCLUDED_ */
