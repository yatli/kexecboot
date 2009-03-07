/*
 *  kexecboot - A kexec based bootloader
 *  XPM parsing routines based on libXpm
 *  NOTE: Only XPM 3 are supported!
 *
 *  Copyright (c) 2008-2009 Yuri Bushmelev <jay4mail@gmail.com>
 *  Copyright (C) 1989-95 GROUPE BULL
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

/* NOTE: Sorry, but we don't support ATM:
 * - hotspot coordinates;
 * - 's' color context;
 * - XPM 1 and XPM 2 notation.
 */


#ifndef _HAVE_XPM_H
#define _HAVE_XPM_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "util.h"
#include "hash.h"

/* Limit maximum xpm file size to 64Kb */
#ifndef MAX_XPM_FILE_SIZE
#define MAX_XPM_FILE_SIZE 65535
#endif

#define MAX_COLORNAME_LEN 32

/* Color keys */
enum xpm_ckey_t {
	XPM_KEY_MONO	= 0,
	XPM_KEY_GREY4	= 1,
	XPM_KEY_GRAY4	= 1,
	XPM_KEY_GREY	= 2,
	XPM_KEY_GRAY	= 2,
	XPM_KEY_COLOR	= 3,
	XPM_KEY_UNKNOWN = 4,
};

/* Colors triplet structure */
struct xpm_color_t {
	uint8 r;
	uint8 g;
	uint8 b;
};

struct xpm_parsed_t {
    unsigned int width;		/* image width */
    unsigned int height;	/* image height */
    unsigned int chpp;		/* number of characters per pixel */
    unsigned int ncolors;	/* number of colors */
    struct xpm_color_t *colors;	/* colors array */
    struct xpm_color_t **pixels;/* pixels array (pointers to colors) */
};

/* Macro to find number of lines in compiled-in XPM image array
 * NOTE: Use it only with compiled-in arrays! */
#define XPM_ROWS(array)	(sizeof(array)/sizeof(*array))


/*
 * Function: xpm_destroy_image()
 * Free XPM image array allocated by xpm_load_image()
 * Args:
 * - pointer to xpm image data
 * - rows count of xpm image data
 * Return value: None
 * NOTE: Use it only on images loaded with xpm_load_image()
 */
void xpm_destroy_image(char **xpm_data, const int rows);

/*
 * Function: xpm_load_image()
 * Load XPM image to array of strings to be like compiled-in image.
 * Args:
 * - pointer to store address of XPM image data
 * - filename of XPM image to load
 * Return value:
 * - rows count of xpm image data
 * - -1 on error
 * xpm_data should be destroyed with xpm_destroy_image()
 */
int xpm_load_image(char ***xpm_data, const char *filename);

/*
 * Function: xpm_parse_image()
 * Process XPM image data and make it 'drawable'.
 * Processed data will be stored into allocated buffer.
 * Args:
 * - pointer to xpm image data
 * - rows count of xpm image data
 * - device bits per pixel value
 * Return value:
 * - pointer to allocated and processed data
 * - NULL on error
 * Should be free()'d
 */
struct xpm_parsed_t *xpm_parse_image(char **xpm_data, const int rows,
		unsigned int bpp);

/*
 * Function: xpm_destroy_parsed()
 * Free XPM image data allocated by xpm_parse_image()
 * Args:
 * - pointer to xpm parsed data
 * Return value: None
 */
void xpm_destroy_parsed(struct xpm_parsed_t *xpm);

#endif // _HAVE_XPM_H
