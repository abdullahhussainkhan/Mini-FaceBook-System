#include<iostream>
#include<stack>
#include<queue>
using namespace std;

class FriendNode {
public:
    string name;
    FriendNode* left;
    FriendNode* right;

    FriendNode(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

class FriendTree {
public:
    FriendNode* root;
    FriendTree() {
        root = NULL;
    }
    void setRoot(const string& name) {
        if (root) {
            cout << "Root already set to: " << root->name << endl;
            return;
        }
        root = new FriendNode(name);
        cout << name << "  set as the root user." << endl;
    }
    FriendNode* findNode(const string& name) {
        if (!root) {
            return NULL;
        }
        queue<FriendNode*> q;
        q.push(root);
        while (!q.empty()) {
            FriendNode* temp = q.front();
            q.pop();
            if (temp->name == name) {
                return temp;
            }
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
        return NULL;
    }
    FriendNode* findParent(const string& name) {
        if (!root) {
            return NULL;
        }
        queue<FriendNode*> q;
        q.push(root);
        while(!q.empty()) {
            FriendNode* temp = q.front();
            q.pop();
            if ((temp->left && temp->left->name == name) || (temp->right && temp->right->name == name)) {
                return temp;
            }
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
        return NULL;
    }
    void insertFriend(const string& parentName, const string& friendName, char side) {
        if (!root) {
            cout << "Set root first." << endl;
            return;
        }
        FriendNode* parent = findNode(parentName);
        if(!parent) {
            cout << parentName << " not found." << endl;
            return;
        }

        if (side == 'L' || side == 'l') {
            if (parent->left) {
                cout <<"Left spot already taken by " << parentName << endl;
            } else {
                parent->left = new FriendNode(friendName);
                cout << friendName << " added as left friend of " << parentName << endl;
            } 
        } else {
            if (parent->right) {
                cout << "Right spot alraedy taken by " << parentName << endl;
            } else {
                parent->right = new FriendNode(friendName);
                cout << friendName << " added as right friend of " <<parentName << endl;
            }       
        }
    }
    void deleteSubtree(FriendNode* node) {
        if(!node) {
            return;
        }
        queue<FriendNode*> q;
        q.push(node);
        while(!q.empty()) {
            FriendNode* temp = q.front();
            q.pop();
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
            delete temp;
        }
    }

    void deleteFriend(const string& name) {
        if(!root) {
            cout << "Tree is empty." << endl;
            return;
        }
        if (root->name == name) {
            cout << "Cannot delete root user." << endl;
            return;
        }
        FriendNode* parent = findParent(name);
        if (!parent) {
            cout << name << " not found." << endl;
            return;
        }
        FriendNode* target = (parent->left && parent->left->name == name) ? parent->left : parent->right;
        if (parent->left == target) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        deleteSubtree(target);
        cout << name << " and their subtree deleted." << endl;
    }

    void preorder() {
        if(!root) {
            cout << "Empty tree." << endl;
            return;
        }
        stack<FriendNode*> s;
        s.push(root);
        cout << "Preorder: ";
        while(!s.empty()) {
            FriendNode* temp = s.top();
            s.pop();
            cout << temp->name << " ";
            if (temp->left) {
                s.push(temp->left);
            }
            if (temp->right) {
                s.push(temp->right);
            }
        }
        cout << endl;
    }
    void inorder() {
        if (!root) {
            cout << "Empty tree." << endl;
            return;
        }
        stack<FriendNode*> s;
        FriendNode* curr = root;
        cout << "Inorder: ";
        while(curr != NULL || !s.empty()) {
            while(curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->name << " ";
            curr = curr->right;
        }
        cout << endl;
    }

    void postorder() {
        if (!root) {
            cout << "Empty tree." << endl;
            return;
        }
        stack<FriendNode*> s1, s2;
        s1.push(root);
        while(!s1.empty()) {
            FriendNode* temp = s1.top();
            s1.pop();
            s2.push(temp);
            if (temp->left) {
                s1.push(temp->left);
            } if (temp->right) {
                s1.push(temp->right);
            }
        }
        cout << "Postorder: ";
        while(!s2.empty()) {
            cout << s2.top()->name << " ";
            s2.pop();
            cout << endl;
        }
    }

    void countFriends() {
        if (!root) {
            cout << "Total friends: 0" << endl;
            return;
        }
        int count = -1; //exclude
        queue<FriendNode*> q;
        q.push(root);
        while (!q.empty()) {
            FriendNode* temp = q.front();
            q.pop();
            count++;
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
        cout << "Total friends: " << count << endl;
    }
// collect all names in a stack for mutaual friends
    void collectAllNames(stack<string>& names) {
        if (!root) {
            return;
        }
        queue<FriendNode*> q;
        q.push(root);
        while(!q.empty()) {
            FriendNode* temp = q.front();
            q.pop();
            names.push(temp->name);
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
// collect direcr friends of root into queueu
    void collectDirectFriends (queue<string>& q) {
        if(!root) {
            return;
        }
        if (root->left) {
            q.push(root->left->name);
        }
        if (root->right) {
            q.push(root->right->name);
        }
    }
// collect children friends of a named node into queue
    void collectChildFriends (const string& nodeName, queue<string>& result) {
        FriendNode* node = findNode(nodeName);
        if(!node) {
            return;
        }
        if (node->left) {
            result.push(node->left->name);
        }
        if (node->right) {
            result.push(node->right->name);
        }
    }
};

// feature 2 BST 
class PostNode {
public:
    int postID;
    string content;
    PostNode* left;
    PostNode* right;
    PostNode(int id, const string& cont) {
        postID = id;
        content = cont;
        left = NULL;
        right = NULL;
    }
};
class PostBST {
public: 
    PostNode* root;
    PostBST() {
        root = NULL;
    }
    PostNode* insert(PostNode* node, int id, const string& content) {
        if(!node) {
            return new PostNode(id, content);
        }
        if (id < node->postID) {
            node->left = insert(node->left, id, content);
        } else if (id > node->postID) {
            node->right = insert(node->right, id, content);
        } else {
            cout << "Post ID: " << id << " alreday existss." << endl;
        }
        return node;
    }
    PostNode* findMin(PostNode* node) {
        while(node->left) {
            node = node->left;
        }
        return node;
    }
    void insertPost(int id, const string& content) {
        root = insert(root, id, content);
        cout << "Post: " << id << " inserted." << endl;
    }

    PostNode* deletePost(PostNode* node, int id) {
        if(!node) {
            cout << "Post: " << id << " not found." << endl;
            return NULL;
        }
        if (id < node->postID) {
            node->left = deletePost(node->left, id);
        } else if (id > node->postID) {
            node->right = deletePost(node->right, id);
        } else {
            if (!node->left) {
                PostNode* temp = node->right;
                delete node;
                cout << "Post: " << id << " deleted." << endl;
                return temp;
            }
            else if (!node->right) {
                PostNode* temp = node->left; 
                delete node; 
                cout << "Post: " << id << " deleted." << endl;
                return temp;
            }
            PostNode* successor = findMin(node->right);
            node->postID = successor->postID;
            node->content = successor->content;
            node->right = deletePost(node->right, successor->postID);
            
        }
        return node;
    }

    void deletePost(int id) {
        root = deletePost(root, id);
    }
    void displayPosts() {
        if(!root) {
            cout << "No posts available." << endl;
            return;
        }
        stack<PostNode*> s;
        PostNode* curr = root;
        cout << "Posts inorder by ID: " << endl;
        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << " ID: " << curr->postID << " Content: " << curr->content << endl;
            curr = curr->right;
        }
    }

    void searchPost(int id) {
        PostNode* curr = root;
        while(curr) {
            if (curr->postID == id) {
                cout << "Post found - ID: " << id << " Content: " << curr->content << endl;
                return;
            }
            curr = (id < curr->postID) ? curr->left : curr->right;
        }
        cout << "Post: " << id << " not found." << endl;
    }
};
// feature 3 mutaul friends
bool nameExistsInStack(stack<string> s, const string& name) {
    while(!s.empty()) {
        if (s.top() == name) {
            return true;
        }
        s.pop();
    }
    return false;
}

void findMutualFriends(FriendTree& tree1, FriendTree& tree2) {
    stack<string> names1, names2;
    tree1.collectAllNames(names1);
    tree2.collectAllNames(names2);

    // remove root from stack to avoid counting as mutual friend
    string root1 = tree1.root ? tree1.root->name : "";
    string root2 = tree2.root ? tree2.root->name : "";

    cout << "Mutual Friends: ";
    bool found = false;
    stack<string> copy1 = names1; // copy to preserve original stack
    while (!copy1.empty()) {
        string n = copy1.top();
        copy1.pop();
        if (n == root1 || n == root2) {
            continue; // skip root names
        }
        if (nameExistsInStack(names2, n)) {
            cout << n << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "No mutual friends found " << endl;
    }
}

// feature 4 friend suggestions based on friends of friends
bool nameExistsInQueue(queue<string> q, const string& name) {
    while(!q.empty()) {
        if(q.front() == name) {
            return true;
        }
        q.pop();
    }
    return false;
}
void friendSuggestions(FriendTree& userTree) {
    if(!userTree.root) {
        cout << "Tree is empty." << endl;
        return;
    }
    queue<string> directFriends;
    userTree.collectDirectFriends(directFriends);

    // build a queue of suggestions based on friends of friends
    queue<string> suggestions;
    queue<string> tempDirect = directFriends;

    while (!tempDirect.empty()) {
        string friendName = tempDirect.front();
        tempDirect.pop();
        queue<string> fof;  // friends of friend(fof)
        userTree.collectChildFriends(friendName, fof);
        while (!fof.empty()) {
            string candidate = fof.front();
            fof.pop();
            if (candidate != userTree.root->name && 
                ! nameExistsInQueue(directFriends, candidate) && 
                ! nameExistsInQueue(suggestions, candidate)) {
                suggestions.push(candidate);
            }
        }
    }
    cout << "Friend Suggestions for " << userTree.root->name << ": ";
    if (suggestions.empty()) {
        cout << "None";
    } else {
        while (!suggestions.empty()) {
            cout << suggestions.front() << " ";
            suggestions.pop();
        }
        cout << endl;
    }
}
int main(){
    FriendTree abdullah, anas, huzaifa;
    PostBST postFeed;
    abdullah.setRoot("Abdullah");
    abdullah.insertFriend("Abdullah", "Anas", 'L');
    abdullah.insertFriend("Abdullah", "Huzaifa", 'R');
    abdullah.insertFriend("Anas", "Ahmad", 'L');
    abdullah.insertFriend("Anas", "Hamza", 'R');
    abdullah.insertFriend("Huzaifa", "Hanzala", 'L');

    anas.setRoot("Anas");
    anas.insertFriend("Anas", "Ahmad", 'L');
    anas.insertFriend("Anas", "Hamza", 'R');
    anas.insertFriend("Ahmad", "Haris", 'L');

    huzaifa.setRoot("Huzaifa");
    huzaifa.insertFriend("Huzaifa", "Hanzala", 'L');
    huzaifa.insertFriend("Huzaifa", "Hamza", 'R');
    huzaifa.insertFriend("Hanzala", "Haris", 'L');

    postFeed.insertPost(102, "Hello Guyz");
    postFeed.insertPost(101, "Good Morning");
    postFeed.insertPost(103, "Work Hard, Play Nice");
    postFeed.insertPost(104, "Trees are fun, but bad");
  
    int choice;
    cout << endl;
    cout << "               MINI FaceBook System            " << endl;
    do { 
        cout << "    Main Menu     " << endl;
        cout << "1. Insert Friend " << endl;
        cout << "2. Delete Friend " << endl;
        cout << "3. Preorder Traversal " << endl;
        cout << "4. Inorder Traversal " << endl;
        cout << "5. Postorder Traversal " << endl;
        cout << "6. Count Total Friends " << endl;
        cout << "7. Insert Post " << endl;
        cout << "8. Delete Post " << endl;
        cout << "9. Display All Posts " << endl;
        cout << "10. Search Post " << endl;
        cout << "11. Find Mutual Friends (Anas & Huzaifa) " << endl;
        cout << "12. Friend Suggestions (Abdullah) " << endl;
        cout << "0. Exit " << endl;
        cout << " Enter Choice (0-12): " << endl;
        cin >> choice;
        if (choice == 1) {
            string parent, friendName;
            char side;
            cout << "Enter parent name: ";
            cin >> parent;
            cout << "Enter friend name: ";
            cin >> friendName;
            cout << "Enter side (L/R): ";
            cin >> side;
            abdullah.insertFriend(parent, friendName, side);
        } else if (choice == 2) {
            string name;
            cout << "Enter friend name to delete: ";
            cin >> name;
            abdullah.deleteFriend(name);
        } else if (choice == 3) {
            abdullah.preorder();
        } else if (choice == 4) {
            abdullah.inorder();
        } else if (choice == 5) {
            abdullah.postorder();
        } else if (choice == 6) {
            abdullah.countFriends();
        } else if (choice == 7) {
            int id;
            string content;
            cout << "Enter Post ID: ";
            cin >> id;
            cout << "Enter content: ";
            getline(cin, content); // there are some issues with cin, i think buffer is not cleared 
            postFeed.insertPost(id, content);
        } else if (choice == 8) {
            int id; 
            cout << "Enter Post ID to delete: ";
            cin >> id;
            postFeed.deletePost(id);
        } else if (choice == 9) {
            postFeed.displayPosts();
        } else if (choice == 10) {
            int id;
            cout << "Enter Post ID to search: ";
            cin >> id;
            postFeed.searchPost(id);
        } else if (choice == 11) {
            findMutualFriends(anas, huzaifa);
        } else if (choice == 12) {
            friendSuggestions(abdullah);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
        
    cout << "Existing The System. " << endl;
    return 0;
}