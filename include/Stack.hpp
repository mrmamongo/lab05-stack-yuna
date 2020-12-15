//
// Created by lamp on 15.12.2020.
//

#ifndef STACK_STACK_HPP
#define STACK_STACK_HPP

#include <memory>
#include <string>
#include <iostream>


template <typename T>
class Stack {
 protected:

  size_t length;

 public:
  Stack(Stack&) = delete;
  Stack& operator=(Stack&) = delete;

  Stack(): length(0){};
  virtual ~Stack() = default;
  virtual void push(T&& value) = 0;

  [[nodiscard]] inline auto Length() const -> size_t {
    return length;
  }
  virtual inline auto head() const -> const T& = 0;
};

#endif  // STACK_STACK_HPP
