#  This file is part of smatrix.                                           
#                                                                          
#  Smatrix is free software: you can redistribute it and/or modify it      
#  under the terms of the GNU General Public License as published by       
#  the Free Software Foundation, either version 2 of the License, or       
#  (at your option) any later version.                                     
#                                                                          
#  Smatrix is distributed in the hope that it will be useful, but WITHOUT  
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY      
#  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public         
#  License for more details.                                               
#                                                                          
#  You should have received a copy of the GNU General Public License       
#  along with smatrix. If not, see <https://www.gnu.org/licenses/>.        

include=glib-2.0
cflags=`pkgconf --cflags $(include)`
libs=`pkgconf --libs $(include)`

smatrix :													\
			drop.h											\
			matrix.h 										\
			row.h 											\
			settings.h										\
			slist.h											\
															\
			main.c main.h 									\
															\
			advance.c advance.h								\
			char_new_random.c char_new_random.h				\
			check_size.c check_size.h						\
			draw.c draw.h									\
			drop_new_random.c drop_new_random.h				\
			drop_print.c drop_print.h						\
			event_handler.c event_handler.h					\
			frame_buffer_update.c frame_buffer_update.h		\
			length_new_random.c length_new_random.h			\
			matrix_new.c matrix_new.h						\
			position_new_random.c position_new_random.h		\
			settings_parse_args.c settings_parse_args.h		\
			slist_new.c slist_new.h							\
			spawn.c spawn.h									\
			velocity_new_random.c velocity_new_random.h		\
	
	gcc  -Wall main.c -o smatrix

clean :
	rm smatrix

run : smatrix
	./smatrix
