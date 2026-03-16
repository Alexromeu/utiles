#include <iostream>
#include <string>

using namespace std;


// double computeInterest (double base_val, double rate, int years)
// {
//     double final_multiplier = 1;
//     for ( int i = 0; i < years; i++ )
//         {
//             final_multiplier *= (1 + rate);
//         }
//     return base_val * final_multiplier;
// }
// int main ()
// {
//     double base_val;
//     double rate;
//     int years;
//     cout << "Enter a base value: ";
//     cin >> base_val;
//     cout << "Enter an interest rate: ";
//     cin >> rate;
//     cout << "Enter the number of years to compound: ";
//     cin >> years;
//     cout << "After " << years << " you will have " << computeInterest(
//     base_val, rate, years ) << " money" << endl;
// }


// struct LinkedList
// {
//     int val;
//     LinkedList *next;
// };

// void printList (const LinkedList *lst)
// {
//     if ( lst != nullptr )
//     {
//         cout << lst->val;
//         cout << "\n";
//         printList( lst->next );
//     }
// }

// int main ()
// {
//     LinkedList *lst;
//     lst = new LinkedList;
//     lst->val = 10;
//     lst->next = new LinkedList;
//     lst->next->val = 11;
//     lst->next->next = nullptr;
//     printList( lst );
//     return 0;
// }

// int main ()
// {
// int factorial = 1;
// for ( int i = 0; i < 10; i++ )
// {
// factorial *= i;
// }
// int sum = 0;
// for ( int i = 0; i < 10; i++ )
// {
// sum += i;
// }
// // factorial w/o two
// int factorial_without_two = 1;
// for ( int i = 0; i < 10; i++ )
// {
// if ( i == 2 )
// {
// continue;
// }
// factorial_without_two *= i;
// }
// // sum w/o two
// int sum_without_two = 0;
// for ( int i = 0; i < 10; i++ )
// {
// if ( i = 2 )
// {
// continue;
// }
// sum_without_two += i;
// }
// }


// int exponent (int base, int exp)
// {
//     int running_value = 1;
//     for ( int i = 0; i < exp; i++ )
//     {
//         running_value *= base;
//     }
//     return running_value;
// }

// int main()
// {
//     int base;
//     int exp;
//     cout << "Enter a base value: ";
//     cin >> base;
//     cout << "Enter an exponent: ";
//     cin >> exp;
//     cout << exponent( base, exp );

//     return 0;
// }

// int sumValues (int *values, int n)
// {
//     int sum = 0;
//     for ( int i = 0; i <= n; i++ )
//     {
//         sum += values[ i ];
//     }
//     return sum;
// }

//     int main()
//     {
//         int size;
//         cout << "Enter a size: ";
//         cin >> size;
//         int *values = new int[ size - 1 ];
//         int i = 0;
//         while ( i < size )
//         {
//             cout << "Enter value to add: ";
//             ++i;
//             cin >> values[i];
//         }
//         cout << "Total sum is: " << sumValues( values, size );
//         return 0;
// }


struct Node
{
    int val;
    Node *p_next;
};


int main()
{
    int val;
    Node *p_head = nullptr;

    while ( 1 )
    {
        cout << "Enter a value, 0 to replay: " <<endl;
        cin >> val;

        if ( val == 0 )
        {
            break;
        }

        Node *p_temp = new Node;
        p_temp->val = val;
        p_temp->p_next = p_head;
        p_head = p_temp;
    }

        Node *p_itr = p_head;
        while ( p_itr != nullptr )
            {
                cout << p_itr->val << endl;
                p_itr = p_itr->p_next;          
                p_head = p_itr;
            }
}