#ifndef _VIDEO_H
#define _VIDEO_H

#include "vice.h"

#include "palette.h"

#define CANVAS_USES_TRIPLE_BUFFERING(c) 0

typedef struct _frame_buffer {
    int   width;
    int   height;
    BYTE *bitmap;
    ULONG ulBuffer; // DIVE buffer number
} *frame_buffer_t;

#define FRAME_BUFFER_SIZE(f)         (f->width)
#define FRAME_BUFFER_LINE_START(f,n) (((f->bitmap)+(f->width)*n*sizeof(BYTE)))
#define FRAME_BUFFER_START(f)        (f->bitmap)

typedef void (*canvas_redraw_t)(UINT width, UINT height);

typedef struct _canvas {
    HWND  hwndFrame;        // Handle to Frame of Window
    HWND  hwndClient;       // Handle to Paint Area of Window
    UINT  width;            // width of canvas graphic area
    UINT  height;           // width of canvas graphic area
    RGB2 *palette;          // pointer to structure which stores colorinfo
    BOOL  init_ready;       // dont't use exposure_handler to early
    BOOL  vrenabled;        // only BlitImage when Visible Region Enabled
    canvas_redraw_t exposure_handler;
} *canvas_t;

/* ------------------------------------------------------------------------ */

extern void video_free(void);

extern int video_init_resources(void);
extern int video_init_cmdline_options(void);
extern int video_init(void);

extern int  frame_buffer_alloc(frame_buffer_t *f, UINT width, UINT height);
extern void frame_buffer_free (frame_buffer_t *f);
extern void frame_buffer_clear(frame_buffer_t *f, BYTE value);

extern canvas_t canvas_create(const char *win_name, UINT *width, UINT *height,
                              int mapped, canvas_redraw_t exposure_handler,
                              const palette_t *palette, PIXEL *pixel_return);
extern void canvas_map        (canvas_t c);
extern void canvas_unmap      (canvas_t c);
extern void canvas_resize     (canvas_t c, UINT width, UINT height);
extern int  canvas_set_palette(canvas_t c, const palette_t *p,
                               PIXEL *pixel_return);

extern void canvas_refresh    (canvas_t c, frame_buffer_t f,
                               int xs, int ys, int xi, int yi, int w, int h);

void wmCreate();
void wmDestroy();


#endif
