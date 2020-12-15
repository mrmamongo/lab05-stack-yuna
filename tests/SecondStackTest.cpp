//
// Created by lamp on 08.12.2020.
//

#include <gtest/gtest.h>

#include <utility>
#include "SecondInhStack.hpp"
using std::string;

class NotCopiableClass {
  string name;
  int value;
 public:
  NotCopiableClass(NotCopiableClass&) = delete;
  NotCopiableClass& operator=(NotCopiableClass&) = delete;
  NotCopiableClass(NotCopiableClass&& obj)  noexcept {
    name = std::move(obj.name);
    value = obj.value;
  }
  NotCopiableClass& operator=(NotCopiableClass&& obj)  noexcept {
    name = std::move(obj.name);
    value = obj.value;
    return *this;
  }
  explicit NotCopiableClass(int value_ = 0, string name_ = "EMPTY")
      : name(std::move(name_)), value(value_){}

  string GetName() const {return name;}
  int GetValue() const {return value;}
};

TEST(SecondStack, NullTest) {
  SecondStack<NotCopiableClass> nullStack;

  EXPECT_EQ(nullStack.head().GetName(), "EMPTY");
  EXPECT_EQ(nullStack.head().GetValue(), 0);
}

TEST(SecondStack, BasicTest) {
 SecondStack<NotCopiableClass> stack;
 stack.push_emplace(NotCopiableClass(10, "First"));
 stack.push_emplace(NotCopiableClass(20, "Second"));
 EXPECT_EQ(stack.Length(), 2);
 EXPECT_EQ(stack.head().GetName(), "Second");
 EXPECT_EQ(stack.head().GetValue(), 20);

 stack.push_emplace(30, "Third");

  EXPECT_EQ(stack.head().GetName(), "Third");
  EXPECT_EQ(stack.head().GetValue(), 30);
}

TEST(SecondStack, PopTest) {
  NotCopiableClass notCopiableObject1(10, "First");
  NotCopiableClass notCopiableObject2(20, "Second");
  SecondStack<NotCopiableClass> stack;
  stack.push_emplace(std::move(notCopiableObject1));
  stack.push_emplace(std::move(notCopiableObject2));
  NotCopiableClass poppedObject = stack.pop();

  EXPECT_EQ(poppedObject.GetName(), "Second");
  EXPECT_EQ(poppedObject.GetValue(), 20);

  EXPECT_EQ(stack.head().GetName(), "First");
  EXPECT_EQ(stack.head().GetValue(), 10);
}

TEST(SecondStack, MovingConstructorTest) {
  SecondStack<NotCopiableClass> firstStack;
  firstStack.push_emplace(10, "First");
  firstStack.push_emplace(20, "Second");
  SecondStack<NotCopiableClass> secondStack(std::move(firstStack));
  EXPECT_EQ(secondStack.head().GetValue(), 20);
  EXPECT_EQ(secondStack.head().GetName(), "Second");
}

TEST(SecondStack, MovingOperatorTest) {
  SecondStack<NotCopiableClass> firstStack;
  firstStack.push_emplace(10, "First");
  firstStack.push_emplace(20, "Second");
  SecondStack<NotCopiableClass> secondStack = std::move(firstStack);
  EXPECT_EQ(secondStack.head().GetValue(), 20);
  EXPECT_EQ(secondStack.head().GetName(), "Second");
}

TEST(SecondStack, TypeTraitsTest) {
  EXPECT_FALSE(std::is_copy_constructible<SecondStack<NotCopiableClass>>::value);
  EXPECT_TRUE(std::is_move_constructible<SecondStack<NotCopiableClass>>::value);
  EXPECT_TRUE(std::is_move_assignable<SecondStack<NotCopiableClass>>::value);
  EXPECT_FALSE(std::is_copy_assignable<SecondStack<NotCopiableClass>>::value);
}
