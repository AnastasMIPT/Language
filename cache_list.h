//
// Created by anastas on 20.04.2020.
//

#ifndef HASHTABLE_CACHE_LIST_H
#define HASHTABLE_CACHE_LIST_H


#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>

template<typename ValueType>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, ValueType, int> {

    int num;
    ValueType* data;
    int* prev;
    int* next;

public:
    ListIterator (int point, ValueType* data, int* next, int* prev) :
            num (point), data (data), prev (prev), next (next) {}

    ListIterator (const ListIterator& it) :
            num (it.num), data (it.data), prev (it.prev), next (it.next) {}

    bool operator== (ListIterator const& it) const { return num == it.num; }

    bool operator!= (ListIterator const& it) const { return num != it.num; }

    typename ListIterator::reference operator* () const { return data[num]; }

    ListIterator& operator++ () {
        num = next[num];
        return *this;
    }

    ListIterator operator++ (int) {
        ListIterator temp = *this;
        num = next[num];
        return temp;
    }

    ListIterator& operator-- () {
        num = prev[num];
        return *this;
    }

    ListIterator operator-- (int) {
        ListIterator temp = *this;
        num = prev[num];
        return temp;
    }
};


template<typename Type>
class list {
    Type* data;
    int* next;
    int* prev;

    int head;
    int free;
    int tail;

    size_t size;
    size_t max_size;
    bool sorted;

    const static unsigned int DefaultSize = 5000;
    const static int Empty = -1;
    Type Poison;

    void ListElementInit (int pos, Type data, int next, int prev);

public:

    typedef ListIterator<Type> iterator;
    typedef const    iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;

    iterator begin () {
        return ListIterator (head, data, next, prev);
    }

    iterator end () {
        return ListIterator (0, data, next, prev);
    }

    reverse_iterator rbegin () {
        return reverse_iterator (ListIterator (tail, data, next, prev));
    }

    reverse_iterator rend () {
        return reverse_iterator (ListIterator (0, data, next, prev));
    }

    explicit list (Type Poison, size_t max_size = DefaultSize);

    list ();

    ~list ();

    size_t list_size () {
        return size;
    }

    int PushFront (Type value);

    int PushBack (Type value);

    int InsertAfter (int pos, Type value);

    int InsertBefore (int pos, Type value);

    int DeleteAfter (int pos);

    int DeleteBefore (int pos);

    int DeleteFront ();

    int DeleteBack ();

    int Delete (int pos);

    void SwapElements (int pos, int cur_el);

    int SearchElementByLogicNum (int num);

    void ListSort ();

    int Dump (int limit = DefaultSize, const char* str = "Information lst");

    void DrawDump (int limit = DefaultSize, FILE* f_out = fopen ("F:\\Graphs\\output.dot", "w"));

    friend struct list_testing;


};


template<>
int list<int>::Dump (int limit, const char* str) {

    printf ("%s\n", str);

    printf ("LIST:\n"
            "{\n");
    for (int i = 0; i < limit; i++) {
        printf (" %2d ", i);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", data[i]);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", next[i]);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", prev[i]);
    }
    printf ("\n");

    printf ("head = %d\n", head);
    printf ("free = %d\n", free);
    printf ("size = %ld\n", size);
    printf ("tail = %d\n", tail);
    printf ("sorted = %d\n", sorted);
    printf ("}\n");

    return 0;
}


template<typename Type>
int list<Type>::SearchElementByLogicNum (int num) {
    if (sorted) {
        return data[num];
    } else {
        int pos = head;
        for (int i = 1; i != num && i < size + 1; i++) {
            pos = next[pos];
        }
        return data[pos];
    }
}

template<typename Type>
int list<Type>::DeleteFront () {

    sorted = false;

    int rezult = head;
    head = next[head];
    prev[rezult] = Empty;
    next[rezult] = free;
    free = rezult;
    prev[head] = 0;
    data[rezult] = Poison;
    size--;
    if (size == 0) tail = 0;
    return rezult;
}

template<typename Type>
int list<Type>::DeleteBack () {

    if (size == 0) {
        printf ("ERROR attempt delete empty element\n");
        return 0;
    }

    if (prev[tail] == 0) head = 0;


    next[prev[tail]] = 0;
    next[tail] = free;
    free = tail;
    tail = prev[tail];
    prev[free] = Empty;
    data[free] = Poison;

    size--;

    return free;
}

template<typename Type>
int list<Type>::DeleteBefore (int pos) {

    if (prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    if (prev[prev[pos]] != 0)
        return DeleteAfter (prev[prev[pos]]);

    return DeleteFront ();
}

template<typename Type>
void list<Type>::ListElementInit (int pos, Type data, int next, int prev) {

    this->data[pos] = data;
    this->next[pos] = next;
    this->prev[pos] = prev;
}

template<typename Type>
int list<Type>::Delete (int pos) {

    if (prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    if (pos != tail) sorted = false;

    if (prev[pos] != 0)
        next[prev[pos]] = next[pos];
    else {
        head = next[head];
        prev[head] = 0;
    }

    if (next[pos] != 0)
        prev[next[pos]] = prev[pos];
    else {
        tail = prev[tail];
        next[tail] = 0;
    }
    data[pos] = Poison;
    next[pos] = free;
    prev[pos] = Empty;
    free = pos;

    size--;

    return pos;
}

template<typename Type>
int list<Type>::DeleteAfter (int pos) {

    if (next[pos] == 0 || prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    sorted = false;

    if (next[next[pos]] != 0) prev[next[next[pos]]] = pos;
    data[next[pos]] = Poison;
    prev[next[pos]] = Empty;
    int buf = next[next[pos]];
    next[next[pos]] = free;
    free = next[pos];
    next[pos] = buf;
    size--;

    if (next[pos] == 0) tail = pos;

    return free;
}

template<typename Type>
int list<Type>::InsertBefore (int pos, Type value) {

    if (prev[pos] == Empty) {

        printf ("ERROR attempt to insert before empty element\n");
        return 0;

    }
    if (prev[pos] == 0) return PushFront (value);
    return InsertAfter (prev[pos], value);

}

template<typename Type>
void list<Type>::ListSort () {

    int cur_el = head;

    for (int pos = 1; pos < size + 1; pos++) {
        printf ("pos = %d , cur_el = %d\n", pos, cur_el);
        if (cur_el != pos && cur_el != 0) {
            SwapElements (pos, cur_el);
        }
        cur_el = next[pos];
        Dump (20);
    }

    sorted = true;
    tail = size;
}

template<typename Type>
void list<Type>::SwapElements (int pos, int cur_el) {

    int n_pos = pos;
    int n_cur_el = cur_el;
    std::swap (data[pos], data[cur_el]);


    if (next[pos] == cur_el || next[cur_el] == pos) {

        if (next[cur_el] == pos) {
            n_pos = cur_el;
            n_cur_el = pos;
        }

        next[prev[n_pos]] = n_cur_el;
        prev[n_cur_el] = prev[n_pos];

        next[n_pos] = next[n_cur_el];
        prev[next[n_cur_el]] = n_pos;

        prev[n_pos] = n_cur_el;
        next[n_cur_el] = n_pos;
    } else {
        next[prev[pos]] = cur_el;
        prev[next[pos]] = cur_el;

        next[prev[cur_el]] = pos;
        prev[next[cur_el]] = pos;

        std::swap (next[pos], next[cur_el]);
        std::swap (prev[pos], prev[cur_el]);
    }

    if (pos == head) {
        head = cur_el;
        next[0] = 0;
    } else if (cur_el == head) {
        next[0] = 0;
        head = pos;
    }
    if (pos == tail) {
        tail = cur_el;
        prev[0] = 0;
    } else if (cur_el == tail) {
        tail = pos;
        prev[0] = 0;
    }
    if (pos == free) {
        free = cur_el;
        prev[next[cur_el]] = -1;
    } else if (cur_el == free) {
        free = pos;
        prev[next[pos]] = -1;
    }
}

template<typename Type>
list<Type>::list (Type Poison, size_t max_size) :  free (1), head (0), size (0), sorted (true), tail (0) {

    this->Poison = Poison;
    data = new Type[max_size];
    next = new int[max_size];
    prev = new int[max_size];

    for (int i = 1; i < DefaultSize; i++) {
        next[i] = i + 1;
    }

    for (int i = 1; i < DefaultSize; i++) {
        prev[i] = -1;
    }


    for (int i = 1; i < DefaultSize; i++) {
        data[i] = Poison;
    }

}

template<typename Type>
list<Type>::list () : max_size (DefaultSize), free (1), head (0), size (0), sorted (true), tail (0) {

    data = new Type[max_size];
    next = new int[max_size];
    prev = new int[max_size];

    for (int i = 1; i < DefaultSize; i++) {
        next[i] = i + 1;
    }

    for (int i = 1; i < DefaultSize; i++) {
        prev[i] = -1;
    }
}

template<typename Type>
list<Type>::~list () {

    delete[] (data);
    delete[] (next);
    delete[] (prev);
}

template<typename Type>
int list<Type>::InsertAfter (int pos, Type value) {
    if (prev[pos] == Empty) {
        printf ("ERROR attempt to insert after empty element\n");
        return 0;
    }

    if (pos != tail && size != 0) sorted = false;


    if (size == 0) return PushFront (value);

    size += 1;

    data[free] = value;
    int buf = free;
    free = next[free];

    next[buf] = next[pos];
    prev[buf] = pos;
    if (next[buf] != 0) prev[next[buf]] = buf;
    if (next[buf] == 0) tail = buf;
    next[pos] = buf;


    return buf;
}

template<typename Type>
int list<Type>::PushFront (Type value) {
    if (size != 0) {
        sorted = false;
    }


    int pos = free;
    data[pos] = value;
    free = next[free];
    next[pos] = head;
    head = pos;
    if (next[pos] != 0) prev[next[pos]] = pos;
    prev[pos] = 0;
    if (size == 0) tail = pos;
    size++;
    return pos;
}

template<typename Type>
int list<Type>::PushBack (Type value) {
    //sorted = false;


    int pos = free;
    if (size == 0) head = pos;
    free = next[free];
    ListElementInit (pos, value, 0, tail);
    if (tail != 0) next[tail] = pos;
    tail = pos;
    size++;

    return pos;
}


template<typename Type>
int list<Type>::Dump (int limit, const char* str) {
    printf ("%s\n", str);

    printf ("LIST:\n"
            "{\n"
            "data[]:\n");

    for (int i = 0; i < limit; i++) {
        std::cout << data[i] << " ";
    }


    printf ("\n"
            "next[]:\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", next[i]);
    }
    printf ("\n"
            "prev[]:\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", prev[i]);
    }
    printf ("\n");

    printf ("head = %d\n", head);
    printf ("free = %d\n", free);
    printf ("size = %ld\n", size);
    printf ("tail = %d\n", tail);
    printf ("sorted = %d\n", sorted);
    printf ("}\n");

    return 0;


}


template<typename Type>
void list<Type>::DrawDump (int limit, FILE* f_out) {
    assert (f_out);
    fprintf (f_out, "digraph G {\n"
                    "ranksep = 1.8;\n"
                    "subgraph Head {\n"
                    "\tHEAD [label = \"head\"]\n"
                    "\tedge[color=\"Orange\"]\n"
                    "HEAD->A:%d1\n"
                    "\tlabel = \"\";\n"
                    "}\n"
                    "subgraph Empty {\n"
                    "\tEMPTY [label = \"empty\"]\n"
                    "\tedge [color=\"gray\", arrowsize=\"0.5\", penwidth=\"1\", constrain = \"false\", weigth = \"0.1\"];\n",
             head);

//    for (int i = free; i < limit; i = next[i]) {
    //      fprintf (f_out, "EMPTY->A:i%d\n", i);
    // }
    fprintf (f_out, "EMPTY->A:%d1\n", free);
    fprintf (f_out, "A:%d2", free);

    for (int i = next[free]; i != 0 && i < limit; i = next[i]) {
        fprintf (f_out, "->A:%d1\n", i);\
        if (next[i] != 0) fprintf (f_out, "A:%d2", i);
    }

    fprintf (f_out, "\tlabel = \"\";\n"
                    "}\n"
                    "\n"
                    "subgraph List {\n"
                    "\tA [shape = \"record\", label = \"{{<01> | <02> } |<i0> %d |<val0> %d | {<03> | <04> }}",
             0, data[0]);

    for (int i = 1; i < limit; i++) {
        fprintf (f_out, "| {{<%d1> | <%d2> } |<i%d> %d |<val%d> %d | {<%d3> | <%d4> }}", i, i, i, i, i, data[i], i,
                 i);
    }
    fprintf (f_out, "\"]\n");
    fprintf (f_out, "    lebel = \"\";\n"
                    "}\n"
                    "\n"
                    "{rank = same; HEAD; EMPTY;}\n"
                    "{rank = same; A;}\n"
                    "subgraph Next {\n"
                    "\tedge[color=\"#ffcbdb\"]\n");
    fprintf (f_out, "A:%d2", head);

    for (int i = next[head]; i != 0; i = next[i]) {
        fprintf (f_out, "->A:%d1\n", i);\
        if (next[i] != 0) fprintf (f_out, "A:%d2", i);
    }

    fprintf (f_out, "\n\tlebel = \"\";\n"
                    "}\n"
                    "subgraph Prev {\n"
                    "\tedge[color=\"#98ff98\"]\n");

    //Prev
    fprintf (f_out, "A:%d3", tail);
    for (int i = prev[tail]; i != 0; i = prev[i]) {
        fprintf (f_out, "->A:%d4\n", i);
        if (prev[i] != 0) fprintf (f_out, "A:%d3", i);
    }


    fprintf (f_out, "\tlabel = \"\";\n"
                    "}\n"
                    "}\n");

    fclose (f_out);
}

#endif //HASHTABLE_CACHE_LIST_H
