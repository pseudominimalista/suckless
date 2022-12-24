/*  This file is part of smatrix.                                           */
/*                                                                          */
/*  Smatrix is free software: you can redistribute it and/or modify it      */
/*  under the terms of the GNU General Public License as published by       */
/*  the Free Software Foundation, either version 2 of the License, or       */
/*  (at your option) any later version.                                     */
/*                                                                          */
/*  Smatrix is distributed in the hope that it will be useful, but WITHOUT  */
/*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY      */
/*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public         */
/*  License for more details.                                               */
/*                                                                          */
/*  You should have received a copy of the GNU General Public License       */
/*  along with smatrix. If not, see <https://www.gnu.org/licenses/>.        */

#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct
settings
{
						/*		VOLATILE settings:							*/
	int *WIDTH;			/*	Width of terminal window						*/
	int *HEIGHT;		/*	Height of terminal Window						*/

						/*		Drop settings:								*/
	int VELOCITY_MAX;  	/*	Speed of the fastest drops. "speed" actually	*/
						/*	means the number of frames that need to pass	*/
						/*  before reprinting. Lower value means faster		*/
						/*	movement.										*/
	int VELOCITY_MIN;  	/*	Speed of the slowest drops						*/
	int LENGTH_MAX;	   	/*	Length of the longest drops						*/
	int LENGTH_MIN;	   	/*	Length of the shortest drops					*/
	int SPAWN_MIN;	   	/*	Minimum spawns per cycle						*/
	int SPAWN_MAX;	   	/*	Maximum spawns per cycle						*/

						/*		Character-set Settings:						*/
	int KATAKANA;		/*	Include Japanese Katakana characters			*/
	int HIRAGANA;		/*	Include Japanese Kiragana characters			*/
	int KANJI;			/*	Include Japanese Kanji							*/
	int ROMAN;			/*	Include Roman Characters (English)				*/
	int CYRILLIC;		/*	Include Cyrillic Characters (Russian)			*/
	int NUMERIC;		/*	Include numbers 0-9								*/
	int SYMBOLS;		/*	Include special symbols like '!' and  '&'		*/
	int EN_SCHIZO;		/*	Include embedded English words					*/	

						/*		Font settings:								*/
	int BOLD;			/*	Make leading characters bold					*/
	int FPS;			/*	Frames per Second cap							*/
	int COLOR;			/*	If set, overrides default color of terminal		*/

						/*		Development/Debugging settings				*/
	int PRINT;			/*	Print matrix (on by default)					*/
	int DEBUG;			/*	Print out debugging messages. Only useful if	*/
						/*	PRINT is set to 0								*/
	int HIDE_CURSOR;	/*	Print characters to hide, then reveal, the		*/
						/*	cursor. On by default.							*/
}
settings;

#endif
