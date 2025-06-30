#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int char_to_integer(char c) {
    return c - 48;
}

char int_to_char(int a) {
    return a + 48;
}


class biginteger {
    public :
    vector<int> vec;
    int nbdigits = 0;
    string s;

    biginteger(string ss) : s(ss) {
        initialize_vector();
    };

    void initialize_vector() {
        for (char c : s) {
            vec.push_back(char_to_integer(c));
            nbdigits++;
        }

        // if string is "123456789"
        // vec is {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9}
    }

    void initialize_string() {
        for (int i : vec) {
            s.push_back(int_to_char(i));
        }
    }

    void print_number() {
        for (int i = 0 ; i < nbdigits ; i++) {
            cout << vec[i];
        }
    }

    void multiply_by_10_to_n(int n) {
        for (int i = 0 ; i < n ; i++) {
        vec.push_back(0);
        nbdigits++; }
    }

    biginteger operator+(biginteger nb2) {
        biginteger nb1 = *this;
        biginteger temp("");
        biginteger result("");
        if (nb1.nbdigits < nb2.nbdigits) {
            temp = nb1;
            nb1 = nb2;
            nb2 = temp;
        } 
        int k = nb1.nbdigits - nb2.nbdigits;   
        for (int i = 0 ; i < k  ; i++) {
            nb2.vec.insert(nb2.vec.begin(),0);
            nb2.nbdigits++;
        }

        int carry = 0;
        int add = 0;
        for (int i = nb2.nbdigits - 1; i >= 0 ; i--) {
            add = carry + nb1.vec[i] + nb2.vec[i];
            result.vec.insert(result.vec.begin(),add%10);
            carry = add / 10;
            result.nbdigits++;
        }

        if (carry != 0) {
            result.vec.insert(result.vec.begin() , carry);
            result.nbdigits++;
        }

        return result;
    }

    biginteger operator*(int a) {
        if (a > 9 || a < 0) {
            throw invalid_argument("what the **** !?");
        }
        biginteger big("");
        
        int carry = 0;
        int ad;
        for (int i = nbdigits - 1 ; i>= 0 ; i--) {
          ad = a * vec[i] + carry;
          big.vec.insert(big.vec.begin(),ad % 10); // eg : if a * vec[0] = 36, we just put 6; carry 3
          carry = ad / 10;
          big.nbdigits++;
        }
        if (carry != 0) {
            big.vec.insert(big.vec.begin() , carry);
            big.nbdigits++;
        }
        
        return big;
    }

    biginteger operator*(biginteger nb2) {
        biginteger result("0");
        biginteger nb1 = *this;
        biginteger temp("");
        if (nb1.nbdigits < nb2.nbdigits) {
         temp = nb1;
         nb1 = nb2;
         nb2 = temp;
        }
        biginteger sum("0");
        for (int i = nb2.nbdigits - 1 ; i >= 0 ; i--) {
            sum = nb1 * nb2.vec[i];
            sum.multiply_by_10_to_n(nb2.nbdigits - i - 1);
            result = result + sum;
        }
        return result;
    }

    

};


int main() {

biginteger A("123") , B("1324");


biginteger R1 = A + B;
R1.print_number();
cout << endl;

biginteger R2 = A * 2;
R2.print_number();
cout << endl;

biginteger R3 = A * B;
R3.print_number();
cout << endl;
    return 0;
}