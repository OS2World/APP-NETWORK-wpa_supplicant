/*
 * wpa_supplicant/hostapd / OS specific functions for OS/2, ArcaOS and
 * eComStation * systems
 * Copyright (c) 2005, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */
#include "includes.h"
#include "os.h"
#include "common.h"

#define INCL_ERRORS
#define INCL_DOS
#define INCL_VIO
#define INCL_WIN
#include <os2.h>

// ---------- helper functions

static PID _showWindow( BOOL fShow)
{
         PPIB    ppib;
         PTIB    ptib;
         HSWITCH hswitch;
static   SWCNTRL swcntrl;
         ULONG   ulWindowCommand;

// query pid
DosGetInfoBlocks( &ptib, &ppib);

// query tasklist entry and hide entry
hswitch = WinQuerySwitchHandle( NULLHANDLE, ppib->pib_ulpid);

if (hswitch)
   if (!WinQuerySwitchEntry( hswitch, &swcntrl))
      {
      if (fShow)
         {
         swcntrl.uchVisibility = SWL_VISIBLE;
         ulWindowCommand       = SC_RESTORE;
         }
      else
         {
         swcntrl.uchVisibility = SWL_INVISIBLE;
         ulWindowCommand       = SC_MINIMIZE;
         }

      // modify visibility
      WinChangeSwitchEntry( hswitch, &swcntrl);
      WinPostMsg( swcntrl.hwnd, WM_SYSCOMMAND, MPFROMLONG( ulWindowCommand), 0);
      if (fShow)
         {
         WinSwitchToProgram( hswitch);
         WinShowWindow( swcntrl.hwnd, fShow);
         }

      } // if (!WinQuerySwitchEntry( hswitch, &swcntrl))

return ppib->pib_ulpid;
}

/* // ---------- functions missing in C lib of innotek gcc

unsigned short bswap_16( unsigned short us )
{
    return (us & 0xFF)|(us >> 8);
}
*/
unsigned int  alarm(unsigned int a)
{
    sleep( a);
    return 0 ;
}

// ------------------------------------------------------------

void os_sleep(os_time_t sec, os_time_t usec)
{
        if (sec)
                sleep(sec);
        if (usec)
                usleep(usec);
}

int os_get_time(struct os_time *t)
{
        int res;
        struct timeval tv;
        res = gettimeofday(&tv, NULL);
        t->sec = tv.tv_sec;
        t->usec = tv.tv_usec;
        return res;
}

int os_get_reltime(struct os_reltime *t)
{
	int res;
	struct timeval tv;
	res = gettimeofday(&tv, NULL);
	t->sec = tv.tv_sec;
	t->usec = tv.tv_usec;
	return res;
}

int os_mktime(int year, int month, int day, int hour, int min, int sec,
	      os_time_t *t)
{
	struct tm tm, *tm1;
	time_t t_local, t1, t2;
	os_time_t tz_offset;

	if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31 ||
	    hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 ||
	    sec > 60)
		return -1;

	memset(&tm, 0, sizeof(tm));
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;

	t_local = mktime(&tm);

	/* figure out offset to UTC */
	tm1 = localtime(&t_local);
	if (tm1) {
		t1 = mktime(tm1);
		tm1 = gmtime(&t_local);
		if (tm1) {
			t2 = mktime(tm1);
			tz_offset = t2 - t1;
		} else
			tz_offset = 0;
	} else
		tz_offset = 0;

	*t = (os_time_t) t_local - tz_offset;
	return 0;
}

int os_daemonize(const char *pid_file)
{
   PID pid;

   // hide tasklist entry
   pid = _showWindow( FALSE);

   // write pid file
   if (pid_file) {
      FILE *f = fopen( pid_file, "w");
      if (f) {
         fprintf(f, "%u\n", (int)pid);
         fclose(f);
      }
   }

   return -0;
}

void os_daemonize_terminate(const char *pid_file)
{
   if (pid_file)
      unlink(pid_file);
}

int os_get_random(unsigned char *buf, size_t len)
{
    int i ;
    for( i = 0 ; i < len ; i++)buf[i] = rand();
    return 0;
}

unsigned long os_random(void)
{
    return random();
}

char * os_rel2abs_path(const char *rel_path)
{
        char *buf = NULL, *cwd, *ret;
        size_t len = 128, cwd_len, rel_len, ret_len;
        printf("os_rel2abs_path\n");
        printf("  path=%s\n", rel_path);
        if (!rel_path)
          { // no valid rel_path
          return 0;
          }
        if ((rel_path[0] == '/') || ((rel_path[1] == ':') && ((rel_path[2] == '/') || (rel_path[2] == '\\'))))
                return strdup(rel_path);
        printf(" before for\n");
        for (;;) {
                buf = malloc(len);
                if (buf == NULL)
                        return NULL;
                cwd = getcwd(buf, len);
                if (cwd == NULL) {
                        free(buf);
                        if (errno != ERANGE) {
                                return NULL;
                        }
                        len *= 2;
                } else {
                        break;
                }
        }
        printf(" before cwd_len\n");
        cwd_len = strlen(cwd);
        rel_len = strlen(rel_path);
        ret_len = cwd_len + 1 + rel_len + 1;
        ret = malloc(ret_len);
        if (ret) {
                memcpy(ret, cwd, cwd_len);
                ret[cwd_len] = '/';
                memcpy(ret + cwd_len + 1, rel_path, rel_len);
                ret[ret_len - 1] = '\0';
        }
        printf("ret=%s\n", ret);
        free(buf);
        return ret;
}

int os_program_init(void)
{
   APIRET rc;
   PPIB ppib;
   PTIB ptib;
   CHAR szExecutable[ _MAX_PATH];
   PSZ  pszFilename;

   PSZ pszParms;
   BOOL fResize = FALSE;
   PSZ pszResizeValues;
   VIOMODEINFO vmi;

   // identify process - get process info
   if (DosGetInfoBlocks( &ptib, &ppib))
      return 0;
   memset( szExecutable, 0, sizeof( szExecutable));
   DosQueryModuleName( ppib->pib_hmte, sizeof( szExecutable), szExecutable);
   pszFilename = (PSZ) strrchr( szExecutable, '\\');

   // perform init code for wpa supplicant
   // increas priority to keep the key exchange alive
   if ((pszFilename) && (!stricmp( pszFilename, "\\WPA_SUPPLICANT.EXE")))
      {
      // increase priority
      DosSetPriority( PRTYS_PROCESS, PRTYC_FOREGROUNDSERVER , 0, ppib->pib_ulpid);

      // check if verbose parm has been specified
      pszParms = ppib->pib_pchcmd + strlen( ppib->pib_pchcmd) + 1;
      fResize =  (strstr( pszParms, "-d") != NULL);
      if (fResize)
         {
         // increase lines in VIO window
         memset( &vmi, 0, sizeof( VIOMODEINFO));
         vmi.cb = sizeof( VIOMODEINFO);
         rc = VioGetMode( &vmi, 0);
         if (rc == NO_ERROR)
            {

            // determine resize values
            pszResizeValues = getenv( "WPA_SUPPLICANT_RESIZE");
            if ((!pszResizeValues) ||
               (sscanf( pszResizeValues, "%u,%u", (UINT *) &vmi.col, (UINT *) &vmi.row) != 2))
               {
               // available space: 8160 characters
               // some optimum values:
               // 80 * 102 = 8160
               // 68 * 120 = 8160
               // 60 * 136 = 8160
               // set defaults
               vmi.col = 80;
               vmi.row = 102;
               }

            // set VIO mode
            rc = VioSetMode( &vmi, 0);
            }
         }
      }

   return 0;
}

void os_program_deinit(void)
{
        return;
}

int os_setenv(const char *name, const char *value, int overwrite)
{
        return -1;
}


int os_unsetenv(const char *name)
{
        return -1;
}

char * os_readfile(const char *name, size_t *len)
{
   FILE *f;
   char *buf;

   f = fopen(name, "rb");
   if (f == NULL)
      return NULL;

   fseek(f, 0, SEEK_END);
   *len = ftell(f);
   fseek(f, 0, SEEK_SET);

   buf = malloc(*len);
   if (buf == NULL) {
      fclose(f);
      return NULL;
   }

   fread(buf, 1, *len, f);
   fclose(f);

   return buf;
}


int os_fdatasync(FILE *stream)
{
	if (!fflush(stream)) {
    return fsync(fileno(stream));
	}

	return -1;
}


void * os_zalloc(size_t size)
{
   return calloc(1, size);
}

size_t os_strlcpy(char *dest, const char *src, size_t siz)
{
	const char *s = src;
	size_t left = siz;

	if (left) {
		/* Copy string up to the maximum size of the dest buffer */
		while (--left != 0) {
			if ((*dest++ = *s++) == '\0')
				break;
		}
	}

	if (left == 0) {
		/* Not enough room for the string; force NUL-termination */
		if (siz != 0)
			*dest = '\0';
		while (*s++)
			; /* determine total src string length */
	}

	return s - src - 1;
}


int os_memcmp_const(const void *a, const void *b, size_t len)
{
	const u8 *aa = a;
	const u8 *bb = b;
	size_t i;
	u8 res;

	for (res = 0, i = 0; i < len; i++)
		res |= aa[i] ^ bb[i];

	return res;
}


int os_exec(const char *program, const char *arg, int wait_completion)
{
	return -1;
}


void * os_memdup(const void *src, size_t len)
{
	void *r = os_malloc(len);

	if (r)
		os_memcpy(r, src, len);
	return r;
}
