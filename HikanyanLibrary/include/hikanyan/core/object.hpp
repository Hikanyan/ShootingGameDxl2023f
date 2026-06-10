#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

namespace hikanyan {

class Object {
public:
    using Id = std::uint64_t;

    Object();
    explicit Object(std::string name);
    virtual ~Object() = default;

    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&) noexcept = default;
    Object& operator=(Object&&) noexcept = default;

    [[nodiscard]] Id id() const noexcept { return id_; }
    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    void set_name(std::string name) { name_ = std::move(name); }

    template <typename T, typename... Args>
    static std::shared_ptr<T> instantiate(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

private:
    static Id next_id();

    Id id_;
    std::string name_{"DefaultName"};
};

} // namespace hikanyan
