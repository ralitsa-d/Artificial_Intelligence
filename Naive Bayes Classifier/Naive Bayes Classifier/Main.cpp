#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include <sstream>

using namespace std;


struct attribute {
	string name;
	vector<string> features;
	attribute(vector<string> f) {
		for (int i = 0; i < f.size(); i++) {
			features.push_back(f[i]);
		}
	}
	attribute(string name0, vector<string> f) {
		for (int i = 1; i < f.size(); i++) {
			features.push_back(f[i]);
		}
		name = name0;
	}
	attribute& operator=(const attribute& a) {
		if (this != &a) {
			name = a.name;
			features = a.features;
		}
	}
	void print() {
		cout << name << ": ";
		for (int i = 0; i < features.size(); i++) {
			cout << features[i] << " ";
		}
		cout << endl;
	}
};

struct attr {
	string name;
	string value;
	attr(string newname, string newvalue) {
		name = newname;
		value = newvalue;
	}
	attr& operator=(const attr& a) {
		if (this != &a) {
			name = a.name;
			value = a.value;
		}
	}
	void print() {
		cout << name << ": ";
		cout << value << endl;
	}
};

struct Data {
	vector<attr> attributes;
	Data(vector<attr> attributes) {
		for (int i = 0; i < attributes.size(); i++) {
			this->attributes.push_back(attributes[i]);
		}
	}
	Data& operator=(const Data& d) {
		if (this != &d) {
			attributes.clear();
			for (int i = 0; i < d.attributes.size(); i++) {
				attributes[i] = d.attributes[i];
			}
		}
	}
	void print() {
		for (int i = 0; i < attributes.size(); i++) {
			attributes[i].print();
		}
		cout << endl << endl;
	}
};

bool member(vector<string> strings, string str) {
	for (int i = 0; i < strings.size(); i++) {
		if (strings[i] == str) {
			return true;
		}
	}
	return false;
}

void fill_blank_spaces(vector<Data>& dataset, vector<attribute> vectorWithAttr) {
	vector<string> blank_attr;
	for (int i = 0; i < dataset.size(); i++) {
		for (int j = 0; j < dataset[i].attributes.size(); j++) {
			if (dataset[i].attributes[j].value == "?") {
				if (!member(blank_attr, dataset[i].attributes[j].name)) {
					blank_attr.push_back(dataset[i].attributes[j].name);
				}
			}
		}
	}
	/*for (int i = 0; i < blank_attr.size(); i++) {
		cout << blank_attr[i] << " ";
	}*/

	for (int i = 0; i < blank_attr.size(); i++) {
		int k;
		for (int j = 0; j < vectorWithAttr.size(); j++) {
			if (vectorWithAttr[j].name == blank_attr[i]) {
				k = j;
			}
		}
		int max = 0;
		string thefeature;
		for (int a = 0; a < vectorWithAttr[k].features.size(); a++) {
			int count = 0;
			for (int b = 0; b < dataset.size(); b++) {
				if (dataset[b].attributes[k].value == vectorWithAttr[k].features[a]) {
					count++;
				}
			}
			if (count > max) {
				max = count;
				thefeature = vectorWithAttr[k].features[a];
			}
		}

		for (int a = 0; a < dataset.size(); a++) {
			if (dataset[a].attributes[k].value == "?") {
				dataset[a].attributes[k].value = thefeature;
			}
		}
	}
}

int countClassFeatures(vector<Data> dataset, string classFeature) {
	int count = 0;
	for (int i = 0; i < dataset.size(); i++) {
		if (dataset[i].attributes[0].value == classFeature) count++;
	}
	return count;
}

double P(vector<Data> dataset, vector<attribute> vectorWithAttr, string attrName, string feature, string classFeature) {
	int k;
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == attrName) {
			k = i;
		}
	}

	int count = 0;
	for (int i = 0; i < dataset.size(); i++) {
		if (dataset[i].attributes[k].value == feature && dataset[i].attributes[0].value == classFeature) count++;
	}

	return double(count) / countClassFeatures(dataset, classFeature);
}

double ProbabilityClassFeature(vector<Data> dataset, string classFeature) {
	double count = 0.0;
	for (int i = 0; i < dataset.size(); i++) {
		if (dataset[i].attributes[0].value == classFeature) count++;
	}
	return count / dataset.size();
}


int main() {
	ifstream f;
	f.open("house-votes-attr.txt", ios::in);
	if (f.is_open()) {
		cout << "f is open" << endl;
	}
	else {
		cout << "f is not open" << endl;
	}

	ifstream file;
	file.open("house-votes.txt", ios::in);
	if (file.is_open()) {
		cout << "file is open" << endl;
	}
	else {
		cout << "file is not open" << endl;
	}

	vector<attribute> vectorWithAttr;
	while (!f.eof()) {
		string line;
		getline(f, line);
		istringstream iss(line);
		string s;
		vector<string> words;
		while (getline(iss, s, ' ')) {
			words.push_back(s);
		}
		attribute a(words[0], words);
		vectorWithAttr.push_back(a);
	}

	for (int i = 0; i < vectorWithAttr.size(); i++) {
		vectorWithAttr[i].print();
	}
	cout << endl;

	vector<Data> dataset;
	while (!file.eof()) {
		string line;
		getline(file, line);
		istringstream iss(line);
		string s;
		vector<string> words;
		vector<attr> attributes;
		int count = 0;
		while (getline(iss, s, ' ')) {
			attr a(vectorWithAttr[count].name, s);
			attributes.push_back(a);
			//a.print();
			count++;
		}
		dataset.push_back(attributes);
	}

	fill_blank_spaces(dataset, vectorWithAttr);

	vector<attr> attributesOfNewExample;
	attr firstAttr(vectorWithAttr[0].name, "???");
	attributesOfNewExample.push_back(firstAttr);
	for (int i = 1; i < vectorWithAttr.size(); i++) {
		string feature;
		cout << vectorWithAttr[i].name << ": ";
		cin >> feature;
		attr a(vectorWithAttr[i].name, feature);
		attributesOfNewExample.push_back(a);
	}
	Data newExample(attributesOfNewExample);
	cout << endl;
	//newExample.print();

	double maxProb = 0.0;
	string classOfNewExample;
	for (int i = 0; i < vectorWithAttr[0].features.size(); i++) {
		double mult = 1.0;
		for (int j = 1; j < vectorWithAttr.size(); j++) {
			mult = mult * P(dataset, vectorWithAttr, vectorWithAttr[j].name, newExample.attributes[j].value, vectorWithAttr[0].features[i]);
		}
		if (mult > maxProb) {
			maxProb = mult;
			classOfNewExample = vectorWithAttr[0].features[i];
		}
	}

	cout << "Class: " << classOfNewExample << endl;

	return 0;
}