// Travis Lee Presnell - 01/2018
// RSA Encryption - Encryption.cpp
// 	Encrypts integer in range(1-(n-2)) using pub.key-file values

#include <iostream>
#include "lrsa.cpp"

main(){
	
	LRSA myrsa;
	unsigned long int p;
	unsigned long int result;

	// Loads key files
	myrsa.keys.get();

	// spacing
	cout << "\n";

	// Outputs key info
	myrsa.keys.print_pub();
	
	// Ask for integer to encrypt in range
	cout << "Encrypt Integer(1-" << (myrsa.keys.n - 2) << "): ";
	cin >> p;

	// Checks input isn't > keys.n
	if(p > (myrsa.keys.n - 2)){ 
		cout << "Error: Input is too large. Valid range is 1-" << (myrsa.keys.n-1) << "\n\n";
		exit(0); 
	}

	// Runs encryption
	result = myrsa.encrypt(p);

	// Results
	cout << "\nEncrypted(p: " << p << ", e: " << myrsa.keys.e << ", n: " << myrsa.keys.n << "): " << result << "\n\n";
}
