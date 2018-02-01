// Travis Lee Presnell - 01/2018
// RSA Encryption - Generate.cpp
//	 Generates pub & priv key files with <=100 primes

#include <iostream>
#include "lrsa.cpp"

using namespace std;

main(){

	LRSA myrsa;

	// Generates Keys
	myrsa.generate_keys();

	// spacing
	cout << "\n";
	
	// Outputs Variables all pretty like
	cout << "Found {p: " << myrsa.p << ", ";
	cout << "q: " << myrsa.q << ", ";
	cout << "n: " << myrsa.keys.n << ", ";
	cout << "e: " << myrsa.keys.e << ", ";
	cout << "d: " << myrsa.keys.d << "}\n\n";
	
	myrsa.keys.print_pub();
	myrsa.keys.print_priv();

	// Writes keys to current dir
	myrsa.keys.write();

}
