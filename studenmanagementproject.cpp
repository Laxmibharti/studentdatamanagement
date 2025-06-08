#include <iostream>
using namespace std;

// Structure of a student node
struct Student {
    int roll;
    string name;
    float marks;
    Student *left, *right;
};

// Function to create a new student node
Student* createNode(int roll, string name, float marks) {
    Student* newNode = new Student();
    newNode->roll = roll;
    newNode->name = name;
    newNode->marks = marks;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a student in BST
Student* insert(Student* root, int roll, string name, float marks) {
    if (root == NULL)
        return createNode(roll, name, marks);

    if (roll < root->roll)
        root->left = insert(root->left, roll, name, marks);
    else if (roll > root->roll)
        root->right = insert(root->right, roll, name, marks);
    else
        cout << "Student with roll " << roll << " already exists!\n";
    return root;
}

// Search for a student by roll
Student* search(Student* root, int roll) {
    if (root == NULL || root->roll == roll)
        return root;
    if (roll < root->roll)
        return search(root->left, roll);
    return search(root->right, roll);
}

// Find the minimum node in BST
Student* minValueNode(Student* node) {
    Student* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a student by roll number
Student* deleteNode(Student* root, int roll) {
    if (root == NULL) return root;

    if (roll < root->roll)
        root->left = deleteNode(root->left, roll);
    else if (roll > root->roll)
        root->right = deleteNode(root->right, roll);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Student* temp = minValueNode(root->right);
        root->roll = temp->roll;
        root->name = temp->name;
        root->marks = temp->marks;
        root->right = deleteNode(root->right, temp->roll);
    }
    return root;
}

// Inorder traversal to display all students
void inorder(Student* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Roll: " << root->roll << ", Name: " << root->name << ", Marks: " << root->marks << endl;
        inorder(root->right);
    }
}

// Main driver code
int main() {
    Student* root = NULL;
    int choice, roll;
    string name;
    float marks;

    do {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display All\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter roll, name, marks: ";
                cin >> roll >> name >> marks;
                root = insert(root, roll, name, marks);
                break;
            case 2:
                cout << "Enter roll to search: ";
                cin >> roll;
                {
                    Student* found = search(root, roll);
                    if (found)
                        cout << "Found: " << found->name << ", Marks: " << found->marks << endl;
                    else
                        cout << "Student not found!\n";
                }
                break;
            case 3:
                cout << "Enter roll to delete: ";
                cin >> roll;
                root = deleteNode(root, roll);
                break;
            case 4:
                cout << "\nAll student records:\n";
                inorder(root);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}