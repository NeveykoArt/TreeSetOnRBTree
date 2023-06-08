#pragma once

#include <functional>

namespace csc::treeset {

enum class Color {RED, BLACK};

template <typename T> struct TreeSetNode {
  T element_;
  TreeSetNode<T> *parent_ = nullptr;
  TreeSetNode<T> *left_ = nullptr;
  TreeSetNode<T> *right_ = nullptr;
  Color color_;

  T get_element() const { return element_; }

  TreeSetNode(const T &e, TreeSetNode<T> *p) {
    element_ = e;
    parent_ = p;
    left_ = nullptr;
    right_ = nullptr;
    color_ = Color::RED;
  }

  ~TreeSetNode() {}
};

template <typename T, typename Compare = std::less<T>> class TreeSet {
private:
  void removeNode(TreeSetNode<T> *n) {
    if (n == nullptr) {
      return;
    }
    if (n->left_ != nullptr && n->right_ != nullptr) {
      TreeSetNode<T> *nn = getNextNode(n);
      n->element_ = nn->element_;
      n = nn;
    }
    TreeSetNode<T> *c = (n->left_ != nullptr ? n->left_ : n->right_);
    if (c != nullptr) {
      c->parent_ = n->parent_;
    }
    if (n->parent_ == nullptr) {
      root_ = c;
    } else if (n == n->parent_->left_) {
      n->parent_->left_ = c;
    } else {
      n->parent_->right_ = c;
    }
    delete n;
  }

  static TreeSetNode<T> *getNextNode(TreeSetNode<T> *n) {
    if (n == nullptr) {
      return n;
    }
    if (n->right_) {
      n = n->right_;
      while (n != nullptr && n->left_ != nullptr) {
        n = n->left_;
      }
    } else {
      TreeSetNode<T> *c = n;
      n = n->parent_;
      while (n != nullptr && c == n->right_) {
        c = n;
        n = n->parent_;
      }
    }
    return n;
  }

  TreeSetNode<T> *getFirstNode() const {
    TreeSetNode<T> *n = root_;
    while (n != nullptr && n->left_ != nullptr) {
      n = n->left_;
    }
    return n;
  }

  TreeSetNode<T> *getLastNode() const {
    TreeSetNode<T> *n = root_;
    while (n != nullptr && n->right_ != nullptr) {
      n = n->right_;
    }
    return n;
  }

  TreeSetNode<T> *Min(TreeSetNode<T> *node_) {
      TreeSetNode<T> *currentNode = node_;
      if (currentNode == nullptr)
          currentNode = root_;
      if (currentNode == nullptr)
          return nullptr;
      while (currentNode->left_ != nullptr)
          currentNode = currentNode->left_;
      return currentNode;
  }

  void Fixup(TreeSetNode<T> *z) {
      TreeSetNode<T> *parent = z->parent_;
      while (z != root_ && parent->color_ == Color::RED) {
          TreeSetNode<T> *gparent = parent->parent_;
          if (gparent->left_ == parent) {
              TreeSetNode<T> *u = gparent->right_;
              if (u != nullptr && u->color_ == Color::RED) {
                  parent->color_ = Color::BLACK;
                  u->color_ = Color::BLACK;
                  gparent->color_ = Color::RED;
                  z = gparent;
                  parent = z->parent_;
              }
              else {
                  if (z == parent->right_) {
                      if (z->right_ != nullptr)
                        RotateLeft(z);
                      TreeSetNode<T> *temp = z;
                      z = parent;
                      parent = temp;
                  }
                  if (gparent->left_ != nullptr)
                    RotateRight(gparent);
                  parent->color_ = Color::BLACK;
                  gparent->color_ = Color::RED;
                  break;
              }
          }
          else {
              TreeSetNode<T> *u = gparent->left_;
              if (u != nullptr && u->color_ == Color::RED) {
                  parent->color_ = Color::BLACK;
                  u->color_ = Color::BLACK;
                  gparent->color_ = Color::RED;
                  z = gparent;
                  parent = z->parent_;
              }
              else {
                  if (z == parent->left_) {
                      if (z->left_ != nullptr)
                        RotateRight(z);
                      TreeSetNode<T> *temp = z;
                      z = parent;
                      parent = temp;
                  }
                  if (gparent->right_ != nullptr)
                    RotateLeft(gparent);
                  parent->color_ = Color::BLACK;
                  gparent->color_ = Color::RED;
                  break;
              }
          }
      }
      root_->color_ = Color::BLACK;
  }

  void RotateLeft(TreeSetNode<T> *x) {
      TreeSetNode<T> *y = x->right_;
      x->right_ = y->left_;
      if (y->left_ != nullptr)
      {
          y->left_->parent_ = x;
      }
      y->parent_ = x->parent_;
      if (x->parent_ == nullptr)
          root_ = y;
      else {
          if (x == x->parent_->left_)
              x->parent_->left_ = y;
          else
              x->parent_->right_ = y;
      }
      y->left_ = x;
      if (x != nullptr) {
          x->parent_ = y;
      }
  }

  void RotateRight(TreeSetNode<T> *y) {
      TreeSetNode<T> *x = y->left_;
      y->left_ = x->right_;
      if (x->right_ != nullptr) {
          x->right_->parent_ = y;
      }
      x->parent_ = y->parent_;
      if (y->parent_ == nullptr)
          root_ = x;
      else {
          if  (y == y->parent_->right_)
              y->parent_->right_ = x;
          else
              y->parent_->left_ = x;
      }
      x->right_ = y;
      if (y != nullptr) {
          y->parent_ = x;
      }
  }

  void Transplant(TreeSetNode<T> *u, TreeSetNode<T> *v) {
      if (u->parent_ == nullptr) {
          root_ = v;
      } else if (u == u->parent_->left_){
          u->parent_->left_ = v;
      } else {
          u->parent_->right_ = v;
      }
      if (v != nullptr)
        v->parent_ = u->parent_;
  }

  void DeleteFixup(TreeSetNode<T> *x) {
    TreeSetNode<T> *s = nullptr;
    while (x != root_ && x->color_ == Color::BLACK) {
        if (x == x->parent_->left_) {
            s = x->parent_->right_;
            if (s->color_ == Color::RED) {
                s->color_ = Color::BLACK;
                x->parent_->color_ = Color::RED;
                if (x->parent_->right_ != nullptr)
                  RotateLeft(x->parent_);
                s = x->parent_->right_;
            }
            if (s->left_->color_ == Color::BLACK && s->right_->color_ == Color::BLACK) {
                s->color_ = Color::RED;
                x = x->parent_;
            } else {
                if (s->right_->color_ == Color::BLACK) {
                    s->left_->color_ = Color::BLACK;
                    s->color_ = Color::RED;
                    if (s->left_ != nullptr)
                      RotateRight(s);
                    s = x->parent_->right_;
                }
                s->color_ = x->parent_->color_;
                x->parent_->color_ = Color::BLACK;
                s->right_->color_ = Color::BLACK;
                if (x->parent_->right_ != nullptr)
                  RotateLeft(x->parent_);
                x = root_;
            }
        } else {
            s = x->parent_->left_;
            if (s->color_ == Color::RED) {
                s->color_ = Color::BLACK;
                x->parent_->color_ = Color::RED;
                if (x->parent_->left_ != nullptr)
                  RotateRight(x->parent_);
                s = x->parent_->left_;
            }
            if (s->right_->color_ == Color::BLACK && s->right_->color_ == Color::BLACK) {
                s->color_ = Color::RED;
                x = x->parent_;
            } else {
                if (s->left_->color_ == Color::BLACK) {
                    s->right_->color_ = Color::BLACK;
                    s->color_ = Color::RED;
                    if (s->right_ != nullptr)
                      RotateLeft(s);
                    s = x->parent_->left_;
                }
                s->color_ = x->parent_->color_;
                x->parent_->color_ = Color::BLACK;
                s->left_->color_ = Color::BLACK;
                if (x->parent_->left_ != nullptr)
                  RotateRight(x->parent_);
                x = root_;
            }
        }
    }
    x->color_ = Color::BLACK;
  }

  class TreeSetIterator : public std::iterator<std::forward_iterator_tag, T> {
  private:
    TreeSetNode<T> *p_;

  public:
    TreeSetIterator(TreeSetNode<T> *it) : p_(it){}
    TreeSetIterator(TreeSetIterator *it) : p_(it->p_) {}

    bool operator!=(TreeSetIterator &other) const { return !(p_ == other); }
    TreeSetNode<T> &operator*() { return *p_; }
    const TreeSetNode<T> &operator*() const { return *p_; }
    TreeSetNode<T> *operator->() { return p_; }
    TreeSetIterator &operator++() {
      TreeSetNode<T> *nn = getNextNode(p_);
      p_ = nn;
      return *this;
    }
    TreeSetIterator operator++(int) {
        auto old = *this;
        ++(*this);
        return old;
    }
    bool operator==(const TreeSetIterator &other) const {
      if (this == &other) {
        return true;
      }
      return p_ == other.p_;
    }
  }; // class TreeSetIterator

  void swap(TreeSet<T> &other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  TreeSetNode<T> *root_;
  std::size_t size_;
  Compare compare;

public:
  typedef TreeSetIterator iterator;

  iterator begin() const { return iterator(getFirstNode()); }

  iterator end() const { return ++iterator(getLastNode()); }

  explicit TreeSet() : root_(nullptr), size_(0) {}

  explicit TreeSet(Compare comp) : compare(comp) {
    root_ = nullptr;
    size_ = 0;
  }

  std::size_t size() const { return size_; }

  bool isEmpty() const { return size_ == 0 ? true : false; }

  void add(const T &elem) {
    TreeSetNode<T> *parent = nullptr;
	TreeSetNode<T> *currentRoot = root_;
	while (currentRoot != nullptr) {
      parent = currentRoot;
      if (compare(elem, currentRoot->element_)) {
        currentRoot = currentRoot->left_;
      }
      else if (compare(currentRoot->element_, elem)) {
        currentRoot = currentRoot->right_;
      } else {
        return;
      }
	}
	TreeSetNode<T> *newNode = new TreeSetNode<T>(elem, parent);
	if (parent != nullptr) {
      if (compare(elem, parent->element_)) {
        parent->left_ = newNode;
      }
      else if (compare(parent->element_, elem)) {
        parent->right_ = newNode;
      } else {
        return;
      }
	}
	else
      root_ = newNode;
    size_++;
	Fixup(newNode);
  }

  bool contains(const T &elem) const {
    TreeSetNode<T> *n = root_;
    while (n != nullptr) {
      if (compare(elem, n->element_)) {
        n = n->left_;
      } else if (compare(n->element_, elem)) {
        n = n->right_;
      } else {
        return true;
      }
    }
    return false;
  }

  bool remove(const T &elem) {
    TreeSetNode<T> *z = nullptr;
    TreeSetNode<T> *x = nullptr;
    TreeSetNode<T> *y = nullptr;
    TreeSetNode<T> *node = root_;
    while (node != nullptr){
        if (node->element_ == elem) {
            z = node;
        }
        if (compare(node->element_, elem)) {
            node = node->right_;
        } else {
            node = node->left_;
        }
    }
    if (z == nullptr) {
        return false;
    }
    y = z;
    Color y_original_color = y->color_;
    if (z->left_ == nullptr) {
        x = z->right_;
        Transplant(z, z->right_);
    } else if (z->right_ == nullptr) {
        x = z->left_;
        Transplant(z, z->left_);
    } else {
        y = Min(z->right_);
        y_original_color = y->color_;
        x = y->right_;
        if (y->parent_ == z) {
          if (x != nullptr)
            x->parent_ = y;
        } else {
            Transplant(y, y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }
        Transplant(z, y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }
    delete z;
    if (y_original_color == Color::BLACK && x != nullptr){
        DeleteFixup(x);
    }
    --size_;
    return true;
  }

  const T first() {
    TreeSetNode<T> *n = getFirstNode();
    return n->element_;
  }

  const T last() {
    TreeSetNode<T> *n = getLastNode();
    return n->element_;
  }

  /* Rule of five */
  TreeSet(const TreeSet<T> &other) : TreeSet() {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      add(iter->get_element());
    }
  }

  TreeSet(TreeSet<T> &&other) noexcept
      : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  TreeSet &operator=(const TreeSet &rhs) {
    if (this != &rhs) {
      TreeSet copy(rhs);
      copy.swap(*this);
    }
    return *this;
  }

  TreeSet &operator=(TreeSet &&rhs) noexcept {
    if (this != &rhs) {
      root_ = nullptr;
      size_ = 0;
      rhs.swap(*this);
    }
    return *this;
  }

  ~TreeSet() {
    while (root_)
      removeNode(root_);
  }
}; // class TreeSet

} // namespace csc::treeset
