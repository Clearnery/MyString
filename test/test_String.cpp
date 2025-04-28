#include "MyString.h"
#include <gtest.h>

TEST(MyStringTest, DefaultConstructor) {
    MyString s;
    EXPECT_EQ(0, s.size());
    EXPECT_STREQ("", s.c_str());
}

TEST(MyStringTest, CStringConstructor) {
    MyString s("hello");
    EXPECT_EQ(5, s.size());
    EXPECT_STREQ("hello", s.c_str());
}

TEST(MyStringTest, CopyConstructor) {
    MyString s1("test");
    MyString s2(s1);
    EXPECT_EQ(s1.size(), s2.size());
    EXPECT_STREQ(s1.c_str(), s2.c_str());
}

TEST(MyStringTest, MoveConstructor) {
    MyString s1("move");
    MyString s2(std::move(s1));
    EXPECT_EQ(4, s2.size());
    EXPECT_STREQ("move", s2.c_str());
    EXPECT_EQ(0, s1.size());
}

TEST(MyStringTest, AssignmentOperator) {
    MyString s1("original");
    MyString s2;
    s2 = s1;
    EXPECT_EQ(s1.size(), s2.size());
    EXPECT_STREQ(s1.c_str(), s2.c_str());
}


TEST(MyStringTest, ConcatenationOperator) {
    MyString s1("hello");
    MyString s2(" world");
    MyString s3 = s1 + s2;
    EXPECT_EQ(11, s3.size());
    EXPECT_STREQ("hello world", s3.c_str());
}

TEST(MyStringTest, DuplicateOperator) {
    MyString s("ab");
    MyString s2 = s * 3;
    EXPECT_EQ(6, s2.size());
    EXPECT_STREQ("ababab", s2.c_str());
}

TEST(MyStringTest, FindFirstSubstring) {
    MyString s("hello world");
    MyString sub("world");
    EXPECT_EQ(6, s.findFirst(sub));
    EXPECT_EQ(-1, s.findFirst("xyz"));
}

TEST(MyStringTest, FindFirstChar) {
    MyString s("hello");
    EXPECT_EQ(1, s.findFirst('e'));
    EXPECT_EQ(-1, s.findFirst('z'));
}

TEST(MyStringTest, Split) {
    MyString s("a,b,c,d");
    auto parts = s.split(',');
    ASSERT_EQ(4, parts.size());
    EXPECT_STREQ("a", parts[0].c_str());
    EXPECT_STREQ("b", parts[1].c_str());
    EXPECT_STREQ("c", parts[2].c_str());
    EXPECT_STREQ("d", parts[3].c_str());
}

TEST(MyStringTest, DuplicateMethod) {
    MyString s("12");
    MyString s2 = s.duplicate(4);
    EXPECT_EQ(8, s2.size());
    EXPECT_STREQ("12121212", s2.c_str());
}

TEST(MyStringTest, FindAllSubstrings) {
    MyString s("abababab");
    MyString sub("ab");
    auto positions = s.findAll(sub);
    ASSERT_EQ(4, positions.size());
    EXPECT_EQ(0, positions[0]);
    EXPECT_EQ(2, positions[1]);
    EXPECT_EQ(4, positions[2]);
    EXPECT_EQ(6, positions[3]);
}

TEST(MyStringTest, MostFrequentChar) {
    MyString s("abracadabra");
    EXPECT_EQ('a', s.mostFrequentChar());
}

TEST(MyStringTest, UniqueChars) {
    MyString s("abracadabra");
    auto unique = s.uniqueChars();
    ASSERT_EQ(5, unique.size());
    EXPECT_EQ('a', unique[0]);
    EXPECT_EQ('b', unique[1]);
    EXPECT_EQ('r', unique[2]);
    EXPECT_EQ('c', unique[3]);
    EXPECT_EQ('d', unique[4]);
}