/*
 * functions.h
 * 
 * 
 * Author: Zeynep Ferah Akkurt
 * 07.04.2020
 * 150119824
 * CSE2138 - Project 1 - Data Type Converter
 * 
 * 
 * DataTypeConverter library
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define BYTE_INT 2				//unsigned and signed integers represented always 2 byte.
#define MAX_NUM 100
#define MAX_BIT 64

/*some messages for user (to keep program in action)*/
char inf[] = "i";
char nan2[] = "n";
char error[] = "--ERROR--";
char notAnumber[] = "#NaN";
char infinity[] = "#INFINITY";
 

char* convertFinal(char* , int,char);
void memoryCheck(char *);
char* myReverse(char*,int);
char *intToStringBaseTen(int);
int check(char *);
int expBit(int);
int isFull(char* ,int);
char *reverse(char *, int);
char *add(char *, int);
char *binary(char *, int);
char * roundFraction(char *, int);
char *binaryFraction(char *, int);
char * convertFinal(char *, int,char);
char * binaryToHexa(char *, int);
char calculate_2nd(char *);


/*it returns the reverse of a given string - strrev function -*/
char *myReverse(char *str,int size){
	char *RevStr = (char* )calloc(size,sizeof(char));
	memoryCheck(RevStr);
	int j = 0 ,i; 
	int len = strlen(str); 
  	for (i = len - 1; i >= 0; i--){
  		RevStr[j] = str[i];
  		j++;
  	}
  	RevStr[j] = '\0';
  	return RevStr;
}
/*it returns the given unsigned integer number as a string - itoa function -*/
char *intToStringBaseTen(int number){
	char *n = (char* )calloc(10,sizeof(char));
	memoryCheck(n);
	int i=0; 
	if(number == 0){
		n[i++] = 0 + '0';
	}
	while(number > 0){
		n[i]= number%10 + '0';
		number /= 10;
		i++;
	}
	n[i] = '\0';
	return myReverse(n,strlen(n));	
}
/*understanding the number - signed int(-6,5) , unsigned int(6u) , float(-83.67)*/ 
int check(char *data){
	for(size_t j=0; j<strlen(data) ; j++){
		if(data[j] == 'u'){ 					/*unsigned int*/
			return 0;
		}else if(data[j] == '.'){ 				/*float*/
			return 2;
		}else if(data[j] == '-'){
			for(j=1; j<strlen(data) ; ++j){
				if(data[j] == '.'){				/* - float*/
					return 3;
				}
			}
		}
	}
	return 1;									/*otherwise it returns signed integer*/
}
/*it returns the number of bit of exponent for given byte size*/
int expBit(int byte_size){
	if(byte_size == 1){
		return 4;
	}else if(byte_size == 2){
		return 6;
	}if(byte_size == 3){
		return 8;
	}if(byte_size == 4){
		return 10;
	}
	return 0;
}
/*it checks the given binary number is all zero or all 1. Ex: 1111, 0000*/
int isFull(char* number,int size){
	int count = 0, count2 = 0;
	for(int i=0 ; i<size ;++i){
		if(number[i] == '0'){
			count++;
		}else if (number[i] == '1')
			count2++;
	}
	if(count == 0){				//all digits is 1
		return 1;
	}else if (count2 == 0){		//all digits is 0
		return 0;
	}
	return -1;
}
/*it reverse the given binary number string Ex: 10100 ->> 00101*/
char *reverse(char *num, int byte_size){
	char *temp = (char*)calloc(byte_size*8,sizeof(char));
	memoryCheck(temp);
	int x;
	for(size_t i=0 ; i<strlen(num) ;++i){
		char c = num[i];
		x = atoi(&c);
		temp[i] = !x + '0';
	}
	strcpy(num,temp);
	free(temp);
	return num;
}
/* it adds 1 to the given binary number.
 * but in the case of an overflow or carry out, it does not add 1 bit to the number 
 * so for that case, it returns the string number without the most significant digit. Ex: 111+1 = 1000 (it will return without 1) 
 */
char *add(char *num, int byte_size){
	char *temp = num;
	bool done = true;
	int n= strlen(temp);
	while(done){
		if(temp[n-1] == '0'){
			temp[n-1] = '1';
			done= false;
		}else if(temp[n-1] == '1'){
			temp[n-1] = '0';
		}
		if(n == 1){
			done = false;
		}
		n--;
	}
	strcpy(num,temp);
	return num;
}
/*decimal to binary for unsigned and signed integers*/
char *binary(char *numString, int byte_size){
	char*str  = (char*)calloc(4,sizeof(char));
	memoryCheck(str);
	char *temp = (char*)calloc(byte_size*8,sizeof(char));
	memoryCheck(temp);
	*str = '1';
	
	int num = abs(atoi(numString));			
	if(num == 0){
		return numString;
	}
	for(int i=0; num>0 ; ++i){
		temp[i] = num%2 +'0';
		num = num/2;
	}
    /*strrev(temp); ->> it can bu used instead of myReverse function*/  
    strcpy(temp,myReverse(temp,strlen(temp)));
	if(atoi(numString) < 0){								/*if the number is negative signed integer*/
		strcat(str,add(reverse(temp,byte_size),byte_size));
		strcpy(numString,str);
	}else 													/*if the number is positive integer*/
		strcpy(numString,temp);
	free(str);
    return numString;
}
/* Round to nearist even and returns the rounded binary number. 
 * It does not calculate overflow cases. 
 * (ex: let's say 11111111111 (11 bit to 9 bit) is the part of the fraction and 
 * when the last two digit is round to nearist even, the number will increase 1 and this is an overflow for our case
 * because it is going to add 1 bit to the fraction).*/
char * roundFraction(char *fraction, int byte_size){
	int n_bit = strlen(fraction);							/*the number of bits of the given fraction */
	int round_bit;											/*the number of bits that matches to the given byte size for binary represation*/
	
	if(byte_size == 1 || byte_size == 2){
		round_bit = byte_size*8 - (expBit(byte_size)+1);
	}else{
		round_bit = 13;													/*for 3 and 4 bytes the number will be round to 13 bits.*/
	}
	char *round_temp = (char*)calloc(round_bit,sizeof(char));
	memoryCheck(round_temp);
	int count = 0;														/*a counter to understand how many 1 or 0's is in the number, is it half way or not.*/
	if(round_bit < n_bit){				
		//round_bit = round_bit -1;
		if(fraction[round_bit] == '0'){									/*smaller than half way*/
			for(int i=0; i<round_bit ; ++i){
				round_temp[i] = fraction[i];
			}
		}else if(fraction[round_bit] == '1'){
			for(int i=round_bit+1 ; i<n_bit ; ++i){
				if(fraction[i] == '1'){	
					count++;
				}
			}
			if(count == 0){												/*half way*/
				if(fraction[round_bit-1] == '1'){	
					for(int i=0; i<round_bit ; ++i){
						round_temp[i] = fraction[i];
					}
					round_temp = add(round_temp,byte_size);
				}else if(fraction[round_bit-1] == '0'){
					for(int i=0; i<round_bit ; ++i){
						round_temp[i] = fraction[i];
					}
				}
					
			}else{														/*bigger than half way*/
				for(int i=0; i<round_bit ; ++i){
					round_temp[i] = fraction[i];
				}
				round_temp = add(round_temp,byte_size);
			}
		}
		strcpy(fraction,round_temp);
	}
	/*complete the fraction for given byte size with 0's*/
	int new_fsize = strlen(fraction);
	round_bit = byte_size*8 - (expBit(byte_size)+1);
	
	if(new_fsize < round_bit){
		for(int i=0; i<new_fsize ; ++i){
			round_temp[i] = fraction[i];
		}
		for(int i=new_fsize; i<round_bit ; ++i){
			round_temp[i] = '0';
		}
		strcpy(fraction,round_temp);
	}
	free(round_temp);
	return fraction;
}

/* Returns the final binary representation of a given float number
 * it calculates mantissa and fraction seperately , at the end it combine all of them with the sign bit. 
 */
char *binaryFraction(char *numString, int byte_size){
	char *temp = (char*)calloc(byte_size*8,sizeof(char));				/*mantissa fraction part ex: 1.01010 --> 01010 part(normalized or denormalized)*/ 
	memoryCheck(temp);	
	char *temp2 = (char*)calloc(byte_size*8,sizeof(char));				/*numString int part ex: 10101111.*/
	memoryCheck(temp2);
	char *temp3 = (char*)calloc(byte_size*8,sizeof(char));				/*binary fraction part that calculates. ex: if the number is 12.87 then the binary rep. of .87*/
	memoryCheck(temp3);
	
	float num = fabs(atof(numString));									/*numString to absolute float (ex: 12.87)*/
	float num2 = num - (int)num;										/*fraction part (ex: 12)*/
	if(num2 == 0){
		temp3[0] = '0';
	}
	int e,exp;
	int k = expBit(byte_size);
	int bias = pow(2,k-1)-1;
	
	int n=0;
	while(numString[n] != '.'){
		if(atof(numString) < 0){
			temp2[n] = numString[n+1];
		}else{
			temp2[n] = numString[n];
		}
		n++;
	}
	temp2 = binary(temp2,byte_size); 									/*binary rep. for int part of the number*/
	
	int a = 0;
	if(num2 != 0){
		while(num2 != 0.5){
			num2 *=2; 
			temp3[a] = (int)num2 + '0';
			num2 -= (int)num2;  
			a++;
		}
		temp3[a] = '1';
	}
	/*calculating mantissa's fraction*/
	int i=0, j = 0;
	if(num >=1){
		if(temp2[i] == '1'){
			i += 1;
			while(temp2[i] != '\0'){
				temp[j] = temp2[i]; 
				i++;
				j++;
			}
		}
		e = strlen(temp); 												/*E*/
		exp = e + bias;
		if(exp != 0){													/*exp == 0 denormalize ?*/ 
			for(int m=0 ; temp3[m] != '\0' ; m++){
				temp[j] = temp3[m];
				j++;
			}
		}
	}else if(num < 1){
		while(temp3[i] != '1'){
			i++;	
		}
		e = 0-(i +1);													/*E*/
		exp = e + bias;
		if(exp != 0){													/*exp == 0 denormalize ? */
			while(temp3[i] != '\0'){
				temp[j] = temp3[i]; 
				i++;	
				j++;
			}
		}else if(exp == 0){
			while(temp3[i] != '\0'){
				temp[j] = temp3[i]; 
				i++;	
				j++;
			}
		}
	}	
	temp = roundFraction(temp,byte_size);								/*fraction*/
	/*itoa(exp,temp3,10); can be used instead of intToBaseTen function*/
	strcpy(temp3,intToStringBaseTen(exp));
	strcpy(temp2,convertFinal(temp3,byte_size,'f')); 					/*exponent*/
	
	/*for special cases - infinity or NaN*/
	int full = isFull(temp2,strlen(temp2));
	int full2 = isFull(temp2,strlen(temp2));
	
	if( full == 1 ){
		if(full2 == 0){
			return inf;
		}else if(full2 == -1){
			return nan2;
		}
	}
	strcat(temp2,temp);
	/*calculating sign bit*/
	if(atof(numString) < 0 ){
		strcpy(temp3,intToStringBaseTen(1));
		//itoa(1,temp3,10);
	}else if(atof(numString) > 0){
		strcpy(temp3,intToStringBaseTen(0));
		//itoa(0,temp3,10);
	}
	strcat(temp3,temp2);
	return temp3;
}
/* Returns the given base ten number as a binary number with the given byte size (unsigned , signed , float).
 * In the parameters, it takes a char type for floating point numbers to convert in given bit size. 
 * For signed and unsigned integer, it only needs byte size, for char type it can be given any character except 'f' . */
char * convertFinal(char *number, int byte_size,char type){
	char s[2] = {'0','1'};												/*to add the number with 1 or 0's*/
	char *bit = s;
	char *temp = (char*)calloc(byte_size*8,sizeof(char));				/*binary number with given size.(completed)*/
	memoryCheck(temp);
	char *temp2 = (char*)calloc(byte_size*8,sizeof(char));				/*keeps the given number's binary version*/
	memoryCheck(temp2);
	strcpy(temp2,number);
	temp2 = binary(temp2,byte_size);	
	
	int value = atoi(number);
	int n= strlen(temp2);
	int bin_size;														/*for float numbers, bit size depends on byte size*/
	int i=0;
	int head;															/*the difference between the number's length and bit size*/
	
	if(type == 'f'){													/*float number*/
		bin_size = expBit(byte_size);
		head = bin_size - n;
		if(head < 0){
			printf("exponent : %s can not be represented with given byte size.\n",number);
			return error;
		}
	}else{
		bin_size = byte_size*8 ;
		head = bin_size - n;
	}
	/*if the number's size is fits the byte size*/
	if(head == 0){
		return temp2;	
	}
	if(check(number) == 0){												/*unsigned numbers*/
		while(i < head){
			temp[i] = bit[0];
			i++;
		}
	}else if(check(number) == 1){										/*signed numbers*/
		if(value>=0){
			while(i < head){
				temp[i] = bit[0];
				i++;
			}
		}else if(value<0){
			while(i < head){
				temp[i] = bit[1];
				i++;
			}
		}
	}
	int j = head;
	while(j < bin_size){
		temp[j] = temp2[j-head];
		j++;
	}
	temp[bin_size] = '\0';
	return temp;
}

/* Binary to decimal number for hexadecimal represantation*/
char calculate_2nd(char *temp){
	int sum = 0;
	int n = strlen(temp);
	int i=0;
	while(temp[i] != '\0'){
		char c = temp[i];
		int a = atoi(&c);
		sum += pow(2,n-1)*a;
		n--;
		i++;
	}
	if(sum == 10){
		return 'A';
	}else if(sum == 11){
		return 'B';
	}else if(sum == 12){
		return 'C';
	}else if(sum == 13){
		return 'D';
	}else if(sum == 14){
		return 'E';
	}else if(sum == 15){
		return 'F';
	}
	return (sum + '0');
}

/*binary to hexadecimal*/
char * binaryToHexa(char *temp, int byte_size){
	
	/*if there is a special case then no need to calculate hexadecimal value.*/
	if(temp[0] == 'i'){
		return infinity;
	}else if(temp[0] == 'n'){
		return notAnumber;
	}
	/*for hexadecimal value*/
	int numberOf = byte_size*8/4;
	char **temp2 = (char **)calloc(numberOf,sizeof(char*));
	if(temp2 == NULL){
		printf("no memory");
		exit(-1);
	}
	/*memory*/
	for(int i=0 ; i<numberOf ; ++i){
		temp2[i] = (char *)calloc(4,sizeof(char));
		memoryCheck(temp2[i]);
	}
	int a=0;
	for(int i = 0 ; i<numberOf ; i++){
		for(int j = 0 ; j<4 ; j++){
			temp2[i][j] = temp[a];
			a++;
		}
	}
	char *str = (char*)calloc(byte_size*8,sizeof(char));
	memoryCheck(str);
	/*calculating hexa values*/
	for(int i = 0 ; i<numberOf; i++){
		str[i] = calculate_2nd(temp2[i]);			
	}
	strcpy(temp,str);
	free(str);
	for(int i=0; i<numberOf; ++i){
		free(temp2[i]);
	}
	free(temp2);
	return temp;
}
/*Memory allocation check*/
void memoryCheck(char *s){
	if(s == NULL){
		printf("no memory");
		exit(-1);
	}
}
