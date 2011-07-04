/*
 * libshjpeg: A library for controlling SH-Mobile JPEG hardware codec
 *
 * Copyright (C) 2010 IGEL Co.,Ltd.
 * Copyright (C) 2008,2009 Renesas Technology Corp.
 * Copyright (C) 2008 Denis Oliver Kropp
 *
 * This library is dual licensed.
 * You are free to use this library under either the MIT or
 * the GNU LGPL version 2 license.
 *
 * For more information please refer to the licensing files
 * in the root directory of this library package.
 *
 * GNU LGPL license: COPYING_LGPL
 * MIT license: COPYING_MIT
 */

#include "libjpeg_wrap/hooks.h"
#include "shjpeg/shjpeg_types.h"

typedef struct {
	j_common_ptr cinfo;
	shjpeg_context_t *context;
	buffer_cache_context_t *cache_con;
} cinfo_context;

/*With libjpeg functions
  ------------------
  These functions will work with the existing libjpeg API and link in the
  JPU support.  They will fall back to the libjpeg implementation if there is
  no support in the JPU for the requested operation.  */
void shjpeg_start_compress(j_compress_ptr cinfo, boolean write_all_tables);
boolean shjpeg_start_decompress(j_decompress_ptr cinfo);
int shjpeg_read_header(j_decompress_ptr cinfo, boolean require_image);

/*JPU override functions
  --------------
  These functions will be used when it has been determined that JPU support is
  available for a given operation.  These functions have no fallback to libjpeg
  since the libjpeg state is not recoverable from where these functions may
  fail.  */

JDIMENSION shjpeg_write_scanlines(j_compress_ptr cinfo, JSAMPARRAY scanlines, 
				  JDIMENSION num_lines);
void shjpeg_finish_compress(j_compress_ptr cinfo);

JDIMENSION shjpeg_read_scanlines(j_decompress_ptr cinfo, JSAMPARRAY scanlines, 
				  JDIMENSION max_lines);
boolean shjpeg_finish_decompress(j_decompress_ptr cinfo);

/*Common functions
  -----------------
  These functions can be legally called from either mode.*/
void shjpeg_destroy(j_common_ptr cinfo);
void shjpeg_abort(j_common_ptr cinfo);

struct jpeg_error_mgr *shjpeg_std_error(struct jpeg_error_mgr * err);
void shjpeg_CreateCompress(j_compress_ptr cinfo, int version, size_t structsize);
void shjpeg_CreateDecompress(j_decompress_ptr cinfo, int version, 
		 		size_t structsize);
