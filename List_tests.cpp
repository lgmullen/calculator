// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
};
TEST(test1) {
    List<int> list;
    list.push_front(23);
    list.push_front(30);
    list.push_front(33);
    ASSERT_FALSE(list.empty());
    ASSERT_TRUE(list.size() == 3);

};
TEST(test2) {
    List<int> list;
    ASSERT_TRUE(list.size() == 0);
};
TEST(test3) {
    List<int> list;
    list.push_front(10);
    ASSERT_TRUE(list.front()==10);
    ASSERT_TRUE(list.back()== 10);
    list.push_front(7);
    ASSERT_TRUE(list.front()==7);
    ASSERT_TRUE(list.back()== 10);
    list.push_front(5);
    ASSERT_TRUE(list.front()==5);
    list.push_back(99);
    ASSERT_TRUE(list.front()==5);
    ASSERT_TRUE(list.back()==99);
    
};
TEST(test_pop) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    ASSERT_TRUE(list.front()== 2);
    list.pop_front();
    ASSERT_TRUE(list.front()== 1);
    
};
TEST(test_pop2) {
    List<int> list;
    list.push_front(1);
    list.pop_front();
    list.push_front(1);
    list.pop_back();
    ASSERT_TRUE(list.empty());
};
TEST(copy) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int> list2 = list;
    ASSERT_TRUE(list.front() == 3);
    ASSERT_TRUE(list.back() == 1);
    ASSERT_TRUE(list2.size() == 3);
    list2.pop_front();
    ASSERT_TRUE(list2.size() == 2);
    list2.pop_front();
    ASSERT_TRUE(list2.size() == 1);
    list2.pop_front();
    
};
TEST(iterator_add) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter2 = iter;
    ASSERT_TRUE(*iter2 == 3);
    ASSERT_TRUE(*iter == 3);
    ASSERT_TRUE(*iter2 == *iter);
    ++iter;
    ASSERT_TRUE(*iter == 2);
    ++iter;
    ASSERT_TRUE(*iter == 1);
    ++iter;
};
TEST(erase) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter2 = iter;
    ++iter2;
    ++iter2;
    list.erase(iter2);
    ASSERT_TRUE(list.size()== 2);
    while(iter != list.end()) {
        cout << *iter << endl;
        ++iter;
    }
};
TEST(insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter2 = iter;
    ++iter2;
    ++iter2;
    list.insert(iter2, 77);
    ASSERT_TRUE(list.size() == 4);
    while(iter != list.end()) {
        cout << *iter << endl;
        ++iter;
    }
};



TEST_MAIN()
