#include <iostream> 
using namespace std; 
  
// Header files, namespaces, 
// macros as defined above 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<class T> using ordered_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Driver program to test above functions 
int main() 
{ 
    ordered_multiset<int> s; 
  
    // insert function to insert in 
    // ordered set same as SET STL 
    s.insert(5); 
    s.insert(1);
    s.insert(1); 
    s.insert(2);
	for(int i : s) cout << i << ' ';
	cout << endl;

	// int oredered_multiset lower_bound work as upperbound and viceversa 
	// but for ordered_set they work just like in stl set
	auto it = s.upper_bound(2);
	s.erase(it); // will erasse 2 from the set not 3
	for(int i : s) cout << i << ' ';
}
