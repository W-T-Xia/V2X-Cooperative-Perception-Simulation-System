#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>

template<typename T>
class SensorContainer {
public:
    void add(T item) {
        auto it = std::find_if(container_.begin(), container_.end(),
            [&](const T& elem) { return elem->getId() == item->getId(); });
        if (it != container_.end()) {
            throw std::runtime_error("Duplicate ID: " + item->getId());
        }
        container_.push_back(item);
    }

    const T& findById(const std::string& id) const {
        auto it = std::find_if(...);
        if (it == container_.end()) throw std::runtime_error(...);
        return *it;
    }

    void sortBy(std::function<bool(const T&, const T&)> comp) {
        std::sort(container_.begin(), container_.end(), comp);
    }

    size_t size() const { return container_.size(); }
    const std::vector<T>& getAll() const { return container_; }

private:
    std::vector<T> container_;
};