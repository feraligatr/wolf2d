

#ifndef __WOLF_MENU_H__
#define __WOLF_MENU_H__

#include "../../../common/arch.h"
#include "../../../common/common_utils.h"
#include "../../../video/video.h"

#include "../../../client/menu_conf.h"


extern colour3_t bgcolour;
extern colour3_t bord2colour;
extern colour3_t deactive;
extern colour3_t bkgdcolour;

extern colour3_t readcolour;
extern colour3_t readhcolour;
extern colour3_t textcolour;
extern colour3_t highlight;


extern colour3_t bannerline;

extern colour3_t interbkgnd;


extern colour3_t sodbgcolour;

extern colour3_t sodbord2colour;
extern colour3_t soddeactive;
extern colour3_t sodbkgdcolour;


extern const char *menu_in_sound;
extern const char *menu_move_sound;
extern const char *menu_out_sound;

extern void M_PopMenu( void );
extern void M_ForceMenuOff( void );
extern void M_PushMenu( void (*draw) (void), const char *(*key) (int k) );

#define NUM_CURSOR_FRAMES 2
extern void M_DrawCursor( int x, int y, int f );
extern void M_BannerString( const char *string, W16 nYOffset );
extern void M_Banner( const char *name, W16 nYOffest );
extern void M_DrawWindow( int x, int y, int w, int h, colour3_t bg, 
							colour3_t act, colour3_t deact );
extern void M_DrawInfoBar( void );

extern const char *Default_MenuKey( menuframework_s *m, int key );


#endif /* __WOLF_MENU_H__ */
