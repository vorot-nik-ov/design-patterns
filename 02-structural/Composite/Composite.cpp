#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class FileSystemNode {
protected:
    string name;
public:
    FileSystemNode(const string& n) : name(n) {}
    virtual ~FileSystemNode() {}

    virtual void display(int depth = 0) const = 0;
    virtual int getSize() const = 0;
    virtual void add(FileSystemNode* node) {}
    virtual void remove(FileSystemNode* node) {}
};

class File : public FileSystemNode {
private:
    int size;
public:
    File(const string& n, int s) : FileSystemNode(n), size(s) {}

    void display(int depth = 0) const override {
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }
        cout << "[Файл] " << name << " (" << size << " КБ)" << endl;
    }

    int getSize() const override {
        return size;
    }
};

class Folder : public FileSystemNode {
private:
    vector<FileSystemNode*> children;
public:
    Folder(const string& n) : FileSystemNode(n) {}

    ~Folder() {
        for (size_t i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
    }

    void add(FileSystemNode* node) override {
        children.push_back(node);
    }

    void remove(FileSystemNode* node) override {
        for (size_t i = 0; i < children.size(); i++) {
            if (children[i] == node) {
                children.erase(children.begin() + i);
                break;
            }
        }
    }

    void display(int depth = 0) const override {
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }
        cout << "[Папка] " << name << "/" << endl;

        for (size_t i = 0; i < children.size(); i++) {
            children[i]->display(depth + 1);
        }
    }

    int getSize() const override {
        int total = 0;
        for (size_t i = 0; i < children.size(); i++) {
            total += children[i]->getSize();
        }
        return total;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    File* file1 = new File("document.txt", 120);
    File* file2 = new File("image.jpg", 2048);
    File* file3 = new File("video.mp4", 5120);
    File* file4 = new File("notes.txt", 45);
    File* file5 = new File("report.pdf", 1024);
    File* file6 = new File("photo.png", 3500);
    File* file7 = new File("song.mp3", 3200);

    Folder* root = new Folder("Диск C");
    Folder* documents = new Folder("Документы");
    Folder* pictures = new Folder("Изображения");
    Folder* music = new Folder("Музыка");

    root->add(documents);
    root->add(pictures);
    root->add(music);

    documents->add(file1);      // document.txt
    documents->add(file4);      // notes.txt
    documents->add(file5);      // report.pdf

    pictures->add(file2);       // image.jpg
    pictures->add(file6);       // photo.png

    music->add(file3);          // video.mp4
    music->add(file7);          // song.mp3

    cout << "Файловая система" << endl;
    root->display();

    cout << "\nОбщий размер: " << root->getSize() << " КБ" << endl;

    cout << "\nРазмер папки документы" << endl;
    cout << "Размер: " << documents->getSize() << " КБ" << endl;

    delete root;

    return 0;
}