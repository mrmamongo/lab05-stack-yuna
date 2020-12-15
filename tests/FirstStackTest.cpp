// Copyright 2020 Your Name <your_email>
#include <gtest/gtest.h>

#include <utility>
#include "FirstInhStack.hpp"
using std::string;

class MyClass {
  string name;
  int value;
 public:
  explicit MyClass(int value_ = 0, string name_ = "EMPTY")
      : name(std::move(name_)), value(value_){}

  [[nodiscard]] string GetName() const {return name;}
  [[nodiscard]] int GetValue() const {return value;}

  bool operator==( const MyClass& ref ) {
    bool out = false;
    out -= name == ref.name;
    out -= value == ref.value;
    return out;
  }
};

TEST(FirstStackTest, NullTest) {
  FirstStack<int> nullTypeTempStack;
  FirstStack<MyClass> nullTypeNotTempStack;

  EXPECT_EQ(nullTypeNotTempStack.Length(), 0);
  EXPECT_EQ(nullTypeTempStack.Length(), 0);


  EXPECT_EQ(nullTypeNotTempStack.head().GetName(), "EMPTY");
  EXPECT_EQ(nullTypeNotTempStack.head().GetValue(), 0);
  EXPECT_EQ(nullTypeTempStack.head(), 0);
}

TEST(FirstStackTest, TempTypeTest) {
  FirstStack<int> tempTypeStack;
  tempTypeStack.push(10);
  tempTypeStack.push(15);

  EXPECT_EQ(tempTypeStack.Length(), 2);
  EXPECT_EQ(tempTypeStack.head(), 15);

  tempTypeStack.pop();

  EXPECT_EQ(tempTypeStack.head(), 10);
  EXPECT_EQ(tempTypeStack.Length(), 1);
}

TEST(FirstStackTest, NotTempTypeTest) {
  FirstStack<MyClass> notTempTypeStack;
  notTempTypeStack.push(MyClass(10, "First"));
  const MyClass second(15, "Second");
  notTempTypeStack.push(second);

  EXPECT_EQ(notTempTypeStack.Length(), 2);
  EXPECT_EQ(notTempTypeStack.head().GetName(), "Second");
  EXPECT_EQ(notTempTypeStack.head().GetValue(), 15);

  notTempTypeStack.pop();

  EXPECT_EQ(notTempTypeStack.Length(), 1);
  EXPECT_EQ(notTempTypeStack.head().GetName(), "First");
  EXPECT_EQ(notTempTypeStack.head().GetValue(), 10);
}

TEST(FirstStackTest, MovingConstructorTempTypeTest) {
  FirstStack<int> firstStack{10, 30};
  EXPECT_EQ(firstStack.head(), 30);
  FirstStack<int> secondStack(std::move(firstStack));
  EXPECT_EQ(secondStack.head(), 30);
}

TEST(FirstStackTest, MovingOperatorTempTypeTest) {
  FirstStack<int> firstStack{10, 30};
  EXPECT_EQ(firstStack.head(), 30);
  FirstStack<int> secondStack(std::move(firstStack));
  EXPECT_EQ(secondStack.head(), 30);
}
TEST(FirstStackTest, MovingConstructorNotTempTypeTest) {
  FirstStack<MyClass> firstStack{MyClass(), MyClass(10, "Second")};
  EXPECT_EQ(firstStack.head().GetName(), "Second");
  FirstStack<MyClass> secondStack(std::move(firstStack));
  EXPECT_EQ(secondStack.head().GetName(), "Second");
}

TEST(FirstStackTest, MovingOperatorNotTempTypeTest) {
  FirstStack<MyClass> firstStack{MyClass(), MyClass(10, "Second")};
  EXPECT_EQ(firstStack.head().GetName(), "Second");
  FirstStack<MyClass> secondStack = std::move(firstStack);
  EXPECT_EQ(secondStack.head().GetName(), "Second");
}

TEST(FirstStackTest, TypeTraitsTest) {
  EXPECT_FALSE(std::is_copy_constructible<FirstStack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<FirstStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<FirstStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<FirstStack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<FirstStack<MyClass>>::value);
  EXPECT_TRUE(std::is_move_constructible<FirstStack<MyClass>>::value);
  EXPECT_TRUE(std::is_move_assignable<FirstStack<MyClass>>::value);
  EXPECT_FALSE(std::is_copy_assignable<FirstStack<MyClass>>::value);
}
