// Travis Lee Presnell - 01/2018
// RSA Encryption - Decryption.cpp
// 	Decrypts integer using priv.key-file values

#include <iostream>
#include "lrsa.cpp"

main(){
	LRSA myrsa;
	unsigned long int c;
	unsigned long int result;

	// Loads key files
	myrsa.keys.get();

	// spacing
	cout << "\n";
	
	// Outputs key info
	myrsa.keys.print_priv();

	// Ask for integer
	cout << "Decrypt Integer: ";
	cin >> c;

	// runs the decryption
	result = myrsa.decrypt(c);

	// Results
	cout << "\nDecrypted(c: " << c << ", d: " << myrsa.keys.d << ", n: " << myrsa.keys.n << "): " << result << "\n\n";

}
