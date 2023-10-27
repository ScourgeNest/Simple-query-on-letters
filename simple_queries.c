//Niculici Mihai-Daniel 315CA - simple_queries
//Sper ca e bine, doamne ajuta.
#include <stdio.h>
#define ull unsigned long long
void afis_fract_ired(ull a, ull b)
{
	ull copie_a = a, copie_b = b;
	//Folosesc Algoritmul lui Euclid ca sa aflu cmmdc dintre a si b
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	//Dupa calculez fractia ireductibila
	printf("%llu/%llu\n", copie_a / a, copie_b / a);
}

char q_query(ull aparitii[])
{
	//Citesc un caracter si afisez numarul de aparitii ale acestuia
	char caract;
	scanf(" %c", &caract);
	printf("%c %llu\n", caract, aparitii[caract - 'a']);
	return caract;
}

void t_query(ull aparitii[])
{
	int k, ok = 0;
	scanf(" %d", &k);
	//folosesc un vector ca sa vad daca
	//am folosit sau nu numarul de aparitii
	//ale caracterului respectiv
	ull folosit[26] = {0};
	for (int i = 1; i <= k; i++) {
		ull maxim = 0;
		int poz;
		//Caut caracaterul care a aparut de cele mai multe ori si
		// vad daca l-am folosit sau nu
		for (int j = 25; j >= 0; j--) {
			if (aparitii[j] >= maxim && folosit[j] == 0) {
				maxim = aparitii[j];
				poz = j;
			}
		}
		folosit[poz] = 1;
		//Folosesc variabila ok pentru a nu afisa un spatiu la final
		if (ok == 0) {
			printf("%c", poz + 'a');
			ok = 1;
		} else {
			printf(" %c", poz + 'a');
		}
	}
	printf("\n");
}

char e_query(ull aparitii[], ull *contor)
{
	//Citesc un caracter si elimin nr de aparitii ale caracterelor din
	//vectorul de aparitii dar si din numarul total de caractere citite
	char caract;
	scanf(" %c", &caract);
	*contor = *contor - aparitii[caract - 'a'];
	aparitii[caract - 'a'] = 0;
	return caract;
}

void verif_alerta(ull cnt, ull ap[], char car, int *alert)
{
	//Verific daca am citit cel putin 5 caractere si
	//ca am citit cel putin 2.
	if (cnt >= 5 && cnt != ap[car - 'a'] &&
		(car >= 'a' && car <= 'z') && (*alert == 0)) {
	//Am doua cazuri (contor par si impar)
		if (cnt % 2 == 0) {
			for (int i = 0; i <= 25; i++) {
				if (cnt / 2 <= ap[i]) {
					//Daca un caracater respecta conditia, se afiseaza alerta
					printf("%c ", i + 'a');
					afis_fract_ired(ap[i], cnt);
					*alert = 5;
					break;
				}
			}
		} else {
			for (int i = 0; i <= 25; i++) {
				if ((cnt / 2) + 1 <= ap[i]) {
					//Daca un caracater respecta conditia, se afiseaza alerta
					printf("%c ", i + 'a');
					afis_fract_ired(ap[i], cnt);
					*alert = 5;
					break;
				}
			}
		}
	}
}

int main(void)
{
	//Toate variabilele sunt explicat in README
	ull aparitii[26] = {0}, contor = 0;
	ull *pointer_contor = &contor;
	int alert = 0;
	int *pointer_alerta = &alert;
	char car = 'a', exec_terminata = '0';
	//Citesc caratere pana intalnesc unul care nu respecta conditiile
	while ((car >= 'a' && car <= 'z') || (car == 'T') || (car == 10)) {
		scanf("%c", &car);
		//Ignor spatiile
		if (car == 10)
			continue;
		//Daca e caracter, cresc contorul si
		// micsorez timer-ul de la alerta
		if (car >= 'a' && car <= 'z') {
			contor++;
			if (alert != 0)
				alert--;
		}
		//Daca e 'X', executia se termina si nu se mai iau in
		//considerare caracterele de dupa el
		if (car == 'X')
			exec_terminata = '1';
		else if (exec_terminata == '0')
		//Daca executia nu e terminata cred nr de aparitii ale caracterului
			aparitii[car - 'a']++;
			//Verific alerta
		verif_alerta(contor, aparitii, car, pointer_alerta);
		//Si daca nu cumva caracterul citit este un query
		//Executia trebuia sa nu fie terminata.
		if (car == 'Q' && exec_terminata == '0')
			car = q_query(aparitii);
		else if (car == 'T' && exec_terminata == '0')
			t_query(aparitii);
		else if (car == 'E' && exec_terminata == '0')
			car = e_query(aparitii, pointer_contor);
	}
	return 0;
}
