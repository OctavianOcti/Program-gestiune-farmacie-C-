#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include<ctype.h>
FILE* f;
FILE* g;
typedef struct medicament {
	int cantitate;
	char* nmed;//nume medicament propus
	struct medicament* urm1;//pointer la urmatorul medicament al tratamentului
}medicament;
typedef struct tratament {

	char* af;//numele bolii
	struct medicament* sl1;
	struct tratament* urm2;//pointer la sublista de medicamente
}tratament;
tratament* prim = NULL;

typedef struct m {
	char* nume;
	int c;
	float pret;
	struct m* urm;
}m;
m* rad = NULL;
//introduce afectiunea in lista de afectiuni
void majuscula(char* s)
{
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		if (!i) s[i] = toupper(s[i]);
		else s[i] = tolower(s[i]);
	}

}

tratament* intr3(tratament* lista, tratament* t)
{
	tratament* q1, * q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->af, t->af) < 0; q2 = q1, q1 = q1->urm2);
	t->urm2 = q1;
	// daca nodul este inserat la inceputul listei
	if (q1 == q2)
		return t;
	//daca nodul este inserat pe parcurs
	else {
		q2->urm2 = t;
		return lista;
	}
}
// introduce medicamentul in sublista bolii
medicament* intr1(medicament* lista, medicament* md)
{
	medicament* q1, * q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->nmed, md->nmed) < 0; q2 = q1, q1 = q1->urm1);
	md->urm1 = q1;
	// daca nodul este inserat la inceputul listei
	if (q1 == q2)
		return md;
	//daca nodul este inserat pe parcurs
	else {
		q2->urm1 = md;
		return lista;
	}
}
// cauta afectiunea in lista de afectiuni
tratament* cauta3(tratament* lista, char* boala)
{
	tratament* q;
	for (q = lista; q != NULL && strcmp(q->af, boala) < 0; q = q->urm2);
	if (q != NULL && strcmp(q->af, boala) == 0)
		//daca nodul a fost gastit
		return q;
	return NULL;

}

//cauta medicamentul in sublista bolii
medicament* cauta2(medicament* lista, char* nmed)
{
	medicament* q;
	for (q = lista; q != NULL && strcmp(q->nmed, nmed) < 0; q = q->urm1);
	if (q != NULL && strcmp(q->nmed, nmed) == 0)
		//daca nodul a fost gastit
		return q;
	return NULL;

}

//citeste reteta din fisier
void introd() {
	tratament* t;
	medicament* md;
	char boala[50], medpropus[50];
	int x, i;
	while (!feof(g))
	{
		fscanf(g, "%s", boala);
		fscanf(g, "%s", medpropus);
		fscanf(g, "%d", &x);
		majuscula(boala);
		majuscula(medpropus);
		if (t = cauta3(prim, boala)) //daca a gasit afectiunea deja inregistrata
		{
			if ((md = (medicament*)malloc(sizeof(medicament))) == NULL || (md->nmed = (char*)malloc(strlen(medpropus) + 1)) == NULL)
				printf("Nu este suficienta memorie");
			strcpy(md->nmed, medpropus);
			md->cantitate = x;
			t->sl1 = intr1(t->sl1, md);

		}
		else
		{
			// daca numele bolii nu a fost gasit creeaza un nod
			if ((t = (tratament*)malloc(sizeof(tratament))) == NULL || (t->af = (char*)malloc(strlen(boala) + 1)) == NULL)
				printf("Nu este suficienta memorie");
			strcpy(t->af, boala);
			t->sl1 = NULL;
			prim = intr3(prim, t);
			//introducem medicamentul in sublista bolii
			if ((md = (medicament*)malloc(sizeof(medicament))) == NULL || (md->nmed = (char*)malloc(strlen(medpropus) + 1)) == NULL)
				printf("Nu este suficienta memorie");
			strcpy(md->nmed, medpropus);
			md->cantitate = x;
			t->sl1 = intr1(t->sl1, md);


		}

	}

}
//citeste reteta de la tastatura
void introd1(char* s) {
	char d;
	tratament* t;
	medicament* md;
	char boala[50], medpropus[50];
	int x, i;
	strcpy(boala, s);
	printf("\nIntroduceti numele medicamentului: ");
	scanf("%s", medpropus);
	printf("\nIntroduceti cantitatea: ");
	scanf("%d", &x);
	majuscula(medpropus);
	if ((t = (tratament*)malloc(sizeof(tratament))) == NULL || (t->af = (char*)malloc(strlen(boala) + 1)) == NULL)
		printf("Nu este suficienta memorie");
	strcpy(t->af, boala);
	t->sl1 = NULL;
	prim = intr3(prim, t);
	//introducem medicamentul in sublista bolii
	if ((md = (medicament*)malloc(sizeof(medicament))) == NULL || (md->nmed = (char*)malloc(strlen(medpropus) + 1)) == NULL)
		printf("Nu este suficienta memorie");
	strcpy(md->nmed, medpropus);
	md->cantitate = x;
	t->sl1 = intr1(t->sl1, md);
	while (printf("\nDoriti sa introduceti si alte medicamente pentru aceasta boala d/n:"), (d = _getche()) != 'n') {
		printf("\nIntroduceti medicamentul:");
		scanf("%s", medpropus);
		majuscula(medpropus);
		/*cauta daca medicamentul exista deja */
		if ((md = cauta2(t->sl1, medpropus))) {
			printf("Medicamentul %s a fost deja introdus pentru %s!!!",medpropus,boala);
			continue;
		}
		printf("\nIntroduceti cantitatea: ");
		scanf("%d", &x);
		if ((md = (medicament*)malloc(sizeof(medicament))) == NULL || (md->nmed = (char*)malloc(strlen(medpropus) + 1)) == NULL)
			printf("Nu este suficienta memorie");
		strcpy(md->nmed, medpropus);
		md->cantitate = x;
		t->sl1 = intr1(t->sl1, md);
			
		
	}




}
//sterge un medicament din sublista bolii
medicament* sterg2(medicament* lista)
{

	medicament* q1, * q2;
	for (q1 = q2 = lista; q1 != NULL; q2 = q1, q1 = q1->urm1);
	if (q1 != NULL) {
		if (q1 == q2)
			lista = lista->urm1;
		else
			q2->urm1 = q1->urm1;
		free(q1);
	}
	return lista;
}
//sterge o reteta (citita de la tastatura) din lista
tratament* sterg(tratament* lista, char* s) {
	tratament* t;
	medicament* md1, * md2;
	tratament* t1, * t2;
	char boala[50], medpropus[50];
	strcpy(boala, s);
	t = cauta3(prim, boala);
	for (t1 = t2 = lista; t1 != NULL && (strcmp(t1->af, s)) != 0; t2 = t1, t1 = t1->urm2);
	if (t1 != NULL) {
		t->sl1 = sterg2(t->sl1);
		if (t1 == t2)
			lista = lista->urm2;
		else
			t2->urm2 = t1->urm2;
		free(t1);

	}


	return lista;


}

// adauga medicament in lista simplu inlantuita
m* add(m* lista, m* aux) {
	m* q1, * q2;
	for (q1 = q2 = lista; q1 != NULL && (strcmp(aux->nume, q1->nume) > 0); q2 = q1, q1 = q1->urm);
	if (q1 == q2)
	{
		aux->urm = lista;
		lista = aux;
	}
	else
	{
		q2->urm = aux;
		aux->urm = q1;
	}

	return lista;

}
//afiseaza lista retetelor in ordine alfabetica
void afis()
{
	tratament* t;
	medicament* md;
	printf("\nAfectiune  |     Medicament       | Cantitate");
	printf("\n--------------------------------------------------------------------");
	for (t = prim; t != NULL; t = t->urm2)
	{
		printf("\n%s: | ", t->af);
	
		for (md = t->sl1; md != NULL; md = md->urm1)
			printf(" %s x %d |", md->nmed, md->cantitate);
	}
}
void afisnou()
{
	tratament* t;
	medicament* md;

	for (t = prim; t != NULL; t = t->urm2)
	{
		for (md = t->sl1; md != NULL; md = md->urm1)
			fprintf(g, "%s %s  %d\n", t->af, md->nmed, md->cantitate);
	}
}
void afisare(m* lista)
{
	printf("\n");
	m* q;
	for (q = lista; q != NULL; q = q->urm) {
		printf("%s\t%d\t%g\n", q->nume, q->c, q->pret);
	}
}
void afisarenou(m* lista)
{
	printf("\n");
	m* q;
	for (q = lista; q != NULL; q = q->urm) {
		fprintf(f, "%s %d %g\n", q->nume, q->c, q->pret);
	}
}
// adauga in lista simplu inlantuita
void citire(void)
{
	char n[50];
	int cant, nr = 0;
	float pr;
	m* aux;
	int i;
	//fisier();
	if (!(g = fopen("retete.txt", "r+")) || !(f = fopen("stoc.txt", "r+")))
		printf("Nu se poate aloca memorie");


	while (!feof(f)) {
		aux = (m*)malloc(sizeof(m));
		fscanf(f, "%s", n);
		fscanf(f, "%d", &cant);
		fscanf(f, "%f", &pr);
		majuscula(n);
		aux->pret = pr;
		aux->c = cant;
		aux->nume = (char*)malloc(strlen(n) + 1);
		strcpy(aux->nume, n);
		rad = add(rad, aux);
	}
}
m* cautare(m*, char*);
//adauga un nod in lista simplu inlantuita(optiunea 6)
void citire1(void)
{
	m* medication;
	char n[50];
	int cant, nr = 0;
	float pr;
	m* aux;
	int i;
	aux = (m*)malloc(sizeof(m));
	printf("\nIntroduceti numele medicamentului: ");
	scanf("%s", n);
	majuscula(n);
	if (medication = cautare(rad, n)) {
		printf("\nMedicamentul  a fost deja  introdus! ");
		return;
	}
	printf("\nIntroduceti cantitatea aflata in stoc: ");
	scanf("%d", &cant);
	printf("\nIntroduceti pretul: ");
	scanf("%f", &pr);

	aux->pret = pr;
	aux->c = cant;
	aux->nume = (char*)malloc(strlen(n) + 1);
	strcpy(aux->nume, n);
	rad = add(rad, aux);
}
//verifica daca medicamentele sunt in stoc pentru o boala
void verifica(char* boala)
{
	m* q;
	tratament* t;
	medicament* md;
	int i, ok = 0;
	float p = 0;
	majuscula(boala);
	if (t = cauta3(prim, boala))
	{
		for (md = t->sl1; md != NULL; md = md->urm1) {
			ok = 0;
			for (q = rad; q != NULL; q = q->urm) {
				if (strcmp(q->nume, md->nmed) == 0)
				{
					ok = 1;
					if (q->c >= md->cantitate) {
						p = p + (md->cantitate) * (q->pret);
						printf("\nPretul pentru %s este %g lei ", q->nume, (md->cantitate) * (q->pret));
						//break;
					}
					else printf("\n%s nu se gaseste in stoc", q->nume);
				}
			}
			if (!ok) printf("\n%s nu se gaseste in stoc", md->nmed);

		}
		printf("\n Pretul total al medicamentelor(aflate in stoc) pentru tratarea bolii este %g lei", p);


	}
	else printf("\n Nicio afectiune cu acest nume nu este inregistrata! ");
}
//sterge medicament din lista simplu inlantuita
m* stergere(m* lista, char* s) {
	m* q1, * q2;
	for (q1 = q2 = lista; q1 != NULL && (strcmp(q1->nume, s)) != 0; q2 = q1, q1 = q1->urm);
	if (q1 != NULL && strcmp(q1->nume, s) == 0) {
		if (q1 == q2)
			lista = lista->urm;
		else
			q2->urm = q1->urm;
		free(q1);
	}
	return lista;
}
//modifica informatiile unui medicament din lista simplu inlantuita
m* modifica(m* lista, char* s) {
	int cant;
	float pr;
	m* q1, * q2;
	for (q1 = lista; q1 != NULL && (strcmp(q1->nume, s)) != 0; q1 = q1->urm);
	if (q1 != NULL && strcmp(q1->nume, s) == 0) {
		printf("\n Introduceti noua cantitate pentru medicament: ");
		scanf("%d", &cant);
		printf("\n Introduceti pretul: ");
		scanf("%f", &pr);
		q1->c = cant;
		q1->pret = pr;
	}
	return lista;
}
//cauta medicamentul in lista simplu inlantuita
m* cautare(m* lista, char* s)
{
	m* q;
	for (q = lista; q != NULL && strcmp(q->nume, s) < 0; q = q->urm);
	if (q != NULL && strcmp(q->nume, s) == 0)
		//daca nodul a fost gastit
		return q;
	return NULL;
}





void meniu() {
	printf("\n--------------------------------------------------------------------");
	printf("\n1. Incarca datele din fisierul \"retete.txt\" intr-o structura de lista cu subliste \n");
	printf("     iar datele din \"stoc.txt\" intr - o lista simplu inlantuita \n");
	printf("2.Afiseaza lista retetelor in ordine alfabetica \n");
	printf("3. Verifica pentru o reteta citita de la tastatura daca exista toate medicamentele in stoc\n");
	printf("   si care e pretul ei in acest caz\n");
	printf("4. Afiseaza lista medicamentelor in ordine alfabetica din stoc cu informatiile legate de ele\n");
	printf("5. Adauga/sterge o reteta in/din lista\n");
	printf("6. Adauga/sterge/modifica un medicament in/din lista\n");
	printf("7. Salvare inapoi in fisierele aferente a retetelor si medicamentelor.\n");
	printf("0. Iesire\n");
	printf("\n--------------------------------------------------------------------\n");
}
void meniu1()
{
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n a. Stergerea medicamentului din lista \n");
	printf("\n b. Adaugarea medicamentului in lista \n");
	printf("\n c. Modificarea medicamentului din lista \n");
	printf("\ne. Exit \n");
	printf("\n Introduceti litera corespunzatoare ");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}
void meniu2() {
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n a. Adauga reteta in lista \n");
	printf("\n b. Sterge o reteta din lista \n");
	printf("\ne. Exit \n");
	printf("\n Introduceti litera corespunzatoare ");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void fisier()
{
	g = fopen("retete.txt", "r");
	if (!g) {
		printf("Nu s-a putut deschide fisierul\"retete.txt\" ");
		exit(EXIT_FAILURE);
	}
	f = fopen("stoc.txt", "r");
	if (!f) {
		printf("Nu s-a putut deschide fisierul\"stoc.txt\" ");
		exit(EXIT_FAILURE);
	}
}
void fisiernou()
{
	g = fopen("retete.txt", "w");
	if (!g) {
		printf("Nu s-a putut deschide fisierul\"retete.txt\" ");
		exit(EXIT_FAILURE);
	}
	f = fopen("stoc.txt", "w");
	if (!f) {
		printf("Nu s-a putut deschide fisierul\"stoc.txt\" ");
		exit(EXIT_FAILURE);
	}
}
int main()
{
	m* medication;
	tratament* t;
	int ok = 0, i, ver = 1;
	char c, boala[50], s[50], d;
	fisier();
	while (1)
	{
		meniu();
		printf("Introduceti optiunea: ");
		c = _getche();
		switch (c) {
		case '1':introd();//introduce lista cu subliste
			citire();//citeste lista simplu inlantuita
			ok = 1;
			break;
		case '2':afis();
			break;
		case '3':printf("\nIntroduceti afectiunea: ");
			scanf("%s", boala);
			verifica(boala);
			//printf("%s", boala);
			break;
		case '4':if (ok)
			afisare(rad);
				else printf("\nNu ati incarcat lista de medicamente aflate in stoc!");
			break;
		case '5':while (ver == 1)
		{
			meniu2();
			d = _getche();
			d = tolower(d);
			switch (d)
			{
			case 'a':printf("\n Introduceti numele afectiunii:");
				scanf("%s", s);
				majuscula(s);
				if ((t = cauta3(prim, s))) {
					printf("\n !!!!!!!!!!!Aceasta afectiune a fost deja introdusa!!!!!!!!!!!! ");
					break;
				}
				introd1(s);
				break;
			case 'b':printf("\n Introduceti numele afectiunii:");
				scanf("%s", s);
				majuscula(s);
				if (!(t = cauta3(prim, s))) {
					printf("\n !!!!!!!!!!!Aceasta afectiune nu a fost introdusa!!!!!!!!!!!! ");
					break;
				}
				prim = sterg(prim, s);
				break;

			case 'e':ver = 0;
				break;
			}

		}
				ver = 1;
				break;
		case'6':
			while (ver == 1)
			{
				meniu1();
				d = _getche();
				d = tolower(d);
				switch (d)
				{
				case 'a':
					printf("\nIntroduceti numele medicamentului: ");
					scanf("%s", s);
					majuscula(s);
					if (!(medication = cautare(rad, s))) {
						printf("\nMedicamentul nu a fost  introdus! ");
						break;
					}
					rad = stergere(rad, s);
					//afisare(rad);
					break;
				case 'b':citire1();
					break;
				case 'c':printf("\nIntroduceti numele medicamentului: ");
					scanf("%s", s);
					majuscula(s);
					if (!(medication = cautare(rad, s))) {
						printf("\nMedicamentul nu a fost  introdus! ");
						break;
					}

					rad = modifica(rad, s);
					break;
				case 'e':ver = 0;
					break;

				}
			}
			ver = 1;
			break;
		case '7':fisiernou();
			afisnou();
			afisarenou(rad);
			exit(1);
			break;
		case '0':exit(1); break;


		}

	}


	return 0;
}