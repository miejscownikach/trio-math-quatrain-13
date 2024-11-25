# making education less bad, if possible (starting with math) -- no promises

# no idea if liballegro will make this work dynamically linked on a fresh install, your mileage may vary, as may your cubic metres and mililitres of aluminium.
# tested on xubuntu, try apt search liballegro, designed for allegro 5.2.
# _this line left blank intentionally_
sudo apt install -y liballegro5.2 liballegro5-dev build-essential astyle

gcc main.c -o main -I/usr/include/allegro5 -L/usr/lib -lm -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf

astyle --indent=tab main.c init.h keyboard.h util.h
