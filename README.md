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
## ▶️ Cum se utilizează

### 🔧 Cerințe
- Compilator C (de ex. `gcc`)
- Un sistem Unix-like (Linux/macOS) sau Windows cu suport pentru terminal

### 🛠️ Compilare
```bash
gcc game_of_life.c -o game_of_life
```

### 📥 Format fișier input
```
T
N M
K
<matrix of NxM characters with 'X' for alive and '+' for dead>
```

Exemplu:
```
1
6 6
2
++++++
++++X+
++XX++
+++X++
+X++++
++++++
```

### ▶️ Rulare
```bash
./game_of_life input.txt output.txt
```

---
## 🧹 Curățare

Pentru a șterge executabilul:

```bash
make clean
```

---
## 📚 Structura codului

### 🗂 Fișier principal
- `game_of_life.c` – Conține implementarea completă a tuturor task-urilor.

### 📌 Structuri de date cheie
- `cell`: listă înlănțuită cu coordonatele celulelor care se schimbă
- `generation`: stivă de generații; fiecare element e o listă de celule modificate
- `Node`: nod în arborele binar pentru task 3 și 4
- `graph`: structură pentru grafurile construite din celulele vii

## 🧩 Descriere funcții

### 🔹 Funcții pentru liste și stive (Task 2 & Bonus)
- `create_cell(int l, int c)` – Creează și returnează un pointer către o celulă cu coordonatele date.
- `create_generation(int nr)` – Creează o generație nouă care va stoca modificările unei iterații.
- `push_list_sc(cell** head, int l, int c)` – Adaugă o celulă sortat într-o listă (după linie și coloană).
- `push_generation(generation** top, int nr, cell* list_ch)` – Adaugă o generație în stiva de generații.
- `free_generations(generation* top)` – Eliberează întreaga stivă de generații.
- `print_generation(FILE* output_file, generation* top)` – Scrie în fișier generațiile și modificările celulare.

### 🔹 Funcții pentru manipularea grilei
- `create_table(int N, int M)` – Alocă memorie pentru o grilă NxM de celule (`char**`).
- `free_memory_table(char** table, int N)` – Eliberează memoria grilei.
- `copy_table(char** t1, int N, int M)` – Creează și returnează o copie a grilei.
- `print_table(FILE* output_file, char** table, int N, int M)` – Scrie grila într-un fișier.
- `countAliveNeighbors(char** table, int N, int M, int i, int j)` – Returnează numărul de vecini vii ai celulei `(i, j)`.

### 🔹 Funcții pentru reguli de joc
- `game_of_life_task1(char** table, int N, int M)` – Aplică regulile clasice Game of Life pe o grilă.
- `game_of_life_task2(char** table, int N, int M, generation** top, int gen_nr)` – Aplica regulile și salvează modificările în stivă.
- `rule_b(...)` – Aplică regula alternativă: orice celulă cu exact doi vecini vii devine vie.

### 🔹 Funcții pentru arbori binari (Task 3 & 4)
- `game_of_life_task3(...)` – Construiește un arbore binar de generații, stânga (regula B), dreapta (regula clasică).
- `preorder_write(FILE* output_file, Node* root, int N, int M)` – Parcurgere în preordine pentru a scrie grilele din arbore.
- `free_tree(Node* root, int N)` – Eliberează recursiv arborele binar.

### 🔹 Funcții pentru grafuri și Hamiltonian (Task 4)
- `neighbors(cell_coord x, cell_coord y)` – Verifică dacă două celule sunt vecine (inclusiv diagonal).
- `build_graph(char** table, int N, int M)` – Construiește un graf: celule vii ca vârfuri, vecinătate ca muchii.
- `free_graph(graph* g)` – Eliberează memoria grafului.
- `dfs(...)` – Caută recursiv în adâncime cel mai lung lanț Hamiltonian dintr-o componentă conexă.
- `find_longest_path(FILE* output_file, graph* g)` – Caută cel mai lung lanț și îl scrie în fișier.
- `preorder_longest_path(Node* root, int N, int M, FILE* output_file)` – Aplică `find_longest_path` pentru fiecare nod din arbore.

### 🔹 Funcție pentru bonus (undo)
- `undo_generations(char** table, int N, int M, generation* top)` – Inversează modificările salvate în stivă pentru a obține starea inițială.

### 🔹 Funcție principală
- `main(int argc, const char* argv[])` – Punctul de intrare al programului. Alege ce task să execute în funcție de valoarea `T` din input.
---

## 🔄 Output

În funcție de task:
- **Task 1:** Matricele generațiilor succesive
- **Task 2:** Listele de modificări per generație
- **Task 3:** Matricea fiecărui nod din arbore (preorder)
- **Task 4:** Lungimea și traseul lanțului Hamiltonian
- **Task 5:** Matricea inițială reconstruită prin undo

---

