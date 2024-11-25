ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_DISPLAY_MODE   disp_data;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;



bool redraw = true;


if(!al_init()) {
	fprintf(stderr, "failed to initialize allegro!\n");
	return -1;
}

   int i;
   ALLEGRO_SAMPLE **sample_data;
   ALLEGRO_SAMPLE_INSTANCE **sample;
   ALLEGRO_MIXER *mixer;
   ALLEGRO_VOICE *voice;
   float longest_sample;
   
   char const **filenames;   
   filenames = malloc(sizeof *filenames * 3);
   
   al_init_acodec_addon();

   if (!al_install_audio()) {
       fprintf(stderr, "Could not init sound!\n");
       return 1;
   }

   sample = malloc(argc * sizeof(*sample));
   if (!sample)
      return 1;

   sample_data = malloc(argc * sizeof(*sample_data));
   if (!sample_data)
      return 1;

   /* a voice is used for playback */
   voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,
      ALLEGRO_CHANNEL_CONF_2);
   if (!voice) {
      fprintf(stderr, "Could not create ALLEGRO_VOICE from sample\n");
      return 1;
   }

   mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,
      ALLEGRO_CHANNEL_CONF_2);
   if (!mixer) {
      fprintf(stderr, "al_create_mixer failed.\n");
      return 1;
   }

   if (!al_attach_mixer_to_voice(mixer, voice)) {
      fprintf(stderr, "al_attach_mixer_to_voice failed.\n");
      return 1;
   }

	filenames[0]="click.wav";
	filenames[1]="correct.wav";
	filenames[2]="incorrect.wav";

   for (i = 0; i < 3; ++i) {
      const char *filename = filenames[i];

      sample[i] = NULL;

      /* loads the entire sound file from disk into sample data */
      sample_data[i] = al_load_sample(filename);
      if (!sample_data[i]) {
         fprintf(stderr, "Could not load sample from '%s'!\n", filename);
         continue;
      }

      sample[i] = al_create_sample_instance(sample_data[i]);
      if (!sample[i]) {
         fprintf(stderr, "Could not create sample!\n");
	 al_destroy_sample(sample_data[i]);
	 sample_data[i] = NULL;
	 continue;
      }

      if (!al_attach_sample_instance_to_mixer(sample[i], mixer)) {
         fprintf(stderr, "al_attach_sample_instance_to_mixer failed.\n");
         continue;
      }
   }

   longest_sample = 0;



if(!al_install_mouse()) {
	fprintf(stderr, "failed to initialize the mouse!\n");
	return -1;
}

if(!al_install_keyboard()) {
	fprintf(stderr, "failed to initialize the keyboard!\n");
	return -1;
}

al_init_font_addon();

if (!al_init_ttf_addon()) {
	fprintf(stderr, "failed to initialize the ttf (True Type Font) addon!\n");
}

if(!al_init_image_addon()) {
	fprintf(stderr, "failed to initialize allegro_image!\n");
	return -1;
}

if(!al_init_primitives_addon()) {
	fprintf(stderr, "failed to initialize allegro_primitives!\n");
	return -1;
}

timer = al_create_timer(1.0 / FPS);
if(!timer) {
	fprintf(stderr, "failed to create timer!\n");
	return -1;
}

al_init_font_addon(); // initialize the font addon
al_init_ttf_addon();// initialize the ttf (True Type Font) addon

al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
display = al_create_display(disp_data.width, disp_data.height);
if(!display) {
	fprintf(stderr, "failed to create display!\n");
	al_destroy_timer(timer);
	return -1;
}
float mouse_x = disp_data.width / 2.0;
float mouse_y = disp_data.height / 2.0;
mouse_cursor_x = mouse_x;
mouse_cursor_y = mouse_y;
al_hide_mouse_cursor(display);
display_width=al_get_display_width(display);
display_height=al_get_display_height(display);

event_queue = al_create_event_queue();
if(!event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
}
al_register_event_source(event_queue, al_get_display_event_source(display));

al_register_event_source(event_queue, al_get_timer_event_source(timer));

al_register_event_source(event_queue, al_get_mouse_event_source());

al_register_event_source(event_queue, al_get_keyboard_event_source());

ALLEGRO_FONT *font = al_load_ttf_font("Go-Mono.ttf",24,0 );

if (!font) {
	fprintf(stderr, "Could not load 'Go-Mono.ttf'.\n");
	return -1;
}

al_clear_to_color(al_map_rgb(0,0,0));

al_flip_display();

al_start_timer(timer);
