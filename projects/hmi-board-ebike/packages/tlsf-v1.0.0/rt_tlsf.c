/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include "rt_tlsf.h"

#if defined (RT_USING_USERHEAP) && defined (PKG_USING_TLSF)

static tlsf_t tlsf_ptr = 0;
static struct rt_semaphore heap_sem;

struct pool_list
{
    pool_t pool_addr;
    rt_slist_t list;
};
typedef struct pool_list *pool_list_t;

static pool_list_t pools_list;

#ifdef RT_USING_HOOK
static void (*rt_malloc_hook)(void *ptr, rt_size_t size);
static void (*rt_free_hook)(void *ptr);

void rt_malloc_sethook(void (*hook)(void *ptr, rt_size_t size))
{
    rt_malloc_hook = hook;
}

void rt_free_sethook(void (*hook)(void *ptr))
{
    rt_free_hook = hook;
}
#endif

void rt_system_heap_init(void *begin_addr, void *end_addr)
{
    size_t size;

    if (begin_addr < end_addr)
    {
        size = (rt_uint32_t)end_addr - (rt_uint32_t)begin_addr;
    }
    else
    {
        return;
    }
    if (!tlsf_ptr)
    {
        tlsf_ptr = (tlsf_t)tlsf_create_with_pool(begin_addr, size);
        rt_sem_init(&heap_sem, "heap", 1, RT_IPC_FLAG_PRIO);

        pools_list = rt_malloc(sizeof(struct pool_list));
        rt_slist_init(&pools_list->list);
        pools_list->pool_addr = tlsf_get_pool(tlsf_ptr);
    }
    else
    {
        RT_ASSERT(0);
    }
}

void *rt_system_heap_add(void *begin_addr, void *end_addr)
{
    pool_t tlsf_pool;
    size_t size;
    pool_list_t heap;

    if (begin_addr < end_addr)
    {
        size = (rt_uint32_t)end_addr - (rt_uint32_t)begin_addr;
    }
    else
    {
        RT_ASSERT(0);
    }

    if (tlsf_ptr)
    {
        tlsf_pool = tlsf_add_pool(tlsf_ptr, begin_addr, size);
        if (tlsf_pool != RT_NULL)
        {
            heap = rt_malloc(sizeof(struct pool_list));
            rt_slist_append(&pools_list->list, &heap->list);
            heap->pool_addr = tlsf_pool;
            return heap;
        }
    }
    return RT_NULL;
}

void rt_system_heap_remove(void *heap)
{
    RT_ASSERT(heap != RT_NULL);

    pool_list_t pool_node = (pool_list_t)heap;
    pool_t pool = pool_node->pool_addr;

    if (tlsf_ptr)
    {
        rt_slist_remove(&pools_list->list, &pool_node->list);
        rt_free(pool_node);
        tlsf_remove_pool(tlsf_ptr, pool);
    }
}

#ifdef PKG_TLSF_USING_ALIGN
void *rt_malloc_align(rt_size_t size, rt_size_t align)
{
    void *ptr = RT_NULL;

    if (tlsf_ptr)
    {
        rt_sem_take(&heap_sem, RT_WAITING_FOREVER);
        ptr = tlsf_memalign(tlsf_ptr, align, size);
        rt_sem_release(&heap_sem);
    }
    return ptr;
}

void rt_free_align(void *ptr)
{
    rt_free(ptr);
}
#endif

void *rt_malloc(rt_size_t nbytes)
{
    void *ptr = RT_NULL;

    if (tlsf_ptr)
    {
        rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

        ptr = tlsf_malloc(tlsf_ptr, nbytes);
        RT_OBJECT_HOOK_CALL(rt_malloc_hook, ((void *)ptr, nbytes));

        rt_sem_release(&heap_sem);
    }
    return ptr;
}
RTM_EXPORT(rt_malloc);

void rt_free(void *ptr)
{
    if (tlsf_ptr)
    {
        rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

        tlsf_free(tlsf_ptr, ptr);
        RT_OBJECT_HOOK_CALL(rt_free_hook, (ptr));

        rt_sem_release(&heap_sem);
    }
}
RTM_EXPORT(rt_free);

void *rt_realloc(void *ptr, rt_size_t nbytes)
{
    if (tlsf_ptr)
    {
        rt_sem_take(&heap_sem, RT_WAITING_FOREVER);

        ptr = tlsf_realloc(tlsf_ptr, ptr, nbytes);

        rt_sem_release(&heap_sem);
    }
    return ptr;
}
RTM_EXPORT(rt_realloc);

void *rt_calloc(rt_size_t count, rt_size_t size)
{
    void *ptr = RT_NULL;
    rt_size_t total_size;

    total_size = count * size;
    ptr = rt_malloc(total_size);
    if (ptr != RT_NULL)
    {
        /* clean memory */
        rt_memset(ptr, 0, total_size);
    }

    return ptr;
}
RTM_EXPORT(rt_calloc);

static size_t used_mem = 0;
static size_t total_mem = 0;

static void mem_info(void *ptr, size_t size, int used, void *user)
{
    if (used)
    {
        used_mem += size;
    }
    total_mem += size;
}

void rt_memory_info(rt_size_t *total,
                    rt_size_t *used,
                    rt_size_t *max_used)
{
    used_mem = 0;
    total_mem = 0;

    tlsf_walk_pool(tlsf_get_pool(tlsf_ptr), mem_info, 0);

    *total = total_mem;
    *used = used_mem;
    *max_used = used_mem;
}

void list_mem(void)
{
    rt_uint8_t i = 0;
    rt_uint8_t len = 0;

    pool_list_t pool_node;
    struct rt_slist_node *node;
    node = &pools_list->list;

    used_mem = 0;
    total_mem = 0;

    len = rt_slist_len(node) + 1;
    for (i = 0; i < len; i++)
    {
        pool_node = rt_container_of(node, struct pool_list, list);
        tlsf_walk_pool(pool_node->pool_addr, mem_info, 0);
        node = node->next;
    }
    rt_kprintf("total memory: %d\n", total_mem);
    rt_kprintf("used memory : %d\n", used_mem);
}

#endif

