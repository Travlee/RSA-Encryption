// Travis Lee Presnell - 01/2018
// RSA Encryption - LRSA.cpp
//	LRSA: Class with methods for generate.cpp/encrypt.cpp/decrypt.cpp
// 	Keys: Class which manages the keys ofc

#include <iostream>	// lib for cout magic
#include <cstdlib> 	// lib for srand & rand func
#include <cmath>	// lib for sqrt
#include <ctime>	// lib for time
#include <fstream>	// lib for files

using namespace std; 	// QOL improvements

// Container for prub/priv keys.
class Keys{
public:
	unsigned long int n = 0;
	unsigned long int e = 0;
	unsigned long int d = 0;

	// Reads both pub.key & priv.key files; stores values as e, d, n
	void get(){
		
		ifstream f{"pub.key", ios::in};
		f >> e >> n;
		f.close();
		f.open("priv.key", ios::in);
		f >> d >> n;
		f.close();

	}
	// Writes both key files to disk in current dir
	void write(){
		ofstream f{"priv.key", ios::out};
		f << d << " " << n << "\n";
		f.close();
		f.open("pub.key", ios::out);
		f << e << " " << n << "\n";
		f.close();
	}
	
	// Prints the private_key info all pretty like
	void print_priv(){
		cout << "Private Key {d: " << d << ", n: " << n << "}\n\n";
	}
	// Prints the pub_key info all pretty like
	void print_pub(){
		cout << "Public Key {e: " << e << ", n: " << n << "}\n\n";
	}

};

class LRSA{
private:
	// Recursive function that generates a rand int(2-max) then 
	// 	makes sure it's prime before returing.
	int get_prime(int max){
		int temp = 2 + (rand() % max);	
		
		if(!is_prime(temp)) temp = get_prime(max);
	
		return(temp);
	}

	// Rand int in range(1-max)
	int myrand(int max){
		return(1 + (rand() % max));
	}
	
	// Checks if input is prime using a loop; returns bool
	// 	Had to phone a friend on this one, and that friend was the internet.
	// 	Loops through all digits less than the sqrt(input) to see if any are divisors.
	bool is_prime(int value){
		
		for(int i = 2; i <= sqrt(value); i++){
			if(value % i == 0) return false;
		}
		return true;
	}
	
	// Finds the greatest common divisor, if the result is > 1, then it isnt coprime; return bool
	bool coprime(int a, int b){
		unsigned int x;
		while(b){
			x = a % b;
			a = b;
			b = x;
		}
		if(a > 1) return false;
		return true;
	}

	// Makes big numbers more managable for all this math!
	// 	Spent waaaaay too much time thinking about this issue, the greatest solution though..
	// 	Takes the input from either self.encrypt/self.decrypt, along with the key info
	// 	Finally, breaks the number into smaller parts and does the work from there; returns int
	// 	it's also very fancy
	int fancy(unsigned long long int input, unsigned long long int ex, unsigned long long int mod){
		
		unsigned long long int result = 1;
		
		// If the exponent isn't even, take 1 from ex, then set result to input.
		// Trust me it works.
		if(ex % 2 != 0){
			ex -= 1;
			result = input;
		}
		// Loops through and squares input for ex/2
		for(int i = 0, j = ex/2; i < j; i++){
			result = (result * (unsigned long long int)pow(input, 2)) % mod; 
		}
		
		return result % mod;
	}

public:
	// Secret helpful stuff
	unsigned int p;
	unsigned int q;
	Keys keys;

	// Constructor
	LRSA(){}

	// Generates RSA Key-Files
	void generate_keys(){
		
		// Feeds the seed for better rand()
		srand(time(NULL));
		
		// Vars used in the magic-math
		unsigned long int t = 0;
		unsigned long int d = 0;
		unsigned long int e = 0;
		unsigned long int n = 0;

		// Gets random, unique primes
		p = get_prime(100);
		q = get_prime(100);
		// Makes sure p and q aren't the same number; not sure if important
		while(q == p){
			q = get_prime(100);
		}

		// Calcs n & t
		//	the hardest part of all this...
		n = p * q;
		t = (p - 1) * (q - 1);
		
		// Finds e; makes sure e fits the constraints
		//	1 < e < t && coprime(e, t)
		e = myrand(t-1);
		while(!coprime(e, t)){ e = myrand(t-1); }

		// Finds the D; tests all values in 1-n
		//	d = i*e mod t = 1
		for(int i = 1, x = 0; i < n; i++){
			x = (e * i) % t;
			if(x == 1){
				d = i;
				break;
			}
		}
	
		// fills key object
		keys.n = n;
		keys.e = e;
		keys.d = d;
	}	
	
	// Pretty clean below as i do most of the work in self.fancy
	//	Not much to talk about..
	int encrypt(unsigned long long int input){
		
		unsigned long long int c = 0;
		
		c = fancy(input, keys.e, keys.n);

		return(c);
	}
	
	// Pretty clean below as i do most of the work in self.fancy
	//	Not much to talk about..
	int decrypt(unsigned long long int input){

		unsigned long long int p = 0;
		
		p = fancy(input, keys.d, keys.n);

		return(p);
	}
};
