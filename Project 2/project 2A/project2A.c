#include <stdio.h>

int main() {
	int print_factors = 0;
	for (int i = 2 ; i < 1000 ; i++) {
		int the_number = i; int num_factors = 0;
		for (int j = 2 ; j < i - 1 ; j++){
			if ( the_number % j == 0){
				num_factors ++;
				while (the_number % j == 0){
					the_number = the_number/j;
			}
		}
	}
		if (num_factors == 3){
			printf( "%d has three factors\n" ,i);
			if (print_factors){
				the_number = i; num_factors = 0;
				printf( "%d = " ,the_number);
				for (int j =2; j < i-1; j++){
					if (the_number % j == 0){
						num_factors ++;
						int num_instances = 0;
						while (the_number % j == 0){
							num_instances ++;
							the_number = the_number/j;}
						if (num_instances == 1){
							printf( "/t%d/n", (j)); }
						else {
							printf( "t/%d^%d/n" ,(j), num_instances);
						}
					}
			}
		}
	}
	}

						return 0;
	}





