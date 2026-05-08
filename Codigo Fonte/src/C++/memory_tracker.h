#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>

struct MemoryTracker {
    long atual = 0;
    long pico  = 0;

    void alocar(long bytes) {
        atual += bytes;
        pico = std::max(pico, atual);
        std::cout << "PICO ATUAL: " << pico << "\n";
    }

    void liberar(long bytes) {
        atual -= bytes;
    }

    void resetar() {
        atual = 0;
        pico  = 0;
    }

    long pico_kb() const {
        return (pico + 1023) / 1024;
    }
};

// instância global acessível por todos os arquivos
inline MemoryTracker g_mem;
inline bool g_rastreando = false;

inline void* operator new(std::size_t bytes) {
    void* ptr = std::malloc(bytes);
    if (g_rastreando)
        g_mem.alocar((long)bytes);
    return ptr;
}

inline void operator delete(void* ptr, std::size_t bytes) noexcept {
    if (g_rastreando)
        g_mem.liberar((long)bytes);
    std::free(ptr);
}