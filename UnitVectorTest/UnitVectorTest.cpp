#include "pch.h"
#include "CppUnitTest.h"
#include "../MyVector/myVector.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitVectorTest
{
	class Node {

	public:
		const char* name = "I am a Node";
		Node(){}

		friend std::ostream& operator << (std::ostream out, const Node& obj) {
			out << obj.name;
			return out;
		}

	};

	TEST_CLASS(UnitVectorTest)
	{
	public:
		TEST_METHOD(remove) {
			myVector<int> m;
			m.add(1, 2, 3, 4);

			m.remove(0); //remove index 0

			Assert::AreEqual(m[0], 2);
			
			m.reset();

			m.add(1, 2, 3, 4);

			m.remove(1); //remove index 1

			Assert::AreEqual(m[1], 3);
			Assert::AreEqual(m.getSize(), size_t(3));
			
		
			m.reset();
			m.remove(0);
			m.remove(0);
			m.remove(0);


			try {
				int tmp = m[0]; //should throw an error
				
				Assert::Fail();
				
			}
			catch (std::string e) {
				std::cout << "In test case: " << e << "\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
			
			m.reset();
			m.add(1, 2, 3, 4);
			m.remove(3);
			Assert::AreEqual(m[2], 3);

			m.reset();
			Assert::AreEqual(m.remove(8), false);
		}
		
		TEST_METHOD(removeAll) {
			myVector<int> m;
			m.add(1, 3, 2, 4, 4, 2, 1, 1);
			m.removeAll(2);
			Assert::AreEqual(m.contains(2), false);

			myVector<double> n;
			n.add(4.2,1.3,1.3,4.23,4.222,1.3);

			n.removeAll(1.3);
			Assert::AreEqual(n.contains(1.3), false);		
			
			myVector<const char*> c;
			c.add("hello", "how", "hello", "mae", "hello");

			c.removeAll("hello");
			Assert::AreEqual(c.contains("hello"), false);
			Assert::AreEqual(c.getSize(), size_t(2));

			myVector<Node*> nodes;
			Node a;
			Node b;
			nodes.add(&a, &a, &a, &b);

			nodes.removeAll(&a);
			Assert::AreEqual(nodes.getSize(), size_t(1));
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
			nodes.add(b);			//add one node
			Assert::AreEqual(nodes[0].name, b.name);

			nodes.reset();
			Node a;
			nodes.add(a,a,a,a);
			Assert::AreEqual(nodes.getSize(), size_t(4));
	



			
		}
		
		TEST_METHOD(addElementsOf) { 
			myVector<int> m;
			int arrayints[] = { 1,2,3,4,5 };

			m.addElementsOf(arrayints);
			Assert::AreEqual(m.getSize(), size_t(5));
			Assert::AreEqual(m.contains(1, 2, 3, 4, 5), true);

			m.reset();

			std::vector<int> tmp = { 1,2,3,4,5 };
			m.addElementsOf(tmp);
			Assert::AreEqual(m.getSize(), size_t(5));
			Assert::AreEqual(m.contains(1, 2, 3, 4, 5), true);
			m.reset();

			myVector<Node> nodes;
			Node a;
			Node b;
			Node c;
			Node d;
			Node arr[] = { a,b,c,d };

			nodes.addElementsOf(arr);
			Assert::AreEqual(nodes.getSize(), size_t(4));
			Assert::AreEqual(nodes[0].name == a.name, true);

			myVector<Node*> ptrs;

			Node* arrptrs[] = { &a,&b,&c,&d };
			ptrs.addElementsOf(arrptrs);
			//ptrs.removeElement(&a);
			Assert::AreEqual(ptrs.getSize(), size_t(4));
			bool t = ptrs.contains(&a, &b, &c, &d);
			Assert::AreEqual(t, true);


		}

		TEST_METHOD(addAt) {
			myVector<int> m;
			m.add(1, 2, 3, 4);
			m.addAt(2, 99);

			Assert::AreEqual(m.getSize(), size_t(5));
			Assert::AreEqual(m[2], 99);
			m.addAt(0, 100);
			Assert::AreEqual(m[0], 100);
			Assert::AreEqual(m.getSize(), size_t(6));
			m.reset();

			//adding at an index out of bounds
			m.add(1); //one element

			try {
				 //should throw an error
				m.addAt(1, 99); //adding out of bounds
				Assert::Fail();
			}
			catch (std::string e) {
				std::cout << "In test case: " << e << "\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}

			try {
				//should throw an error
				m.addAt(-9, 99); //adding out of bounds
				Assert::Fail();
			}
			catch (std::string e) {
				std::cout << "In test case: " << e << "\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}

			myVector<const char*> c;
			c.add("hello", "from", "cpu");
			c.addAt(2, "the");
			Assert::AreEqual(c[2], "the");
			c.addAt(3, "heavy");
			Assert::AreEqual(c[3], "heavy");
			Assert::AreEqual(c[4], "cpu");


			/*
			nodes.add(&aa, &bb, &cc);

			nodes.addAt(3, &dd);//Test writer must define specialization of ToString<Q* q> for

			Assert::AreEqual(nodes.getSize(), size_t(4));
			Assert::AreEqual(nodes[3], ToString(&dd));
			Assert::AreEqual(nodes[4], &cc);
			nodes.addAt(0, &ee);
			Assert::AreEqual(nodes[0], &ee);
			*/
		}

		TEST_METHOD(removeElement) {

			myVector<int> n;
			myVector<std::string> m;
			myVector<double> d;
			myVector<const char*> c;


			n.add(1, 2, 3, 4, 5);

			d.add(1.2, 3.2, 4.2, 5.55);

			c.add("my", "char", "vector");
						
			d.removeElement(3.2);

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

			myVector<Node*> nodes;
			Node a;
			Node bb;
			nodes.add(&a, &a, &a, &bb);
			bool n = nodes.contains(&a, &a, &a, &bb);
			Assert::AreEqual(n, true);


		}

		TEST_METHOD(isEmpty) {
			myVector<int> m;
			Assert::AreEqual(m.isEmpty(), true);
			m.add(0, 2, 3, 4);
			m.reset();

			Assert::AreEqual(m.isEmpty(), true);

			m.add(1, 2, 3, 4);
			m.erase(0, 3);
			Assert::AreEqual(m.isEmpty(), true);

		}

		TEST_METHOD(erase) {
			myVector<int> m;

			m.add(1, 2, 3, 4, 5, 6, 7);
			m.erase(0, 1);
			Assert::AreEqual(m.contains(3, 4, 5, 6, 7), true);
			Assert::AreEqual(m.getSize(), size_t(5));

			try {
				m.erase(0, 5); //throw error
				Assert::Fail();
			}
			catch (std::string e) { std::cout << e << std::endl;}
			catch (std::exception e) { std::cout << e.what() << std::endl; }

			myVector<const char*> cc;
			cc.add("hello", "bears", "have", "won", "yippe");
			cc.erase(0, cc.getSize() - 1);
			
			Assert::AreEqual(cc.getSize(), size_t(0));

		}

		TEST_METHOD(swap) {
			myVector<int> m;
			myVector<int> c;
			m.add(1, 2, 3, 4);
			c.add(1);
			m.swap(c);

			Assert::AreEqual(m.getSize(), size_t(1));
			Assert::AreEqual(c.getSize(), size_t(4));
			Assert::AreEqual(c.contains(1, 2, 3, 4), true);

			m.reset();
			c.reset();
			m.add(1, 2, 3, 4);
			c.add(1);
			c.swap(m);

			Assert::AreEqual(m.getSize(), size_t(1));
			Assert::AreEqual(c.getSize(), size_t(4));
			Assert::AreEqual(c.contains(1, 2, 3, 4), true);


		}

		TEST_METHOD(resize) {
			myVector<int> m;
			m.add(1, 2, 3, 4);

			m.resize(2);
			Assert::AreEqual(m.getSize(), size_t(2));
		}

		TEST_METHOD(find) {
			myVector<int> m;
			m.add(1, 2, 3, 4, 5);

			Assert::AreEqual(m.find(1), size_t(0));
			Assert::AreEqual(m.find(-1), size_t(-1));
			Assert::AreEqual(m.find(4), size_t(3));
		}


	};


}

