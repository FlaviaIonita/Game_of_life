# 🧬 Game of Life - Proiect în C

Acest proiect implementează o versiune extinsă a „Game of Life” creat de John Conway, în cadrul cursului de *Proiectarea algoritmilor*. Este scris în C și integrează concepte avansate precum stive, liste înlănțuite, arbori binari și grafuri.

---

## 📁 Structura fișierelor

- `game_of_life.c` – Fișierul principal de execuție.
- `Makefile` – Permite compilarea rapidă.
- `README.md` – Documentația proiectului.
- `InputData` – Conține fișiere de teste de intrare
- `RefData` - Conține fișierele de iesire pentru inputurile date

---

## 🧠 Ce face programul?

Programul simulează evoluția unei populații de celule pe o grilă 2D conform unor reguli precise. În funcție de `task-ul` selectat, se aplică diverse operații:

- **Task 1:** Simulează regulile clasice Game of Life și afișează fiecare generație.
- **Task 2:** Păstrează doar modificările dintre generații într-o stivă de liste.
- **Task 3:** Construiește un arbore binar de evoluții aplicând două seturi de reguli (original și alternativă).
- **Task 4:** Caută cel mai lung lanț Hamiltonian în grafuri construite din celulele vii ale fiecărei generații.
- **Task 5 (Bonus):** Permite operația de *undo*, refăcând starea inițială pe baza stivei de diferențe.

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
