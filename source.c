/*
 * source.c
 * 
 * 
 * Author: Zeynep Ferah Akkurt
 * 07.04.2020
 * 150119824
 * CSE2138 - Project 1 - Data Type Converter
 * 
 * This program reads maximum 100 numbers which is unsigned,signed and floating point numbers from a file 
 * and then gives the number's hexadecimal values as a output file 
 * For float values, iy uses IEEE representation
 *  For signed integers, it uses 2's complement representation
 * For unsigned integers, it uses normal binary method.
 * 
 */

#include "functions.h" 

/*main*/
int main(int argc, char **argv)
{	
	char filename[128];													/*filename*/
	printf("Please enter file name with .text\n");
	scanf("%123s",filename);
	
	FILE *file;
	file = fopen(filename,"r");
	if(file == NULL){
		printf("File could not open");
		exit(-1);
	}
	FILE *file2;
	file2 = fopen("output.txt","w");
	if(file2 == NULL){
		printf("File could not open");
		exit(-1);
	}
	char **data;														/*keeps the numbers in the file as a string*/
	
	/* Initial memory allocation */
	data = (char **)calloc(MAX_NUM,sizeof(char*));
	if(data == NULL){
		printf("no memory");
		exit(-1);
	}
	//memory
	for(int i=0 ; i<MAX_NUM ; ++i){
		data[i] = (char *)calloc(MAX_BIT,sizeof(char));
		memoryCheck(data[i]);
	}
	/*Byte ordering Type : Big or little endian */
	int order;
	printf("Please choose byte ordering type:\n\t1:Little Endian\n\t2:Big Endian\n");
	scanf("%d",&order);
	if(order != 1 && order != 2 ){
		printf("Please enter only 1 or 2 for next time.");
		return 0;
	}
	
	/*the size of the floating point data type*/
	int size;
	printf("the size of the floating point data type : 1-2-3-4 byte\n");
	scanf("%d",&size);
	if(!(size > 0 && size < 5 )){
		printf("Next time please enter only 1-2-3-4 for byte size.");
		return 0;
	}
	/*Reading the data*/ 
	int i=0 , j=0;;
	char c;
	while((c = fgetc(file)) !=  EOF){		
		if(c != '\n'){	
			data[i][j] = c;
			j++;
		}else{
			i++;
			j =0;
		}
	}
	/* Reallocating memory */
	int size_data = i;
	data = (char **)realloc(data,size_data*sizeof(char*));
	
	/*output*/
	char *temp = (char *)calloc(size*8/4,sizeof(char));
	memoryCheck(temp);
	for(int n=0; n<size_data ; n++){
		if(check(data[n]) !=1 && check(data[n]) !=0){					/*for float point numbers*/
			strcpy(temp,binaryToHexa(binaryFraction(data[n],size),size));
			if(order == 1){ 											/*little endian*/	
				for(int i=strlen(temp)-1; i>0 ; i=i-2){
					for(int j=i-1 ; j<i+1 ; ++j){
						fprintf(file2,"%c",temp[j]);
					}
					fprintf(file2," ");
				}
			}else if(order == 2){										/*big endian*/
				for(int i=0; i<strlen(temp) ; i=i+2){
					for(int j=i ; j<i+2 ; ++j){
						fprintf(file2,"%c",temp[j]);
			
					}
					fprintf(file2," ");
				}
			}
			fprintf(file2,"\n");
		}else{ 															/*for signed and unsigned numbers*/
			strcpy(temp,binaryToHexa(convertFinal(data[n],BYTE_INT,'a'),BYTE_INT));
			if(order == 1){ 											/*little endian*/
				for(int i=strlen(temp)-1; i>0 ; i=i-2){
					for(int j=i-1 ; j<i+1 ; ++j){
						fprintf(file2,"%c",temp[j]);
					}
					fprintf(file2," ");
				}
			}else if(order == 2){										/*big endian*/
				for(int i=0; i<strlen(temp) ; i=i+2){
					for(int j=i ; j<i+2 ; ++j){
						fprintf(file2,"%c",temp[j]);
			
					}
					fprintf(file2," ");
				}
			}
			fprintf(file2,"\n");
		}
	}
	/*free*/
	free(temp);
	for(int i=0; i<size_data; ++i){
		free(data[i]);
	}
	free(data);
	fclose(file);
	fclose(file2);
	return 0;
}

