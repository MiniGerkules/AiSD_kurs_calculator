﻿#include "CppUnitTest.h"
#include <iostream>
#include "../kurs/h-files/Сalculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testkurs
{
	TEST_CLASS(Testkurs)
	{
	public:
		Сalculator* calc = NULL;

		TEST_METHOD_INITIALIZE(setUp)
		{
			calc = new Сalculator;
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			// Freeing memory from a Сalculator object
			delete calc;
		}

		TEST_METHOD(if_float_test1)
		{
			std::string expression = "123+345";
			size_t index = expression.length();

			Assert::AreEqual(true, calc->if_float(expression, &index));
			Assert::AreEqual(false, calc->if_float(expression, &index));
			calc->if_sign(expression, &index);
			Assert::AreEqual(true, calc->if_float(expression, &index));
		}

		TEST_METHOD(if_float_test2)
		{
			std::string expression = "123.234.345";
			size_t index = expression.length();

			try
			{
				calc->if_float(expression, &index);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (found two points in the number). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(if_float_test3)
		{
			std::string expression = "123.123";
			size_t index = expression.length();

			Assert::AreEqual(calc->if_float(expression, &index), true);
		}

		TEST_METHOD(if_sign_test1)
		{
			std::string expression = "0";
			size_t index = expression.length();

			Assert::AreEqual(calc->if_sign(expression, &index), false);
		}

		TEST_METHOD(if_sign_test2)
		{
			std::string expression = "5+5";
			size_t index = expression.length();
			
			calc->if_float(expression, &index);
			Assert::AreEqual(calc->if_sign(expression, &index), true);
		}

		TEST_METHOD(if_brackets_test1)
		{
			std::string expression = "ABVGD";
			size_t index = expression.length();

			Assert::AreEqual(calc->if_brackets(expression, &index), false);
		}

		TEST_METHOD(if_brackets_test2)
		{
			std::string expression1 = "aleop(";
			std::string expression2 = "aleop)";
			size_t index = expression1.length();
			// Only the last character is checked
			Assert::AreEqual(calc->if_brackets(expression2, &index), true);
			index++;
			Assert::AreEqual(calc->if_brackets(expression1, &index), true);
		}

		TEST_METHOD(if_constant_test1)
		{
			std::string expression = "ABVGD";
			size_t index = expression.length();

			Assert::AreEqual(calc->if_constant(expression, &index), false);
		}

		TEST_METHOD(if_constant_test2)
		{
			std::string expression1 = "ABVGDE";
			std::string expression2 = "ABVe";
			size_t index = expression1.length();

			Assert::AreEqual(calc->if_constant(expression1, &index), true);
			calc->if_sign("ABVG+", &index);			// To change the program's internal flags
			Assert::AreEqual(calc->if_constant(expression2, &index), true);
		}

		TEST_METHOD(if_constant_test3)
		{
			std::string expression1 = "ABVGDPI";
			std::string expression2 = "ABVGDPi";
			std::string expression3 = "ABVGDpI";
			std::string expression4 = "ABVGDpi";
			size_t index = expression1.length();

			Assert::AreEqual(calc->if_constant(expression1, &index), true);
			calc->if_sign("ABVG+", &index);			// To change the program's internal flags
			index += 3;
			Assert::AreEqual(calc->if_constant(expression2, &index), true);
			calc->if_sign("ABVG+", &index);			// To change the program's internal flags
			index += 3;
			Assert::AreEqual(calc->if_constant(expression3, &index), true);
			calc->if_sign("ABVG+", &index);			// To change the program's internal flags
			index += 3;
			Assert::AreEqual(calc->if_constant(expression4, &index), true);
		}

		TEST_METHOD(if_function_test1)
		{
			std::string expression1 = "ABVG";
			std::string expression2 = "ttan5";
			size_t index = expression1.length();

			Assert::AreEqual(calc->if_function(expression1, &index), false);
			calc->if_float(expression2, &index);		// To change the program's internal flags
			Assert::AreEqual(calc->if_function(expression2, &(--index)), false);
		}

		TEST_METHOD(if_function_test2)
		{
			std::string expression1 = "TAN5";
			std::string expression2 = "Tan5";
			std::string expression3 = "tan5";
			std::string expression4 = "tAn5";
			size_t index = expression1.length();
			size_t index1 = 1;

			calc->if_float(expression1, &index);		// To change the program's internal flags
			Assert::AreEqual(calc->if_function(expression1, &index), true);
			index += 5;
			calc->if_sign("    +", &index);			// To change the program's internal flags
			calc->if_float(expression1, &index);		// To change the program's internal flags
			Assert::AreEqual(calc->if_function(expression2, &index), true);
			index += 5;
			calc->if_sign("    +", &index);			// To change the program's internal flags
			calc->if_float(expression1, &index);		// To change the program's internal flags
			Assert::AreEqual(calc->if_function(expression3, &index), true);
			index += 5;
			calc->if_sign("    +", &index);			// To change the program's internal flags
			calc->if_float(expression1, &index);		// To change the program's internal flags
			Assert::AreEqual(calc->if_function(expression4, &index), true);
		}

		TEST_METHOD(verification_and_forming_test1)
		{
			std::string expression = " 2 + 4 / 6 * 89 ^ 4 + tan(58 + 3) ";
			std::string result = "2+4/6*89^4+tan(58+3)";

			Assert::AreEqual(result, calc->verification_and_forming(expression));
		}

		TEST_METHOD(verification_and_forming_test2)
		{
			std::string expression = " 2 + 4 / 6 * 89 ^ 4 + tan(58 + 3 ";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (incorrect parenthesis sequence found). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(verification_and_forming_test3)
		{
			std::string expression = " * 2 + 4 / 6 * 89 ^ 4 + tan(58 + 3) ";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (expression ends with an arithmetic sign or a function with no value). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(verification_and_forming_test4)
		{
			std::string expression = " 2 + 4 / ABV * 89 ^ 4 + tan(58 + 3) ";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (invalid characters found). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(verification_and_forming_test5)
		{
			std::string expression = "25 / 89 + + 4";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (found an incorrect sequence of arithmetic signs or arithmetic signs and brackets). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(verification_and_forming_test6)
		{
			std::string expression = "25 / 89 + 4 +";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (the string ends with an arithmetic sign). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(verification_and_forming_test7)
		{
			std::string expression = "25 / 89 + 4 + tancot5";

			try
			{
				calc->verification_and_forming(expression);
			}
			catch (std::domain_error error)
			{
				Assert::AreEqual("The expression is invalid (found wrong sequence of functions or functions and arithmetic signs). Try entering it again.", error.what());
			}
		}

		TEST_METHOD(count_test)
		{
			std::string expressions[] = { " rnd( 123 + 900 * cos(800 / 10) + 10^3 - 743 ) ", "1+sin(pi/2)", "(sin25)^2 + (cos25)^2", 
										"(sqrt(36) + cos(-pi)) / 5^2", "", "((16^2) / sqrt64) / (sin((15*pi)/2))", "rnd(lg12 * (ln10)/(ln6))",
										"rnd(((12*5+4)/5 * 3/4 - (4*11+4)/11 * (4*8 + 1)/8) / ((11*3 + 2)/3 * 7/18))" };
			double result_function;
			double results[] = { 281, 2, 1, 0.2, 0, -32, 1, -2 };
			size_t i;

			for (i = 0; i < 8; i++)
			{
				calc->verification_and_forming(expressions[i]);
				result_function = calc->count();
				Assert::AreEqual(results[i], result_function);
			}
		}

		TEST_METHOD(my_find_test)
		{
			std::string first[] = { "TANGENS", "sINUs_CoSiNuS", "Nus_nus" };
			std::string second[] = { "snegnat", "sUnIsOc", "sun_" };
			size_t i;

			for (i = 0; i < 1; i++)
				Assert::AreEqual(true, my_find(first[i], second[i], first[i].length()));
		}

		TEST_METHOD(Stack_test)
		{
			Stack stack;

			Assert::AreEqual(true, stack.is_empty());
			stack.push(5.0);
			stack.push('a');
			stack.push(123.0);
			stack.push((char)123);

			Assert::AreEqual(0.0, stack.pop_double());
			Assert::AreEqual(' ', stack.pop_char());
			Assert::AreEqual(stack.pop_char(), stack.peek_char());
			Assert::AreEqual(stack.pop_double(), 5.0);
		}

		TEST_METHOD(List_test)
		{
			std::string leti[] = { "I", "T", "E", "L" };
			List list;
			size_t i;

			list.push_front("L");
			list.push_front("E");
			list.push_front("T");
			list.push_front("I");

			Assert::AreEqual(false, list.is_empty());
			for (i = 0; i < 4; i++)
				Assert::AreEqual(leti[i], list.pop());
		}
	};
}