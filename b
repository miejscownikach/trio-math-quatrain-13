rm -f main
gcc main.c -o main -I/usr/include/allegro5 -L/usr/lib -lm -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf
#astyle --indent=tab main.c
./main
