#include "catch2/catch_all.hpp"
#include "solution.h"

using namespace std;

void clean(Node*& n) {
    if (n == nullptr) return;
    clean(n->left);
    clean(n->right);
    delete n;
}

TEST_CASE("Validate isContains") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);

    CHECK(isContains(test, 140) == true);
    CHECK(isContains(test, 25) == true);
    CHECK(isContains(test, 0) == false);
    CHECK(isContains(test,  150) == false);
    clean(test);
}

TEST_CASE("Validate getMin") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);

    CHECK(getMin(test)->key == 25);
    test->left->left->left = new Node(5);
    CHECK(getMin(test)->key == 5);

    clean(test);
}

TEST_CASE("Validate getMax") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    CHECK(getMax(test)->key == 140);
    test->right->right = new Node(180);
    CHECK(getMax(test)->key == 180);

    clean(test);
}

TEST_CASE("Validate LCA") {

    Node* test = new Node(100);
    test = insert(test, 150);
    test = insert(test, 50);
    test = insert(test, 15);
    test = insert(test, 12);
    test = insert(test, 200);

    CHECK(LCA(test, 50, 200) == 100);
    CHECK(LCA(test, 15, 12) == 15);
    CHECK(LCA(test, 15, 120) == -1);

    clean(test);
}


TEST_CASE("Validate insert") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    test = insert(test, 150);
    CHECK(test->right->right->key == 150);
    test = insert(test, 75);
    CHECK(test->left->right->key == 75);

    clean(test);
}

TEST_CASE("Validate remove") {

    Node* test = new Node(100);
    test->left = new Node(50);
    test->right = new Node(140);
    test->left->left = new Node(25);
    test = remove(test, 25);
    CHECK(test->left->left == nullptr);
    test = remove(test, 100);
    CHECK(test->key == 140);
    CHECK(test->right == nullptr);


    clean(test);
}


TEST_CASE("Validate delGreaterThanX") {

    Node* test = new Node(17);
    test->left = new Node(15);
    test->left->left = new Node(9);
    test->left->left->left = new Node(5);
    test->right = new Node(72);
    test->right->right = new Node(79);
    test->right->right->right = new Node(80);
    test->right->right->right->right = new Node(90);
    test->right->right->right->right->right = new Node(98);
    test->right->right->right->right->right = new Node(95);
    test->right->left = new Node(67);
    test->right->left->left = new Node(59);
    test->right->left->left->left = new Node(45);
    test->right->left->left->left->left = new Node(36);
    test = delGreaterThanX(test, 9);
    CHECK(isContains(test,59) == false);
    CHECK(isContains(test, 67) == false);
    CHECK(isContains(test, 72) == false);
    CHECK(isContains(test, 79) == false);
    CHECK(isContains(test, 80) == false);
    CHECK(isContains(test, 90) == false);
    CHECK(isContains(test, 98) == false);
    CHECK(isContains(test, 95) == false);

    clean(test);
}


TEST_CASE("Validate section") {

    Node* test = new Node(17);
    test->left = new Node(15);
    test->left->left = new Node(9);
    test->left->left->left = new Node(5);
    test->right = new Node(72);
    test->right->right = new Node(79);
    test->right->right->right = new Node(80);
    test->right->right->right->right = new Node(90);
    test->right->right->right->right->right = new Node(98);
    test->right->right->right->right->right = new Node(95);
    test->right->left = new Node(67);
    test->right->left->left = new Node(59);
    test->right->left->left->left = new Node(45);
    test->right->left->left->left->left = new Node(36);


    Node* test2 = new Node(17);
    test2->left = new Node(15);
    test2->left->left = new Node(9);
    test2->left->left->left = new Node(5);
    test2->right = new Node(72);
    test2->right->right = new Node(79);
    test2->right->right->right = new Node(80);
    test2->right->right->right->right = new Node(90);
    test2->right->right->right->right->right = new Node(98);

    Node* totest = section(test, test2);

    CHECK(isContains(totest, 95) == false);
    CHECK(isContains(totest, 67) == false);
    CHECK(isContains(totest, 59) == false);
    CHECK(isContains(totest, 45) == false);
    CHECK(isContains(totest, 36) == false);

    clean(test);
}

TEST_CASE("Validate areCousins") {

    Node* test = new Node(17);
    test->left = new Node(15);
    test->left->left = new Node(9);
    test->left->left->left = new Node(5);
    test->right = new Node(72);
    test->right->right = new Node(79);
    test->right->right->right = new Node(80);
    test->right->right->right->right = new Node(90);
    test->right->right->right->right->right = new Node(98);
    test->right->right->right->right->right = new Node(95);
    test->right->left = new Node(67);
    test->right->left->left = new Node(59);
    test->right->left->left->left = new Node(45);
    test->right->left->left->left->left = new Node(36);

    CHECK(areCousins(test, 15, 72) == false);
    CHECK(areCousins(test, 9, 67) == true);
    CHECK(areCousins(test, 5, 80) == true);
    CHECK(areCousins(test, 15, 95) == false);

}
