#include<iostream>
#include <cmath>
#include <stack>
#include <fstream>
using namespace std;

stack<float> st;

class ICalculate
{
public:
	virtual void calc()=0;
};

class Addition: public ICalculate
{
public:
	void calc() override
	{
		float num1 = st.top();
		st.pop();
		float num2 = st.top();
		st.pop();
		st.push(num1+num2);
	}
};

class Subtraction: public ICalculate
{
public:
	void calc() override
	{
		float num1 = st.top();
		st.pop();
		float num2 = st.top();
		st.pop();
		st.push(num2-num1);
	}
};

class Multiplication: public ICalculate
{
public:
	void calc() override
	{
		float num1 = st.top();
		st.pop();
		float num2 = st.top();
		st.pop();
		st.push(num1*num2);
	}
};

class Division: public ICalculate
{
public:
	void calc() override
	{
		float num1 = st.top();
		st.pop();
		float num2 = st.top();
		st.pop();
		st.push(num2/num1);
	}
};

class Square: public ICalculate
{
public:
	void calc() override
	{
		
		float num1 = st.top();
		st.pop();
		st.push(num1*num1);
	}
};

class SquareRoot: public ICalculate
{
public:
	void calc() override
	{
		
		float num1 = st.top();
		st.pop();
		st.push(sqrt(num1));
	}
};


class CalculateLogBase10: public ICalculate
{
public:
	void calc() override
	{
		float num1 = st.top();
		st.pop();
		st.push(log10(num1));
	}
};



class CreateOperations
{
public:
	virtual ICalculate* create_operations()=0;
	static CreateOperations* create_compute(char choice);
};


class AddOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new Addition();
	}
};

class SubtractOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new Subtraction();
	}
};

class MultiplicationOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new Multiplication();
	}
};

class DivisionOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new Division();
	}
};

class SquareOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new Square();
	}
};

class SquareRootOperations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new SquareRoot();
	}
};

class CalculateLogBase10Operations: public CreateOperations
{
public:
	ICalculate* create_operations() override
	{
		return new CalculateLogBase10();
	}
};

CreateOperations* CreateOperations::create_compute(char choice)
	{
		if(choice == 'a')
		{
			return new AddOperations();
		}
		else if(choice == 'b')
		{
			return new SubtractOperations();
		}
		else if(choice == 'c')
		{
			return new MultiplicationOperations();
		}
		else if(choice == 'd')
		{
			return new DivisionOperations();
		}
		else if(choice == 'e')
		{
			return new SquareOperations();
		}
		else if(choice == 'f')
		{
			return new SquareRootOperations();
		}
		else if(choice == 'g')
		{
			return new CalculateLogBase10Operations();
		}
		else
			return nullptr;

	}

class CalculationHistory
{
public:
	void view_history(){
		cout<<"View";
	}
	void create_history()
	{
		cout<<"Create History";
	}
};

class InFileHistory: public CalculationHistory{
public:
	void view_history()
	{
		cout<<"\n";
		cout<<"Calculations History!!"<<"\n";
		fstream my_file;
		my_file.open("cal_history.txt", ios::in);
		string sa;
        
        while (getline(my_file, sa)) { 
            // Print the data of the string.
            cout << sa << "\n"; 
        }
	}

	void create_history(char choice, string exp, string query)
	{
		if(query == "expression")
		{
			fstream my_file;
			my_file.open("cal_history.txt", ios::app | ios::out);
			if (!my_file) {
				cout << "File not created!";
			}
			else {
				cout << "File created successfully!";
				my_file << exp << "\n";
				my_file.close();
			}
		}
		else if(query == "result")
		{
			fstream my_file;
			my_file.open("cal_history.txt", ios::app | ios::out);
			if (!my_file) {
				cout << "File not created!";
			}
			else {
				my_file << "Result:"<<" "<< st.top() << "\n";
				my_file.close();
			}
		}
		
	}
};

class TakeInput
{
public:
	static string take_input_according_to_choice(char choice)
	{
		if(choice == 'a')
		{
			
			string expr = "";
			if(st.empty())
			{
				float num1, num2;
				cout<<"Enter the First Number"<<"\n";
				cin>>num1;
				cout<<"Enter the Second Number"<<"\n";
				cin>>num2;
				st.push(num1);
				st.push(num2);
				expr = expr+to_string(num1)+'+'+to_string(num2);
				return expr;
			}
			else
			{
				float num1;
				cout<<"Enter the  Number"<<"\n";
				cin>>num1;
				expr = expr+to_string(st.top())+'+'+to_string(num1);
				st.push(num1);
				return expr;
			}
		}
		else if(choice == 'b')
		{
			
			string expr = "";
			if(st.empty())
			{
				float num1, num2;
				cout<<"Enter the First Number"<<"\n";
				cin>>num1;
				cout<<"Enter the Second Number"<<"\n";
				cin>>num2;
				st.push(num1);
				st.push(num2);
				expr = expr+to_string(num1)+'-'+to_string(num2);
				return expr;
			}
			else
			{
				float num1;
				cout<<"Enter the  Number"<<"\n";
				cin>>num1;
				expr = expr+to_string(st.top())+'-'+to_string(num1);
				st.push(num1);
				return expr;
			}
		}
		else if(choice == 'c')
		{
			
			string expr = "";
			if(st.empty())
			{
				float num1, num2;
				cout<<"Enter the First Number"<<"\n";
				cin>>num1;
				cout<<"Enter the Second Number"<<"\n";
				cin>>num2;
				st.push(num1);
				st.push(num2);
				expr = expr+to_string(num1)+'*'+to_string(num2);
				return expr;
			}
			else
			{
				float num1;
				cout<<"Enter the  Number"<<"\n";
				cin>>num1;
				expr = expr+to_string(st.top())+'*'+to_string(num1);
				st.push(num1);
				return expr;
			}
		}
		else if(choice == 'd')
		{
			
			string expr = "";
			if(st.empty())
			{
				float num1, num2;
				cout<<"Enter the First Number"<<"\n";
				cin>>num1;
				cout<<"Enter the Second Number"<<"\n";
				cin>>num2;
				st.push(num1);
				st.push(num2);
				expr = expr+to_string(num1)+'/'+to_string(num2);
				return expr;
			}
			else
			{
				float num1;
				cout<<"Enter the  Number"<<"\n";
				cin>>num1;
				expr = expr+to_string(st.top())+'/'+to_string(num1);
				st.push(num1);
				return expr;
			}
		}
		else if(choice == 'e')
		{
			float num1;
			string expr = "";
			cout<<"Enter the Number"<<"\n";
			cin>>num1;
			while(!st.empty())
				st.pop();
			st.push(num1);
			expr = expr+"Sqaure of"+" "+to_string(num1);
			
			return expr;
		}
		else if(choice == 'f')
		{
			float num1;
			string expr = "";
			cout<<"Enter the Number"<<"\n";
			cin>>num1;
			while(!st.empty())
				st.pop();
			st.push(num1);
			expr = expr+"Sqaure Root of"+" "+to_string(num1);
			
			return expr;
		}
		else if(choice == 'g')
		{
			float num1;
			string expr = "";
			cout<<"Enter the Number"<<"\n";
			cin>>num1;
			while(!st.empty())
				st.pop();
			st.push(num1);
			expr = expr+"Log Base 10 of"+" "+to_string(num1);
			
			return expr;
		}
		return "Invalid";
	}
};

int main()
{
	char choice;
	float result;
	while(true)
	{

		cout<<"\n"<<"\n"<<"a. Add"<<"\n"<<"b. Subtract"<<"\n"<<"c. Multiply"<<"\n"<<"d. Divide"<<"\n"<<"e. Square"<<"\n"<<"f. SquareRoot"<<"\n"<<"g. LogBase10"<<"\n"<<"h. Clear"<<"\n"<<"i. Quit"<<"\n"<<"j. View History"<<"\n"<<"\n";
		cin>>choice;
		if(choice == 'i')
		{
			cout<<"Exiting..."<<"\n";
			break;
		}
		else if(choice == 'h')
		{
			while(!st.empty())
				st.pop();
		}
		else if(choice == 'j')
		{
			InFileHistory* history_obj = new InFileHistory();
			history_obj->view_history();
		}
		else
		{
			CreateOperations* factory_obj = CreateOperations::create_compute(choice);
			string expr = TakeInput::take_input_according_to_choice(choice);

			// Calcultion History
			InFileHistory* history_obj = new InFileHistory;
			history_obj->create_history(choice, expr, "expression");

			ICalculate* compute = factory_obj->create_operations();
			compute->calc();

			cout<<"\n"<<"Result....."<<"\n";
			cout<<st.top()<<"\n"<<"\n";

			history_obj->create_history(choice, to_string(st.top()), "result");
		}
		
	}
	
	return 0;
}