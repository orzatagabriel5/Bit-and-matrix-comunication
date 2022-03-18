gates.c
	Task 1
	Am folosit mask pentru a verifica valoarea bitului de pe indexul dat
	si in functie de cerinta am facut modificari asupra lui
	Task 2
	Am scris circuitele date pe site-ul temei in operatii cu opearatori
	logici, iar apoi am implemantat in program acele operatii cu ajutorul
	funtictiilor deja facute
	Task 3
	full_adder :
		Am dedus circuitul aferent pentru full adder si l-am implementat
	in program.
		Am dat valorile corespunzatoare variabilelor sum si carry si in
                functie de acestea am modificat bitul cu indexul 0 pentru sum
		si bitul cu indexul 1 pentru carry al numarului res.
	ripple_carry_adder :
		Am identificat fiecare bit al numarelor a si b, apoi am verificat
		valoarea biitilor de pe indexul 0 (sum) si 1 (carry)
		Daca bitul cu indexul 1 avea valoare pozitiva insemna ca carry era
		egal cu 1, air daca avea valoare negativa insemna ori ca carry a fost
		deja folosit in etapa precedenta ori ca era 0 si inainte.
		In final, daca carry ramanea la final 1 nu il mai pot aduna la
		sumafinala deoarece aceasta este de 64 de biti
communication.c
Am folosit funtiile facute la gates.c.
	Task 1
	Cu ajutorul codului ASCII am codificat fiecare litera din alfabet scazand
	64 din numarul reperzentat de fiecare in ASCII.
	Pentru fiecare mesaj primit am asociat un vector care stockeaza fiecare 
	litera din el.
	Parcurgand vectorul cu un for am trimis si primit mesaje.
	Task 2
	Codificarea numarului de elemente l am facut initial shiftand de doua ori 
	la stanga numarul necodat, iar apoi am citit cei 4 biti din nuamrul de 8 biti pe care era scris si folisind functia activate_bit am format un numar nou care este egal cu valoare decodificata
	Task 3
	Send_squanch2
		Am identificat valoarea primilor 4 biti din fiecare caracter,
		iar apoi i-am scris intr-un octet punand conditia ca biti de pe c2 sa fie pe pozitiile pare si cei de pe c1 sa fie pe pozitiile impare.
	decode_squanch2
		Am citit fiecare bit din octet si daca se afla pe o pozitie 
		para l-am pus pe primele 4 pozitii alea caracterului decodat.
		Pentru restul bitilor am specificat exact pozitia pe care se 
		afla si i-am pus pe urmatoarele 4 pozitii alea caracterului decodat.
hunt.c
Am folosit funtiile facute la gates.c
	Task 1
	find_spell
		Am identificat unde se aflta 5 biti de 1 consecutiv cu ajutorul
		unei intructiuni for.
		Am parcurs fiecare bit al numarului dat si totodata am contorizat 
		indexul la care am ajuns.
		De fiecare data cand bitul gasit avea valoarea 1 contor crestea cu 1,
		insa daca nu ajungea la 5 si urma un bit cu valoarea 0 acesta 
		revenea la valoarea 0.
		Cu ajutoarul indexului la care am ajuns am citit urmatorii 16 biti 
		din numar si i-am scris pe resultatul final.
	find_key
		Am procedat la fel ca la find_spell numai ca in sens invers.
	decrypt_key
		Din proprietatile operatilor cu porti logice am dedus ca 
		spell_plaintext este spell ^ key.
	Task 2
	choose_sword
		Am identificat numarul de biti activi din enemy.
		Pentru fiecare dintre cele doua cazuri (biti activi apar de un numar 
		par sau impar de ori) am atribuit lui value valorile corespunzatoare 
		si transpus-o pe res.
		Monster
			Daca un numar xor alt numar da 0 inseamna ca cele doua numere	
			sunt egale (daca o pereche de biti ar fi diferiti 1 ^ 0 ar da 1 
			si rezultatul operatiei nu ar mai fi 0)
		Human
			Cele doua numere adunate dau 0 doar daca se produce overflow, 
			deci value este fix diferenta dintre 2 la puterea 33 si enemy 
			(am ales 33 deoarece orice numere de 32 de biti adunate nu pot
			da mai mult de un numar de 33 de biti).  
	Task 3
	trial_of_the_grasses
		Opeartiile intre variabile se fac de fiecare data intre 3 biti,
		cate un bit de pe acelasi index de la 
       		-antibodies_low
        	-antibodies_high
        	-cocktail
        	deci am atribuit pe rand valoarea 1 sau 0 fiecarui bit rezultand 
		astfel 8 cazuri posibile si am ajuns la concluzia ca
        	antibodies_low = 0
       	 	antibodies_high = cocktail pentru a satisface conditiile date.
	trial_of_forest_eyes
	Pentru identificarea padurii am pus mai multe conditii :
	Brokilon
		Am citit fiecare bit din map si daca era 1 am crescut variabila 
		contor cu 1, insa daca aparea un 0 o reinitializam cu 0.
		Am retinut daca contor a avut vreodata valoarea 4 in parcurgerea 
		instructiunii for folosind doua intructiuni if si doua variabile 
		x si y carora le-am dat valoarea 1 in cazul in care contor a fost 
		fix 4 sau a depasit valoarea 4.
		In acelasi timp am numarat cati pomi sunt in padure.
		Daca numarul de pomi este zero sau contor a avut valoarea 4 si nu 
		mai mult, padurea Brokilon.
	Hindar
		Am pus conditia ca indexurile 31 si 32 (biti din mijloc) sa fie 
		ocupate de biti activi si numarul de pomi sa fie exact 2.
	Wolven Glade
		Am pus conditia ca numarul de pomi sa fie 64.
	Caed Dhu
		Daca toate celelalte conditii nu sunt satisfacute atunci padurea 
		este de tip Caed Dhu.
	trial_of_dreams
	Am identificat fiecare bit din map de la ultima pozitie la prima de fiecare 
	data scazand din contor 1 pentru a retine pozitia in care apare primul 1, 
	moment in care ies din instructiunea for.
	Incepand de la indexul gasit adaug la res numarul de biti 0 care sunt dupa 
	el pana cand apare al doilea 1, moment in care ies din instructiunea for.

		