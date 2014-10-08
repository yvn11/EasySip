#include <utility>
#include <iostream>
#include <set>

int main()
{
	std::pair<int, int> fo;
	std::set<std::pair<int, int> > fos;

	fo = std::make_pair(100, 33);
	std::pair<int, int> foe = std::make_pair(100, 33);

	std::cout << fo.first << ' ' << fo.second << '\n';
	fos.insert(fo);

	std::set<std::pair<int, int> >::iterator it = fos.find(foe);
	std::cout << (it == fos.end()) << '\n';

	std::cout << fo.first << ' ' << fo.second << '\n';
}

