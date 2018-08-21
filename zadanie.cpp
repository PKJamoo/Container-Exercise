#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Synchronizer
{
public:
	Synchronizer(int i);
	~Synchronizer();

	/* member functions */
	void init_data();
	void delete_data();
	void sync_data();
	void print_data();

	/* Данные */
private:
	int size;
	std::vector<int> vec;
	std::map<int, int> map;
	std::vector<int>::iterator it_v;
	std::map<int, int>::iterator it_m;
	std::vector<std::pair<int, int> >::iterator it_rev_m;



};

Synchronizer::Synchronizer(int i)
	: size (i)
{}

Synchronizer::~Synchronizer(){

}

void Synchronizer::init_data(){
	
	srand(unsigned(time(0)));
	
	int num;
	/* заполнить вектор */
	for (int i = 0; i < Synchronizer::size; i++){
		num = (rand() % 9) + 1;
		vec.push_back(num);
	}

	/* заполнить мап */
	for (int i = 0; i < Synchronizer::size; i++){
		num = (rand() % 9) + 1;
		/* ключ будет индекс элемента */
		map.insert(std::make_pair(map.size(), num));
	}

}

void Synchronizer::delete_data(){

	int num_to_del;
	srand(unsigned(time(0)));
	if (Synchronizer::size < 15) {
		num_to_del = (rand() % Synchronizer::size) + 1;
	}
	else {
		num_to_del = (rand() % 15) + 1;
	}

	while (num_to_del > 1){
		vec.erase(vec.begin());
		map.erase(map.begin());

		num_to_del--;
	}
}

void Synchronizer::sync_data(){

	/* создать новый вектор с парами, где каждая пара состоит из элементов помененных местами */
	std::vector<std::pair<int, int> > reverse_map;

	for (it_m = Synchronizer::map.begin(); it_m != Synchronizer::map.end(); it_m++){
		reverse_map.push_back(std::make_pair((*it_m).second, (*it_m).first));
	}


	std::sort(vec.begin(), vec.end());
	std::sort(reverse_map.begin(), reverse_map.end());


	std::vector<int>::iterator new_it_v;
	it_rev_m = reverse_map.begin();

	for (it_v = vec.begin(), new_it_v = vec.begin(); it_v != vec.end(); it_v = new_it_v){

			// базовый вариант
			// больше нет элементов в мап
			if (it_rev_m == reverse_map.end()) {
				it_v = vec.erase(it_v);

			}
			// элементы одинаковые
			else if ((*it_v) == (*it_rev_m).first) {
			new_it_v++;
			it_rev_m++;


			}
			// элемент в вектор меньше всех в мап
			else if ((*it_v) < (*it_rev_m).first) {
				it_v = vec.erase(it_v);

				}
			
			// элемент в вектор больше всех в мап
			else {
				it_rev_m = reverse_map.erase(it_rev_m);

			}

	}

	// удалить все лишные элементы из конца сохраненных элементов мапа
	if (vec.size() < reverse_map.size()) {
		reverse_map.erase(reverse_map.begin() + vec.size(), reverse_map.end());
	}
	map.clear();
	// переписать нужные элементы в мап
	if (!reverse_map.empty()){
		for (it_rev_m = reverse_map.begin(); it_rev_m != reverse_map.end(); it_rev_m++){

		map.insert(std::make_pair((*it_rev_m).second, (*it_rev_m).first));
		}

	}
}

void Synchronizer::print_data(){

	for (it_v = Synchronizer::vec.begin(); it_v != Synchronizer::vec.end(); it_v++){
			std::cout << (*it_v) << ' ';
	}

	std::cout << std::endl;

		for (it_m = Synchronizer::map.begin(); it_m != Synchronizer::map.end(); it_m++){
			std::cout << (*it_m).second << ' ';
	}

	std::cout << std::endl;
}



int main(int argc, char** argv){
	
int i = std::stoi(argv[1]);
Synchronizer sync = Synchronizer(i);

sync.init_data();
sync.print_data();
sync.delete_data();
sync.print_data();
sync.sync_data();
sync.print_data();

}