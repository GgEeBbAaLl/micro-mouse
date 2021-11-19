#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <limits.h>
#include <vector>
#include <set>

using namespace std;

const int LABIRYNT_WIDTH = 8;
const int LABIRYNT_HEIGHT = 8;
const int BOX_LENGHT = 20; // cm

int get_bit(char* data, int n)
{
    uint byte_index = n / CHAR_BIT;
    uint bit_index = n % CHAR_BIT;
    uint bit_mask = (1 << bit_index);
    return (data[byte_index] & bit_mask != 0);
}

void set_bit (char* data, int n)
{
    uint byte_index = n / CHAR_BIT;
    uint bit_index = n % CHAR_BIT;
    uint bit_mask = (1 << bit_index);

    data[byte_index] |= bit_mask;
}

void clear_bit (char* data, int n)
{
    uint byte_index = n / CHAR_BIT;
    uint bit_index = n % CHAR_BIT;
    uint bit_mask = (1 << bit_index);

    data[byte_index] &= ~bit_mask;
}

void print_list (char* data, int n){
    for (int i = 0; i < n * CHAR_BIT; i++) {
        cout << "Element nr. " << i << " = " << get_bit(data, i) << endl;
    }
}

void save_side (char* data, bool iswall, int x_pos, int y_pos) {
    int cell_x = x_pos / BOX_LENGHT;
    int cell_y = y_pos / BOX_LENGHT;
    if (iswall) 
    {
        set_bit(data, cell_y * LABIRYNT_WIDTH + cell_x);
    } else {
        clear_bit(data, cell_y * LABIRYNT_WIDTH + cell_x);
    }
}

struct Node{
    int x; 
    int y;
    Node* parent;
    float gCost;
    float hCost;
    float fCost;
};

inline bool operator < (const Node& n1, const Node& n2) {
    return n1.fCost < n2.fCost;
}

inline bool operator == (const Node& n1, const Node& n2) {
    if (n1.x == n2.x && n1.y == n2.y)
    {
        return true;
    }
    return false;
}

class AStar
{   
    static bool isDestination (Node& current, Node& dest) {
        return current == dest;
    }
    static double calculateHCost (Node& current, Node& dest) {
        return dest.x - current.x + dest.y - current.y;
    }
};

int main () {

    int num_of_bytes = LABIRYNT_WIDTH * LABIRYNT_HEIGHT * 4 / CHAR_BIT;

    char* data = (char *) malloc(num_of_bytes);

    if (data != NULL) {       

        for (int i = 0; i < num_of_bytes * CHAR_BIT; i++) {
            int bit = (int)get_bit(data, i);
            cout << "Elem nr. " << i << " = " << bit << endl;
        }
        for (int i = 0; i < num_of_bytes * CHAR_BIT; i++) {
            set_bit(data, i);
        }
        // set_bit(data, 3);
        // set_bit(data, 2);
        // set_bit(data, 1);
        // set_bit(data, 0);
        print_list(data, num_of_bytes);
    }

    free(data);

    return 0;
}