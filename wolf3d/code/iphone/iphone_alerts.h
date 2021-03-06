/*
 *  iphone_alerts.h
 *  wolf3d
 *
 *  Created by Greg Hodges on 7/14/09.
 *  Copyright 2009 id software. All rights reserved.
 *
 *  C wrappers for the UIAlertView.
 *
 */
/*
 
 Copyright (C) 2009 Id Software, Inc.
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 
 */


#ifndef __IPHONE_ALERTS__
#define __IPHONE_ALERTS__

void iphoneMessageBox(char *title, char *message);
void iphoneKillMessageBox();
void iphoneYesNoBox(char *title, char *message);

#endif