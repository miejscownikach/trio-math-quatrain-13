
int draw_function_icon(int function_name, float x, float y, float r) {
	float adjacent = cos(M_PI*2.0*30/360.0);
	if (function_name==inc) {
		al_draw_triangle(x-adjacent*r,y+0.5*r,x,y-r,x+adjacent*r,y+0.5*r,al_map_rgb(255,255,255),2);
		al_draw_filled_rectangle(x-r,y+0.6*r,x+r,y+0.5*r,al_map_rgb(127,127,127));
	}
	if (function_name==dec) {
		al_draw_triangle(x-adjacent*r,y-r,x,y+r*0.5,x+adjacent*r,y-r,al_map_rgb(255,255,255),2);
		al_draw_filled_rectangle(x-r,y+0.6*r,x+r,y+0.5*r,al_map_rgb(127,127,127));
	}
	if (function_name==add) {
		al_draw_rectangle(x-r*0.9,y-r,x-r*0.05,y+0.5*r,al_map_rgb(255,255,255),2);
		al_draw_rectangle(x+r*0.9,y-r,x+r*0.05,y+0.5*r,al_map_rgb(255,255,255),2);
		al_draw_filled_rectangle(x-r,y+0.6*r,x+r,y+0.5*r,al_map_rgb(127,127,127));
	}
	if (function_name==neg) {
		al_draw_circle(x,y-r*0.25,r*0.75,al_map_rgb(255,255,255),2);
		al_draw_filled_rectangle(x-r,y+0.6*r,x+r,y+0.5*r,al_map_rgb(127,127,127));
	}
	if (function_name==mul) {
		al_draw_rectangle(x-r*0.8,y-1.0*r,x-r*0.05,y-0.3*r,al_map_rgb(255,255,255),2);
		al_draw_rectangle(x-r*0.8,y-0.2*r,x-r*0.05,y+0.5*r,al_map_rgb(255,255,255),2);
		al_draw_rectangle(x+r*0.05,y-1.0*r,x+r*0.8,y-0.3*r,al_map_rgb(255,255,255),2);
		al_draw_rectangle(x+r*0.05,y-0.2*r,x+r*0.8,y+0.5*r,al_map_rgb(255,255,255),2);
		al_draw_filled_rectangle(x-r,y+0.6*r,x+r,y+0.5*r,al_map_rgb(127,127,127));
	}
}

int draw_counter(float x, float y, float r, int sign, int place, int number) {
	float r2=r*0.7/6.0;
	float tens=1.0;
	if (place==1) tens=0.4;
	int color=0;
	if (sign==-1) color=255;
	if (sign>0) {
		al_draw_filled_rectangle(x-r2*tens, y-r2, x+r2*tens, y+r2,
		                         al_map_rgb(255,255,255) );
	}
	if (sign<0) {
		//al_draw_filled_rectangle(x-r2*tens, y-r2, x+r2*tens, y+r2, al_map_rgb(255,0,0));
		al_draw_rectangle(x-r2*tens, y-r2, x+r2*tens, y+r2, al_map_rgb(255,255,255), 2);
	}
	if (place==1) {
		al_draw_line(x, y-r2, x, y+r2, al_map_rgb(color,color,color), 2);
		for (int i = 1; i <= 4; i++)
			al_draw_line(x-r2*tens, y-r2+r2*2.0*i/5, x+r2*tens, y-r2+r2*2.0*i/5, al_map_rgb(color,color,color), 2);
	}
}

int draw_digit(float x, float y, float r, int number, int sign, int place) {
	int counter = 0;
	if (number < 0) number*=-1;
	for (int iy = 0; iy < 3; iy++) {
		for (int ix = 0; ix < 3; ix++) {
			if (counter < number) draw_counter( x - r * 0.25 + ix * r * 0.25, y - r * 0.25 + iy * r * 0.25, r, sign, place, number);
			counter++;
		}
	}
}

int draw_digits(float x, float y, float r, int number) {
	int sign = 1;
	if (number < 0) sign = -1;
	al_draw_circle(x, y, r, al_map_rgb(255,255,255), 2);
	draw_digit(x - r * 0.9 / 2, y, r, (number%100-number%10)/10, sign, 1 );
	draw_digit(x + r * 0.9 / 2, y, r, number%10, sign, 0 );
}

