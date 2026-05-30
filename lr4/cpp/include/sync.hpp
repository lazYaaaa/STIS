// Синхронизация временных потоков: простая реализация
#pragma once

#include <vector>
#include <optional>
#include <memory>
#include "types.hpp"
#include "sequence.hpp"
#include "vector_sequence.hpp"

namespace lr4 {

// Синхронизирует n упорядоченных по времени последовательностей Event<T>
// Использует первый поток как справочный: для каждого его события с отметкой t_ref
// ищутся в других потоках первые события, попадающие в окно [t_ref, t_ref+tau].
// Возвращается материализованная последовательность пар: (t_ref, vector<optional<T>>).
template<typename T>
std::shared_ptr<Sequence<std::pair<double, std::vector<std::optional<T>>>>>
SynchronizeStreams(const std::vector<std::shared_ptr<Sequence<Event<T>>>>& streams, double tau) {
    if (streams.empty()) return std::make_shared<VectorSequence<std::pair<double, std::vector<std::optional<T>>>>>(std::vector<std::pair<double, std::vector<std::optional<T>>>>{});
    std::vector<std::pair<double, std::vector<std::optional<T>>>> out;
    auto ref = streams[0];
    size_t i = 0;
    while (true) {
        try {
            auto ev = ref->Get(i);
            double t_ref = ev.t;
            std::vector<std::optional<T>> row;
            // значение справочного потока
            row.push_back(ev.value);
            // для каждого вспомогательного потока ищем первое событие в окне
            for (size_t s = 1; s < streams.size(); ++s) {
                auto seq = streams[s];
                bool found = false;
                size_t j = 0;
                while (true) {
                    try {
                        auto e2 = seq->Get(j);
                        if (e2.t >= t_ref && e2.t <= t_ref + tau) { row.push_back(e2.value); found = true; break; }
                        if (e2.t > t_ref + tau) break;
                        ++j;
                    } catch (...) { break; }
                }
                if (!found) row.push_back(std::nullopt);
            }
            out.emplace_back(t_ref, row);
            ++i;
        } catch (...) {
            break;
        }
    }
    return std::make_shared<VectorSequence<std::pair<double, std::vector<std::optional<T>>>>>(std::move(out));
}

}
