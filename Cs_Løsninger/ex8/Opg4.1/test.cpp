#include <iostream>
#include <boost/shared_ptr.hpp>

int main(int argc , char* argv [])
{
    struct tester
    {
        std::string name;
        int data;
    };

    /* Create boost::shared_ptr A holding the string "A" */
    boost::shared_ptr<tester> A(new tester);
    
    A->name = "Anton";
    A->data = 4;

    std::cout << "shared_ptr used: \n"; 
    std::cout << A.use_count() << " time(s) for ptr A pointing to struct with string: " << A->name << "\n\n";


    /* Create boost::shared_ptr B holding the string "B" */
    boost::shared_ptr<tester> B(new tester);

    B->name = "Britta";
    B->data = 5;

    std::cout << "shared_ptr used: \n"; 
    std::cout << A.use_count() << " time(s) for ptr A pointing to struct with string: " << A->name << "\n";
    std::cout << B.use_count() << " time(s) for ptr B pointing to struct with string: " << B->name << "\n\n";


    /* Assign B to A */
    std::cout << "Assigning " << B->name << " to " << A->name << "\n\n";
    A = B;

    std::cout << "shared_ptr used: \n"; 
    std::cout << A.use_count() << " time(s) for ptr A pointing to struct with string: " << A->name << "\n";
    std::cout << B.use_count() << " time(s) for ptr B pointing to struct with string: " << B->name << "\n\n";


    /* Create boost::shared_ptr C holding the string "C" */
    boost::shared_ptr<tester> C(A);

    std::cout << "Creating C, using A's copy constructor\n\n";

    std::cout << "shared_ptr used: \n"; 
    std::cout << A.use_count() << " time(s) for ptr A pointing to struct with string: " << A->name << "\n";
    std::cout << B.use_count() << " time(s) for ptr B pointing to struct with string: " << B->name << "\n";
    std::cout << C.use_count() << " time(s) for ptr C pointing to struct with string: " << C->name << "\n\n";


    /* Reseting shared_ptr's */
    A.reset();
    B.reset();
    C.reset();

    std::cout << "Reseting shared pointers\n\n";

    std::cout << "shared_ptr used: \n"; 
    std::cout << A.use_count() << " time(s) for ptr A\n";
    std::cout << B.use_count() << " time(s) for ptr B\n";
    std::cout << C.use_count() << " time(s) for ptr C\n";

    return 0;
}
