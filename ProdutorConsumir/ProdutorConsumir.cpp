/*
------------------------------------------------------------
    Produtor-Consumidor com Threads, Mutex e Semáforos
    Autor: Luciano Rovanni
    Descrição:
      Este programa implementa o problema clássico do
      Produtor-Consumidor utilizando recursos modernos de
      C++ (threads, mutex, semáforos e fila). O objetivo
      é simular a produção e o consumo de itens de forma
      concorrente, respeitando as restrições de capacidade
      do buffer.

      - Produtores geram itens e inserem no buffer (queue),
        aguardando espaço disponível.
      - Consumidores removem itens do buffer, aguardando que
        haja algo para consumir.
      - O acesso ao buffer é protegido com mutex para evitar
        condições de corrida.
      - Os semáforos controlam a quantidade de itens e de
        espaços disponíveis no buffer circular.

      O código cria múltiplas threads produtoras e consumidoras,
      que atuam em paralelo de modo sincronizado e seguro.

      Principais recursos:
        - std::thread          → execução paralela
        - std::mutex           → exclusão mútua no buffer
        - std::counting_semaphore → controle de espaços/itens
        - std::queue           → buffer compartilhado
        - std::lock_guard      → gerenciamento de lock autômato
        - std::sleep_for       → simulação de tempo

      Para compilar (C++20+):
        g++ -std=c++20 -pthread produtor_consumidor.cpp -o prodcons

------------------------------------------------------------
*/
// Inclui a biblioteca padrão para operações de entrada e saída (cout, cin).
#include<iostream>

// Inclui suporte ao tipo de string, útil para manipular textos.
#include<string>

// Permite uso de threads (execução simultânea), essencial para implementar produtor e consumidor.
#include<thread>

// Oferece utilitários para manipular tempo (intervalos, temporizações).
#include<chrono>

// Traz mecanismos para proteção de recursos compartilhados entre threads, como o mutex.
#include<mutex>

// Permite uso de semáforos (controle de acesso por número de permissões), útil para controlar o buffer.
#include<semaphore>

// Estrutura de dados fila (queue), usada como buffer entre produtor e consumidor.
#include<queue>

// Disponibiliza variáveis de condição (não utilizadas neste código, pode ser removido).
#include<condition_variable>

// Facilita o uso dos namespaces padrão para simplificar o código abaixo.
using namespace std;
using namespace chrono;
using namespace this_thread;

// Cria um mutex para garantir que só uma thread acesse o buffer por vez.
mutex mtx;

// Semáforo que controla quantos itens há no buffer. Começa com 0 (nenhum produzido).
counting_semaphore<10> items(0);

// Semáforo que controla o espaço disponível no buffer. Começa com 10 (buffer vazio).
counting_semaphore<10> espaco(10);

// Fila (queue) usada como buffer, onde produtores inserem e consumidores removem itens.
queue<int> buffer;

// Função executada pelo produtor, recebe um id para identificação.
void produtor(const int id) {
    // Aguarda até haver espaço disponível (semáforo espaco).
    espaco.acquire();
    {
        // Garante acesso exclusivo ao buffer usando lock_guard e o mutex.
        lock_guard<mutex> lock(mtx);
        // Insere o item produzido no buffer.
        buffer.push(1);
        cout << "Produtor " << id << " esta produzindo..." << endl;
        // Simula tempo de produção.
        sleep_for(milliseconds(100));
    }
    // Sinaliza que agora há um item produzido no buffer (libera semáforo items).
    items.release();
}

// Função executada pelo consumidor, recebe um id para identificação.
void consumidor(int id) {
    // Aguarda até haver um item disponível para consumir (semáforo items).
    items.acquire();
    {
        // Garante acesso exclusivo ao buffer usando lock_guard e o mutex.
        lock_guard<mutex> lock(mtx);
        // Remove o item do buffer para consumir.
        auto item = buffer.front();
        buffer.pop();
        cout << "Consumidor " << id << " esta Consumindo..." << endl;
        // Simula tempo de consumo.
        sleep_for(milliseconds(100));
    }
    // Sinaliza que agora há espaço livre no buffer (libera semáforo espaco).
    espaco.release();
}

// Função principal do programa.
int main() {
    // Vetor para armazenar as threads criadas.
    vector<thread> threads;
    // Cria 10 threads produtoras.
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(produtor, i + 1);
    }
    // Cria 10 threads consumidoras.
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(consumidor, i + 1);
    }
    // Aguarda finalização de todas as threads.
    for (auto& t : threads) t.join();
    return 0;
}
