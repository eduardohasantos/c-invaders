# 🛸 C Invaders

**C Invaders** — jogo 2D em **C** rodando no **terminal** (linha de comando).  
Inspiração: *Space Invaders*. Projeto acadêmico para demonstrar conceitos de C através de um jogo funcional.

---

## 🎮 Visão geral
Controle uma nave na base e destrua as ondas de invasores antes que lhe acertem. Jogo renderizado em modo texto usando a biblioteca **cli-lib**.

---

## ✅ Requisitos implementados
- **Structs** para entidades (player, enemy, projectile, game state).  
- **Ponteiros** para manipulação de dados e passagem eficiente de estruturas.  
- **Alocação dinâmica** (malloc/free) para entidades criadas em tempo de execução.  
- **Listas encadeadas** para gerenciar projéteis e inimigos ativos.  
- **Matrizes** para representar o campo de jogo.  
- **Leitura/escrita em arquivo** para salvar top scores (`assets/scores.txt`).  

---

## ⚙️ Requisitos do ambiente
- Linux ou macOS (WSL/VM no Windows).  
- GCC (ou compilador compatível).  
- Biblioteca **cli-lib** disponível (submódulo ou instalada localmente).

---

## 🏗️ Compilação e Execução
Abaixo está a documentação ensinando como compilar e rodar o jogo em todas as plataformas.

[![Abrir no Google Docs](https://img.shields.io/badge/Google%20Docs-Acessar-blue?logo=google-docs&logoColor=white)](https://docs.google.com/document/d/1mG1EGNAmWWgenAhzveU3yGY-b2QAjuM1PTyladAfXYY/edit?usp=sharing)

---

## ⌨️ Controles

* `←` / `→` — mover a nave  
* `Espaço` — atirar  
* `p` — pausar/retomar  
* `q` — sair do jogo  

---

## 📈 Sistema de pontuação

* Pontuação acumulada por inimigo destruído.  
* `highscores.txt` mantém os top scores (lido/escrito ao finalizar partida).  

---

## 🔎 Destaques de implementação (breve)

* Lista encadeada para projéteis: adição no fim, remoção ao colidir/fora da tela.  
* Matriz do mapa usada para detectar colisões e renderizar a tela em buffer.  
* Módulo de I/O para abstrair leitura do teclado e escrita em arquivo.  

---

## 👨‍💻 Membros

* **Eduardo Henrique**  
* **Tiago Abrãao**  
* **Lucas Ramon**  

---

## 📚 Referências

* Biblioteca usada: [https://github.com/tgfb/cli-lib](https://github.com/tgfb/cli-lib)

---
## 📷Vídeo do jogo
https://youtu.be/l-_knaUofXs
