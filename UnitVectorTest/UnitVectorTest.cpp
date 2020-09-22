#include "pch.h"
#include "CppUnitTest.h"
#include "../VectorIterator/myVector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitVectorTest
{
	class Node {

	public:
		const char* name = "my Node object";


		friend std::ostream& operator << (std::ostream out, const Node& obj) {
			out << obj.name;
			return out;
		}


	};

	TEST_CLASS(UnitVectorTest)
	{
	public:
		
			//Test: removing first element correctly realligns vector
		TEST_METHOD(remove) {
			myVector<int> m;
			m.add(1, 2, 3, 4);

			m.remove(0); //remove index 0

			Assert::AreEqual(m[0], 2);
			
			m.reset();

			m.add(1, 2, 3, 4);

			m.remove(1); //remove index 0

			Assert::AreEqual(m[1], 3);
			
			m.reset();

			m.add(1, 2, 3, 4);

			m.remove(1);

			Assert::AreEqual(m.getSize(), size_t(3));
		
			m.reset();

			m.remove(0);
			m.remove(0);
			m.remove(0);
		
			try {
				m[0]; //should throw an error
				
				Assert::Fail();
				
			}
			catch (std::string e) {
				std::cout << "In test case: " << e << "\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
			
		}
		
		//test if an empty container correctly blocks a remove
			
		TEST_METHOD(removeAll) {
			myVector<int> m;
			m.add(1, 3, 2, 4, 4, 2, 1, 1);
			m.removeAll(2);
			Assert::AreEqual(m.contains(2), false);
		}

		TEST_METHOD(add) {
			myVector<int> m;
			
			m.add(99); //add one int
			Assert::AreEqual(m[0], 99);

			m.reset();
			m.add(1, 2, 3, 4); //add multiple ints
			bool t = (m.contains(1,2,3,4));
			Assert::AreEqual(t, true);


			myVector<double> dbl;
			dbl.add(1.3);// add one double
			Assert::AreEqual(dbl[0], 1.3);

			dbl.reset();
			dbl.add(1.3, 3.2, 44.21); //add multiple doubles
			t = dbl.contains(1.3, 3.2, 44.21);
			Assert::AreEqual(t, true);

			myVector<Node> nodes;

			Node b;
			nodes.add(b);
			Assert::AreEqual(nodes[0], b);
			//Assert::AreEqual(str[1], std::string("how"));
			//Assert::AreEqual(str[2], std::string("goes"));
			//Assert::AreEqual(str[3], std::string("it"));
		}
		
		TEST_METHOD(removeElement) {

			myVector<int> n;
			myVector<std::string> m;
			myVector<double> d;
			myVector<const char*> c;


			n.add(1, 2, 3, 4, 5);

			//m.add(std::string("hi"), std::string("how"), std::string("goes"), std::string("it"));

			d.add(1.2, 3.2, 4.2, 5.55);

			c.add("my", "char", "vector");
						
		//	m.removeElement(std::string("how"));

			d.removeElement(3.2);

		//	c.removeElement("char");

			n.removeElement(3);
			bool t = n.contains(3);
			n.removeElement(2);
			Assert::AreEqual(t, false);
			Assert::AreEqual(n.getSize(), size_t(3));
			Assert::AreEqual(n.contains(2), false);
			c.removeElement("char");

			Assert::AreEqual(c.contains("char"), false);
			Assert::AreEqual(c.getSize(), size_t(2));

			Assert::AreEqual(d.contains(3.2), false);
			Assert::AreEqual(d.getSize(), size_t(3));
		}

		TEST_METHOD(contains) { //test contains single element and multiple elements
			myVector<int> m;
			m.add(1, 2, 3, 4, 5);

			bool t = m.contains(1, 2, 3, 4, 5);
			Assert::AreEqual(t, true);			
			
			bool f = m.contains(1, 2, 99, 4, 5);
			Assert::AreEqual(f, false);
			
			bool b = m.contains(1, 2, 4, 5);
			Assert::AreEqual(b, true);

		}
	};


}

