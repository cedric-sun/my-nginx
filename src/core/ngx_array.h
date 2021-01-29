
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    void        *elts;  // content
    ngx_uint_t   nelts; // # of elements
    size_t       size;  // size of each element
    ngx_uint_t   nalloc; // capacity in # of element
    ngx_pool_t  *pool;
} ngx_array_t;


ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
void ngx_array_destroy(ngx_array_t *a);

// enlarge nelts by 1 (realloc-copy if necessary),
// and return a pointer to that slot; "push" is kinda confusing
void *ngx_array_push(ngx_array_t *a);

// enlarge nelts by n,
// return a pointer to the first slot of those n slots.
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);

// init `array` as empty array of initial capacity `n` elements each of size `size`
static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
