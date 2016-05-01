#include "bmp_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	char R;
	char G;
	char B;
} pixel;

typedef struct{
	int x;
	int y;
	pixel color;
	int digit;
} number;

char is_white(pixel spot)
{
	//functia returneaza . daca locul e alb
	//functia returneaza X daca locul e colorat
	if((spot.R != '\xff') || (spot.G != '\xff') || (spot.B != '\xff')){
		return 'X';
	}
	return '.';
}

int can_be_digit(pixel **array, int x, int y)
{
	//functia preia coltul din stanga sus si vede
	//daca se poate ca de acolo sa inceapa o cifra
	//verificand daca
	//coltul dreapta sus
	//coltul dreapta jos
	//si drepta mijloc
	//sunt diferite de alb
	if((is_white(array[x-0][y+4]) == 'X') && //dreapta sus
		(is_white(array[x-2][y+4]) == 'X') && //dreapta mijloc
		(is_white(array[x-4][y+4]) == 'X') ) //dreapta jos
	{
		return 1;
	}

	return 0;
}


int what_is(pixel **array,int x, int y, char *hardcoded)
{
	//functia returneaza cifra care se afla
	//la pozitia x y unde x y este
	//coltul din stanga sus
	//in caz de nepotrivire returneaza -1
	int i, j, k_nr;
	int goto_next;
	for(k_nr = 0 ; k_nr <= 9 ; k_nr++)
	//pentru fiecare digit posibil
	{
		goto_next=0;
		for (i = 0 ; i < 5 ; i++)
		{
			for (j = 0 ; j < 5 ; j++)
			{
				//x este inceputul cifrei si scade in jos (i)
				//y este inceputul cifrei si creste in dreapta (j)
				if ( is_white(array[x-i][y+j]) !=
					(*(hardcoded + k_nr*25 + i*5 + j)) )
				{
					goto_next = 1;
					break;
				}

			}
			if (goto_next) break;
		}
		if (!(goto_next)) return k_nr; //a gasit un numar intre 0 si 9 care convine
	}
	return -1;
}


int check_if_already_in(int x, int y, number *saved, int *count)
{
	//verificam daca punctul de coordonate x y
	//se gaseste in cifrele deja descoperite
	int i;
	for(i = 0 ; i < *count ; i++)
	{
		if(saved[i].x >= x && (saved[i].x) - 5 < x &&
			saved[i].y <= y && (saved[i].y) + 5 > y )
		{
			return 1;
		}
	}
	return 0;
}
void add(pixel **array, int x, int y, number *saved, int *count, char *hardcoded)
{
	int temp = what_is(array, x, y, hardcoded);
	if (temp != -1 && what_is(array, x, y+4, hardcoded) == -1)
	{
		//apelarea cu y+4 o facem deoarece vrem sa ne asiguram
		//ca ultima coloana de fapt nu face parte dintr-un alt
		//numar, astfel adaugand inutil numarul actual
		//e facuta ca si caz general pentru cazul specific
		//in care in cifrele 6 8 si 0 ,prima coloana formeaza 1
		//si astfel ar fi eronat descoperita cifra 1
		saved[*count].x = x;
		saved[*count].y = y;
		saved[*count].color.R = array[x][y+4].R;
		saved[*count].color.G = array[x][y+4].G;
		saved[*count].color.B = array[x][y+4].B;
		//am ales y+4 deoarece semnifica coltul dreapta sus,
		//ce va fi mereu colorat oricare ar fi cifra gasita
		saved[*count].digit = temp;
		(*count)++;
	}
}
char* create_digit_array() {
	//hardcodam sablonul cifrelor in diverse variabile
	//pe care in final le reunim intr-un vector
	//variabilele zero, one, ... le folosim
	//pentru a oferi lizibilitate codului
	char zero[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'X','.','.','.','X'} ,
		{'X','.','.','.','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};
	char one[5][5] =
	{
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
	};
	char two[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
		{'X','.','.','.','.'} ,
		{'X','X','X','X','X'} ,
	};
	char three[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};
	char four[5][5] =
	{
		{'X','.','.','.','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
	};
	char five[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'X','.','.','.','.'} ,
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};
	char six[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'X','.','.','.','.'} ,
		{'X','X','X','X','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};
	char seven[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
		{'.','.','.','.','X'} ,
	};
	char eight[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};
	char nine[5][5] =
	{
		{'X','X','X','X','X'} ,
		{'X','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
		{'.','.','.','.','X'} ,
		{'X','X','X','X','X'} ,
	};

	char *result = (char *)malloc(10 * sizeof(zero));
	if (result == NULL) exit(1);

	memcpy(result ,zero, 25 * sizeof(char)); //result+0
	memcpy(result + 25, one,25 * sizeof(char));
	memcpy(result + 25*2,two, 25 * sizeof(char));
	memcpy(result + 25*3,three, 25 * sizeof(char));
	memcpy(result + 25*4,four, 25 * sizeof(char));
	memcpy(result + 25*5,five, 25 * sizeof(char));
	memcpy(result + 25*6,six, 25 * sizeof(char));
	memcpy(result + 25*7,seven, 25 * sizeof(char));
	memcpy(result + 25*8,eight, 25 * sizeof(char));
	memcpy(result + 25*9,nine, 25 * sizeof(char));

	return result;
}


//folosim typedef pentru a facilita
//scrierea mai lizibila a codului
//fara a repeta de multe ori struct
typedef struct bmp_fileheader HEAD1;
typedef struct bmp_infoheader HEAD2;





void op1(char *name, pixel **array, int new[3], HEAD1 h1, HEAD2 h2)
{
	FILE * output1;
	output1 = fopen(strcat(name, "_task1.bmp"), "wb");
	if (output1 == NULL) exit(2);
	fwrite(&h1, sizeof(HEAD1), 1, output1);
	fwrite(&h2, sizeof(HEAD2), 1, output1);
	int i, j, offset;
	for (i = 0 ; i < h2.height ; i++)
	{
		offset = 0;
		for(j = 0 ; j < h2.width ; j++)
		{
			if (is_white(array[i][j]) == '.')
			{
				putc('\xff', output1);
				putc('\xff', output1); //pune un pixel alb
				putc('\xff', output1);
			}
			else
			{
				putc(new[0], output1);
				putc(new[1], output1); //pune un pixel cu culoarea noua
				putc(new[2], output1);
			}
			offset += 3;
		}
		for( ; offset % 4 != 0 ; offset++)
		{ //umplem cu 0-uri pana offset se divide la 4
			putc('\x00', output1);
		}
	}
	fclose(output1);

	//scapam de sufixul _task1.bmp de la finalul numelui
	name[strlen(name) - 10] = '\0';
}

void op2(char *name, number *saved, int* count)
{
	FILE * output2;
	output2 = fopen(strcat(name, "_task2.txt"), "w");
	if (output2 == NULL) exit(2);
	int i;
	for(i = 0 ; i < *count ; i++)
	{
		fprintf(output2, "%d", saved[i].digit);
	}
	fclose(output2);

	//scapam de sufixul adaugat anterior (_task2.txt)
	name[strlen(name) - 10] = '\0';
}



void remove_unwanted(number *saved, int *count, int *cifre, int *nrcifre)
{
	int i = 0, j, k, increment_i; //functia se incheie in 2 moduri: se mareste i si scade count
	while (i < (*count))
	{
		//luam fiecare struct de tip number
		increment_i = 1;
		for (j = 0 ; j < (*nrcifre) ; j++)
		{
			if (saved[i].digit == cifre[j])
			{
				//inseamna ca e una din cifrele ce trebuie eliminate
				for(k = i ; k < (*count) - 1 ; k++)
				{
					//mutam cu o pozitie la stanga tot in afara de x si y
					saved[k].color = saved[k+1].color;
					saved[k].digit = saved[k+1].digit; //schimbam doar culoarea si cifra
				}

				(*count)--;
				increment_i = 0;
				break; //am gasit ca e una din cifrele necerute, nu ma mai intereseaza
			}
		}

		if (increment_i){
			i++;
		}
	}
}



void op3(char *name, pixel **array, number *saved, int *count, HEAD1 h1, HEAD2 h2, int *cifre, int *nrcifre, char *hardcoded)
{

	remove_unwanted(saved, count, cifre, nrcifre);
	//acum saved are doar cifrele ce trebuiesc printate

	FILE * output3;
	output3 = fopen(strcat(name, "_task3.bmp"), "wb");
	if (output3 == NULL) exit(2);
	fwrite(&h1, sizeof(HEAD1), 1, output3);
	fwrite(&h2, sizeof(HEAD2), 1, output3);

	int i, j, k, offset, pixel_part_of_digit;
	for (i = 0 ; i < h2.height ; i++)
	{
		offset = 0;
		for(j = 0 ; j < h2.width ; j++)
		{
			pixel_part_of_digit = 0;
			for (k = 0 ; k < (*count) ; k++)
			{
				if (saved[k].x >= i && i > saved[k].x-5 &&
					saved[k].y <= j && j < saved[k].y+5)
				{
					//pixelul e dintr-un digit
					if ( (*(hardcoded +
						(saved[k].digit)*25 +
						(saved[k].x-i)*5 +
						(j-saved[k].y))) == 'X')
					{
						//daca in pozitia respectiva, cifra are pixelul colorat/setat
						putc(saved[k].color.B, output3);
						putc(saved[k].color.G, output3); //il scriem
						putc(saved[k].color.R, output3);
					}
					else
					{
						//daca pixelul face parte din cifra dar e alb
						putc('\xff', output3);
						putc('\xff', output3); //pune un pixel alb
						putc('\xff', output3);

					}

					pixel_part_of_digit = 1;
					break; //am umplut pixelul, trecem la urmatorul


				}
			}
			if (pixel_part_of_digit == 0)
			{
				//daca dupa parcurgerea a tot saved
				//pixelul nu se gaseste in nici o cifra
				putc('\xff', output3);
				putc('\xff', output3); //pune un pixel alb
				putc('\xff', output3);

			}
			offset += 3;


		}
		for( ; offset % 4 != 0 ; offset++)
		{ //umplem cu 0-uri pana offset divizibil cu 4
			putc('\x00', output3);
		}
	}
	fclose(output3);
}




/*DE AICI INCEP FUNCTIILE DE BONUS */




int what_is_bonus(pixel **array, int x, int y, char *hardcoded)
{
	//diferenta fata de functia what_is simpla este
	//ca aceasta permite eroare de un pixel
	//programul executand break doar cand goto_next este
	//2 sau mai mult
	int i, j, k_nr;
	int goto_next;
	for(k_nr = 0 ; k_nr <= 9 ; k_nr++)
	{
		goto_next = 0;
		for (i = 0 ; i < 5 ; i++)
		{
			for (j = 0 ; j < 5 ; j++)
			{
				//x este inceputul cifrei si scade in jos
				//y este inceputul cifrei si creste in dreapta
				if (is_white(array[x-i][y+j]) !=
					(*(hardcoded + k_nr*25 + i*5 + j)))
				{
					goto_next++;
					if (goto_next == 2) {break;}
				}

			}
			if (goto_next == 2) {break;}
		}
		//a gasit un numar intre 0 si 9
		//care convine cu o eroare de minim un pixel
		if (goto_next < 2) {return k_nr;}
	}
	return -1; //-1 inseamna numar negasit, eroare
}


void add_bonus(pixel **array, int x, int y, number *saved, int *count, char *hardcoded, int height, int width)
{

	int local_digit = what_is(array, x, y, hardcoded);
	int local_digit_with_error = what_is_bonus(array, x, y, hardcoded);




	saved[*count].x = x; //pun acolo x si y
	saved[*count].y = y; //oricum count nu creste
	saved[*count].color.R = '\x00';
	saved[*count].color.G = '\x00'; //nu ma intereseaza culoarea asa ca pun negru
	saved[*count].color.B = '\x00';



	if (local_digit == 1)
	{
		//am gasit o bara verticala
		int right_digit_with_error = what_is_bonus(array, x, y+4, hardcoded);

		if (right_digit_with_error == -1)
		{
			//avem o bara verticala si in dreapta ei nu se formeaza cifra
			saved[*count].digit = local_digit;
			(*count)++;
			return;
		}
		//else avem o bara verticala, dar in dreapta se formeaza o cifra deci ignoram
	}
	else
	{
		//nu am gasit o bara verticala
		if(local_digit_with_error==1)
		{
			//dar am gasit o bara (unu) cu erori

			//x-1 y   sa nu fie cifra unu intreaga
			//(daca exista cifra 1, primii 4 pixeli vor forma)
			//(o cifra 1 cu eroare si vrem sa evitam asta)

			//x y+4   sa nu fie o cifra eronata fix in dreapta
			//x-1 y+4   sau sa nu fie o cifra eronata dreapta putin mai jos
			//x+1 y+4   sa nu fie cifra eronata dreapta putin mai sus
			//folosim a b c d

			//cu operatorul ternar verific daca nu depaseste
			//marginile imaginii in cele 4 cazuri
			//in cazul in care depaseste pun -1
			int a = ((x-1) >= 4) ? what_is(array, x-1, y, hardcoded) : -1 ;
			int b = ((y+4) < width-4) ? what_is_bonus(array, x, y+4, hardcoded) : -1 ;
			int c = (((x-1) >= 4) && ((y+4) < width-4)) ? what_is_bonus(array, x-1, y+4, hardcoded) : -1 ;
			int d = (((x+1) < height) && ((y+4) < width-4)) ? what_is_bonus(array, x+1, y+4, hardcoded) : -1;


			if(a == -1 && b == -1 && c == -1 && d == -1)
			{
				saved[*count].digit = local_digit_with_error;
				(*count)++;
				return;
			}


		}
		else
		{
			if(local_digit != -1)
			{
				//am gasit o alta cifra (nu unu)
				saved[*count].digit = local_digit;
				(*count)++;
				return;
			}
			else
			{
				if (local_digit_with_error != -1)
				{
					//am gasit alta cifra cu erori (nu unu)
					saved[*count].digit = local_digit_with_error;
					(*count)++;
					return;
				}
			}
		}
	}
}







void op_bonus(char *name, number *saved, int *count)
{
	FILE * outputbonus;
	outputbonus = fopen(strcat(name, "_bonus.txt"), "w");
	if (outputbonus == NULL) exit(2);
	int i;
	for(i = 0 ; i < *count ; i++)
	{
		fprintf(outputbonus, "%d", saved[i].digit);
	}
	fclose(outputbonus);
}




/* AICI SE TERMINA FUNCTIILE DE BONUS */





void get_digits(char *pointer, int *cifre, int *nrcifre)
{
	int i;
	for(i = 0 ; i < strlen(pointer) ; i += 2)
	{
		//facem din ascii-ul cifrei cifra in sine
		cifre[i/2] = (*(pointer + i)) - '0';
		(*nrcifre)++;
	}
}

int main()
{

	char *image_name = (char *)malloc(100 * sizeof(char));
	char *image_name_bonus = (char *)malloc(100 * sizeof(char));
	if(image_name == NULL || image_name_bonus == NULL) return 1;

	int new_color[3];

	char *cifre_str = (char *)malloc(25 * sizeof(char));
	int *cifre = (int*)malloc(10 * sizeof(int));
	int *nrcifre = (int *)malloc(1 * sizeof(int));
	if (cifre_str == NULL || cifre == NULL || nrcifre == NULL) return 1;
	(*nrcifre) = 0;


	FILE *input;
	input = fopen("input.txt", "r");
	if (input == NULL) return 1;

	//de aici se citesc liniile in fisierul input.txt

	fscanf(input, "%s\n", image_name);

	fscanf(input, "%d ", &new_color[0]);
	fscanf(input, "%d ", &new_color[1]);
	fscanf(input, "%d", &new_color[2]);

	fgets(cifre_str, 2, input); //aici scapa de newlineul de la inceput
	fgets(cifre_str, 22, input); //aici citeste linia respectiva

	//scapam de newlineul de la final
	cifre_str[strlen(cifre_str)] = '\0';

	//facem din stringul de cifre cu spatii un sir de int
	get_digits(cifre_str, cifre, nrcifre);


	fscanf(input, "%s\n", image_name_bonus);

	fclose(input);

	//am terminat cu input.txt

	char *hardcoded;
	hardcoded=create_digit_array();
	//hardcoded acum contine toti pixelii cifrelor
	//sub forma de X si .

	FILE *imagine;
	imagine = fopen(image_name, "rb");
	if (imagine == NULL) return 1;

	HEAD1 header1;
	HEAD2 header2; //am declarat cele 2 headere
	fread(&header1, sizeof(header1), 1, imagine);
	fread(&header2, sizeof(header2), 1, imagine);


	pixel** array = (pixel**)malloc(header2.height * sizeof(pixel*));
	if (array == NULL) return 1;

	int i, j, offset;
	for (i = 0 ; i < header2.height ; i++)
	{
		array[i] = (pixel*)malloc(header2.width * sizeof(pixel));
		if (array[i] == NULL) return 1;
		offset = 0;
		for(j = 0 ; j < header2.width ; j++)
		{
			fread(&(array[i][j].B), sizeof(char), 1, imagine);
			fread(&(array[i][j].G), sizeof(char), 1, imagine);
			fread(&(array[i][j].R), sizeof(char), 1, imagine);
			offset += 3;
		}
		if (offset % 4 != 0)
		{
			//sarim peste paddingul de 0
			fseek(imagine, (4 - (offset % 4)), SEEK_CUR);
		}
	}

	fclose(imagine);
	//pana aici am citit tot fisierul imagine



	//aici tinem toate numerele gasite in captcha
	//salvand x y cifra si culoarea, stiind ca ele sunt 5*5
	//iar in count e numarul de elemnte gasite pana acum
	number* saved_numbers = (number*)malloc(500 * sizeof(number));
	int *count_saved_numbers = (int*)malloc(1 * sizeof(int));
	if (saved_numbers == NULL || count_saved_numbers == NULL) return 1;

	*count_saved_numbers = 0;

	for(j = 0 ; j < header2.width - 4 ; j++)
	{
		// -4 deoarece ultimele 4 coloane nu pot avea cifre noi
		for(i = header2.height - 1 ; i >= 0 + 4 ; i--)
		{
			// +4 deoarece identic ultimele 4 linii
			//nu pot avea cifre noi
			//parcurgem mai intai de sus in jos
			//dupa care mergem si inspre dreapta
			if(can_be_digit(array, i, j))
			{
				if (!(check_if_already_in(i, j, saved_numbers, count_saved_numbers)))
				{
					add(array, i, j, saved_numbers, count_saved_numbers, hardcoded);
				}
			}
		}
	}

	//avem toti pixelii
	//in array-ul "array"
	//avem toate cifrele si pozitiile
	//in structura saved_numbers
	//cu lungimea count_saved_numbers

	//scoatem extensia .bmp din numele fisierului
	image_name[strlen(image_name) - 4] = '\0';

	//cele 3 functii ce fac fisierele cerute
	op1(image_name, array,new_color, header1, header2);
	op2(image_name, saved_numbers, count_saved_numbers);
	op3(image_name, array, saved_numbers, count_saved_numbers, header1, header2, cifre, nrcifre, hardcoded);


	//DE AICI INCEPE PRELUCRAREA PENTRU IMAGINEA BONUS

	for (i = 0 ; i < header2.height ; i++)
	{
		free(array[i]); //refolosim pixel **array
	}
	free(array);
	//acum array e gol si gata sa fie refolosit

	FILE *imagine_bonus;
	imagine_bonus = fopen(image_name_bonus, "rb");
	if (imagine_bonus == NULL) return 1;

	HEAD1 header1_bonus; //am declarat cele 2 headere
	HEAD2 header2_bonus; //pentru bonus
	fread(&header1_bonus, sizeof(header1), 1, imagine_bonus);
	fread(&header2_bonus, sizeof(header2), 1, imagine_bonus);


	array = (pixel**)malloc(header2_bonus.height * sizeof(pixel*));
	if (array == NULL) return 1;

	//refolosim i j offset
	for (i = 0 ; i < header2_bonus.height ; i++)
	{
		array[i] = (pixel*)malloc(header2_bonus.width * sizeof(pixel));
		if (array[i] == NULL) return 1;
		offset = 0;
		for(j = 0 ; j < header2_bonus.width ; j++)
		{
			fread(&(array[i][j].B), sizeof(char), 1, imagine_bonus);
			fread(&(array[i][j].G), sizeof(char), 1, imagine_bonus);
			fread(&(array[i][j].R), sizeof(char), 1, imagine_bonus);
			offset += 3;
		}
		if (offset % 4 != 0)
		{
			//sarim peste paddingul de 0
			fseek(imagine_bonus, (4 - (offset % 4)), SEEK_CUR);
		}
	}
	fclose(imagine_bonus);


	//pana aici am citit tot fisierul imagine bonus
	//identic cum am facut mai sus
	//si avem ca rezultat array-ul "array"


	number* saved_numbers_bonus = (number*)malloc(500 * sizeof(number));
	int *count_saved_numbers_bonus = (int*)malloc(1 * sizeof(int));
	if (saved_numbers_bonus == NULL) return 1;
	if (count_saved_numbers_bonus == NULL) return 1;

	*count_saved_numbers_bonus=0;

	for(j = 0 ; j < header2_bonus.width - 4 ; j++)
	{
		// -4 deoarece ultimele 4 coloane nu pot avea cifre noi
		for(i = header2_bonus.height - 1 ; i >= 4 ; i--)
		{
			//4 deoarece jos nu mai gasesti cifre
			//parcurgem mai intai de sus in jos
			//dupa mergem si inspre dreapta
			if (!(check_if_already_in(i, j, saved_numbers_bonus, count_saved_numbers_bonus)))
			{
				add_bonus(array, i, j, saved_numbers_bonus,
					count_saved_numbers_bonus, hardcoded,
					header2_bonus.height, header2_bonus.width);
			}
		}
	}

	//scoatem extensia .bmp
	image_name_bonus[strlen(image_name_bonus) - 4] = '\0';

	//functia care creeaza fisierul cerut
	op_bonus(image_name_bonus, saved_numbers_bonus, count_saved_numbers_bonus);

	return 0;
}
