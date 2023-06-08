#include <libcs/libcs/treeset.hpp>
#include <gtest/gtest.h>

TEST(TreeSetTest, TreeSetTest1) {
    std::string a[] = { "Kann", "man", "Herzen", "brechen", "Konnen",
        "Herzen", "sprechen", "Doch", "seh", "ich", "dann", "nach", "unten", "weck"};
    std::string tmp[] = { "Doch", "Herzen", "Kann", "Konnen", "brechen",
        "dann", "ich", "man", "nach", "seh", "sprechen", "unten", "weck"};
    //ПАМЯТКА: в таблице ASKII заглавные буквы идут раньше строчных
    csc::treeset::TreeSet<std::string> ts;
    EXPECT_TRUE(ts.isEmpty());
    for (int i = 0; i < 14; i++) {
        ts.add(a[i]);
    }
    std::size_t expct = 13;
    EXPECT_EQ(ts.size(), expct);
    int i = 0;
    for (auto &node : ts) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    EXPECT_TRUE(ts.contains("Kann"));
    EXPECT_TRUE(ts.contains("man"));
    EXPECT_TRUE(ts.contains("Herzen"));
    EXPECT_TRUE(ts.contains("brechen"));
    i = 0;
    for (auto iter = ts.begin(); iter != ts.end(); iter++) {
        EXPECT_EQ(iter->get_element(), tmp[i]);
        i++;
    }
    EXPECT_TRUE(ts.remove("brechen"));
    EXPECT_FALSE(ts.contains("brechen"));
    expct = 12;
    EXPECT_EQ(ts.size(), expct);
    EXPECT_EQ(ts.first(), "Doch");
    EXPECT_EQ(ts.last(), "weck");
}

TEST(TreeSetTest, TreeSetTest2) {
    int a[] = { 22, 33, 65, 11, 33};
    int tmp[] = { 11, 22, 33, 65};
    csc::treeset::TreeSet<int> ts;
    EXPECT_TRUE(ts.isEmpty());
    for (int i = 0; i < 5; i++) {
        ts.add(a[i]);
    }
    std::size_t expct = 4;
    EXPECT_EQ(ts.size(), expct);
    int i = 0;
    for (auto &node : ts) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    EXPECT_TRUE(ts.contains(11));
    EXPECT_TRUE(ts.contains(22));
    EXPECT_TRUE(ts.contains(33));
    EXPECT_TRUE(ts.contains(65));
    EXPECT_EQ(ts.first(), 11);
    EXPECT_EQ(ts.last(), 65);
    EXPECT_TRUE(ts.remove(22));
    EXPECT_FALSE(ts.contains(22));
    EXPECT_EQ(ts.first(), 11);
    EXPECT_EQ(ts.last(), 65);
}

TEST(TreeSetTest, TreeSetTest3) {
    double a[] = { 2.2, 3.3, 6.5, 1.1, 1.1};
    double tmp[] = { 1.1, 2.2, 3.3, 6.5};
    csc::treeset::TreeSet<double> ts;
    EXPECT_TRUE(ts.isEmpty());
    for (int i = 0; i < 5; i++) {
        ts.add(a[i]);
    }
    std::size_t expct = 4;
    EXPECT_EQ(ts.size(), expct);
    int i = 0;
    for (auto &node : ts) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    EXPECT_TRUE(ts.contains(1.1));
    EXPECT_TRUE(ts.contains(2.2));
    EXPECT_TRUE(ts.contains(3.3));
    EXPECT_TRUE(ts.contains(6.5));
    EXPECT_EQ(ts.first(), 1.1);
    EXPECT_EQ(ts.last(), 6.5);
    EXPECT_TRUE(ts.remove(2.2));
    EXPECT_FALSE(ts.contains(2.2));
    EXPECT_EQ(ts.first(), 1.1);
    EXPECT_EQ(ts.last(), 6.5);
}

TEST(TreeSetTest, TreeSetTest4) {
    char a[] = { 'f', 'c', 'h', 'a', 'h' };
    char tmp[] = { 'a', 'c', 'f', 'h'};
    csc::treeset::TreeSet<char> ts;
    EXPECT_TRUE(ts.isEmpty());
    for (int i = 0; i < 5; i++) {
        ts.add(a[i]);
    }
    std::size_t expct = 4;
    EXPECT_EQ(ts.size(), expct);
    int i = 0;
    for (auto &node : ts) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    EXPECT_TRUE(ts.contains('a'));
    EXPECT_TRUE(ts.contains('c'));
    EXPECT_TRUE(ts.contains('f'));
    EXPECT_TRUE(ts.contains('h'));
    EXPECT_EQ(ts.first(), 'a');
    EXPECT_EQ(ts.last(), 'h');
    EXPECT_TRUE(ts.remove('f'));
    EXPECT_FALSE(ts.contains('f'));
    EXPECT_EQ(ts.first(), 'a');
    EXPECT_EQ(ts.last(), 'h');
}

TEST(TreeSetTest, TreeSetTest5stl) {
    char a[] = { 'f', 'c', 'h', 'a', 'h' };
    csc::treeset::TreeSet<char> ts;
    for (int i = 0; i < 5; i++) {
        ts.add(a[i]);
    }
    auto exp = std::find_if(ts.begin(), ts.end(), [](auto &iter) {
        return iter.get_element() == 'a';
    });
    EXPECT_EQ(exp->get_element(), 'a');
    auto exp2 = std::max_element(
        ts.begin(), ts.end(), [](auto &lhs, auto &rhs) {
            return lhs.get_element() < rhs.get_element();
        });
    EXPECT_EQ(exp2->get_element(), 'h');
}

TEST(TreeSetTest, TreeSetTest6RuleOfV) {
    csc::treeset::TreeSet<std::string> ts;
    EXPECT_EQ(ts.begin(), ts.end());
    std::size_t expct = 0;
    EXPECT_EQ(ts.size(), expct);
    std::string tmp[] = { "Herzen", "Kann", "brechen", "man"};
    std::string a[] = { "Kann", "man", "Herzen", "brechen", "Kann"};
    EXPECT_TRUE(ts.isEmpty());
    for (int i = 0; i < 5; i++) {
        ts.add(a[i]);
    }
    expct = 4;
    EXPECT_EQ(ts.size(), expct);
    int i = 0;
    for (auto &node : ts) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    EXPECT_EQ(ts.size(), expct);
    auto ts2(ts);
    EXPECT_EQ(ts2.size(), ts.size());
    i = 0;
    for (auto &node : ts2) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    auto ts3(std::move(ts2));
    expct = 0;
    EXPECT_EQ(ts2.size(), expct);
    expct = 4;
    EXPECT_EQ(ts3.size(), expct);
    i = 0;
    for (auto &node : ts3) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    auto ts4 = ts3;
    EXPECT_EQ(ts4.size(), expct);
    i = 0;
    for (auto &node : ts4) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
    ts = ts;
    EXPECT_EQ(ts.size(), expct);
    ts2 = std::move(ts4);
    expct = 0;
    EXPECT_EQ(ts4.size(), expct);
    EXPECT_EQ(ts.size(), ts2.size());
    i = 0;
    for (auto &node : ts2) {
        EXPECT_EQ(node.get_element(), tmp[i]);
        i++;
    }
}
