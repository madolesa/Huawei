#include <iostream>
#include <algorithm>

using namespace std;
const int MAX_NODES = 40 * 40 * 100;
const int MAX_ROWS = 100 + 10;

// Dancing Links X
struct DLX {
    int left[MAX_NODES], right[MAX_NODES], up[MAX_NODES], down[MAX_NODES]; // left[i], right[i]. up[i], down[i] - left,
    // right, up and down nodes of node i
    int col[MAX_NODES]; // col[i] - column of node i
    int head_of_row[MAX_ROWS]; // head_of_row[i] - head of row i
    int size_of_col[MAX_NODES]; // size_of_col[i] - amount of nodes in column i (size of column i)
    int ans; // the least possible number of selected rows
    int sz; // amount of nodes

    // Create two-dimensional bidirectional list with given size
    void create(int rows, int columns) {
        for (int i = 0; i <= columns; i++) {
            up[i] = down[i] = i;
            left[i] = i - 1;
            right[i] = i + 1;
            size_of_col[i] = 0;
        }
        right[columns] = 0;
        left[0] = columns;
        sz = columns;
        ans = -1;
        for (int i = 1; i <= rows; i++)
            head_of_row[i] = -1;
    }

    // This method adds node to given row and column
    void add(int row, int column) {
        down[++sz] = down[column];
        up[down[column]] = sz;
        up[sz] = column;
        down[column] = sz;
        col[sz] = column;
        size_of_col[column]++;
        if (head_of_row[row] == -1)
            head_of_row[row] = right[sz] = left[sz] = sz;
        else {
            right[sz] = right[head_of_row[row]];
            left[right[head_of_row[row]]] = sz;
            left[sz] = head_of_row[row];
            right[head_of_row[row]] = sz;
        }
    }

    // This method removes the column with given number and its corresponding row
    void remove(int column) {
        left[right[column]] = left[column];
        right[left[column]] = right[column];
        for (int i = down[column]; i != column; i = down[i]) {
            for (int j = right[i]; j != i; j = right[j]) {
                up[down[j]] = up[j];
                down[up[j]] = down[j];
                size_of_col[col[j]]--;
            }
        }
    }

    // This method resumes the column with given number and its corresponding row
    void resume(int column) {
        for (int i = up[column]; i != column; i = up[i]) {
            for (int j = left[i]; j != i; j = left[j]) {
                up[down[j]] = down[up[j]] = j;
                size_of_col[col[j]]++;
            }
        }
        left[right[column]] = right[left[column]] = column;
    }

    // This recursive method gets number of selected rows(rectangles) and selects possible row selection options in
    // column with the least number of nodes
    void dance(int num_of_rectangles) {
        // If answer exists and number of selected rows(rectangles) is larger than answer, then it is impossible to
        // improve answer, so there is no point in going further
        if (ans != -1 && num_of_rectangles >= ans) {
            return;
        }

        // If list is empty, answer is found
        if (right[0] == 0) {
            if (ans == -1) {
                ans = num_of_rectangles;
            } else {
                ans = min(ans, num_of_rectangles);
            }
            return;
        }

        // Find number of column with the least number of nodes
        int column = right[0];
        for (int i = right[0]; i != 0; i = right[i]) {
            if (size_of_col[i] < size_of_col[column])
                column = i;
        }

        remove(column);
        for (int i = down[column]; i != column; i = down[i]) {
            // Remove columns and rows which do not comply with the rule: "Each row and column has only one node."
            for (int j = right[i]; j != i; j = right[j]) {
                remove(col[j]);
            }
            dance(num_of_rectangles + 1);
            // Since no answer was found, resume removed rows and columns to continue brute force
            for (int j = left[i]; j != i; j = left[j]) {
                resume(col[j]);
            }
        }
        resume(column);
    }
} dlx;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int width, height, num_of_pieces;
        cin >> width >> height >> num_of_pieces;
        dlx.create(num_of_pieces, width * height);
        for (int j = 1; j <= num_of_pieces; ++j) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            // Add node for each coordinate that current rectangle covers
            for (int k = x1 + 1; k <= x2; ++k) {
                for (int l = y1 + 1; l <= y2; ++l) {
                    dlx.add(j, (k - 1) * height + l);
                }
            }
        }
        // Start brute force with zero selected rectangles
        dlx.dance(0);
        cout << dlx.ans << endl;
    }
    return 0;
}