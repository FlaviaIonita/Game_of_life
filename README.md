# 🧬 Game of Life - Proiect în C

Acest proiect implementează o versiune extinsă a „Game of Life” creat de John Conway, în cadrul cursului de *Proiectarea algoritmilor*. Este scris în C și integrează concepte avansate precum stive, liste înlănțuite, arbori binari și grafuri.
---

## 📁 Structura fișierelor

- `main.c` – Fișierul principal de execuție.
- `task1.c`, `task2.c`, `task3.c`, `task4.c`, `task_bonus.c` – Fiecare fișier conține logica unui task diferit.
- `utils.c/.h` – Funcții auxiliare (inițializare, eliberare memorie etc.).
- `Makefile` – Permite compilarea rapidă.
- `README.md` – Documentația proiectului.
- `tests/` – Conține fișiere de test și cazuri de intrare/ieșire.

---

## 🧩 Task-uri

### ✅ Task 1 – Inițializare și Rulare Simplă
- Se citește o matrice binară (0 sau 1) ce reprezintă tabla de joc.
- Se simulează **T** iterații ale jocului.
- Regulile Game of Life sunt aplicate la fiecare pas:
  - o celulă vie cu <2 sau >3 vecini moare;
  - o celulă moartă cu exact 3 vecini devine vie.

### ✅ Task 2 – Detectarea Formelor în Arbore
- Se construiește un **arbore binar de căutare (BST)** cu forme (glider, beacon, blinker etc.).
- Se determină dacă o configurație dată este o subformă a alteia.
- Se afișează formele în ordine crescătoare și în preordine.

### ✅ Task 3 – Aranjamente cu Forme Multiple
- Se citește o matrice și o listă de forme.
- Se verifică dacă formele pot fi așezate pe tablă într-o anumită configurație.
- Se simulează câteva generații și se afișează rezultatul.

### ✅ Task 4 – Graful Configurațiilor
- Fiecare configurație este un nod într-un **graf**.
- Muchiile leagă configurații ce pot apărea una după alta.
- Se folosește **DFS** pentru a căuta cicluri și componente conexe.
- Se identifică noduri de plecare care pot duce la o configurație țintă.

### 🎁 Bonus – Funcționalitate Undo
- Se poate reveni la starea anterioară a jocului.
- Implementat cu ajutorul unei **stive**.

---

## 🛠️ Compilare

Pentru a compila proiectul:

```bash
make
```

Aceasta va crea un executabil numit `game_of_life`.

---

## ▶️ Rulare

```bash
./game_of_life <task_number> <input_file> <output_file>
```

**Exemple:**
```bash
./game_of_life 1 tests/input1.txt output1.txt
./game_of_life 4 tests/input4.txt output4.txt
```

---

## ✅ Dependențe

- Compilator C (e.g. `gcc`)
- Make (`make`)

---

## 🧹 Curățare

Pentru a șterge executabilul:

```bash
make clean
```

---

## 📚 Resurse

- [Wikipedia - Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- [Structuri de date - Arbori, Grafuri](https://www.geeksforgeeks.org/data-structures/)
