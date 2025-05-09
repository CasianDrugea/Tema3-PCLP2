# Task 2 - Operatii (25p)

Cosminel, mare fan al literaturii moderne, vrea sa separe un text filozofic in cuvinte dupa niste delimitatori si, dupa aceea, sa sorteze aceste cuvinte folosind functia qsort. Sortarea se va face intai dupa lungimea cuvintelor si in cazul egalitatii se va sorta lexicografic. <br>

Va trebui sa implementati 2 functii cu semnaturile "`void get_words(char *s, char **words, int number_of_words);`" si "`void sort(char **words, int number_of_words, int size);`" din fisierul task3.asm. Functia get_words primeste ca parametri textul, un vector de stringuri in care va trebui sa salvati cuvintele pe care ulterior le veti sorta si numarul de cuvinte. Functia sort va primi vectorul de cuvinte, numarul de cuvinte si dimensiunea unui cuvant.

## Precizări:
- lungimea textului este mai mica decat 1000;
- vectorul de cuvinte va avea maxim 100 de cuvine a 100 de caractere fiecare;
- delimitatorii pe care trebuie sa ii luati in calcul sunt: " ,.\n"
- nu aveti voie sa folositi alta metoda de sortare in afara de qsort. In cazul in care veti folosi alta metoda punctajul pe acest task se va pierde.

## Exemplu
```
number_of_words: 9
s: "Ana are 27 de mere, si 32 de pere."
dupa apelul get_words: words = ["Ana", "are", "27", "de", "mere", "si", "32", "de", "pere"]
dupa apelul sort: words = ["27", "32", "de", "de", "si", "Ana", "are", "mere", "pere"]
```

## Hint:
- pentru mai multe informatii despre qsort puteti accesa linkul: https://man7.org/linux/man-pages/man3/qsort.3.html
