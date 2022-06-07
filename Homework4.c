#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


int readDataFile();
int localities(int items);
char *getDateAndTime ();
FILE generateLocalityRpt(int count, int locals, char name[]);



struct address_t
{
	int first, second, third, fourth;
	char alias[10];
};

FILE *outputReport;
struct address_t addressArray[100];

int main()
{	
	char name[50];
	printf ("Enter your name:");
	fgets (name, sizeof (name), stdin);
	name[strlen(name)-1] = '\0';
	int count = readDataFile();
    int locals = localities(count);
	generateLocalityRpt(count,locals, name);
}

int readDataFile()
{	
	FILE *read = fopen("CS222_Inet.txt", "r");
	
	char data;
	int count = 0;
	for(data = getc(read); data != EOF; data = getc(read)){	
		if(data == '\n'){
		count++;
		}		
	}
	fclose(read);
	
	read = fopen("CS222_Inet.txt", "r");
	int address = 0;
	char none[4] = "NONE";
		while(fscanf(read, "%d.%d.%d.%d %s", &addressArray[address].first,
		&addressArray[address].second, &addressArray[address].third,
		&addressArray[address].fourth, addressArray[address].alias) == 5)
		{
			if(strcmp(addressArray[address].alias, none) == 0){
				break;
			}
			else
				 address++;
		}
		
	fclose(read);	
	return count;
	
}

int localities(int items)
{	


	int count = 0;
	
	
	for(int i = 0; i < items; i++){
		if(addressArray[i].fourth == -1){
		}
		
		else{
					int temp1 = addressArray[i].first;
					int temp2 = addressArray[i].second;
					
				for(int j = i+1; j < items; j++){
					int temp3 = addressArray[j].first;
					int temp4 = addressArray[j].second;

					if(temp1 == temp3 && temp2 == temp4){
							int l = addressArray[j].fourth = -1;
						}
			
				}
			count++;
		}
		
	}
	
	return count;
	
}


FILE generateLocalityRpt(int count, int locals, char name[])
{
	FILE *ptr_file = fopen("222_Locality_Report.txt", "w");
	fprintf(ptr_file, "%s %s", name, getDateAndTime());
	fprintf(ptr_file, "Address total:%d\n", count);
	fprintf(ptr_file, "Localities: %d\n\n", locals);
	
	for(int i = 0; i < count; i++){
		
		if(addressArray[i].fourth != -1){
			fprintf(ptr_file, "%d.%d\n", addressArray[i].first, addressArray[i].second);
			for(int j = i; j<count; j++){
				if(addressArray[i].first == addressArray[j].first && addressArray[i].second == addressArray[j].second)
				fprintf(ptr_file, "%s\n", addressArray[j].alias);
			}
		}
		fprintf(ptr_file, "\n");
	}
	return *ptr_file;
	
}


//Grabs date and time for file printing.
char *getDateAndTime ()
{
  time_t t;
  time (&t);
  return ctime (&t);
}