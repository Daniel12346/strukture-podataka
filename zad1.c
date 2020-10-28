#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct _stud {
	char ime[MAX];
	char prez[MAX];
	int bod;
};

typedef struct _stud Student;

int main()
{
	int cnt = 0, max_bod = 0;
	char tmp[MAX];
	Student * studenti = NULL;
	FILE *fp = fopen("stud.txt", "r");

	if (!fp){
		printf("Greska pri citanju datoteke");
	};
	while (!feof(fp) && fgets(tmp, MAX, fp)) cnt ++;
	studenti = malloc(cnt * sizeof(Student));
	rewind(fp);	
	if (!studenti){
		printf("Greska");
	};	

	for (int i = 0; i < cnt; i++){
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prez, &studenti[i].bod);
		if (studenti[i].bod > max_bod) max_bod = studenti[i].bod;
	}

	printf("IME PREZIME APS.BODOVI REL.BODOVI \n");
	for (int i = 0; i < cnt; i++){
		printf("%s %s %d %.1f\n", studenti[i].ime, studenti[i].prez, studenti[i].bod, (float) studenti[i].bod/max_bod * 100);
	}
	fclose(fp);
}
