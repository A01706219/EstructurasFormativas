/*
 * main.cpp
 *
 *  Created on: 10/08/2020
 *      Author: bvaldesa
 */
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include "heap.h"

using namespace std;


int main(int argc, char* argv[]) {
	Heap<int> heap(20);
	string ans;
	heap.push(8);

  ans =	"[8]";
	cout << " 1 " <<	(!ans.compare(heap.toString()) ? "success\n" : "fail\n");

	heap.push(20);
	heap.push(31);
	heap.push(5);
	heap.push(87);
	ans ="[5 8 31 20 87]";
	cout << " 2 " <<	(!ans.compare(heap.toString()) ? "success\n" : "fail\n");

	heap.pop();
	ans ="[8 20 31 87]";
	cout << " 3 " <<	(!ans.compare(heap.toString()) ? "success\n" : "fail\n");

	cout << " 4 " <<	((4 == heap.size()) ? "success\n" : "fail\n");

	heap.pop();
	ans ="[20 87 31]";
	cout << " 5 " <<	(!ans.compare(heap.toString()) ? "success\n" : "fail\n");

	cout << " 6 " <<	((3 == heap.size()) ? "success\n" : "fail\n");

	cout << " 7 " <<	((20 == heap.top()) ? "success\n" : "fail\n");

	cout << " 8 " <<	((0 == heap.empty()) ? "success\n" : "fail\n");

	heap.pop();

	cout << " 9 " <<	((31 == heap.top()) ? "success\n" : "fail\n");

	heap.pop();

	cout << " 10 " <<	((0 == heap.empty()) ? "success\n" : "fail\n");

}
