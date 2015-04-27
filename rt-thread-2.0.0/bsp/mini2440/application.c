/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 */

/**
 * @addtogroup mini2440
 */
 
/*@{*/

#include <rtthread.h>
#include "touch.h"
#include "lcd.h"
#include "led.h"
#include "dm9000.h"

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM FatFs filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#ifdef RT_USING_DFS_UFFS
/* dfs filesystem:UFFS filesystem init */
#include <dfs_uffs.h>
#endif
#endif

#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

#ifdef RT_USING_FTK
#include "ftk.h"
#endif

#define RT_INIT_THREAD_STACK_SIZE (2*1024)

#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif

#ifdef RT_USING_FTK
static int argc = 1;
static char* argv[] = {"ftk", NULL};

void rt_ftk_thread_entry(void *parameter)
{
	int FTK_MAIN(int argc, char *argv[]);

	FTK_MAIN(argc, argv);

	return;
}

#endif

void rt_init_thread_entry(void *parameter)
{
	while (1) {
		rt_kprintf("init\n");
	}
}

void rt_led_thread_entry(void *parameter)
{
	while (1)
	{
		rt_kprintf("led\n");
	}
}

int rt_application_init(void)
{
	rt_thread_t init_thread;
	rt_thread_t led_thread;

	init_thread = rt_thread_create("init",
				       rt_init_thread_entry, RT_NULL,
				       512, 8, 4);

	led_thread = rt_thread_create("led",
				      rt_led_thread_entry, RT_NULL,
				      512, 8, 4);

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	if (led_thread != RT_NULL)
		rt_thread_startup(led_thread);

	return 0;
}

/*@}*/
