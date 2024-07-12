#include <iostream>
// in some compilers u must incude this for INT32_MIN
#include <cinttypes>

using namespace std;

class LinkedList
{
    friend class STACK;
private:
    struct Node
    {
        int data;
        Node* next;
    };
    Node* first = nullptr;
public:
    ~LinkedList()
    {
        clear();
    }
    void clear()
    {
        Node* current = first;
        while (current)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        first = nullptr;
    }

    void create(int A[], int n)
    {
        int i;
        Node* t, * last;
        first = new Node();
        first->data = A[0];
        first->next = nullptr;
        last = first;
        for (i = 1; i < n; i++)
        {
            t = new Node();
            t->data = A[i];
            t->next = nullptr;
            last->next = t;
            last = t;
        }
    }

    void display() const
    {
        Node* temp = first;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
    void displayReverse() const
    {
        RDisplay(first);
    }

    int count()
    {
        int c = 0;
        Node* temp = first;
        while (temp)
        {
            c++;
            temp = temp->next;
        }
        return c;
    }

    int sum()
    {
        int res = 0;
        Node* temp = first;
        while (temp)
        {
            res += temp->data;
            temp = temp->next;
        }
        return res;
    }

    int max()
    {
        int m = INT32_MIN;
        Node* temp = first;
        while (temp)
        {
            if (temp->data > m)
                m = temp->data;
            temp = temp->next;
        }
        return m;
    }
    int maxUsingRecursion()
    {
        return maxUsingRecursion(first);
    }

    Node* search(int key)
    {
        Node* temp = first;
        while (temp)
        {
            if (temp->data == key)
                return temp;
            temp = temp->next;
        }
        return nullptr;

    }
    Node* searchImproving(int key)
    {
        if (first->data == key)
            return first;
        Node* p = first;
        Node* q = nullptr;
        while (p)
        {
            if (p->data == key)
            {
                q->next = p->next;
                p->next = first;
                first = p;
            }
            q = p;
            p = p->next;
        }
        return nullptr;
    }

    void insert(int index, int key)
    {
        if (index > count() || index < 0)
            return;

        Node* p = new Node();
        p->data = key;
        if (index == 0)
        {

            p->next = first;
            first = p;
        }
        else
        {
            Node* temp = first;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            p->next = temp->next;
            temp->next = p;
        }
    }
    void insertSorted(int x)
    {
        Node* t, * q = nullptr, * p = first;
        t = new Node();
        t->data = x;
        t->next = nullptr;

        if (!first)
            first = t;
        else
        {
            while (p && p->data < x)
            {
                q = p;
                p = p->next;
            }
            if (p == first)
            {
                t->next = first;
                first = t;
            }
            else
            {
                t->next = q->next;
                q->next = t;
            }
        }
    }

    void Delete(int key)
    {
        if (!first)
            return;
        if (first->data == key)
        {
            Node* p = first;
            first = first->next ? first->next : nullptr;
            delete p;
        }
        else
        {
            Node* p = first->next;
            Node* q = first;
            while (p && p->data != key)
            {
                q = p;
                p = p->next;
            }
            if (!p)
                return;
            q->next = p->next;
            delete p;
        }
    }
    void deleteByIndex(int index)
    {
        if (index < 0 || index > count() - 1)
            return;
        if (index == 0)
        {
            Node* p = first;
            first = first->next;
            delete p;
        }
        else
        {
            Node* p = first;
            Node* q = nullptr;

            for (int i = 0; i < index; i++)
            {
                q = p;
                p = p->next;
            }

            q->next = p->next;
            delete p;
        }
    }

    bool is_sorted()
    {
        if (!first) return false;
        if (count() == 1) return true;
        int x = INT32_MIN;
        Node* p = first;

        while (p)
        {
            if (p->data < x)
                return false;
            x = p->data;
            p = p->next;

        }

        return true;

    }

    void remove_dublicates()
    {
        if (!first || count() == 1) return;
        Node* p = first;
        Node* q = first->next;
        while (q)
        {
            if (p->data != q->data)
            {
                p = q;
                q = q->next;
            }
            else
            {
                p->next = q->next;
                delete q;
                q = p->next;
            }

        }
    }

    void reverse()
    {
        Node* p = first, * q = nullptr, * r = nullptr;
        while (p)
        {
            r = q;
            q = p;
            p = p->next;
            q->next = r;
        }
        first = q;
    }
    void RReverse()
    {
        RReverse(nullptr, first);
    }

private:
    void RReverse(Node* q, Node* p)
    {
        if (p)
        {
            RReverse(p, p->next);
            p->next = q;
        }
        else
        {
            first = q;
        }
    }
    int maxUsingRecursion(Node* temp)
    {
        if (!temp)
            return INT32_MIN;
        int x = maxUsingRecursion(temp->next);
        return  x > temp->data ? x : temp->data;
    }
    void RDisplay(Node* temp) const
    {
        if (temp)
        {
            RDisplay(temp->next);
            cout << temp->data << " ";
        }
    }

};

class STACK
{
private:
    typedef typename LinkedList::Node Node;
    Node* top;
    int size;
public:
    STACK() :size{}, top{ nullptr } {}
    ~STACK()
    {
        while (top)
        {
            Node* p = top->next;
            delete top;
            top = p;
        }
    }

    void push(int x)
    {
        Node* t = new Node();
        t->data = x;
        t->next = top;
        top = t;
        size++;
        
    }

    bool isEmpty() { return size == 0; }

    void pop()
    {
        if (isEmpty())
            cout << "STACK IS EMPTY! " << endl;
        else
        {
            Node* p = top;
            top = top->next;
            delete p;
            --size;
        }
    }

    void display() const
    {
        Node* p = top;
        while (p)
        {
            cout << p->data << " ";
            p = p->next;
        }
    }

    int peek(int pos)
    {
        Node* p = top;
        for (int i = 0; p&&i < pos - 1; i++)
            p = p->next;
        return p ? p->data : -1;
    }

    int stackTop()
    {
        if (top)
            return top->data;
        return -1;
    }
};

int isBalanced(string s)
{
    STACK st;
    for (int i = 0; i < s.length(); i++)
    {

        int c = s[i];

        if (c == '(' || c == '{' || c == '[')
            st.push(c);
        
        else if (c == ')' || c == '}' || c == ']')
        {
            if (st.isEmpty())
                return false;

            int top = st.stackTop();

            if ((c == ')' && top == '(') || (c == '}' && top == '{') || (c == ']' && top == '['))
                st.pop();
            else return false;
        }
    }
    return st.isEmpty();
}

bool is_higher_precedence(char operator_one, char operator_two)
{
    int precedence_one;
    int precedence_two;

    switch (operator_one) {
    case '+':
    case '-':
        precedence_one = 1;
        break;
    case '*':
    case '/':
    case '%':
        precedence_one = 2;
        break;
    default:
        return false;
    }

    switch (operator_two) {
    case '+':
    case '-':
        precedence_two = 1;
        break;
    case '*':
    case '/':
    case '%':
        precedence_two = 2;
        break;
    default:
        return false;
    }

    return precedence_one >= precedence_two;
}


string infix_to_postfix(string s)
{
    STACK mina;
    string postfix;
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (c < '10' && c >= '0')
            postfix.push_back(c);
        else
        {
            if (mina.isEmpty())
                mina.push(c);
            else
            {
                while (!mina.isEmpty()&& is_higher_precedence(mina.stackTop(),c))
                {
                    postfix += mina.stackTop();
                    mina.pop();
                }
                mina.push(c);
            }

        }

    }
    while (!mina.isEmpty())
    {
        postfix += mina.stackTop();
        mina.pop();
    }
    return postfix;
}


int isOperand(char x)
{
    if (x == '+' || x == '-' || x == '/' || x == '*' || x == '(' || x == ')' || x == '^')
        return 0;
    else
        return 1;
}

int outPre(char x) {
    if (x == '+' || x == '-')
        return 1;
    else if (x == '/' || x == '*')
        return 3;
    else if (x == '^')
        return 6;
    else if (x == '(')
        return 7;
    else if (x == ')')
        return 0;
    else
        return -1;
}

int inPre(char x) {
    if (x == '+' || x == '-')
        return 2;
    else if (x == '/' || x == '*')
        return 4;
    else if (x == '^')
        return 5;
    else if (x == '(')
        return 0;
    else
        return -1;
}
string TO_POST_FIX(string s)
{
    STACK mina;
    string postfix;
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (isOperand(c))
        {
            postfix.push_back(c);
        }
        else
        {
            if (mina.isEmpty() || outPre(c) > inPre(mina.stackTop()))
            {
                mina.push(c);
            }
            else
            {
                if (outPre(c) == inPre(mina.stackTop()))
                {
                    mina.pop();
                }
                else
                {
                    postfix += mina.stackTop();
                    mina.pop();
                }
            }
        }
    }
    while (!mina.isEmpty() ) {
        postfix.push_back(mina.stackTop());
        mina.pop();
    }
    return postfix;
}


int eval(string postfix)
{
    STACK mina;
    int x1, x2, r;
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isOperand(postfix[i]))
        {
            mina.push((postfix[i] - '0'));
        }
        else
        {
            x2 = mina.stackTop(); mina.pop();
            x1 = mina.stackTop(); mina.pop();
            switch (postfix[i])
            {
            case '+':
                r = x1 + x2;
                mina.push(r);
                break;
            case '-':
                r = x1 - x2;
                mina.push(r);
                break;
            case '*':
                r = x1 * x2;
                mina.push(r);
                break;
            case '/':
                r = x1 / x2;
                mina.push(r);
                break;
            default:
                break;
            }

        }
    }
    return mina.stackTop();
}

int main()
{
    cout << isBalanced("[((){}]") <<endl;
    cout << eval(infix_to_postfix("1+2*4/2"));

}

