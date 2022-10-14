#include <iostream>
#include <climits>

	//Function Decleration

	bool verify_checksum( unsigned int n );
	unsigned int add_checksum( unsigned int n );
	void add_checksum( unsigned int array[], std::size_t capacity );
	unsigned int remove_checksum( unsigned int n );
	void remove_checksum( unsigned int array[], std::size_t capacity );

	//Calculate checksum using decimal moving operations
	//such as mod 10 which determines the last digit from 
	//8 digit number without implementing an array.

	unsigned int add_checksum( unsigned int n ) {

		int temp1;
		int digit2{0};
		int digit{0};
		int sum{0};
		int checksum;

		//count is implemented so that all decremented by two digits
		//can be multiplied by 2.

		unsigned int count{0};
		if (n<=99999999){
			temp1 = n;

			while (n > 0) {

				digit = n%10;
				n /= 10;

				if ((count%2) == 0) {
					digit*=2;

					//checking if digit is greater than 9 
					//and adding the sum of the doubled number.

					if (digit>9) {
						int temp = digit%10;
						digit2 = digit - temp;
						digit2 /= 10;
						digit2 += temp;
						digit = digit2;
					}
				}

				//sum is calculated of all digits other than the checksum digit.
				sum += digit;
				count++;
			}
				checksum = (sum*9)%10;

				//return the checksum included with the other 8 digit number.

				return ((temp1*10) + checksum);
		}
		else{
			return UINT_MAX;
		}
	}

	//manipulate the entries within the array which have an 8 digit number
	//and the the checksum digit being the 9th digit.

	//ivoking the checksum function takes in the 8 digit and cancatonates 
	//the 9th checksum digit.

	void add_checksum( unsigned int array[], std::size_t capacity ){
		for (int k{0}; k<capacity; k++){
			array[k] = add_checksum(array[k]);
		}
	}

	//check if the add checksum function actually works
	//by turing that 9th digit number into an 8th digit number.
	//You then want to invoke your brilliant add_checksum function
	//to get a 9 digit number and compare it to the correct
	//number "n".

	bool verify_checksum( unsigned int n ){
		if (n<1e9){

			if (add_checksum(n/10) == n){
				return true;
			}
			else{
				return false;
			}
		}

		else{
			return false;
		}
	}

	//check if the add checksum number is greater than the 9 digit
	//and return that maximum unsigned integer.
	//otherwise we will return the 8 digit number.

	unsigned int remove_checksum( unsigned int n ){
		if (!verify_checksum(n)){
			return UINT_MAX;
		}

		else{
			return n/10;
		}
	}

	//check if the 9 digit number has the correct checksum digit then we 
	//will remove the checksum digit. Otherwise, we will assign that entry
	//to be the maximum unsigned integer.

	void remove_checksum( unsigned int array[], std::size_t capacity ){

		for (int i{0}; i<capacity; i++){
			if (verify_checksum(array[i])) {
				array[i] = array[i] / 10;
			}
			else {
				array[i] = UINT_MAX;
			}
		}
	}

	#ifndef MARMOSET_TESTING
	int main();
	#endif
	#ifndef MARMOSET_TESTING
	int main() {
		unsigned int value_to_protect{21352411};
		unsigned int protected_value = add_checksum(value_to_protect);

		std::cout << "The value " << value_to_protect
			<< " with the checksum added is " << protected_value
			<< "." << std::endl;

			if (verify_checksum(protected_value))
			{
				std::cout << "The checksum is valid." << std::endl;
			}
			else {
				std::cout << "The checksum is invalid." << std::endl;
			}
			const std::size_t QTY_VALUES {3};
			unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};

			add_checksum(value_series, QTY_VALUES);

			std::cout << "Series with checksums added: ";
			for (std::size_t series_index {0};
			series_index < QTY_VALUES; series_index++)
			{
				std::cout << value_series[series_index] << " ";
			}
			std::cout << std::endl;

			return 0;
			}
	#endif





