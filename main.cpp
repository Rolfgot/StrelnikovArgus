#include <iostream>
#include <sstream>
#include <Magick++.h>

using namespace std;

std::vector<std::string> &spl(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> spl(const std::string &s, char delim) {
    std::vector<std::string> elems;
    spl(s, delim, elems);
    return elems;
}

void hello_func() {
    cout<<"Hello, user!\n";
    cout<<"This program can load, process and save image.\n";
    cout<<"Working commands:\n";
    cout<<"\tload (or ld) name filename\n";
    cout<<"\tstore (or s) name filename\n";
    cout<<"\tblur from_name to_name size\n";
    cout<<"\tresize from_name to_name new_width new_height\n";
    cout<<"\thelp (or h)\n";
    cout<<"\texit (or quit, or q)\n";
    cout<<"Please, enter a command:"<<endl;
}

int proc(string command, map<string,Magick::Image> &images) {
    vector<string> words = spl(command,' ');
    string first_com = words[0];

    if (first_com == "load" || first_com == "ld") {
        if (words.size() != 3) {
            cout << "Wrong amount of parameters!" << endl;
            return 2;
        }
        string name = words[1];
        string filename = words[2];
        images[name].read(filename);
        cout<<"Image "<<name<<" has been loaded from file "<<filename<<endl;
        return 0;
    }
    if (first_com == "store" || first_com == "s") {
        if (words.size() != 3) {
            cout << "Wrong amount of parameters!" << endl;
            return 2;
        }
        string name = words[1];
        string filename = words[2];
        if (images.count(name)==0) {
            cout << "Image " << name << " has not been found!" << endl;
            return 3;
        }
        images[name].write(filename);
        cout<<"Image "<<name<<" has been saved in file "<<filename<<endl;
        return 0;
    }
    if (first_com == "blur") {
        if (words.size() != 4) {
            cout << "Wrong amount of parameters!" << endl;
            return 2;
        }
        string from_name = words[1];
        string to_name = words[2];
        int size = std::atoi(words[3].c_str());
        if (images.count(from_name)==0) {
            cout << "Image " << from_name << " has not been found!" << endl;
            return 3;
        }
        images[to_name] = Magick::Image(images[from_name]);
        images[to_name].blur(size);
        cout<<"Image "<<from_name<<" has been blured with size "<<size<<" saved in file "<<to_name<<endl;
        return 0;
    }
    if (first_com == "resize") {
        if (words.size() != 5) {
            cout << "Wrong amount of parameters!" << endl;
            return 2;
        }
        string from_name = words[1];
        string to_name = words[2];
        int new_width = std::atoi(words[3].c_str());
        int new_height = std::atoi(words[4].c_str());
        if (images.count(from_name)==0) {
            cout << "Image " << from_name << " has not been found!" << endl;
            return 3;
        }
        images[to_name] = Magick::Image(images[from_name]);
        images[to_name].resize(Magick::Geometry(new_width,new_height));
        cout<<"Image "<<from_name<<" has been resized with new size ["<<new_width<<","<<new_height<<"] saved in file "<<to_name<<endl;
        return 0;
    }
    if (first_com == "help" || first_com == "h") {
        hello_func();
        return 0;
    }
    if (command == "exit" || command == "quit" || command == "q") {
        cout<<"Good bye!"<<endl;
        return 0;
    }

    cout<<"Wrong command!"<<endl;
    return 1;
}

int main(int argc, char** argv) {
    map<string,Magick::Image> images;
    string command = "";

    hello_func();

    while (command != "exit" && command != "quit" && command != "q") {
        char cm_char[256];
        cin.getline(cm_char, 256, '\n');
        command = cm_char;
        cout<<"Call command: "<<command<<endl;
        proc(command, images);
    }

    return 0;
}