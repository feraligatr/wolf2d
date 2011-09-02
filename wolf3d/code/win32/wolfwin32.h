
#include <windows.h>

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <setjmp.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <io.h>

#include <al.h>
#include <alc.h>
#include <GL/gl.h>

#include "glext.h"

#define pfglClearColor glClearColor
#define pfglCullFace glCullFace
#define pfglColor3f glColor3f
#define pfglColor4f glColor4f
#define pfglEnable glEnable
#define pfglDisable glDisable
#define pfglShadeModel glShadeModel
#define pfglBlendFunc glBlendFunc
#define pfglColor4ubv glColor4ubv
#define pfglBegin glBegin
#define pfglVertex2i glVertex2i
#define pfglEnd glEnd
#define pfglTexCoord2f glTexCoord2f
#define pfglVertex3f glVertex3f
#define pfglDepthMask glDepthMask
#define pfglColor3ubv glColor3ubv
#define pfglLineWidth glLineWidth
#define pfglGenTextures glGenTextures
#define pfglBindTexture glBindTexture
#define pfglTexImage2D glTexImage2D
#define pfglTexParameteri glTexParameteri
#define pfglTexParameterf glTexParameterf
#define pfglFrustum glFrustum
#define pfglReadPixels glReadPixels
#define pfglGetString glGetString
#define pfglGetIntegerv glGetIntegerv
#define pfglGetError glGetError
#define pfglDeleteTextures glDeleteTextures
#define pfglTexEnvi glTexEnvi
#define FULL_BRIGHT pfglColor3f( 1, 1, 1 )

extern void pfglCompressedTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLsizei size, const GLvoid *pixels);
extern void (*pfglActiveTextureARB)(GLenum texture);
extern void (*pfglClientActiveTextureARB)(GLenum texture);
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0

//#include "iphone/gles_glue.h"

typedef BOOL bool;
