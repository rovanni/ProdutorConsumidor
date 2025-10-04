# Produtor-Consumidor com Threads, Mutex e Semáforos

**Autor:** Luciano Rovanni

## Descrição

Este projeto implementa o clássico problema do **Produtor-Consumidor** com recursos modernos do C++, aproveitando:
- **std::thread** para execução paralela
- **std::mutex** para exclusão mútua do buffer
- **std::counting_semaphore** para controle dos itens/slots disponíveis
- **std::queue** como buffer compartilhado
- **std::lock_guard** para gerenciamento automático de locks
- **std::this_thread::sleep_for** para simulação de tempo de produção/consumo

O objetivo é simular, concorrentemente e de forma segura, um cenário onde múltiplos produtores geram itens e os inserem num buffer, enquanto múltiplos consumidores removem e processam esses itens. Todos os acessos ao buffer são protegidos para evitar condições de corrida e as restrições de capacidade são respeitadas com ajuda de semáforos.

## Funcionamento

- **Produtores:** Geram itens e inserem no buffer, aguardando se não houver espaço disponível.
- **Consumidores:** Retiram itens do buffer, aguardando caso o buffer esteja vazio.
- **Mutex:** Protege o acesso simultâneo ao buffer compartilhado.
- **Semáforos:** Garantem a sincronização do número de itens e espaços disponíveis no buffer circular.

## Recursos e Tecnologias

- `std::thread`             → Execução paralela de produtores e consumidores.
- `std::mutex`              → Exclusão mútua no buffer/fila.
- `std::counting_semaphore` → Controle de espaços livres/itens disponíveis.
- `std::queue`              → Buffer compartilhado de itens.
- `std::lock_guard`         → Lock automático com escopo garantido.
- `std::this_thread::sleep_for` → Simulação realista de tempo de processamento.

## Compilação

É necessário um compilador com suporte ao padrão C++20 ou superior.

g++ -std=c++20 -pthread produtor_consumidor.cpp -o prodcons


## Execução

Após a compilação, execute o binário gerado:


## Observações

- O número de produtores, consumidores e o tamanho do buffer podem ser ajustados diretamente no código.
- O programa ilustra conceitos importantes de programação concorrente: sincronização, exclusão mútua e uso eficiente de threads modernos.
- Ideal para fins didáticos ou como base para implementações mais complexas.

---

Sinta-se à vontade para contribuir ou reportar melhorias via issues ou pull requests!

