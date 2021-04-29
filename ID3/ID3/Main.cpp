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


struct Node {
	string attribute;
	string className;
	string feature;
	vector<Node*> children;

	Node(string attr, string className) {
		this->attribute = attr;
		this->className = className;
	}
	Node(string attr, string className, string feature) {
		this->attribute = attr;
		this->className = className;
		this->feature = feature;
	}
	Node& operator=(const Node& node) {
		if (this != &node) {
			attribute = node.attribute;
			className = node.className;
			feature = node.feature;
			for (int i = 0; i < children.size(); i++) {
				delete children[i];
			}
			children.clear();
			for (int i = 0; i < node.children.size(); i++) {
				children.push_back(node.children[i]);
			}
		}
	}
	void setChildren(vector<Node*> children_) {
		for (int i = 0; i < children.size(); i++) {
			delete children[i];
		}
		children.clear();
		for (int i = 0; i < children_.size(); i++) {
			children.push_back(children_[i]);
		}
	}
};

double Entropy(vector<Data> dataset, vector<attribute> vectorWithAttr, string attrName) {
	int k;
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == attrName) k = i;
	}
	double sum = 0.0;
	for (int i = 0; i < vectorWithAttr[k].features.size(); i++) {
		double count = 0;
		for (int j = 0; j < dataset.size(); j++) {
			if (dataset[j].attributes[k].value == vectorWithAttr[k].features[i]) count++;
		}
		if (count == 0) {
			count = 0.0000000000000001;
		}
		sum = sum - (double(count) / dataset.size())*log2(double(count) / dataset.size());
	}
	return sum;
}

double P(vector<Data> dataset, vector<attribute> vectorWithAttr, string attrName, string feature) {
	int k;
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == attrName) {
			k = i;
		}
	}
	double count = 0.0;
	for (int i = 0; i < dataset.size(); i++) {
		if (dataset[i].attributes[k].value == feature) count++;
	}
	return count / dataset.size();
}

double Entropy2(vector<Data> dataset, vector<attribute> vectorWithAttr, string attrName1, string attrName2) {
	int k1, k2;
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == attrName1) k1 = i;
	}
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == attrName2) k2 = i;
	}

	double sum = 0.0;
	for (int i = 0; i < vectorWithAttr[k2].features.size(); i++) {
		double e = 0.0;
		for (int j = 0; j < vectorWithAttr[k1].features.size(); j++) {
			double count = 0.0;
			double count_general = 0.0;
			for (int k = 0; k < dataset.size(); k++) {
				if (dataset[k].attributes[k2].value == vectorWithAttr[k2].features[i] &&
					dataset[k].attributes[k1].value == vectorWithAttr[k1].features[j]) {
					count++;
				}
				if (dataset[k].attributes[k2].value == vectorWithAttr[k2].features[i]) {
					count_general++;
				}
			}
			if (count_general == 0) {
				count_general = 0.00000000000001;
			}
			if (count == 0) {
				count = 0.0000000000000001;
			}
			e = e - (double(count) / count_general)*log2(double(count) / count_general);
		}
		sum = sum + P(dataset, vectorWithAttr, attrName2, vectorWithAttr[k2].features[i])*e;
	}
	return sum;
}

double Gain(vector<Data> dataset, vector<attribute> vectorWithAttr, string attrName1, string attrName2) {
	return Entropy(dataset, vectorWithAttr, attrName1) - Entropy2(dataset, vectorWithAttr, attrName1, attrName2);
}

//returns root of tree
Node* ID3(vector<Data> dataset, vector<attribute> vectorWithAttr, string class_feature, string feature) {
	if (Entropy(dataset, vectorWithAttr, vectorWithAttr[0].name) == 0.0 || dataset.size() < 15) {
		//cout << "NEW!!" << endl;
		//cout << dataset.size() << endl;

		int m = 0; //max
		string the_class_feature;
		for (int i = 0; i < vectorWithAttr[0].features.size(); i++) {
			int count = 0;
			for (int j = 0; j < dataset.size(); j++) {
				if (dataset[j].attributes[0].value == vectorWithAttr[0].features[i]) {
					count++;
				}
			}
			if (count > m) {
				m = count;
				the_class_feature = vectorWithAttr[0].features[i];
			}
		}
		if (dataset.size() != 0) {
			Node r("", the_class_feature, feature);
			vector<Node*> empty;
			r.setChildren(empty);
			//cout << "RETURN LEAF - There is data left" << endl << endl;
			return &r;
		}
		else {
			Node r("", class_feature, feature);
			vector<Node*> empty;
			r.setChildren(empty);
			//cout << "RETURN LEAF" << endl << endl;
			return &r;
		}
		/*Node r("", dataset[0].attributes[0].value);
		vector<Node*> empty;
		r.setChildren(empty);
		return &r;*/
	}

	double max = 0.0;
	string theattr;
	for (int i = 1; i < vectorWithAttr.size(); i++) {
		double g = Gain(dataset, vectorWithAttr, vectorWithAttr[0].name, vectorWithAttr[i].name);
		if (g > max) {
			max = g;
			theattr = vectorWithAttr[i].name;
		}
	}
	if (theattr == "") {
		cout << "theattr is empty" << endl;
		cout << dataset.size() << endl;
	}
	int k;
	for (int i = 0; i < vectorWithAttr.size(); i++) {
		if (vectorWithAttr[i].name == theattr) {
			k = i;
		}
	}
	max = 0.0;
	double p;
	string most_common_class_feature;
	for (int i = 0; i < vectorWithAttr[0].features.size(); i++) {
		p = P(dataset, vectorWithAttr, vectorWithAttr[0].name, vectorWithAttr[0].features[i]);
		if (p > max) {
			max = p;
			most_common_class_feature = vectorWithAttr[0].features[i];
		}
	}
	Node root(theattr, most_common_class_feature, feature);
	//Node root(vectorWithAttr[k].name, most_common_class_feature);

	vector<Node*> children;
	for (int i = 0; i < vectorWithAttr[k].features.size(); i++) {
		vector<Data> dataset_new;
		for (int j = 0; j < dataset.size(); j++) {
			if (dataset[j].attributes[k].value == vectorWithAttr[k].features[i]) {
				dataset_new.push_back(dataset[j]);
			}
		}
		Node* child = ID3(dataset_new, vectorWithAttr, most_common_class_feature, vectorWithAttr[k].features[i]);
		children.push_back(child);
	}
	root.setChildren(children);
	//cout << "RETURN ROOT "<<root.attribute << endl << endl;
	return &root;
}


string examine(Data d, Node* root, vector<attribute> vectorWithAttr) {
	if (root != nullptr) {
		if (root->children.size() == 0 or root->attribute == "") {
			return root->className;
		}
		else {
			string atr = root->attribute;
			int k;
			for (int i = 0; i < vectorWithAttr.size(); i++) {
				if (vectorWithAttr[i].name == atr) {
					k = i;
				}
			}
			string atr_value = d.attributes[k].value;
			for (int i = 0; i < root->children.size(); i++) {
				if (root->children[i]->feature == atr_value) {
					examine(d, root->children[i], vectorWithAttr);
				}
			}
		}
	}
}




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


int main() {
	ifstream f;
	f.open("breast-cancer-attr.txt", ios::in);
	if (f.is_open()) {
		cout << "f is open" << endl;
	}
	else {
		cout << "f is not open" << endl;
	}

	ifstream file;
	file.open("breast-cancer.txt", ios::in);
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

	/*for (int i = 0; i < vectorWithAttr.size(); i++) {
		vectorWithAttr[i].print();
	}*/

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

	cout << dataset.size() << endl << endl;
	for (int i = 0; i < 5; i++) {
		dataset[i].print();
	}


	/*cout << Gain(dataset, vectorWithAttr, "Class", "age") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "menopause") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "tumor-size") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "inv-nodes") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "node-caps") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "deg-malig") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "breast") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "breast-quad") << endl;
	cout << Gain(dataset, vectorWithAttr, "Class", "irradiat") << endl;*/

	Node* root = ID3(dataset, vectorWithAttr, "", "");
	//cout << root->attribute << endl;

	cout << "Enter new example: ";
	vector<attr> attributes;
	attr a(vectorWithAttr[0].name, "???");
	attributes.push_back(a);
	for (int i = 1; i < dataset[0].attributes.size() - 1; i++) {
		string val;
		cin >> val;
		attr at(vectorWithAttr[i].name, val);
		attributes.push_back(at);
	}
	Data d(attributes);
	cout << endl;
	d.print();

	//string result = examine(d, root, vectorWithAttr);
	//cout << "RESULT: " << result << endl;

	return 0;
}