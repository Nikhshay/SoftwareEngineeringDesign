//1st quenstion
class MyObject
{
public:
	float height, width, length, volume;
	MyObject(float h, float w, float l) { height = h, width = w, length = l };
};


int Calc_data(MyObject m)
{
	*m.volume = *m / 2;
	return volume;
}

int main(int argc, char *argv[])
{

	MyObject square(2, 4, 7);
	cout << Calc_data(&square) << endl;
	return 0;

}

//mcq question why wont it compile and how to fix it.


//the question 2 or 3 with max student and the average mark of student
//fill in the black the 1st answer is float * and delete[]
//and then which variable is in stack and which one is in heaps
//where does the function run, in heap or stack
//difference between stack and heap tick tick

//inheritance with solid shape and 
//how to declare a cube shape with size 
//how to call a fuction from the top level in main 
//mcq: class transportdriver: tramdriver
//whic is the inheritance of which


//4th question the lock with 2 sequence 3-3-0 and 7-7-0. if even 1 number is wrong it should reset. if correct combo is pressed then unlock
//list out the state 
//what trigger state change
//draw state diagram
