//
// Created by lamp on 15.12.2020.
//

#ifndef STACK_FIRSTINHSTACK_HPP
#define STACK_FIRSTINHSTACK_HPP

#include <Stack.hpp>

template <typename T>
class FirstStack: public Stack<T> {

  using Stack<T>::length;

  struct Cell {
    std::unique_ptr<Cell> nextCell;
    T value;
    explicit Cell(std::unique_ptr<Cell> cell = nullptr, T val = T())
        : nextCell{std::move(cell)}, value(val) {}
  };

  std::unique_ptr<Cell> headCell;

 public:
  inline void pop(){
    headCell = std::move(headCell->nextCell);
    length--;
  };

  void push(const T& value) {
    headCell = std::make_unique<Cell>(
            std::move(headCell),
            value
        );
    length++;
  };

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

  FirstStack() {
    headCell = std::unique_ptr<Cell>
        (new Cell(nullptr));
    length = 0;
  }

  FirstStack(std::initializer_list<T> values) {
    headCell = std::unique_ptr<Cell>(new Cell(nullptr));
    length = 0;
    for (const auto& value : values) {
      push(value);
    }
  }

  FirstStack(FirstStack&& stack) noexcept
      {
    *this = std::move(stack);
  }

  FirstStack& operator=(FirstStack&& stack) noexcept{
    headCell = std::move(stack.headCell);
    length = std::move(stack.length);
    return *this;
  };

  ~FirstStack() = default;
};

#endif  // STACK_FIRSTINHSTACK_HPP
