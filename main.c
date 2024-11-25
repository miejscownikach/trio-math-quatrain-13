//main.c
//sudo apt install -y liballegro5-dev build-essential astyle
//gcc main.c -o main -I/usr/include/allegro5 -L/usr/lib -lm -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf && astyle --indent=tab main.c
//astyle --indent=tab main.c init.h keyboard.h util.h
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define load_level "chapter1.csv"
#define file_bytes 1234567

char infile[file_bytes];
char input_chars[18];
int s[256][256][48];
int ints[256][256];
int unrolled[256][65536];
int counter_row=0;
int counter_column=0;

int difference=0;

int counter=0;

int inc=1;
int dec=2;
int add=3;
int neg=4;
int mul=5;

int increment=1;
int decrement=2;
int negate=4;
int multiply=5;

const float FPS = 60;
int is_paused=1;
int display_width=0;
int display_height=0;
float mouse_cursor_x=0.0;
float mouse_cursor_y=0.0;
bool key[118] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

enum MYKEYS {
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_PAD_0, KEY_PAD_1, KEY_PAD_2, KEY_PAD_3, KEY_PAD_4, KEY_PAD_5, KEY_PAD_6, KEY_PAD_7, KEY_PAD_8, KEY_PAD_9, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_ESCAPE, KEY_TILDE, KEY_MINUS, KEY_EQUALS, KEY_BACKSPACE, KEY_TAB, KEY_OPENBRACE, KEY_CLOSEBRACE, KEY_ENTER, KEY_SEMICOLON, KEY_QUOTE, KEY_BACKSLASH, KEY_BACKSLASH2, KEY_COMMA, KEY_FULLSTOP, KEY_SLASH, KEY_SPACE, KEY_INSERT, KEY_DELETE, KEY_HOME, KEY_END, KEY_PGUP, KEY_PGDN, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_PAD_SLASH, KEY_PAD_ASTERISK, KEY_PAD_MINUS, KEY_PAD_PLUS, KEY_PAD_DELETE, KEY_PAD_ENTER, KEY_PRINTSCREEN, KEY_PAUSE, KEY_ABNT_C1, KEY_YEN, KEY_KANA, KEY_CONVERT, KEY_NOCONVERT, KEY_AT, KEY_CIRCUMFLEX, KEY_COLON2, KEY_KANJI, KEY_LSHIFT, KEY_RSHIFT, KEY_LCTRL, KEY_RCTRL, KEY_ALT, KEY_ALTGR, KEY_LWIN, KEY_RWIN, KEY_MENU, KEY_SCROLLLOCK, KEY_NUMLOCK, KEY_CAPSLOCK, KEY_PAD_EQUALS, KEY_BACKQUOTE, KEY_SEMICOLON2, KEY_COMMAND
};

bool doexit = false;

const int HOW_MANY_PARTICLES=1000;
float particles[15][1000000];
int x=0;
int y=1;
int z=2;
int xr=9;
int yr=10;
int zr=11;
int xt=12;
int yt=13;
int zt=14;
int x_speed=3;
int y_speed=4;
int z_speed=5;
int r=6;
int g=7;
int b=8;
int bearing=3;
int pitch=4;
int yaw=5;
double camera[6]= {0,0,0,0,0,0};
int up=0;
int forward=1;
int right=2;
double unitvectors[3][3]= {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

int number=0;
int input1=0;
int input2=0;
int output[5]={0,0,0,0,0};
int question_index=0;

int click_=0;
int correct_=1;
int incorrect_=2;

#include "mersenne_t.h"
#include "util_allegro.h"
#include "util.h"

int ev_key_up(int which_key) {
	if (which_key == ALLEGRO_KEY_ESCAPE) //doexit=true;
		return 0;
}

int ev_key_down(int which_key) {
	if (which_key == ALLEGRO_KEY_ESCAPE) is_paused=(is_paused+1)%2;
	if (which_key == ALLEGRO_KEY_C) {
		if (key[KEY_LCTRL]) doexit=true;
	}
	return 0;
}


int main(int argc, char **argv) {


	init_();
	
	


if(0){
	for (int i = 1; i < HOW_MANY_PARTICLES; i++)
	{
		particles[x][i]=0.0;
		particles[y][i]=10.0;
		particles[z][i]=0.0;
		particles[x][i]=random_float(-100.0,100.0);
		particles[y][i]=random_float(-100.0,100.0);
		particles[z][i]=random_float(-100.0,100.0);
		particles[x_speed][i]=0.0;
		particles[y_speed][i]=0.0;
		particles[z_speed][i]=0.0;
		particles[r][i]=0.0;
		particles[g][i]=0.0;
		particles[b][i]=0.0;
		particles[r][i]=random_float(0.0,1.0);
		particles[g][i]=random_float(0.0,1.0);
		particles[b][i]=random_float(0.0,1.0);
	}
}

#include "init.h"
	int lesser_display_dimension=display_height;
	if (display_height>display_width) lesser_display_dimension=display_width;

	int which_answer=0;

	while(!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(1) {
				for (int i = 1; i < HOW_MANY_PARTICLES; i++)
				{
					particles[x][i]+=particles[x_speed][i]*0.1;
					particles[y][i]+=particles[y_speed][i]*0.1;
					particles[z][i]+=particles[z_speed][i]*0.1;
					particles[z_speed][i]-=0.1*0.1;
				}
				for (int i = counter; i <= counter; i++)
				{
					particles[x][i]=0.0;
					particles[y][i]=10.0;
					particles[z][i]=0.0;
					float heading  =random_float(0.0,4.0*3.141596);
					float magnitude=random_float(0.0,0.2*3.141596);
					particles[x_speed][i]=sin(heading)*magnitude;
					particles[y_speed][i]=cos(heading)*magnitude;
					int min=-10.0;
					int max=10.0;
					particles[z_speed][i]=random_float(0.1,1.0);
					particles[r][i]=random_float(0.0,1.0);
					particles[g][i]=random_float(0.0,1.0);
					particles[b][i]=random_float(0.0,1.0);
				}
			}

			//right is x+, up is z+, forward is y+
			unitvectors[forward][x]=sin(2.0*3.141596*camera[bearing]/360.0)*cos(2.0*3.141596*camera[pitch]/360.0);
			unitvectors[forward][y]=cos(2.0*3.141596*camera[bearing]/360.0)*cos(2.0*3.141596*camera[pitch]/360.0);
			unitvectors[forward][z]=sin(2.0*3.141596*camera[pitch]/360.0);
			unitvectors[up][x]=sin(2.0*3.141596*camera[bearing]/360.0)*( 0.0-sin(2.0*3.141596*camera[pitch]/360.0) );
			unitvectors[up][y]=cos(2.0*3.141596*camera[bearing]/360.0)*( 0.0-sin(2.0*3.141596*camera[pitch]/360.0) );
			unitvectors[up][z]=cos(2.0*3.141596*camera[pitch]/360.0);
			unitvectors[right][x]=cos(2.0*3.141596*camera[bearing]/360.0);
			unitvectors[right][y]=0.0-sin(2.0*3.141596*camera[bearing]/360.0);
			unitvectors[right][z]=0.0;
			float speed=1.1;
			int diagonal=-1;
			if (key[KEY_S]) {
				camera[x]-=unitvectors[forward][x]*speed;
				camera[y]-=unitvectors[forward][y]*speed;
				camera[z]-=unitvectors[forward][z]*speed;
				diagonal++;
			}
			if (key[KEY_W]) {
				camera[x]+=unitvectors[forward][x]*speed;
				camera[y]+=unitvectors[forward][y]*speed;
				camera[z]+=unitvectors[forward][z]*speed;
				diagonal++;
			}
			if (key[KEY_D]) {
				camera[x]+=unitvectors[right][x]*speed;
				camera[y]+=unitvectors[right][y]*speed;
				camera[z]+=unitvectors[right][z]*speed;
				diagonal++;
			}
			if (key[KEY_A]) {
				camera[x]-=unitvectors[right][x]*speed;
				camera[y]-=unitvectors[right][y]*speed;
				camera[z]-=unitvectors[right][z]*speed;
				diagonal++;
			}
			if (diagonal%2) speed*=pow(2.0,0.5);
			for (int i=0; i<HOW_MANY_PARTICLES; i++) {
				particles[xt][i]=particles[x][i]-camera[x];
				particles[yt][i]=particles[y][i]-camera[y];
				particles[zt][i]=particles[z][i]-camera[z];
				particles[xr][i]=
				    unitvectors[right][x]*particles[xt][i]+
				    unitvectors[right][y]*particles[yt][i]+
				    unitvectors[right][z]*particles[zt][i];
				particles[yr][i]=
				    unitvectors[forward][x]*particles[xt][i]+
				    unitvectors[forward][y]*particles[yt][i]+
				    unitvectors[forward][z]*particles[zt][i];
				particles[zr][i]=
				    unitvectors[up][x]*particles[xt][i]+
				    unitvectors[up][y]*particles[yt][i]+
				    unitvectors[up][z]*particles[zt][i];
			}
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit=true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
		        ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			camera[bearing]+=ev.mouse.dx * (is_paused+1)%2;
			if (camera[bearing]>360.0)camera[bearing]-=360.0;
			if (camera[bearing]< -0.0)camera[bearing]+=360.0;
			camera[pitch]+=ev.mouse.dy * (is_paused+1)%2;
			if (camera[pitch]>90.0)camera[pitch]=90.0;
			if (camera[pitch]< -90.0)camera[pitch]=-90.0;

			mouse_x += ev.mouse.dx * (is_paused+1)%2;
			mouse_y += ev.mouse.dy * (is_paused+1)%2;
			mouse_cursor_x += ev.mouse.dx*is_paused;
			mouse_cursor_y += ev.mouse.dy*is_paused;
			if (mouse_cursor_x < 0.0) mouse_cursor_x = 0.0;
			if (mouse_cursor_y < 0.0) mouse_cursor_y = 0.0;
			if (mouse_cursor_x > display_width) mouse_cursor_x = display_width;
			if (mouse_cursor_y > display_height) mouse_cursor_y = display_height;
			al_set_mouse_xy(display, display_width/2, display_height/2);
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//doexit=true;
			/*
			if (mouse_cursor_x>display_width*.3&&mouse_cursor_x<display_width*.7
			        &&mouse_cursor_y>display_height*.9&&mouse_cursor_y<display_height*.95) {
				number++;
			}
			*/
			      /* Play sample in looping mode. */
			output[0]=unrolled[10][question_index];
			output[1]=unrolled[11][question_index];
			output[2]=unrolled[12][question_index];
			output[3]=unrolled[13][question_index];
			output[4]=unrolled[14][question_index];
			      int correct=unrolled[16][question_index];
			      //draw_digits(display_width*5.0/6.0, display_height*.8, display_width*0.9/12.0, output[4]);

			      int flag=0;
			      for (int i=1;i<6;i++){
					float diffr=(display_width*0.9/12.0)*(display_width*0.9/12.0);
			      float diffx=(mouse_cursor_x-display_width*i/6.0)*(mouse_cursor_x-display_width*i/6.0);
			      float diffy=(mouse_cursor_y-display_height*.8)*(mouse_cursor_y-display_height*.8);
			      if (diffx+diffx<diffr && output[i-1]==correct) flag=1;
			      if (diffx+diffx<diffr && output[i-1]!=correct) flag=2;
			      if (diffx+diffx<diffr) {which_answer=i;question_index++; question_index%=counter_row+difference;}
			  }
			  al_play_sample_instance(sample[click_]);
			      if (flag==1) al_play_sample_instance(sample[correct_]);
			      if (flag==2) al_play_sample_instance(sample[incorrect_]);
			
			
			if (mouse_cursor_x>display_width*.98&&mouse_cursor_x<display_width*.99
			        &&mouse_cursor_y>display_width*.01&&mouse_cursor_y<display_width*.02) doexit=1;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			//doexit=true;
		}

#include "keyboard.h"

		if(redraw && al_is_event_queue_empty(event_queue)) {
			input1=unrolled[1][question_index];
			input2=unrolled[3][question_index];
			output[0]=unrolled[10][question_index];
			output[1]=unrolled[11][question_index];
			output[2]=unrolled[12][question_index];
			output[3]=unrolled[13][question_index];
			output[4]=unrolled[14][question_index];
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			if(1) {
				for (int i=0; i<HOW_MANY_PARTICLES; i++) {
					if (particles[yr][i]>0.1) {
						al_draw_filled_circle(
						    display_width/2+(200.0*particles[xr][i]/particles[yr][i]),
						    display_height/2-(200.0*particles[zr][i]/particles[yr][i]),
						    2.0, al_map_rgb(rgb(particles[r][i]),rgb(particles[g][i]),rgb(particles[b][i])) );
					}
				}
			}
			if(is_paused)
			al_draw_rectangle(display_width*.98, 2.0*display_width*.01, display_width*.99, display_width*.01, al_map_rgb(255,255,255), 2);
				//al_draw_rectangle(display_width*.3, display_height*.9, display_width*.7, display_height*.95, al_map_rgb(255,255,255), 2);
			draw_digits(display_width*1.0/6.0, display_height*.3, display_width*0.9/6.0, input1);
			draw_digits(display_width*5.0/6.0, display_height*.3, display_width*0.9/6.0, input2);
			draw_function_icon(unrolled[0][question_index],display_width*3.0/6.0,display_height*.3,display_height*0.9/6.0);
			draw_digits(display_width*1.0/6.0, display_height*.8, display_width*0.9/12.0, output[0]);
			draw_digits(display_width*2.0/6.0, display_height*.8, display_width*0.9/12.0, output[1]);
			draw_digits(display_width*3.0/6.0, display_height*.8, display_width*0.9/12.0, output[2]);
			draw_digits(display_width*4.0/6.0, display_height*.8, display_width*0.9/12.0, output[3]);
			draw_digits(display_width*5.0/6.0, display_height*.8, display_width*0.9/12.0, output[4]);
			al_draw_circle(display_width*3.0/6.0,display_height*.8,display_width*0.9/12.0,al_map_rgb(255,127,127),2.0);
			//al_draw_circle(display_width*which_answer/6.0,display_height*.8,display_width*0.9/12.0,al_map_rgb(255,127,127),2.0);
			//draw_function_icon(inc,display_width*1.0/6.0,display_height*0.8,display_height*0.1);
			//draw_function_icon(dec,display_width*2.0/6.0,display_height*0.8,display_height*0.1);
			//draw_function_icon(add,display_width*3.0/6.0,display_height*0.8,display_height*0.1);
			//draw_function_icon(neg,display_width*4.0/6.0,display_height*0.8,display_height*0.1);
			//draw_function_icon(mul,display_width*5.0/6.0,display_height*0.8,display_height*0.1);
			//al_draw_text(font, al_map_rgb(255,255,255), display_width*1.0/6.0, display_height*.3 - display_width*0.9/6.0,
			//ALLEGRO_ALIGN_CENTRE, "A");
			//al_draw_text(font, al_map_rgb(255,255,255), display_width*3.0/6.0, display_height*.3 - display_width*0.9/6.0,
			//ALLEGRO_ALIGN_CENTRE, "B");
			//al_draw_text(font, al_map_rgb(255,255,255), display_width*5.0/6.0, display_height*.3 - display_width*0.9/6.0,
			//ALLEGRO_ALIGN_CENTRE, "G");
			if(0){
			for (int i=question_index; i<=question_index; i++) {
				char str[256];
				sprintf(str,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,",
				        unrolled[0][i],unrolled[1][i],unrolled[2][i],unrolled[3][i],unrolled[4][i],unrolled[5][i],unrolled[6][i],unrolled[7][i],unrolled[8][i],unrolled[10][i],unrolled[11][i],unrolled[12][i],unrolled[13][i],unrolled[14][i]);
				al_draw_text(font, al_map_rgb(255,255,255), display_width/2, i*display_height/53.0,ALLEGRO_ALIGN_CENTRE, str);
			}
		}
			//char str[48];
			//sprintf(str,"%f %f",unitvectors[forward][x],unitvectors[forward][y]);
			//al_draw_text(font, al_map_rgb(255,255,255), display_width/2, display_height/10,ALLEGRO_ALIGN_CENTRE, str);
			if(is_paused)al_draw_filled_circle(
				    mouse_cursor_x,
				    mouse_cursor_y,
				    5.0, al_map_rgb(255,255,255) );
			al_flip_display();
		}
		counter++;
		if (counter >= HOW_MANY_PARTICLES) counter = 0;
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
   for (i = 0; i < 3; ++i) {
      /* free the memory allocated when creating the sample + voice */
      if (sample[i]) {
         al_stop_sample_instance(sample[i]);
         al_destroy_sample_instance(sample[i]);
	 al_destroy_sample(sample_data[i]);
      }
   }
   al_destroy_mixer(mixer);
   al_destroy_voice(voice);

   free(sample);
   free(sample_data);

   al_uninstall_audio();

   	return 0;
}
