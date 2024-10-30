#include "FlexArray.h"

FlexArray::FlexArray() {

	// Initialise Array etc.
	size_ = 0;
	capacity = INITIALCAP;
	arr_ = new int[capacity];

	// Initilise Indexs
	sInd = mid_cap();
	eInd = sInd;

}

FlexArray::FlexArray(const int* arr, int size) {
	
	// Initialise Array etc.
	size_ = size;
	capacity = (LO_THRESHOLD * size);
	arr_ = new int[capacity];

	// // Initilise start index
	sInd = ((capacity - size) / 2);

	// Loop and replace input array values with array values
	for (int i = 0; i < size_; i++){
		// Calculate the index
		int index = (capacity-size)/2 + i;

		// set array values
		arr_[index] = arr[i];
        eInd=index;
	} 
}

FlexArray::~FlexArray() {
	// Delete array if one is intialised
	if (arr_ != nullptr) {
		delete [] arr_;
		arr_ = nullptr;
	}
}

FlexArray::FlexArray(const FlexArray& other) {
	// Initialise Array
	size_ = other.size_;
	capacity = other.capacity;
	arr_ = new int[capacity];

	// Initilise Indexs
	sInd = other.sInd;
	eInd = other.eInd;

	// Loop through and set array values to ther other array values
	for (int i = 0; i < capacity; i++){
		arr_[i] = other.arr_[i];
	}

}

FlexArray& FlexArray::operator=(const FlexArray& other) {
	if (this == &other) {
		return *this;
	} else {
		// Delete original array
		delete [] arr_;

		// Initialise array
		size_ = other.size_;
		capacity = other.capacity;
		arr_ = new int[capacity];

		// Initialise Indexs
		sInd = other.sInd;
		eInd = other.eInd;

		// Loop through and set array values to ther other array values
		for (int i = 0; i < capacity; i++){
			arr_[i] = other.arr_[i];
		}
	}

	return *this;
}

int FlexArray::getSize() const {
	// Return size
	return size_;
}

int FlexArray::getCapacity() const {
	// Return capacity
	return capacity;
}

string FlexArray::print() const {
	string str = "[";
	// If the array has values, they're added to str
	if (size_ != 0){
		for (int i = sInd; i <= eInd; i++){
			str = str + std::to_string(arr_[i]);
			if (i < eInd){
				str = str + ", ";
			}
		}
	} 
	// Closes string
	str = str + "]";
	return str;
}

string FlexArray::printAll() const {
	string str = "[";
	// Loop through array
	for (int i = 0; i < capacity; i++){
		// Add X's when conditions are met
		if (i > eInd){
			str = str + "X";
		} else if (i < sInd){
			str = str + "X";
		} else if (size_ == 0){
			str = str + "X";
		} else{
			str = str + std::to_string(arr_[i]);
		}
		// Add a comma if i != last index
		if (i != capacity - 1) str = str + ", ";
	}

	// Closing bracket
	str = str + "]";
	return str; 
}


int FlexArray::get(int i) const {
	int ind = sInd + i;
	return arr_[ind]; 
}

bool FlexArray::set(int i, int v) {
	int ind = sInd + i;
	// If the i is valid
	if (i >= 0 && i < size_){
		arr_[ind] =  v;
		return true;
	}
	return false; 
}

void FlexArray::push_back(int v) {
	//If the eInd == cap, array is resized
	if (eInd == true_cap()){
		resize();
	}
	// If array is not empty
	if (size_ != 0){
		eInd++;
	}
	// Size is indremented and elemnt added at the end of the array
	size_++;
	arr_[eInd] = v;
	
}

bool FlexArray::pop_back() {
	// If size != 0
	if (size_ != 0) {
		if (size_ != 1){
			// If size != 1
			eInd--;
			size_--;
			// Checks if array needs resizing
			over_limit();
			return true;
		} else {
			// If size = 1
			size_--;
			int newInd = mid_cap();
			sInd = newInd;
			eInd = newInd;
			return true;
		}
	} else {
		// If size = 0
		return false;
	}
}

void FlexArray::push_front(int v) {
	// Array is resized if sInd = 0
	if (sInd == 0){
		resize();
	}
	// sInd is decremnted if the array is not empty
	if (size_ != 0){
		sInd--;
	}
	// Size is incremented and elemnt is placed at the beginning of array
	size_++;
	arr_[sInd] = v;

}

bool FlexArray::pop_front() {
	// If size > 0 the array can be popped
	if (size_  > 0){
		
		if (size_ > 1){
			sInd++;
			// size is decremented because element popped
			size_--;
			// Checks if array needs resizing
			over_limit();
		}else{
			// size is decremented because element popped
			size_--;
			// new index is calculated
			int index = mid_cap();
			sInd = index;
			eInd = index;
		}
		return true;
	}
	// If the size of the array is 0 it cannot be popped
	return false;
}

bool FlexArray::insert(int i, int v) {
	// If the index is < 0 the value cannot be inserted
    if (i < 0 ) {
        return false;
    } else if (i > size_) {
		// If the index is > the size of the array then he value cannot be inserted
		return false;
	}else{
		// If the array is empty, add value and return
		if (size_ == 0){
			arr_[eInd] = v;
			size_++;
			return true;
		}
		// Determines if the array needs resizing
		if (eInd == true_cap() && sInd == 0) {
            resize();
        } 

		// Shifts array in the correct way 
		shift(i, v);
		
        // Increment size after value is added
        size_++;

		// Checks if array needs resizing
		over_limit();

        return true;
    }
}

bool FlexArray::erase(int i) {
	// If array is empty then nothing can be erased
	if (i >= 0 && size_ > 0){
		// i is out of bounds, nothing can be reased
		if (i >= size_){
			return false;
		} else if (size_ == 1){
			// Array is reset to normal
			size_--;
			int index = mid_cap();
			sInd = index;
			eInd = index;
			return true;
		} else{
			// If the element is in the first half of array
			if ((size_ / 2) > i){
				for (int k = i; k > 0; k--){
					int newInd = k + sInd;
                	arr_[newInd]=arr_[newInd - 1]; 
            }
            sInd++;
			} else {
				// If element is in second half of array
				for (int k = i; k < size_ - 1; k++){
					int newInd = k + sInd;
                	arr_[newInd]=arr_[newInd + 1]; 
            }
            eInd--;
			}
		}
		size_--;
		// Checks if array needs resizing
		over_limit();
        return true;
    }
	// Return false if i < 0 or size == 0
	return false; 
}

void FlexArray::resize() {
	// Declare and calc new values
	int newCap = size_ * LO_THRESHOLD;
	int newSind = (newCap - size_)/2;
	int newEind = (newSind + size_ - 1);
	int* newArr = new int[newCap];

	// Set values of new array to old
	for (int i = 0; i < size_; i++) {
		int newInd = i + newSind;
		int oldInd = i + sInd;
		newArr[newInd] = arr_[oldInd];
	}

	// Set new values
	capacity = newCap;
	sInd = newSind;
	eInd = newEind;

	// Delete and set old array to new array
	delete[] arr_;
	arr_ = newArr;
}

void FlexArray::over_limit(){
	// Calculates limit for the array
	int limit = HI_THRESHOLD * size_;
	// If the capacity is > than the limit, it is resized
	if (capacity > limit){
		resize();
	}
}

int FlexArray::true_cap(){
	int trueCap = capacity - 1;
	return trueCap;
}

int FlexArray::mid_cap(){
	int midCap = true_cap() / 2;
	return midCap;
}

void FlexArray::shift(int i, int v){
		// Calculate the midpoint of the array
		float mid = (float)size_/2;
		// set boolean to false by default and define criteria where shift right is needed.
		bool shiftRight = false;
		if (i >= mid && eInd < true_cap()){
			shiftRight = true;
		}if (sInd == 0) {
			shiftRight = true;
		}

		// calculating index using sInd and the index provided
		int index = sInd + i;

		// Shifting array to the correct directions
        if (shiftRight) {
            // Shift elements to the right from the end
            for (int k = size_ - 1; k >= i; --k) {
				int newInd = sInd + k;
                arr_[newInd + 1] = arr_[newInd];
            }
			// Set value at the index sepcified
            arr_[index] = v;
			eInd++;
        } else {
            // Shift elements to the left 
            for (int k = 0; k < i; k++) {
				int newInd = sInd + k;
                arr_[newInd - 1] = arr_[newInd];
            }
			// Set value at the index sepcified
            arr_[index - 1] = v;
			sInd--;
        }
}