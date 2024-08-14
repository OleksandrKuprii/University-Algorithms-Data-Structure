# Week 10 - Balanced Binary Trees

## Team

Team name: Oleksandr
Date: 09-06-2022

Members
Oleksandr Kuprii


| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Oleksandr     |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Oleksandr     |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr     |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion. **NOTE**: in this week you will have to reuse the code of last week. Follow the instructions given in the `main.cpp` file.

### Activity 1: Time complexity

1. The minimum height of balanced binary tree is **h = ⌊log<sub>2</sub>n⌋**
2. Both operations have time complexity **O(logn)**

### Activity 2: Remembering tree heights

```cpp
void bintree_node::update_height() {
    if (m_parent == nullptr)
        return;


    if (has_right_child() && has_left_child()) {
        if (m_left->m_height > m_right->m_height) {
            m_height = m_left->m_height + 1;
        } else {
            m_height = m_right->m_height + 1;
        }
    }
    else if (has_left_child())
        m_height = m_left->m_height + 1;
    else if (has_right_child())
        m_height = m_right->m_height + 1;
    else
        m_height = 1;

    return m_parent->update_height();
}
```
### Activity 3: Do it yourself: Balance factors

Left tree (Figure 3a):
| Node | Height | Balance factor |
|------|:------:|:--------------:|
| A    |   4     |        1        |
| B    |   2     |        -1        |
| C    |   1     |        0        |
| D    |   3     |        -1        |
| E    |   2     |        0        |
| F    |   1     |        0       |
| G    |   1     |        0       |
| H    |   1     |        0       |

Right tree (Figure 3b):
| Node | Height | Balance factor |
|------|:------:|:--------------:|
| K    |   4     |        -2        |
| L    |   3     |        1        |
| M    |   1     |        0        |
| N    |   2     |        0        |
| P    |   1     |        0        |
| Q    |   1     |        0        |
| R    |   1     |        0        |

The left tree is height-balanced.

### Activity 4: Computing the balance factor

```cpp
int bintree_node::balance() const {
    if (has_left_child() && has_right_child())
        return m_right->height() - m_left->height();
    else if (has_left_child())
        return (-1) * m_left->height();
    else if (has_right_child())
        return m_right->height();
    return 0;
}
```

### Activity 5: Balancing acts

From the 4a tree we can infer that B ≤ A ≤ C ≤ D ≤ E.
The 4b tree is correct because it satisfies out inference. The other two trees (4c and 4d) are not correct as they do not satisfy this condition.

### Activity 6: Implement left rotation

```cpp
void bintree_node::rotate_left() {
    auto parent = m_parent;
    auto r = m_right;
    auto rl = m_right->m_left;

    (void) parent;
    (void) r;
    (void) rl;

    if (rl != nullptr) {
        r->replace_child(rl, this);
        replace_child(r, rl);
    } else {
        r->m_left = this;
        m_right = nullptr;
    }
    parent->replace_child(this, r);
    r->update_height();
}
```

### Activity 7: Implement right rotation

```cpp
void bintree_node::rotate_right() {
    auto parent = m_parent;
    auto l = m_left;
    auto lr = m_left->m_right;

    (void) parent;
    (void) l;
    (void) lr;

    if (lr != nullptr) {
        l->replace_child(lr, this);
        replace_child(l, lr);
    } else {
        l->m_right = this;
        m_left = nullptr;
    }

    parent->replace_child(this, l);
    l->update_height();
}
```

### Activity 8: Left rotations and balance
| A (Balance) | C (Balance) | B Height | D Height | E Height | Balance after rot |
|-------------|:-----------:|:--------:|----------|----------|-------------------|
| +2          |      -1     |    H     |  H + 1   |    H     |       -2          |
| +2          |      0      |    H     |  H + 1   |  H + 1   |       -1          |
| +2          |      +1     |    H     |    H     |  H + 1   |       0           |
| +2          |      +2     |    H     |  H - 1   |  H + 1   |       0           |

### Activity 9: Right rotations and balance
| A (Balance) | B (Balance) | C Height | D Height | E Height | Balance after rot |
|-------------|:-----------:|:--------:|----------|----------|-------------------|
| -1          |      -1     |    H     |  H - 1   |    H     |        +1         |
| -1          |      0      |    H     |    H     |    H     |        +1         |
| -1          |      +1     |  H - 1   |    H     |    H     |        +2         |

### Activity 10: Fixing right-heavy trees using rotation combos

1. We need to perform a *right-left* rotation to -1 case.
2. 0 or -1.
3. -2.

### Activity 11: Fixing left-heavy trees
1. We need to perform a *left-right* rotation to +1 case.
2. 0.
3. 0 or +1.

### Activity 12: Rebalancing the tree

```cpp
/// Activity 12: restores the balance of a left-heavy tree
void bintree_node::fix_left_heavy() {
    switch (m_left->balance()) {
        case 0:
        case -1:
            rotate_right();
            break;
        case +1:
            m_left->rotate_left();
            rotate_right();
            break;
    }
}

/// Activity 12: restores the balance of a right-heavy tree
void bintree_node::fix_right_heavy() {
    switch (m_right->balance()) {
        case 0:
        case +1:
            rotate_left();
            break;
        case -1:
            m_right->rotate_right();
            rotate_left();
            break;
    }
}
```

### Activity 13: Verify balance

1. The height of the root node is 4.
2. The balance factor of the root node is 0.
3. 17 rotations were performed.


## Looking back

### What we've learnt

How to make self-balancing binary trees.

### What were the surprises

How the tree can balance itself.

### What problems we've encountered

Updating left and right rotate functions after a while.

### What was or still is unclear

All clear.

### How did the group perform?

A group of one person works perfectly.




