//
// Created by lamp on 08.12.2020.
//

#ifndef STACK_SECONDSTAC_HPP
#define STACK_SECONDSTAC_HPP
#include <memory>
#include <string>
#include <iostream>

using std::string;

template <typename T>
class SecondStack {
 public:
  struct Cell {
    std::unique_ptr<Cell> nextCell;
    T value;
    explicit Cell(T&& val = T(), std::unique_ptr<Cell> cell = nullptr)
        : nextCell(std::move(cell)){
      value = std::forward<T>(val);
    }
  };
 private:
  std::unique_ptr<Cell> headCell;
  size_t length;
 public:
  SecondStack(SecondStack&) = delete;
  SecondStack& operator=(SecondStack&) = delete;

  SecondStack()
      : headCell(std::unique_ptr<Cell>(new Cell())), length(0){}

  SecondStack(SecondStack&& stack) noexcept
  : headCell(std::move(stack.headCell)),
  length(std::move(stack.length)){}
  SecondStack& operator=(SecondStack&& stack) noexcept {
    headCell = std::move(stack.headCell);
    length = std::move(stack.length);
    return *this;
  }

  template <typename ...Args>
  void push_emplace(Args&&... args) {
    auto newValue = T(std::forward<Args>(args)...);
    auto newHead = std::make_unique<Cell>(
        Cell(
        std::move(newValue),
        std::move(headCell)
        ));
    headCell = std::move(newHead);
    length++;
  }
  void push_emplace(T&& value){
    auto newHead = std::make_unique<Cell>(
        Cell(
            std::forward<T>(value),
            std::move(headCell)
            )
        );
    headCell = std::move(newHead);
    length++;
  }
  inline auto head() const -> const T& {
    return (headCell->value);
  }
  inline auto pop() -> T {
    T temp = std::move(headCell->value);
    headCell = std::move(headCell->nextCell);
    length--;
    return temp;
  }
  [[nodiscard]] inline auto Length() const -> size_t {
    return length;
  }
};
#endif  // STACK_SECONDSTAC_HPP
