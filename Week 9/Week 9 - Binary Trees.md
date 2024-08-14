# Week 9 - Binary Trees

## Team

Team name: Encoder
Date:

Members
Oleksandr Kuprii
Illia Kara

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             |      |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              |      |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. |      |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   |      |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion.

### Activity 1: Maintaining order in arrays and linked lists - reprise

Record your answer here
|                    | Array  | Linked List |
| ------------------ | ------ | ----------- |
| value insertion    | O(n)   | O(n)      |
| value removal      | O(n)   | O(n)      |
| membership testing | O(logn)| O(n)      |

### Activity 2: Constructing a binary tree

```cpp
1. int main() {
    bintree_node root{2}, a{3}, b{5}, c{7}, d{11};
    root.set_left(&a);
    root.set_right(&b);
    a.set_left(&c);
    b.set_left(&d);
    bintree_writer::write_dot("../example.dot", root);
}

2. int main() {
    bintree_node root{2}, a{3}, b{5}, c{7}, d{11};
    root.set_left(&a);
    root.set_right(&b);
    a.set_left(&c);
    c.set_left(&d);
    bintree_writer::write_dot("../example.dot", root);
}

3. int main() {
    bintree_node root{2}, a{3}, b{5}, c{7}, d{11};
    root.set_left(&a);
    a.set_left(&b);
    b.set_right(&c);
    c.set_left(&d);
    bintree_writer::write_dot("../example.dot", root);
}
```

### Activity 3: Recognizing BSTs
Tree A - 71 violates the order
Tree B - 84 violates the order
Tree C - binary search tree

### Activity 4: Searching for values

```cpp
bintree_node *bintree_node::find(int value) {
    if (value == m_value) {
        return this;
    } else if (value > m_value) {
        if (has_right_child()) {
            return m_right->find(value);
        } else {
            return nullptr;
        }
    } else {
        if (has_left_child()) {
            return m_left->find(value);
        } else {
            return nullptr;
        }
    }
}
```

### Activity 5: Inserting values

```cpp
bintree_node* bintree_node::insert(int value) {
    if (value == m_value)
        return nullptr;
    else if (value < m_value) {
        if (has_left_child()) {
            return m_left->insert(value);
        } else {
            auto * node = new bintree_node{value};
            set_left(node);
            return node;
        }
    } else {
        if (has_right_child()) {
            return m_right->insert(value);
        } else {
            auto * node = new bintree_node{value};
            set_right(node);
            return node;
        }
    }
}
```

### Activity 6: Properties of the minimum value

1. No. According to the order of invariant of binary trees values in the left subtree are less than tree's root and values in the right subtree are not less then tree's root. Consequently, values in the left subtree are less than the values in the right subtreee.
2. No. The left child of every node is always smaller than its parent, thus the minimum value in tree cannot have the left subtree.
3. The strategy is to always go to the left subtree until reaching the bottom of the tree.

### Activity 7: Finding the minimum value

```cpp
bintree_node &bintree_node::minimum() {
    if (has_left_child()) {
        return m_left->minimum();
    }
    return *this;
}
```

### Activity 8: Removing leafs
```cpp
bintree_node *bintree_node::remove() {
    if (is_leaf()) {
        m_parent->replace_child(this, nullptr);
        return this;
    } else if (has_right_child() && !has_left_child()) {
    } else if (has_left_child() && !has_right_child()) {
    } else {
    }
}
```

### Activity 9: Removing nodes that have one child

```cpp
bintree_node *bintree_node::remove() {
    if (is_leaf()) {
        m_parent->replace_child(this, nullptr);
        return this;
    } else if (has_right_child() && !has_left_child()) {
        m_parent->replace_child(this, m_right);
        return this;
    } else if (has_left_child() && !has_right_child()) {
        m_parent->replace_child(this, m_left);
        return this;
    } else {
    }
}
```


### Activity 10: Moving values around


In the left tree the *root* value can be F (min in the right subtree) or B (max in the left in the left subtree) , due to F<E<D and B>A.
In the right tree the *root* value can be G (min in right subtree) or E (max in left subtree), due to E>C>A in a left subtree, and G<H<F in the right subtree



### Activity 11: Removing full nodes

```cpp
bintree_node *bintree_node::remove() {
    if (is_leaf()) {
        m_parent->replace_child(this, nullptr);
        return this;
    } else if (has_right_child() && !has_left_child()) {
        m_parent->replace_child(this, m_right);
        return this;
    } else if (has_left_child() && !has_right_child()) {
        m_parent->replace_child(this, m_left);
        return this;
    } else {
        auto& node = m_right->minimum();

        if (m_right != &node) {
            node.m_parent->m_left = nullptr;
            node.set_right(m_right);
        }
        node.set_left(m_left);

        m_parent->replace_child(this, &node);
        return this;
    }
}
```

### Activity 12: (Un)balanced trees

First example is an average tree with two subtrees, left and right and four leafs.
Second example is a tree with only right subtree with only right side(max) of the tree.
Third example is a tree with onle left subree with only the left side(min) side.

### Activity 13: Time complexity

| Operation | Time complexity (if balanced)   | Time complexity (if unbalanced) |
| --------- | --------------- | --------------- |
| Lookup    | O(logn)          | O(n)          |
| Insert    | O(logn)          | O(n)          |
| Remove    | O(logn)          | O(n)          |

## Looking back

### What we've learnt

What is the binary search tree, how to use it.

### What were the surprises

Usage of replace_child to delete a node.

### What problems we've encountered

Activity #8,9,11. Remove with a replace_child.

### What was or still is unclear

Removal with a replace_child.

### How did the group perform?
 Team performed well, with no problems in communication.





> Written with [StackEdit](https://stackedit.io/).
