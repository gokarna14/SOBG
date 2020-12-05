#pragma once
#include<vector>


using std::vector;

#define INT_MAX 2147483647


template <typename dt>
class LinkedList
{
    template <typename Data>
    class Node
    {
    public:
        Data data;
        Node* Next, * Previous;
    };
    public:
        Node<dt>* head = NULL;
        void insert(dt n, int pos = -99) {
            Node<dt>* N = new Node<dt>;
            N->data = n;
            if (head == NULL || head->Next == NULL)
            {
                head = new Node<dt>;
                head->Next = N;
                N->Next = N->Previous = head->Previous = NULL;
            }
            else
            {
                if (pos == 0)
                {
                    N->Next = head->Next;
                    head->Next->Previous = N;
                    head->Next = N;
                    N->Previous = NULL;
                    return;
                }
                Node<dt>* node = head->Next;
                int count = 0;
                while (node->Next != NULL && count != pos)
                {
                    node = node->Next;
                    count++;
                }
                if (node->Next == NULL && count != pos)
                {
                    node->Next = N;
                    N->Previous = node;
                    N->Next = NULL;
                }
                else
                {
                    node->Previous->Next = N;
                    N->Previous = node->Previous;
                    node->Previous = N;
                    N->Next = node;
                }

            }
        }
        void delete_(int pos = -99) {
            Node<dt>* N = head->Next;

            if (N->Next == NULL)
            {
                head->Next = NULL;
            }
            else if (pos == 0)
            {
                head->Next = N->Next;
                N->Next->Previous = NULL;
            }
            else
            {
                int count = 0;
                while (N->Next != NULL && count != pos)
                {
                    N = N->Next;
                    count++;
                }
                N->Previous->Next = NULL;
                if (N->Next != NULL)
                {
                    N->Previous->Next = N->Next;
                    N->Next->Previous = N->Previous;
                }
            }
  
            delete N;
        }

        dt get_(int pos = -99) {
            Node<dt>* N = head->Next;
            int count = 0;
            while (N->Next != NULL && count != pos)
            {
                N = N->Next;
                count++;
            }
            if (N->Next == NULL && count != pos)
            {
              //  printf("\nIndex out of range so returning the last index\n");
                count--;
            }
            return N->data;
        }
        int get_index(dt n) {
            Node<dt>* N = head->Next;
            int count = 0;
            while (N->Next != NULL && n != N->data)
            {
                N = N->Next;
                count++;
            }
            if (N->Next == NULL && n != N->data)
            {
               // printf("\nElement not found in list so returning the last index\n");
                count--;
            }
            return --count;
        }
        
        int length(Node<dt>* head)
        {
            if (head == NULL)
            {
                return -1;
            }
            return 1 + length(head->Next);
        }

        static void display(Node<dt>* Head) {
            if (Head->Next == NULL)
            {
                return;
            }
            printf("%d, ", Head->Next->data);
            display(Head->Next);
        }
};


class Graph
{
    float** adj_mat;
    int width, height;

public:

    int n, * latest_parent;
    float* latest_value;
    LinkedList<int> path;

    Graph(int width, int height)
    {
        this->height = height;
        this->width = width;
        this->n = this->width * this->height;
        this->assign_mat();
        this->latest_value = new float[n];
        this->latest_parent = new int[n];
    }
    void assign_mat()
    {
        bool next_col = true, up = true, down = true, pre_col = true;
        this->adj_mat = new float* [this->n];
        for (int i = 0; i < n; i++)
        {
            this->adj_mat[i] = new float[this->n];
        }
        int i, j;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                float a;
                
                if (j == i + 1 && j % height != 0 && up)
                    a = 1;
                else if (j == i - 1 && i % height != 0 && down)
                    a = 1;
                else if (j == i + height || i == j + height && next_col)
                    a = 1;
                else if (j == i + height + 1 && j % height != 0 && next_col)
                    a = 1.414213562;
                else if (i == j + height + 1 && i % height != 0 && next_col)
                    a = 1.414213562;
                else if (j == i - height + 1 && j % height != 0 && pre_col)
                    a = 1.414213562;
                else if (i == j - height + 1 && i % height != 0 && pre_col)
                    a = 1.414213562;
                else
                    a = 0;
                if (return_xy(i, 'x') == 3 && return_xy(i, 'y') <= 16  && (return_xy(i, 'y') >= 3))
                {
                    a = 0;
                }
                if (return_xy(i, 'x') == 28 && return_xy(i, 'y') < 9 && (return_xy(i, 'y') >= 3))
                {
                    a = 0;
                }
                if (return_xy(i, 'x') == 28 && return_xy(i, 'y') <= 16 && (return_xy(i, 'y') > 9))
                {
                    a = 0;
                }
                else if (return_xy(i, 'y') == 3 && return_xy(i, 'x') <= 29 && (return_xy(i, 'x') >= 3))
                {
                    a = 0;
                }
                else if (return_xy(i, 'y') == 16 && return_xy(i, 'x') <= 29 && (return_xy(i, 'x') >= 3))
                {
                    a = 0;
                }
                
                adj_mat[i][j] = a;
            }
        }
    }

    float return_xy(int i_value, char c)
    {
        if (c == 'x')
            return int(i_value / height);
        else
            return int(i_value % height);
    }

    float return_i(float x, float y)
    {
        return x * height + int(y)%height ;

    }

    void display();

    int selectMinVertex(vector<float>& value, vector<bool>& processed, int V);

    void dijkstra(int source_node, int final_node)
    {
        int* parent;
        parent = new int[n];
        vector<float> value(n, INT_MAX);
        vector<bool> processed(n, false);

        parent[source_node] = -1;
        value[source_node] = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            int U = selectMinVertex(value, processed, n);
            processed[U] = true;

            for (int j = 0; j < n; j++)
            {
                if (adj_mat[U][j] != 0 && processed[j] == false && value[U] != INT_MAX
                    && (value[U] + adj_mat[U][j] < value[j]))
                {
                    value[j] = value[U] + adj_mat[U][j];
                    parent[j] = U;
                }
            }
        }
        for (int i = 0; i < n; ++i)
        {
            if (i != source_node)
            {
                latest_parent[i] = parent[i];
            }
        }
        path_finder(source_node, final_node);
       // LinkedList<int>::display(path.head);
    }
    void clear_path()
    {
        int n = path.length(path.head);
        for (int i = 0; i < n; i++)
        {
            path.delete_(0);
        }
    }

private:
    void path_finder(int initial, int final)
    {
        if (initial == final)
        {
            path.insert(initial);
            return;
        }
        path_finder(initial, latest_parent[final]);
        path.insert(final);
    }
};


class Stack
{
    int index;
    LinkedList<int> L;
public:
    Stack(int n = 0)
    {
        index = -1;
        push(n);
    }
    void push(int n)
    {
        L.insert(n);
        index++;
    }
    int pop()
    {
        if (L.length(L.head) > 0)
        {
            L.delete_();
            index--;
        }
        return 0;
    }
    int top()
    {
        if (L.length(L.head) > 0)
        {
            return L.get_(index);
        }
    }
    void clear()
    {
        while (index == -1)
        {
            this->pop();
        }
    }
};