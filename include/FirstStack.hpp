//
// Created by lamp on 08.12.2020.
//

#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP

#include <memory>
#include <string>
#include <iostream>

using std::string;

template <typename T>
class FirstStack {
 private:
  struct Cell {
    std::unique_ptr<Cell> nextCell;
    T value;
    explicit Cell(std::unique_ptr<Cell> cell = nullptr, T val = T())
        : nextCell(std::move(cell)), value(val) {}
  };
  std::unique_ptr<Cell> headCell;
  size_t length;
 public:
  FirstStack(FirstStack&) = delete;
  FirstStack& operator=(FirstStack&) = delete;

  FirstStack()
      : headCell(std::unique_ptr<Cell>(new Cell(nullptr))), length(0) {}

  FirstStack(std::initializer_list<T> values) {
    headCell = std::unique_ptr<Cell>(new Cell(nullptr));
    length = 0;
    for (const auto& value : values) {
      push(value);
    }
  }

  FirstStack(FirstStack&& stack) noexcept
      : headCell(std::move(stack.headCell)),
        length(std::move(stack.length)){};

  FirstStack& operator=(FirstStack&& stack) noexcept {
      headCell = std::move(stack.headCell);
      length = std::move(stack.length);
      return *this;
  };

  void push(T&& value) {
    headCell =
        std::move(std::make_unique<Cell>(Cell(
            std::move(headCell),
            std::move(value))));
    length++;
  }
  void push(const T& value) {
    headCell =
        std::move(std::make_unique<Cell>(Cell(
            std::move(headCell),
            value)));
    length++;
  };

  inline void pop(){
      headCell = std::move(headCell->nextCell);
      length--;
  };
  inline auto Length() -> size_t {
      return length;
  };

  inline auto head() const -> const T&{
      return (headCell->value);
  };

};

#endif  // TEMPLATE_STACK_HPP
