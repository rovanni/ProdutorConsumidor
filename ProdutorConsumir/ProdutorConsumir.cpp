#include<iostream>
#include<string>
#include<thread>
#include<chrono>
#include<mutex>
#include<semaphore>
#include<queue>
#include<condition_variable>
using namespace std;
using namespace chrono;
using namespace this_thread;

mutex mtx;
counting_semaphore<10> items(0);
counting_semaphore<10> espaco(10);
queue<int> buffer;

void produtor(const int id) {
	// Aguarda um item ser consumido
	// Possui espaco?
	espaco.acquire();
	{
		// Acessar o buffer
		lock_guard<mutex> lock(mtx);
		// Produz
		buffer.push(1);
		cout << "Produtor " << id << " esta produzindo..." << endl;
		sleep_for(milliseconds(100));
	}
	// Sinaliza que existe algo no buffer
	items.release();
}

void consumidor(int id) {
	// Aguarda um item ser produzido
	// Possui itens produzidos?
	items.acquire();
	{
		lock_guard<mutex> lock(mtx);
		auto item = buffer.front();
		buffer.pop();
		cout << "Consumidor " << id << " esta Consumindo..." << endl;
		sleep_for(milliseconds(100));
	}
	espaco.release();
}

int main() {
	vector<thread> threads;
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(produtor, i + 1);
	}
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(consumidor, i + 1);
	}
	for (auto& t : threads) t.join();
	return 0;
}
