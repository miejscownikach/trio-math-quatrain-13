//sudo apt install -y liballegro5-dev build-essential astyle
//gcc main.c -o main -I/usr/include/allegro5 -L/usr/lib -lm -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf
//astyle --indent=tab main.c

//regex
//\nALLEGRO_([^\n]*)\n
//case ALLEGRO_\1:\nkey[\1]=false;\nbreak;\n\n

float random_float(float low, float high)
{
	float n=genrand_real1()*(high-low)+low;
	if (n<low) n=low;
	if (n>high) n=high;
	return n;
}

int random_int(int low, int high)
{
	int n=(int)(genrand_real1()*(1.0+high-low)+low-0.5);
	if (n<low) n=low;
	if (n>high) n=high;
	return n;
}

float rgb(float input)
{
	float output=input*255.0;
	if (output > 255.0) output=255.0;
	if (output < 0.0) output=0.0;
	return output;
}

int init_(void)
{
	for (int i=0; i<256; i++) {
		for (int j=0; j<256; j++) {
			ints[i][j]=0;
		}
	}
	char c;
	FILE *fp1;
	fp1 = fopen(load_level, "r");

	for (int i = 0; i < file_bytes; i++) infile[i] = 0;
	while (1) {
		c = fgetc(fp1);
		if (c == EOF)
			break;
		else

			infile[counter] = c;
		//printf("%c",c);

		counter++;
	}
	fclose(fp1);
	counter_column=0;
	counter_row=0;
	int char_counter=0;
	if(1) {
		for (int i = 0; i < counter; i++) {
			s[counter_column][counter_row][char_counter]=0;
			if ((infile[i] > 47 && infile[i] < 58)||infile[i] == '-') {
				s[counter_column][counter_row][char_counter]=infile[i];
				s[counter_column][counter_row][++char_counter]=0;
				//char_counter++;
			}
			if (infile[i] == ',') {
				counter_column++;
				char_counter=0;
			}
			if (infile[i] == 0x0a) {
				counter_row++;
				counter_column=0;
				char_counter=0;
			}
		}
	}
    if(1) {
        for (int i = 0; i<counter_row; i++) {
            for (int j=0; j<9; j++) {
                char ch[48];
                for (int k=0; k<48; k++)ch[k]=0;
                for (int k=0; s[j][i][k]!=0; k++) {
                    ch[k]=s[j][i][k];
                    ch[k+1]=0;
                }
                ints[j][i]=strtol(ch,NULL,10);
                //printf("%i,",ints[j][i]);
            }
            //printf(",,%i\n",i);
        }
    }
	//printf("%i\n",counter_row);
	if(1) {
		for (int iterator = 0; iterator<=counter_row; iterator++) {
			if (ints[2][iterator]==0&&ints[4][iterator]==0) for (int j=0;j<9;j++) unrolled[j][iterator+difference]=ints[j][iterator];
			if ( (ints[2][iterator]!=0||ints[4][iterator]!=0) && ints[5][iterator]==0) {
				int k2=ints[1][iterator]; if(ints[1][iterator]>ints[2][iterator]) k2=ints[2][iterator];
				int l2=ints[3][iterator]; if(ints[3][iterator]>ints[4][iterator]) l2=ints[4][iterator];
				int k3=ints[2][iterator]; if(ints[1][iterator]>ints[2][iterator]) k3=ints[1][iterator];
				int l3=ints[4][iterator]; if(ints[3][iterator]>ints[4][iterator]) l3=ints[3][iterator];
				for (int k=k2;k<=k3;k++) {
					for (int l=l2;l<=l3;l++) {
						for (int j=0;j<9;j++) unrolled[j][iterator+difference]=ints[j][iterator];
						unrolled[1][iterator+difference]=k;
						unrolled[2][iterator+difference]=0;
						unrolled[3][iterator+difference]=l;
						unrolled[4][iterator+difference]=0;
						//if(!(k==k2&&l==l2))
						difference++;
					}
				}
			}
			if ( (ints[2][iterator]!=0||ints[4][iterator]!=0) &&ints[5][iterator]!=0) {
				for (int k=0;k<ints[5][iterator];k++) {
					for (int j=0;j<9;j++) unrolled[j][iterator+difference]=ints[j][iterator];
					unrolled[1][iterator+difference]=random_int(ints[1][iterator],ints[2][iterator]);
					unrolled[2][iterator+difference]=0;
					unrolled[3][iterator+difference]=random_int(ints[3][iterator],ints[4][iterator]);
					unrolled[4][iterator+difference]=0;
					//if(k!=0)
					difference++;
				}
			}
		}
	}
	difference+=counter_row-1;
	printf("%i\n",difference);
	if(1) {
		for (int i = 0; i<difference; i++) {
			for (int j = 10; j < 15; j++) {
				unrolled[j][i]=0;
			}
			int correct=0;
			if (unrolled[0][i]==increment) correct=unrolled[1][i]+1;
			if (unrolled[0][i]==decrement) correct=unrolled[1][i]-1;
			if (unrolled[0][i]==add) correct=unrolled[1][i]+unrolled[3][i];
			if (unrolled[0][i]==negate) correct=unrolled[1][i]*-1;
			if (unrolled[0][i]==multiply) correct=unrolled[1][i]*unrolled[3][i];
			for (int j = 0; j < 5; j++) unrolled[j+10][i]=0;
			for (int j = 0; j < 5; j++) {
				unrolled[j+10][i]=random_int(unrolled[6][i],unrolled[7][i]);
			}
			unrolled[16][i]=correct;
			unrolled[random_int(0,4)+10][i]=correct;
			for (int j = 0; j < 15; j++) {
				if (j!=9) printf ("%i,",unrolled[j][i]);
			}
			printf("\n");
		}
	}
}

