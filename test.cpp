#include <cstdint>
#include <vector>
#include <utility>
#include <iostream>

enum class OpKind { WriteEax, ReadEax, WriteEbx, ReadEbx };

struct Operation {
    OpKind kind;
    uint32_t value;            // para Write*, guarda o valor a escrever
};

class RegisterBatch {
    std::vector<Operation> ops;
public:
    // coleta operação de escrita em EAX
    void write_eax(uint32_t v) { ops.push_back({OpKind::WriteEax, v}); }

    // coleta operação de leitura de EAX
    void read_eax()         { ops.push_back({OpKind::ReadEax, 0}); }

    // mesma coisa para EBX
    void write_ebx(uint32_t v) { ops.push_back({OpKind::WriteEbx, v}); }
    void read_ebx()            { ops.push_back({OpKind::ReadEbx, 0}); }

    // executa todas as operações na ordem e retorna um vetor com os valores lidos
    std::vector<uint32_t> execute() {
        std::vector<uint32_t> results;
        for (auto &op : ops) {
            uint32_t tmp;
            switch (op.kind) {
                case OpKind::WriteEax:
                    asm volatile("movl %0, %%eax" : : "r"(op.value) : "eax");
                    break;
                case OpKind::ReadEax:
                    asm volatile("movl %%eax, %0" : "=r"(tmp) : : "eax");
                    results.push_back(tmp);
                    break;
                case OpKind::WriteEbx:
                    asm volatile("movl %0, %%ebx" : : "r"(op.value) : "ebx");
                    break;
                case OpKind::ReadEbx:
                    asm volatile("movl %%ebx, %0" : "=r"(tmp) : : "ebx");
                    results.push_back(tmp);
                    break;
            }
        }
        ops.clear();  // limpa para reuse
        return results;
    }
};

int main() {
    RegisterBatch batch;

    // “declara” operações
    batch.write_eax(100);
    batch.write_ebx(200);
    batch.read_eax();    // irá capturar o valor atualmente em EAX (depois de escrever 100)
    batch.read_ebx();    // idem para EBX

    // executa tudo de uma vez
    auto results = batch.execute();

    // imprime somente as leituras, na ordem que foram declaradas
    std::cout << "EAX lido: " << results[0] << "\n";
    std::cout << "EBX lido: " << results[1] << "\n";

    return 0;
}