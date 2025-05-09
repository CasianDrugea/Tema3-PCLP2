# Task 4 - Composite Palindrome (35p)

Cosminel, mare fan al [palindroamelor](#palindrom), ar face orice ca sa aiba de-a face cu acestea. <p>
Asadar, se gandeste la urmatoarea problema: fiind dat un vector format din $N$ cuvinte, el vrea sa gaseasca cel mai lung palindrom format din concatenarea unui [subsir](#subsir) de cuvinte, iar in caz de egalitate il va alege pe cel [minim in ordine lexicografica](#ordine-lexicografica).

Intrucat de abia s-a terminat minivacanta de 1 mai, Cosminel e foarte obosit si va cere ajutorul pentru a o rezolva.


#### Palindrom
Numim palindrom un sir de caractere care, citit de la stanga la dreapta sau invers, acesta ramane neschimbat. <p>
Exemplu:
- palindrom: $\text{a}$, $\text{aa}$, $\text{abba}$;
- non-palindrom: $\text{ab}$, $\text{acdc}$.

#### Subsir

Numim subsir al unui vector $V$, indexat de la $0$ si de lungime $N$, o secventa de elemente $[V_{i_0}, V_{i_1}, \ldots, V_{i_{m-1}}]$, unde $i_{k-1} < i_k$ pentru orice $k \in \{1, \ldots, m-1\}$, $i_0 \geq 0$, si $i_{m-1} < N$.

Exemplu: <p>
$V = [\text{Ana}, \text{are}, \text{mere}]$

- Unele subsiruri valide: $[\text{are}]$, $[\text{Ana}, \text{mere}]$, $[\text{Ana}, \text{are}, \text{mere}]$;
- Unele subsiruri invalide: $[\text{mere}, \text{Ana}]$, $[\text{Ana}, \text{mere}, \text{are}]$.


#### Ordine lexicografica

Avand sirul de caractere $A = A_0 A_1 \ldots A_{n-1}$ si $B = B_0 B_1 \ldots B_{m-1}$, numim $A$ mai mic lexicografic decat $B$ daca una din conditii se indeplineste:
- prima pozitie $i$ unde $A_i \neq B_i$, avem $A_i < B_i$;
- $A_0 A_1 \ldots A_{n-1} = B_0 B_1 \ldots B_{n-1}$, $n < m$. <p>

Exemplu: <p>
- $A = abczzz$, $B = abdaaa$ $\Longrightarrow$ $A \lt B$
- $A = a$, $B = aa$ $\Longrightarrow$ $A \lt B$
- $A = aa$, $B = z$ $\Longrightarrow$ $A \lt B$

## Organizare
Task-ul este divizat in doua parti pentru a va modulariza rezolvarea. **Va recomand sa le rezolvati in ordine si sa cititi cu atentie restul enuntului**.<p>
Subtask 1: 5p <p>
Nu exista punctaje partiale la acest subtask, asadar va trebui ca solutia voastra sa treaca toate testele asociate acestuia.<p>
Subtask 2: 30p <p>
Exista punctaje partiale la acest subtask, insa testele sunt impartite in grupuri (😁), iar pentru a lua punctele asociate unui grup va trebui ca toate testele aferente sa fie trecute.

## Subtask 1 - Palindrome Check (5p)
Pentru acest subtask, va trebui sa implementati o functie ce verifica daca un sir de caractere este palindrom.
```c
const int check_palindrome(const char * const str, const int len);
```
Parametrii:
- **str** - sirul de caractere (indexat de la 0);
- **len** - lungimea sirului **str**. 

Functia va intoarce:
- **0**, daca nu este palindrom;
- **1**, daca este palindrom.

## Subtask 2 - Composite Palindrome (30p)
Pentru acest subtask, va trebui sa implementati o functie ce gaseste cel mai lung palindrom, minim lexicografic, obtinut prin concatenarea unui subsir de cuvinte dintr-un vector.
```c
char * const composite_palindrome(const char * const * const strs, const int len);
```
Parametrii:
- **strs** - vectorul de cuvinte (indexat de la 0, la fel si caracterelor in cadrul cuvintelor);
- **len**  - numarul de cuvinte din vector.

Functia va intoarce:
- sirul de caractere cerut. <p>

<span style="color:red">🚨🚨🚨 Sirul de caractere rezultat trebuie sa fie alocat pe <b>heap</b>!!! 🚨🚨🚨</span>



## Constrangeri
- $1 \leq |str_{1,2}| \leq 10 \equiv$ dimensiunea maxima a unui sir este de 10 caractere (subtask 1 + 2);
- $|strs| = 15 \equiv$ numărul de cuvinte din vectorul $strs$ este 15 (subtask 2);
- $str_1 \in \{a, b, \ldots, z\}^* \equiv$ cuvintele sunt formate din caractere apartinand alfabetului englezesc (subtask 1);
- $str_2 \in \{a, b\}^* \equiv$ cuvintele sunt formate doar din caracterele `a` si `b` (subtask 2).


## Folosire si interpretare checker
Checker-ul poate fi folosit individual pentru fiecare subtask, nu inainte de a compila sursele folosind **make**.

- rulati **./checker 1** pentru a verifica primul subtask;
- rulati **./checker 2** pentru a verifica al doilea subtask;
- rulati **./checker** pentru a verifica ambele subtask-uri.

Odata rulat checker-ul:
- veti vedea in consola punctajul obtinut;
- in cazul unei implementari incorecte, in cadrul grupului respectiv vi se afisa numarul primului test
la care output-ul difera de referinta (indexarea este de la 0) pentru a va usura debugging-ul.


