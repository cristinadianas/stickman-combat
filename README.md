# Stickman Combat


## Descriere

Acest proiect reprezintă un joc de tip fighting game 2D scris în C++ și bazat pe principiile programării orientate pe obiecte. Jocul este de sumă zero (un jucător câștigă, celălalt pierde) conceput pentru doi jucători care se joacă de pe o aceeași tastatura. Cei doi jucători sunt 2 stickmen. :) Referitor la interfața grafică și audio, jocul este animat și conține feedback sonor pe baza bibliotecii SFML. Include caracteristicile de baza ale unui fighting game 2D, și anume implementează mișcările jucătorilor, interacțiunile dintre jucători și interacțiunile dintre jucători și mediu. 


### Game Flow
Sunt generate arena (backgroundul, pereții, pământul, datele despre jucători (numărul de vieți rămase), vântul etc.) și cei doi jucători. Cei doi jucători au un număr limitat de vieți. Un jucător pierde o viață atunci când este atacat cu succes de celălalt jucător sau atunci când este lovit de un bulgăre de zăpadă. După ce unul dintre jucători și-a pierdut toate viețile acesta va fi considerat pierzător, iar oponentul lui va fi considerat câștigător. Ulterior sfârșitului unei runde, există opțiunea de a alege a juca din nou. 


### Demo
https://github.com/user-attachments/assets/826618c8-3522-4255-9b3a-8c6d5a9ca7f2


### Acțiuni posibile ale unui jucător
* Mișcare stânga-dreapta
* Săritură
* Atac
* Se poate feri

#### Keybinds:
* v0.1 
  * Jucătorul 1 (jucătorul din stânga): stânga = A, dreapta = D, sus (sari) = W, jos (ferește-te) = S, atacă = E
  * Jucătorul 2 (jucătorul din dreapta): stânga = H, dreapta = K, sus (sari) = U, jos (ferește-te) = J, atacă = I
  * Ieși din joc = Escape (sau se poate închide fereastra)
  * Joacă din nou (valabil la sfârșitul unui joc) = Space (sau se poate apăsa butonul de pe ecran marcat "Replay")

* v0.2.1 , v0.2.2, v0.3, v0.4.1
  * Jucătorul 1 (jucătorul din stânga): stânga = A, dreapta = D, sus (sari) = W, jos (ferește-te) = S, atacă = LShift
  * Jucătorul 2 (jucătorul din dreapta): stânga = K, dreapta = Semicolon (;), sus (sari) = O, jos (ferește-te) = K, atacă = RShift
 
* în plus, pentru v0.4.1
  * Ieși din joc = Escape (sau se poate închide fereastra)
  * Joacă din nou (valabil la sfârșitul unui joc) = Space (sau se poate apăsa butonul de pe ecran marcat "Replay")


### Interacțiunea dintre jucători
* Detectarea coliziunii: Jucătorii nu se pot suprapune, se împing unul pe celălalt
* Atac, în urma căruia se vor întâmpla următoarele:
   * Faza 0: Nu atacă. Este liber să se miște.
   * Faza 1: Atacul este inițializat. Jucătorul rămâne blocat în poziția în care a inițializat atacul. În această perioadă, celălalt jucătoare se poate feri de atac.
   * Faza 2: Atacul este executat. Jucătorul rămâne în continuare blocat în poziția în care a inițializat atacul. Acum se verifică dacă celălalt jucător va fi lovit (dacă este în range-ul atacului și nu se ferește).
   * Faza 3: Cooldown. Acum jucătorul este din nou liber să se miște, însă nu și să atace.
* Se poate feri de un atac din partea altui jucător


### Interacțiunea dintre jucători și mediu
* Detectarea coliziunii dintre jucători și arena: jucătorii se mișcă pe pământ și jucătorii nu se pot duce off screen datorită pereților. Atât pământul, cât și pereții sunt transparenți din motive estetice (avem deja imagine de background).
* Inamici: Bulgări de zăpadă. Un bulgăre de zăpadă care traversează secțiunea inferioară a ecranului de la stânga la dreapta sau de la dreapta la stânga (determinat în mod aleatoriu) apare pe ecran o dată la un interval fix de timp. La detectarea coliziunii cu un jucător, acel jucător va pierde o viață. Coliziunea nu va fi rezolvată (adică bulgărele de zăpadă și jucătorul se pot suprapune). În plus, jucătorul lovit nu se va putea mișca și va fi vulnerabil pentru o perioadă de timp. Jucătorii trebuie să sară peste acești inamici.
* Vântul este inofensiv. Scopul lui este pur și simplu de a crește puțin dificultatea jocului prin adăugarea unei distracții de la pericolele reale.


### Next Steps: To Do
* Crearea unui meniu pentru configurarea jucătorilor (spre exemplu, numărul de vieți) sau configurarea mediului (spre exemplu, alegerea imaginii de fundal)
* Crearea opțiunii de a citi inputul dintr-un fișier (tastatura.txt) folosind Command Design Pattern
* Micșorarea collision box-ului pentru majoritatea obiectelor
* Separarea logicii din clasa Player
* Animații (mai interesante) pentru atac și lovitură


## Cerințe

### Important!
Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar în folder-ul `generated`.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

O cerință nu se consideră îndeplinită dacă este realizată doar ca o serie de apeluri proxy către cod generat.

### Cerințe modele de limbaj la nivel de semestru
- [ ] minim o funcționalitate majoritar doar cu LLM
- [ ] minim 2-3 funcționalități ~50% voi, ~50% LLM-ul
- [ ] minim 2-3 funcționalități suficient de complicate pe care un LLM nu le poate implementa

### Tema 0

- [ ] Nume proiect (poate fi schimbat ulterior)
- [ ] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [ ] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [ ] constructori de inițializare cu parametri
- [ ] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [ ] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [ ] cât mai multe `const` (unde este cazul)
- [ ] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [ ] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.

3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- https://www.youtube.com/watch?v=axIgxBQVBg0&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9 (SFML 2.4 For Beginners)
- Imaginile folosite au fost generate folosind ChatGPT, cu următoarele excepții: animația pentru stickman (player_texture.png) a fost creată în Pivot Animator 5, animația pentru bulgării de zăpadă (snowball_texture.png) a fost preluata de aici: https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?page-name=Animated-snowball-game-projectile&item=1k5h5u4t2r9g0o8q6a, iar animația pentru vânt (wind_texture.png) a fost preluat de aici: https://loading.io/icon/to8zzb.
- Fișierele audio au fost preluate de aici: https://pixabay.com/sound-effects/
