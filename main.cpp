// Travis Lee Presnell - Feb 2018
//	LRSA - RSA Encryption
//	Usage:
//		-Generate Key files: 	lrsa generate
//		-Encrypt Input: 	lrsa encrypt <input>
//		-Decrypt Input:		lrsa decrypt <input>


#include <iostream>
#include "lrsa.cpp"

using namespace std;

// Generates Key-Files
void generate(){

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

// Encrypts input with pub.key
void encrypt(unsigned long long int input = 0){
	LRSA myrsa;
	unsigned long int result;

	// Loads key files
	myrsa.keys.get();

	// spacing
	cout << "\n";

	// Outputs key info
	myrsa.keys.print_pub();
	
	// Ask for integer to encrypt, in range, or use input
	if(input == 0){
		cout << "Encrypt Integer(1-" << (myrsa.keys.n - 2) << "): ";
		cin >> input;
		cout << endl;
	}
	
	// Checks input isn't > keys.n
	if(input > (myrsa.keys.n - 2)){ 
		cout << "Error: Input is too large. Valid range is 1-" << (myrsa.keys.n-1) << "\n\n";
		exit(0); 
	}

	// Runs encryption
	result = myrsa.encrypt(input);

	// Results
	cout << "Encrypted(p: " << input << ", e: " << myrsa.keys.e << ", n: " << myrsa.keys.n << "): " << result << "\n\n";
}

// Decrypts input with priv.key
void decrypt(unsigned long long int input = 0){
	
	LRSA myrsa;
	unsigned long int result;

	// Loads key files
	myrsa.keys.get();

	// spacing
	cout << "\n";
	
	// Outputs key info
	myrsa.keys.print_priv();

	// Ask for integer
	if(input == 0) {
		cout << "Decrypt Integer: ";
		cin >> input;
		cout << endl;
	}

	// runs the decryption
	result = myrsa.decrypt(input);

	// Results
	cout << "Decrypted(c: " << input << ", d: " << myrsa.keys.d << ", n: " << myrsa.keys.n << "): " << result << "\n\n";

}

// Handles program arguments
int main(int argc, char *argv[]){
		
	unsigned long long int input = 0;
	string action = "";

	if(argc == 1){
		cout << "Missing arguments.." << endl;
		exit(0);
	} else {
		action = argv[1];
		if(argc > 2) input = atoi(argv[2]);
	}
	
	// Generate Key Files
	if(action == "generate"){
		generate();
	// Encryption
	} else if(action == "encrypt"){
		encrypt(input);
	// Decryption
	} else if(action == "decrypt"){
		decrypt(input);
	// Invalid Input
	} else { 
		cout << "Invalid input" << endl;
	}

	return(0);
}
