/*
 *  wolfiphone.h
 *  wolf3d
 *
 *  Created by John Carmack on 3/13/09.
 *  Copyright 2009 idSoftware. All rights reserved.
 *
 */

#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <setjmp.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "iphone/gles_glue.h"

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/oalStaticBufferExtension.h>
#undef ALCAPI
#define ALCAPI

#include "iphone/iphone_wolf.h"

#include "iphone_alerts.h"

