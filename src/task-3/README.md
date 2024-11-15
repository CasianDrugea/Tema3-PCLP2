# Task 3 - KFib (20p)

Cosminel este mare fan al [sirului lui Fibonacci](#sirul-lui-fibonacci). In timp ce gatea, acestuia ii trece un gand briliant prin minte: cum ar fi sa generalizeze secventele de tip Fibonacci ?!  

Asadar, el defineste [sirul KFib](#sirul-kfib) si isi propuna sa calculeze rezultatul **recursiv** pentru diferite valori.

Din nefericire, se incurca in multitudinea de cadre de stiva si ... voi trebuie sa salvati situatia!

#### Sirul lui Fibonacci
Numim sirul lui Fibonacci secventa de numere $0, 1, 1, 2, 3, 5, 8, 13, ...$, unde termenul general $F_n = F_{n - 1} + F_{n - 2}$ pentru orice $n \gt 2$, iar $F_{1} = 0$, $F_{2} = 1$.

#### Sirul KFib
Numim sirul KFib secventa generata de urmatoarea functie: <p>
$$
KFib(n) = 
\begin{cases}
0, & \text{daca } n \lt K \\
1, & \text{daca } n = K \hspace{1cm} \text{pentru K fixat} \\
KFib(n - 1) + KFib(n - 2) + \dots + KFib(n - K), & \text{daca } n > K
\end{cases}
$$ <p>
Exemplu: <p>
$3Fib = 0, 0, 1, 1, 2, 4, 7, 13, 24, 44, 81, ...$


## Organizare
Task-ul are doar un subtask. **Va recomand sa cititi cu atentie restul enuntului**.<p>
Subtask 1: 20p <p>
Exista punctaje partiale, insa testele sunt impartite in grupuri (😁), iar pentru a lua punctele asociate unui grup va trebui ca toate testele aferente sa fie trecute.

## Subtask 1 - KFib
Pentru acest subtask, va trebui sa implementati o functie ce intoarce al $n$-lea termen al sirului $KFib$.
```c
const int fib(int n, int K);
```
Parametrii:
- **n** - pozitia termenului cerut din sirul $KFib$ (indexarea este de la 1);
- **K** - specifica tipul sirului de tip Fibonacci. 

Functia va intoarce:
- $KFib_n$

<span style="color:red">🚨🚨🚨 Rezultatul trebuie calculat <b>recursiv</b>, asadar punctajul afisat de checker e provizoriu, fiind validat de echipa la o verificare ulterioara!!! 🚨🚨🚨</span><p>
<span style="color:red">🚨🚨🚨 Se garanteaza ca rezultatul poate fi reprezentat pe 32 de biti!!!🚨🚨🚨</span><p>


## Constrangeri
- $2 \leq K \leq 30 \equiv$  Tipul maxim al unui sir de tip Fibonacci este 30;
- $2 \leq n \leq 40 \equiv$ Pozitia maxima ceruta a unui termen din sirul $KFib$ este 40;
- $K \leq n \equiv$ Rezultatul este garantat mai mare ca 0.


## Folosire si interpretare checker
Checker-ul poate fi folosit selectiv pentru primele $X \hspace{0.05cm}(1 \leq X \leq 4)$ grupuri de teste, nu inainte de a compila sursele folosind **make**.

- rulati **./checker 1** pentru a verifica primul grup de teste;
- rulati **./checker 2** pentru a verifica primele 2 grupuri de teste;
- rulati **./checker 3** pentru a verifica primele 3 grupuri de teste;
- rulati **./checker 4** pentru a verifica toate grupurile de teste;
- rulati **./checker** pentru a verifica toate grupurile de teste; <p>

**Cu ce scop ?** Grupul 4 de teste **va dura mai mult** (de ordinul zecilor de secunde, depinde de ce hardware aveti), asadar **va recomand** sa-l rulati doar dupa ce le rezolvati pe primele 3.


Odata rulat checker-ul:
- veti vedea in consola punctajul obtinut;
- in cazul unei implementari incorecte, in cadrul grupului respectiv vi se afisa numarul primului test
la care output-ul difera de referinta (indexarea este de la 0) pentru a va usura debugging-ul.


