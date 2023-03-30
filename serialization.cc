#include <istream>
#include <iostream>
#include <sstream>
#include <iostream>

using namespace std;

struct Product
{
    string name;
    double price;
    int inventory;
};

// return ostream object
ostream& operator<<(ostream& os, Product const& product)
{
    return os << product.name << ": "
              << product.price << " kr ("
              << product.inventory << " available)";
}

// for price, inventory
template <typename T>
T read(istream& is)
{
    T data;
    is >> data;
    return data;
}

// specialization for name
template<>
string read<string>(istream& is) {
    string str;
    // sets the maximum number of characters to ignore
    is.ignore(numeric_limits<streamsize>::max(), '#');
    getline(is, str, '#');
    return str;
}

// specialization for reading Product obj
template<>
Product read<Product>(istream& is)
{
    Product product{
        read<string>(is),
        read<double>(is),
        read<int>(is),
    };
    return product;
}

// for product.price, product.inventory
template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

// for product.name
void write(ostream& os, string const& str) {
    os << '#' << str << '#';
}

void write(ostream& os, Product const& product) {
    write(os, product.name);
    write(os, product.price);
    write(os, product.inventory);
}

int main()
{
    stringstream ss;
    { // send data to ss

        // generate product obj
        Product apple {"Red Apple", 1.5, 100};
        Product laptop{"Laptop", 5995.0, 10};
        Product monitor{"4K Monitor", 8790.0, 1};
        // write into serial ss
        /*
            1. first call void write(ostream& os, Product const& product)
            2. the firstline is string : product.name
            3. second and third line are double and int
        */
        write(ss, apple);
        write(ss, laptop);
        write(ss, monitor);
    }

    cout << ss.str() << endl;

    { // recieve data from ss

        /*
            1. first call void Product read<Product>(istream& is)
            2. the firstline is string : name
            3. second and third line are double and int
        */
        Product apple  {read<Product>(ss)};
        Product laptop {read<Product>(ss)};
        Product monitor{read<Product>(ss)};
        cout << apple << endl
             << laptop << endl
             << monitor << endl;
    }
}