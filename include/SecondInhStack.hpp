//
// Created by lamp on 15.12.2020.
//

#ifndef STACK_SECONDINHSTACK_HPP
#define STACK_SECONDINHSTACK_HPP

#include <Stack.hpp>

template <typename T>
class SecondStack: public Stack<T> {

  using Stack<T>::length;

  struct Cell {
    std::unique_ptr<Cell> nextCell;
    T value;
    explicit Cell(std::unique_ptr<Cell> cell = nullptr, T&& val = T())
        : nextCell{std::move(cell)} {
      value = std::forward<T>(val);
    }
  };

  std::unique_ptr<Cell> headCell;

 public:
  inline auto pop() -> T {
    T temp = std::move(headCell->value);
    headCell = std::move(headCell->nextCell);
    length--;
    return temp;
  }

  template <typename ...Args>
  void push_emplace(Args&&... args) {
    auto newValue = T(std::forward<Args>(args)...);
    auto newHead = std::make_unique<Cell>(
        Cell(
            std::move(headCell),
            std::move(newValue)
        ));
    headCell = std::move(newHead);
    length++;
  }

  void push(T&& value) override {
    auto newHead = std::make_unique<Cell>(
        std::move(headCell),
        std::move(value));
    headCell = std::move(newHead);
    length++;
  }

  inline auto head() const -> const T& override{
    return headCell->value;
  }

  SecondStack() {
    headCell = std::unique_ptr<Cell>
        (new Cell(nullptr));
    length = 0;
  }

  SecondStack(SecondStack&& stack) noexcept
  {
    *this = std::move(stack);
  }

  SecondStack& operator=(SecondStack&& stack) noexcept{
    headCell = std::move(stack.headCell);
    length = std::move(stack.length);
    return *this;
  };

  ~SecondStack() = default;
};

#endif  // STACK_SECONDINHSTACK_HPP
